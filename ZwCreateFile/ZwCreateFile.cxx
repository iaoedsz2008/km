
/**
 * 用户为本，科技向善
 **/

#include "ZwCreateFile.h"

#include <ntddk.h>

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    HANDLE fileHandle = nullptr;
    IO_STATUS_BLOCK ioStatus = {};
    OBJECT_ATTRIBUTES objectAttributes;
    UNICODE_STRING fileName = RTL_CONSTANT_STRING(L"\\SystemRoot\\Temp\\ZwCreateFileDemo.txt");

    DriverObject->DriverUnload = DriverUnload;

    InitializeObjectAttributes(&objectAttributes, &fileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, nullptr, nullptr);

    NTSTATUS status = ZwCreateFile(&fileHandle, GENERIC_WRITE | SYNCHRONIZE, &objectAttributes, &ioStatus, nullptr, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ, FILE_OPEN_IF, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT, nullptr, 0);

    if (NT_SUCCESS(status)) {
        ZwClose(fileHandle);
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "ZwCreateFile: success\n");
    } else {
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "ZwCreateFile: failed, status = 0x%08X\n", status);
    }

    return STATUS_SUCCESS;
}
