
/**
 * 用户为本，科技向善
 **/

#include "AuthenticAMD.h"
#include "GenuineIntel.h"

#include "kmdf.h"

#include "StringHash.h"
#include "Support.h"

#include <ntifs.h>

#include <ntddk.h>

static ULONG_PTR
KipiBroadcastWorker(_In_ ULONG_PTR Argument)
{
    char vendor[0x10] = {};

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    KdBreakPoint();

    __asm_cpuid(0, &eax, &ebx, &ecx, &edx);

    ((uint32_t*)vendor)[0] = ebx;
    ((uint32_t*)vendor)[1] = edx;
    ((uint32_t*)vendor)[2] = ecx;

    KeGetCurrentProcessorIndex();
    KeGetCurrentProcessorNumber();

    if (memcmp(vendor, "GenuineIntel", 12) == 0)
        return initialize<Hash("GenuineIntel")>();

    if (memcmp(vendor, "AuthenticAMD", 12) == 0)
        return initialize<Hash("AuthenticAMD")>();

    return -1;
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

    KeGetCurrentProcessorNumber();

    if (KeIpiGenericCall(KipiBroadcastWorker, 0))
        return STATUS_UNSUCCESSFUL;

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
