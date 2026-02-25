
/**
 * 用户为本，科技向善
 **/

#include "ExRegisterCallback.h"

#include "Support.h"

#include <ntddk.h>

static PCALLBACK_OBJECT g_CallbackObject = nullptr;
static PVOID g_CallbackRegistration = nullptr;

static VOID
ExDemoCallbackRoutine(_In_ PVOID CallbackContext, _In_opt_ PVOID Argument1, _In_opt_ PVOID Argument2)
{
    UNREFERENCED_PARAMETER(CallbackContext);

    DbgPrint("ExCreateCallbackDemo: ExDemoCallbackRoutine called, Arg1=%p, Arg2=%p\n", Argument1, Argument2);
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    if (g_CallbackRegistration != nullptr) {
        ExUnregisterCallback(g_CallbackRegistration);
        g_CallbackRegistration = nullptr;
    }

    if (g_CallbackObject != nullptr) {
        ObDereferenceObject(g_CallbackObject);
        g_CallbackObject = nullptr;
    }

    DbgPrint("ExCreateCallbackDemo: DriverUnload\n");
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    NTSTATUS status;
    UNICODE_STRING callbackName;
    OBJECT_ATTRIBUTES objectAttributes;

    RtlInitUnicodeString(&callbackName, L"\\Callback\\ExCreateCallbackDemo");

    InitializeObjectAttributes(&objectAttributes, &callbackName, OBJ_PERMANENT | OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, nullptr, nullptr);

    status = ExCreateCallback(&g_CallbackObject, &objectAttributes, TRUE, TRUE);

    if (!NT_SUCCESS(status)) {
        DbgPrint("ExCreateCallbackDemo: ExCreateCallback failed, status=0x%08X\n", status);
        return status;
    }

    g_CallbackRegistration = ExRegisterCallback(g_CallbackObject, ExDemoCallbackRoutine, nullptr);

    if (g_CallbackRegistration == nullptr) {
        DbgPrint("ExCreateCallbackDemo: ExRegisterCallback failed\n");
        ObDereferenceObject(g_CallbackObject);
        g_CallbackObject = nullptr;
        return STATUS_UNSUCCESSFUL;
    }

    ExNotifyCallback(g_CallbackObject, reinterpret_cast<PVOID>(1), reinterpret_cast<PVOID>(2));

    DbgPrint("ExCreateCallbackDemo: DriverEntry success\n");

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
