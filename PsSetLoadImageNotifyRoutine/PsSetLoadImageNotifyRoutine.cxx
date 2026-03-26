
/**
 * 用户为本，科技向善
 **/

#include "PsSetLoadImageNotifyRoutine.h"

#include <ntddk.h>

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

VOID
LoadImageNotifyCallback(_In_opt_ PUNICODE_STRING FullImageName, IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo)
{
    UNREFERENCED_PARAMETER(ImageInfo);

    if (FullImageName != NULL) {
        DbgPrint("Image Load: %wZ, PID: %p\n", FullImageName, ProcessId);
    } else {
        DbgPrint("Image Load: (null name), PID: %p\n", ProcessId);
    }
}

EXTERN_C VOID
DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    PsRemoveLoadImageNotifyRoutine(LoadImageNotifyCallback);
    DbgPrint("PsSetLoadImageNotifyRoutine sample driver unloaded.\n");
}

EXTERN_C NTSTATUS
DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
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
