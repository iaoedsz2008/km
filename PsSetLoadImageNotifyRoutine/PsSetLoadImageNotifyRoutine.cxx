
/**
 * 用户为本，科技向善
 **/

#include "PsSetLoadImageNotifyRoutine.h"

#include "Support.h"

#include <ntddk.h>

VOID
LoadImageNotifyCallback(_In_opt_ PUNICODE_STRING FullImageName, _In_ HANDLE ProcessId, _In_ PIMAGE_INFO ImageInfo)
{
    UNREFERENCED_PARAMETER(ImageInfo);

    if (FullImageName != NULL) {
        DbgPrint("Image Load: %wZ, PID: %p\n", FullImageName, ProcessId);
    } else {
        DbgPrint("Image Load: (null name), PID: %p\n", ProcessId);
    }
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    PsRemoveLoadImageNotifyRoutine(LoadImageNotifyCallback);
    DbgPrint("PsSetLoadImageNotifyRoutine sample driver unloaded.\n");
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    NTSTATUS status;

    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrint("PsSetLoadImageNotifyRoutine sample driver loaded.\n");

    DriverObject->DriverUnload = DriverUnload;

    status = PsSetLoadImageNotifyRoutine(LoadImageNotifyCallback);
    if (!NT_SUCCESS(status)) {
        DbgPrint("PsSetLoadImageNotifyRoutine failed: 0x%08X\n", status);
        return status;
    }

    return STATUS_SUCCESS;
}
