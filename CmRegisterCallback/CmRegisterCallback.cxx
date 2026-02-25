
/**
 * 用户为本，科技向善
 **/

#include "CmRegisterCallback.h"

#include "Support.h"

#include <ntddk.h>

static LARGE_INTEGER Cookie;

static NTSTATUS
_ExCallbackFunction(_In_ PVOID CallbackContext, _In_opt_ PVOID Argument1, _In_opt_ PVOID Argument2)
{
    UNREFERENCED_PARAMETER(CallbackContext);

    REG_NOTIFY_CLASS Operation = (REG_NOTIFY_CLASS)(ULONG_PTR)Argument1;

    union {
        PVOID Argument2;
        REG_CALLBACK_CONTEXT_CLEANUP_INFORMATION* RegCallbackContextCleanupInformation;
        REG_CREATE_KEY_INFORMATION* RegCreateKeyInformation;
        REG_DELETE_KEY_INFORMATION* RegDeleteKeyInformation;
        REG_DELETE_VALUE_KEY_INFORMATION* RegDeleteValueKeyInformation;
        REG_ENUMERATE_KEY_INFORMATION* RegEnumerateKeyInformation;
        REG_ENUMERATE_VALUE_KEY_INFORMATION* RegEnumerateValueKeyInformation;
        REG_FLUSH_KEY_INFORMATION* RegFlushKeyInformation;
        REG_KEY_HANDLE_CLOSE_INFORMATION* RegKeyHandleCloseInformation;
        REG_LOAD_KEY_INFORMATION* RegLoadKeyInformation;
        REG_OPEN_KEY_INFORMATION* RegOpenKeyInformation;
        REG_POST_CREATE_KEY_INFORMATION* RegPostCreateKeyInformation;
        REG_POST_OPEN_KEY_INFORMATION* RegPostOpenKeyInformation;
        REG_POST_OPERATION_INFORMATION* RegPostOperationInformation;
        REG_PRE_CREATE_KEY_INFORMATION* RegPreCreateKeyInformation;
        REG_PRE_OPEN_KEY_INFORMATION* RegPreOpenKeyInformation;
        REG_QUERY_KEY_INFORMATION* RegQueryKeyInformation;
        REG_QUERY_KEY_SECURITY_INFORMATION* RegQueryKeySecurityInformation;
        REG_QUERY_MULTIPLE_VALUE_KEY_INFORMATION* RegQueryMultipleValueKeyInformation;
        REG_QUERY_VALUE_KEY_INFORMATION* RegQueryValueKeyInformation;
        REG_RENAME_KEY_INFORMATION* RegRenameKeyInformation;
        REG_REPLACE_KEY_INFORMATION* RegReplaceKeyInformation;
        REG_RESTORE_KEY_INFORMATION* RegRestoreKeyInformation;
        REG_SAVE_KEY_INFORMATION* RegSaveKeyInformation;
        REG_SET_INFORMATION_KEY_INFORMATION* RegSetInformationKeyInformation;
        REG_SET_KEY_SECURITY_INFORMATION* RegSetKeySecurityInformation;
        REG_SET_VALUE_KEY_INFORMATION* RegSetValueKeyInformation;
        REG_UNLOAD_KEY_INFORMATION* RegUnloadKeyInformation;
    } st;

    st.Argument2 = Argument2;

    switch (Operation) {
    case RegNtDeleteKey:
        st.RegDeleteKeyInformation;
        break;
    case RegNtPostDeleteKey:
        st.RegPostOperationInformation;
        break;
    case RegNtSetValueKey:
        st.RegSetValueKeyInformation;
        break;
    case RegNtPostSetValueKey:
        st.RegPostOperationInformation;
        break;
    case RegNtDeleteValueKey:
        st.RegDeleteValueKeyInformation;
        break;
    case RegNtPostDeleteValueKey:
        st.RegPostOperationInformation;
        break;
    case RegNtSetInformationKey:
        st.RegSetInformationKeyInformation;
        break;
    case RegNtPostSetInformationKey:
        st.RegPostOperationInformation;
        break;
    case RegNtRenameKey:
        st.RegRenameKeyInformation;
        break;
    case RegNtPostRenameKey:
        st.RegPostOperationInformation;
        break;
    case RegNtEnumerateKey:
        st.RegEnumerateKeyInformation;
        break;
    case RegNtPostEnumerateKey:
        st.RegPostOperationInformation;
        break;
    case RegNtEnumerateValueKey:
        st.RegEnumerateValueKeyInformation;
        break;
    case RegNtPostEnumerateValueKey:
        st.RegPostOperationInformation;
        break;
    case RegNtQueryKey:
        st.RegQueryKeyInformation;
        break;
    case RegNtPostQueryKey:
        st.RegPostOperationInformation;
        break;
    case RegNtQueryValueKey:
        st.RegQueryValueKeyInformation;
        break;
    case RegNtPostQueryValueKey:
        st.RegPostOperationInformation;
        break;
    case RegNtQueryMultipleValueKey:
        st.RegQueryMultipleValueKeyInformation;
        break;
    case RegNtPostQueryMultipleValueKey:
        st.RegPostOperationInformation;
        break;
    case RegNtPreCreateKey:
        st.RegPreCreateKeyInformation;
        DbgPrint("RegNtPreCreateKey: %wZ\n", st.RegPreCreateKeyInformation->CompleteName);
        break;
    case RegNtPreCreateKeyEx:
        DbgPrint("RegNtPreCreateKeyEx: %wZ\n", st.RegCreateKeyInformation->CompleteName);
        st.RegCreateKeyInformation;
        break;
    case RegNtPostCreateKey:
        st.RegPostCreateKeyInformation;
        break;
    case RegNtPostCreateKeyEx:
        st.RegPostOperationInformation;
        break;
    case RegNtPreOpenKey:
        st.RegPreOpenKeyInformation;
        DbgPrint("RegNtPreOpenKey: %wZ\n", st.RegPreOpenKeyInformation->CompleteName);
        break;
    case RegNtPreOpenKeyEx:
        DbgPrint("RegNtPreOpenKeyEx: %wZ\n", st.RegOpenKeyInformation->CompleteName);
        st.RegOpenKeyInformation;
        break;
    case RegNtPostOpenKey:
        st.RegPostOpenKeyInformation;
        break;
    case RegNtPostOpenKeyEx:
        st.RegPostOperationInformation;
        break;
    case RegNtKeyHandleClose:
        st.RegKeyHandleCloseInformation;
        break;
    case RegNtPostKeyHandleClose:
        st.RegPostOperationInformation;
        break;
    case RegNtPreFlushKey:
        st.RegFlushKeyInformation;
        break;
    case RegNtPostFlushKey:
        st.RegPostOperationInformation;
        break;
    case RegNtPreLoadKey:
        st.RegLoadKeyInformation;
        break;
    case RegNtPostLoadKey:
        st.RegPostOperationInformation;
        break;
    case RegNtPreUnLoadKey:
        st.RegUnloadKeyInformation;
        break;
    case RegNtPostUnLoadKey:
        st.RegPostOperationInformation;
        break;
    case RegNtPreQueryKeySecurity:
        st.RegQueryKeySecurityInformation;
        break;
    case RegNtPostQueryKeySecurity:
        st.RegPostOperationInformation;
        break;
    case RegNtPreSetKeySecurity:
        st.RegSetKeySecurityInformation;
        break;
    case RegNtPostSetKeySecurity:
        st.RegPostOperationInformation;
        break;
    case RegNtCallbackObjectContextCleanup:
        st.RegCallbackContextCleanupInformation;
        break;
    case RegNtPreRestoreKey:
        st.RegRestoreKeyInformation;
        break;
    case RegNtPostRestoreKey:
        st.RegPostOperationInformation;
        break;
    case RegNtPreSaveKey:
        st.RegSaveKeyInformation;
        break;
    case RegNtPostSaveKey:
        st.RegPostOperationInformation;
        break;
    case RegNtPreReplaceKey:
        st.RegReplaceKeyInformation;
        break;
    case RegNtPostReplaceKey:
        st.RegPostOperationInformation;
        break;
    }

    return STATUS_SUCCESS;
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    CmUnRegisterCallback(Cookie);
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    Cookie.QuadPart = 0;
    CmRegisterCallback(_ExCallbackFunction, NULL, &Cookie);

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
