
/**
 * 用户为本，科技向善
 **/

#include "kmdf.h"

#include "Support.h"

#include <ntifs.h>

#include <ntddk.h>

ULONG_PTR
KipiBroadcastWorker(_In_ ULONG_PTR Argument)
{
    return 0;
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    __asm_cpuid(0, &eax, &ebx, &ecx, &edx);

    KeIpiGenericCall(KipiBroadcastWorker, 0);

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
