
/**
 * 富强、民主、文明、和谐
 * 自由、平等、公正、法治
 * 爱国、敬业、诚信、友善
 **/

#include "ObRegisterCallbacks.h"

#include "Support.h"

#include <ntddk.h>

PVOID ObCallbacks;

static OB_PREOP_CALLBACK_STATUS
_ObPreOperationCallback(_In_ PVOID RegistrationContext, _Inout_ POB_PRE_OPERATION_INFORMATION OperationInformation)
{
    UNREFERENCED_PARAMETER(RegistrationContext);
    UNREFERENCED_PARAMETER(OperationInformation);

    if (OperationInformation->ObjectType != *CmKeyObjectType)
        return OB_PREOP_SUCCESS;

    if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
        OperationInformation->Parameters->CreateHandleInformation;

    if (OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
        OperationInformation->Parameters->DuplicateHandleInformation;

    return OB_PREOP_SUCCESS;
}

static VOID
_ObPostOperationCallback(_In_ PVOID RegistrationContext, _In_ POB_POST_OPERATION_INFORMATION OperationInformation)
{
    UNREFERENCED_PARAMETER(RegistrationContext);
    UNREFERENCED_PARAMETER(OperationInformation);

    if (OperationInformation->ObjectType != *CmKeyObjectType)
        return;

    if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
        OperationInformation->Parameters->CreateHandleInformation;

    if (OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
        OperationInformation->Parameters->DuplicateHandleInformation;
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    ObUnRegisterCallbacks(ObCallbacks);
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    OB_OPERATION_REGISTRATION OperationRegistration;
    OB_CALLBACK_REGISTRATION CallbackRegistration;

    OperationRegistration.ObjectType = CmKeyObjectType;
    OperationRegistration.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
    OperationRegistration.PreOperation = _ObPreOperationCallback;
    OperationRegistration.PostOperation = _ObPostOperationCallback;

    RtlInitUnicodeString(&CallbackRegistration.Altitude, L"360000");
    CallbackRegistration.OperationRegistration = &OperationRegistration;
    CallbackRegistration.OperationRegistrationCount = 1;
    CallbackRegistration.RegistrationContext = NULL;
    CallbackRegistration.Version = OB_FLT_REGISTRATION_VERSION;

    ObRegisterCallbacks(&CallbackRegistration, &ObCallbacks);

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
