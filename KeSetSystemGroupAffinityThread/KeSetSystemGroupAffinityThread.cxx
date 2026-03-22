
/**
 * 用户为本，科技向善
 **/

#include "KeSetSystemGroupAffinityThread.h"

#include <ntddk.h>

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    PROCESSOR_NUMBER ProcessorNumber;
    GROUP_AFFINITY GroupAffinity;
    GROUP_AFFINITY UserGroupAffinity;
    ULONG ProcessorCount = KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);

    NTSTATUS Status = STATUS_SUCCESS;

    for (ULONG i = 0; i < ProcessorCount; i++) {
        Status = KeGetProcessorNumberFromIndex(i, &ProcessorNumber);
        if (!NT_SUCCESS(Status))
            break;

        GroupAffinity.Group = ProcessorNumber.Group;
        GroupAffinity.Mask = 1ULL << ProcessorNumber.Number;
        GroupAffinity.Reserved[0] = GroupAffinity.Reserved[1] = GroupAffinity.Reserved[2] = 0;
        KeSetSystemGroupAffinityThread(&GroupAffinity, &UserGroupAffinity);

        KeRevertToUserGroupAffinityThread(&UserGroupAffinity);

        KeSetSystemAffinityThread;
        KeRevertToUserAffinityThread;

        KeSetSystemAffinityThreadEx;
        KeRevertToUserAffinityThreadEx;

        PsSetSystemMultipleGroupAffinityThread;
        PsRevertToUserMultipleGroupAffinityThread;
    }

    DriverObject->DriverUnload = DriverUnload;

    return Status;
}
