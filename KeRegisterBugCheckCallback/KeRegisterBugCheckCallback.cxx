
/**
 * 用户为本，科技向善
 **/

#include "KeRegisterBugCheckCallback.h"

#include <ntddk.h>

typedef struct _BUGCHECK_DEMO_DATA
{
    ULONG Magic;
    ULONG Processor;
} BUGCHECK_DEMO_DATA, *PBUGCHECK_DEMO_DATA;

static KBUGCHECK_CALLBACK_RECORD g_BugCheckRecord;
static BUGCHECK_DEMO_DATA g_BugCheckData = {};
static BOOLEAN g_BugCheckRegistered = FALSE;
static UCHAR g_ComponentName[] = "BugCheckDemo";

static VOID
BugCheckCallback(_Inout_ PVOID Buffer, _In_ ULONG Length)
{
    if (Length < sizeof(BUGCHECK_DEMO_DATA))
    {
        return;
    }

    PBUGCHECK_DEMO_DATA data = static_cast<PBUGCHECK_DEMO_DATA>(Buffer);
    data->Magic = 'KCHK';
    data->Processor = KeGetCurrentProcessorNumberEx(nullptr);
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    if (g_BugCheckRegistered)
    {
        KeDeregisterBugCheckCallback(&g_BugCheckRecord);
        g_BugCheckRegistered = FALSE;
    }
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    RtlZeroMemory(&g_BugCheckData, sizeof(g_BugCheckData));
    KeInitializeCallbackRecord(&g_BugCheckRecord);

    if (!KeRegisterBugCheckCallback(
            &g_BugCheckRecord,
            BugCheckCallback,
            &g_BugCheckData,
            sizeof(g_BugCheckData),
            g_ComponentName))
    {
        return STATUS_UNSUCCESSFUL;
    }

    g_BugCheckRegistered = TRUE;

    DbgPrintEx(
        DPFLTR_IHVDRIVER_ID,
        DPFLTR_INFO_LEVEL,
        "KeRegisterBugCheckCallback: registered\n");

    DriverObject->DriverUnload = DriverUnload;
    return STATUS_SUCCESS;
}
