
/**
 * 用户为本，科技向善
 **/

#include "kmdf.h"

#include "AuthenticAMD.h"
#include "GenuineIntel.h"

#include "lfqueue.h"

static lfqueue* Contiguous4K = NULL;
static lfqueue* Contiguous8K = NULL;
static lfqueue* Contiguous16K = NULL;
static lfqueue* Contiguous32K = NULL;

void*
operator new(SIZE_T size, void* ptr) noexcept
{
    UNREFERENCED_PARAMETER(size);
    return ptr;
}

template <>
PVOID
allocate<0x1000>()
{
    return Contiguous4K->pop();
}

template <>
void
deallocate<0x1000>(PVOID Mem)
{
    Contiguous4K->push(Mem);
}

template <>
PVOID
allocate<0x2000>()
{
    return Contiguous8K->pop();
}

template <>
void
deallocate<0x2000>(PVOID Mem)
{
    Contiguous8K->push(Mem);
}

template <>
PVOID
allocate<0x4000>()
{
    return Contiguous16K->pop();
}

template <>
void
deallocate<0x4000>(PVOID Mem)
{
    Contiguous16K->push(Mem);
}

template <>
PVOID
allocate<0x8000>()
{
    return Contiguous32K->pop();
}

template <>
void
deallocate<0x8000>(PVOID Mem)
{
    Contiguous32K->push(Mem);
}

static ULONG_PTR
KipiBroadcastWorker(_In_ ULONG_PTR Argument)
{
    UNREFERENCED_PARAMETER(Argument);

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

    while (auto m = allocate<0x8000>()) {
        MmFreeContiguousMemory(m);
    }

    while (auto m = allocate<0x4000>()) {
        MmFreeContiguousMemory(m);
    }

    while (auto m = allocate<0x2000>()) {
        MmFreeContiguousMemory(m);
    }

    while (auto m = allocate<0x1000>()) {
        MmFreeContiguousMemory(m);
    }

    ExFreePool(Contiguous32K);
    ExFreePool(Contiguous16K);
    ExFreePool(Contiguous8K);
    ExFreePool(Contiguous4K);
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    KdBreakPoint();

    PHYSICAL_ADDRESS HighestAcceptableAddress;
    HighestAcceptableAddress.QuadPart = 0xFFFFFFFFFFFFFFFFLL;

    Contiguous4K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Contiguous8K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Contiguous16K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Contiguous32K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();

    for (ULONG i = 0; i < KeQueryActiveProcessorCount(NULL); ++i) {
        for (size_t k = 0; k < 16; k++) {
            auto m = MmAllocateContiguousMemory(0x1000, HighestAcceptableAddress);
            deallocate<0x1000>(m);
        }

        for (size_t k = 0; k < 8; k++) {
            auto m = MmAllocateContiguousMemory(0x2000, HighestAcceptableAddress);
            deallocate<0x2000>(m);
        }

        for (size_t k = 0; k < 4; k++) {
            auto m = MmAllocateContiguousMemory(0x4000, HighestAcceptableAddress);
            deallocate<0x4000>(m);
        }

        for (size_t k = 0; k < 2; k++) {
            auto m = MmAllocateContiguousMemory(0x8000, HighestAcceptableAddress);
            deallocate<0x8000>(m);
        }
    }

    PHYSICAL_MEMORY_RANGE* Ranges = MmGetPhysicalMemoryRanges();

    if (Ranges == NULL)
        return -1;

    for (size_t i = 0; Ranges[i].BaseAddress.QuadPart || Ranges[i].NumberOfBytes.QuadPart; ++i) {
        PHYSICAL_ADDRESS BaseAddress = Ranges[i].BaseAddress;
        LARGE_INTEGER NumberOfBytes = Ranges[i].NumberOfBytes;

        KdPrint(("0x%016llX: 0x%08llX\n", BaseAddress.QuadPart, NumberOfBytes.QuadPart));
    }

    ExFreePool(Ranges);

    if (KeIpiGenericCall(KipiBroadcastWorker, 0))
        return STATUS_UNSUCCESSFUL;

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
