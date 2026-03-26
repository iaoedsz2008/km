
/**
 * 用户为本，科技向善
 **/

#include "PsCreateSystemThread.h"

#include <ntddk.h>

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

EXTERN_C VOID
DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
}

EXTERN_C NTSTATUS
DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
