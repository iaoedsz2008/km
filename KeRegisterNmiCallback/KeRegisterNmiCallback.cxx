
/**
 * 用户为本，科技向善
 **/

#include "KeRegisterNmiCallback.h"

#include <ntddk.h>

static volatile LONG g_NmiCount = 0;
static PVOID g_NmiCallbackHandle = nullptr;

static BOOLEAN
NmiCallback(_In_opt_ PVOID Context, _In_ BOOLEAN Handled)
{
    UNREFERENCED_PARAMETER(Context);

    InterlockedIncrement(&g_NmiCount);

    return Handled;
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    if (g_NmiCallbackHandle != nullptr) {
        KeDeregisterNmiCallback(g_NmiCallbackHandle);
        g_NmiCallbackHandle = nullptr;
    }
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    g_NmiCount = 0;
    g_NmiCallbackHandle = KeRegisterNmiCallback(NmiCallback, nullptr);
    if (g_NmiCallbackHandle == nullptr) {
        return STATUS_UNSUCCESSFUL;
    }

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KeRegisterNmiCallback: registered\n");

    DriverObject->DriverUnload = DriverUnload;
    return STATUS_SUCCESS;
}
