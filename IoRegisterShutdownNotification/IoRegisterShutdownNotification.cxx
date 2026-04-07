
/**
 * 用户为本，科技向善
 **/

#include "IoRegisterShutdownNotification.h"

#include <ntddk.h>

static NTSTATUS
CompleteRequest(_In_ PIRP Irp, _In_ NTSTATUS Status)
{
    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Status;
}

static NTSTATUS
DispatchCreateClose(_In_ PDEVICE_OBJECT DeviceObject, _Inout_ PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);
    return CompleteRequest(Irp, STATUS_SUCCESS);
}

static NTSTATUS
DispatchUnsupported(_In_ PDEVICE_OBJECT DeviceObject, _Inout_ PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);
    return CompleteRequest(Irp, STATUS_NOT_SUPPORTED);
}

static NTSTATUS
DispatchShutdown(_In_ PDEVICE_OBJECT DeviceObject, _Inout_ PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "IoRegisterShutdownNotification: received IRP_MJ_SHUTDOWN\n");

    return CompleteRequest(Irp, STATUS_SUCCESS);
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    PDEVICE_OBJECT deviceObject = DriverObject->DeviceObject;

    if (deviceObject != nullptr) {
        IoUnregisterShutdownNotification(deviceObject);
        IoDeleteDevice(deviceObject);
    }
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    NTSTATUS status;
    PDEVICE_OBJECT deviceObject = nullptr;
    UNICODE_STRING deviceName = RTL_CONSTANT_STRING(L"\\Device\\IoRegisterShutdownNotificationDemo");

    for (ULONG i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; ++i) {
        DriverObject->MajorFunction[i] = DispatchUnsupported;
    }

    DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreateClose;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchCreateClose;
    DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = DispatchShutdown;
    DriverObject->DriverUnload = DriverUnload;

    status = IoCreateDevice(DriverObject, 0, &deviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &deviceObject);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    status = IoRegisterShutdownNotification(deviceObject);
    if (!NT_SUCCESS(status)) {
        IoDeleteDevice(deviceObject);
        return status;
    }

    deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
    return STATUS_SUCCESS;
}
