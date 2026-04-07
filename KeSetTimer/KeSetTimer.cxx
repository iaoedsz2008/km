
/**
 * 用户为本，科技向善
 **/

#include "KeSetTimer.h"

#include <ntddk.h>

static KTIMER g_Timer;
static KDPC g_TimerDpc;
static BOOLEAN g_TimerInitialized = FALSE;

static VOID
TimerDpc(_In_ PKDPC Dpc, _In_opt_ PVOID DeferredContext, _In_opt_ PVOID SystemArgument1, _In_opt_ PVOID SystemArgument2)
{
    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(DeferredContext);
    UNREFERENCED_PARAMETER(SystemArgument1);
    UNREFERENCED_PARAMETER(SystemArgument2);

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KeSetTimer: timer fired\n");
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    if (g_TimerInitialized) {
        KeCancelTimer(&g_Timer);
        g_TimerInitialized = FALSE;
    }
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    LARGE_INTEGER dueTime;

    KeInitializeTimer(&g_Timer);
    KeInitializeDpc(&g_TimerDpc, TimerDpc, nullptr);
    g_TimerInitialized = TRUE;

    dueTime.QuadPart = -30000000LL;
    KeSetTimer(&g_Timer, dueTime, &g_TimerDpc);

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KeSetTimer: timer scheduled\n");

    DriverObject->DriverUnload = DriverUnload;
    return STATUS_SUCCESS;
}
