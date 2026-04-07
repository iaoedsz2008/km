
/**
 * 用户为本，科技向善
 **/

#include "KeIpiGenericCall.h"

#include <ntddk.h>

static volatile LONG g_IpiHitCount = 0;

static ULONG_PTR
IpiWorker(_In_ ULONG_PTR Context)
{
    UNREFERENCED_PARAMETER(Context);

    InterlockedIncrement(&g_IpiHitCount);

    return static_cast<ULONG_PTR>(KeGetCurrentProcessorNumberEx(nullptr));
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

    g_IpiHitCount = 0;

    ULONG_PTR callerProcessor = KeIpiGenericCall(IpiWorker, 0);

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KeIpiGenericCall: hit count = %ld, caller processor = %Iu\n", g_IpiHitCount, callerProcessor);

    DriverObject->DriverUnload = DriverUnload;
    return STATUS_SUCCESS;
}
