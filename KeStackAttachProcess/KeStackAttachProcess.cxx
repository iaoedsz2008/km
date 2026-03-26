
/**
 * 用户为本，科技向善
 **/

#include "KeStackAttachProcess.h"

#include <ntifs.h>

#include <ntddk.h>

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

#define CR4_SMEP (1ULL << 20)
#define CR4_SMAP (1ULL << 21)

ULONG_PTR g_OriginalCr4 = 0;

NTSTATUS
SaveMemoryToFile(IN PVOID Buffer, IN SIZE_T Size, IN PCWSTR FilePath)
{
    NTSTATUS status;
    HANDLE fileHandle = NULL;
    OBJECT_ATTRIBUTES objAttr;
    IO_STATUS_BLOCK ioStatusBlock;
    UNICODE_STRING uniFilePath;

    RtlInitUnicodeString(&uniFilePath, FilePath);

    InitializeObjectAttributes(&objAttr, &uniFilePath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

    status = ZwCreateFile(&fileHandle, GENERIC_WRITE, &objAttr, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, 0, FILE_OVERWRITE_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);

    if (!NT_SUCCESS(status)) {
        KdPrint(("ZwCreateFile failed: 0x%08X\n", status));
        return status;
    }

    status = ZwWriteFile(fileHandle, NULL, NULL, NULL, &ioStatusBlock, Buffer, (ULONG)Size, NULL, NULL);

    if (!NT_SUCCESS(status)) {
        KdPrint(("ZwWriteFile failed: 0x%08X\n", status));
    } else {
        KdPrint(("Successfully wrote %Iu bytes to file\n", ioStatusBlock.Information));
    }

    ZwClose(fileHandle);
    return status;
}

NTSTATUS
CopyMemoryFromProcess(IN PEPROCESS Process, IN PVOID SourceAddress, IN SIZE_T Size, IN PCWSTR OutputFilePath)
{
    NTSTATUS status;
    KAPC_STATE apcState;
    PVOID buffer = NULL;

    buffer = ExAllocatePoolWithTag(NonPagedPool, Size, 'pmem');
    if (buffer == NULL) {
        KdPrint(("Failed to allocate buffer\n"));
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    KeStackAttachProcess(Process, &apcState);

    __try {
        // ProbeForRead(SourceAddress, Size, 1);
        RtlCopyMemory(buffer, SourceAddress, Size);

        KdPrint(("Successfully copied %Iu bytes from process memory at 0x%p\n", Size, SourceAddress));

        status = STATUS_SUCCESS;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        status = GetExceptionCode();
        KdPrint(("Exception occurred while reading memory: 0x%08X\n", status));
    }

    KeUnstackDetachProcess(&apcState);

    if (NT_SUCCESS(status)) {
        status = SaveMemoryToFile(buffer, Size, OutputFilePath);
    }

    if (buffer != NULL) {
        ExFreePoolWithTag(buffer, 'pmem');
    }

    return status;
}

EXTERN_C VOID
DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
    KdPrint(("Driver unloading\n"));
}

EXTERN_C NTSTATUS
DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS status;
    PEPROCESS targetProcess = NULL;
    HANDLE processId;

    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("KeStackAttachProcess Driver loaded\n"));

    processId = (HANDLE)2964;

    status = PsLookupProcessByProcessId(processId, &targetProcess);
    if (!NT_SUCCESS(status)) {
        KdPrint(("PsLookupProcessByProcessId failed: 0x%08X\n", status));
        return STATUS_SUCCESS;
    }

    g_OriginalCr4 = __asm_cr4();
    KdPrint(("CR0: 0x%p\n", (PVOID)__asm_cr0()));
    KdPrint(("CR4 original: 0x%p\n", (PVOID)g_OriginalCr4));

    ULONG_PTR newCr4 = g_OriginalCr4 & ~(CR4_SMEP | CR4_SMAP);
    __asm_cr4(newCr4);
    KdPrint(("CR4 modified: 0x%p (SMEP and SMAP disabled)\n", (PVOID)newCr4));

    PVOID sourceAddress = (PVOID)0xFFFF968000000000;
    SIZE_T copySize = 0x1800000;
    PCWSTR outputFile = L"\\??\\C:\\process_memory.bin";

    status = CopyMemoryFromProcess(targetProcess, sourceAddress, copySize, outputFile);

    if (NT_SUCCESS(status)) {
        KdPrint(("Memory dump completed successfully\n"));
    } else {
        KdPrint(("Memory dump failed: 0x%08X\n", status));
    }

    __asm_cr4(g_OriginalCr4);
    ObDereferenceObject(targetProcess);

    return STATUS_SUCCESS;
}
