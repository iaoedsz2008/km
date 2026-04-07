
/**
 * 用户为本，科技向善
 **/

#include "ExQueueWorkItem.h"

#include <ntddk.h>

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

static WORK_QUEUE_ITEM WorkItem = {};

EXTERN_C VOID
DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
}

EXTERN_C NTSTATUS
DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    ExQueueWorkItem(&WorkItem, NormalWorkQueue);

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
