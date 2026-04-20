
/**
 * 用户为本，科技向善
 **/

#include "kmdf.h"

#include "AuthenticAMD.h"
#include "GenuineIntel.h"

lfqueue* Mem4K = NULL;
lfqueue* Mem8K = NULL;
lfqueue* Mem16K = NULL;
lfqueue* Mem32K = NULL;
lfqueue* Mem64K = NULL;

lfqueue* Contiguous4K = NULL;
lfqueue* Contiguous8K = NULL;
lfqueue* Contiguous16K = NULL;
lfqueue* Contiguous32K = NULL;

void*
operator new(SIZE_T size, void* ptr) noexcept
{
    UNREFERENCED_PARAMETER(size);
    return ptr;
}

static void
initialize(size_t PhysicalSize)
{
    char vendor[0x10] = {};

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    __asm_cpuid(0, &eax, &ebx, &ecx, &edx);

    ((uint32_t*)vendor)[0] = ebx;
    ((uint32_t*)vendor)[1] = edx;
    ((uint32_t*)vendor)[2] = ecx;

    if (memcmp(vendor, "GenuineIntel", 12) == 0)
        initialize<Hash("GenuineIntel")>(PhysicalSize);

    if (memcmp(vendor, "AuthenticAMD", 12) == 0)
        initialize<Hash("AuthenticAMD")>(PhysicalSize);
}

static ULONG_PTR
vmxon(IN ULONG_PTR Argument)
{
    PEPROCESS* System = (PEPROCESS*)Argument;

    char vendor[0x10] = {};

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    __asm_cpuid(0, &eax, &ebx, &ecx, &edx);

    ((uint32_t*)vendor)[0] = ebx;
    ((uint32_t*)vendor)[1] = edx;
    ((uint32_t*)vendor)[2] = ecx;

#if defined(_M_AMD64) || defined(__x86_64__)
    PVOID DirectoryTableBase = *(PVOID*)((UINT8*)System + 0x28);
#endif
#if defined(_M_IX86) || defined(__i386__)
    PVOID DirectoryTableBase = *(PVOID*)((UINT8*)System + 0x18);
#endif

    if (memcmp(vendor, "GenuineIntel", 12) == 0)
        return vmxon<Hash("GenuineIntel")>(DirectoryTableBase);

    if (memcmp(vendor, "AuthenticAMD", 12) == 0)
        return vmxon<Hash("AuthenticAMD")>(DirectoryTableBase);

    return -1;
}

static ULONG_PTR
vmxoff(IN ULONG_PTR Argument)
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
        vmxoff<Hash("GenuineIntel")>(NULL);

    if (memcmp(vendor, "AuthenticAMD", 12) == 0)
        vmxoff<Hash("AuthenticAMD")>(NULL);

    return 0;
}

EXTERN_C VOID
DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    KdBreakPoint();

    if (KeIpiGenericCall(vmxoff, 0))
        return;

    while (auto m = allocateContiguous<0x8000>()) {
        MmFreeContiguousMemory(m);
    }

    while (auto m = allocateContiguous<0x4000>()) {
        MmFreeContiguousMemory(m);
    }

    while (auto m = allocateContiguous<0x2000>()) {
        MmFreeContiguousMemory(m);
    }

    while (auto m = allocateContiguous<0x1000>()) {
        MmFreeContiguousMemory(m);
    }

    while (auto m = allocate<0x10000>()) {
        ExFreePool(m);
    }

    while (auto m = allocate<0x8000>()) {
        ExFreePool(m);
    }

    while (auto m = allocate<0x4000>()) {
        ExFreePool(m);
    }

    while (auto m = allocate<0x2000>()) {
        ExFreePool(m);
    }

    while (auto m = allocate<0x1000>()) {
        ExFreePool(m);
    }

    ExFreePool(Contiguous32K);
    ExFreePool(Contiguous16K);
    ExFreePool(Contiguous8K);
    ExFreePool(Contiguous4K);
    ExFreePool(Mem64K);
    ExFreePool(Mem32K);
    ExFreePool(Mem16K);
    ExFreePool(Mem8K);
    ExFreePool(Mem4K);
}

EXTERN_C NTSTATUS
DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    KdBreakPoint();

    PHYSICAL_MEMORY_RANGE* Ranges = MmGetPhysicalMemoryRanges();

    if (Ranges == NULL)
        return -1;

    LONGLONG PhysicalSize = {};
    for (size_t i = 0; Ranges[i].BaseAddress.QuadPart || Ranges[i].NumberOfBytes.QuadPart; ++i) {
        PHYSICAL_ADDRESS BaseAddress = Ranges[i].BaseAddress;
        LARGE_INTEGER NumberOfBytes = Ranges[i].NumberOfBytes;

        if (BaseAddress.QuadPart > PhysicalSize)
            PhysicalSize = BaseAddress.QuadPart + NumberOfBytes.QuadPart;

        KdPrint(("PHYSICAL_MEMORY_RANGE [0x%016llX - 0x%016llX]\n", BaseAddress.QuadPart, BaseAddress.QuadPart + NumberOfBytes.QuadPart));
    }

    ExFreePool(Ranges);

    PHYSICAL_ADDRESS HighestAcceptableAddress;
    HighestAcceptableAddress.QuadPart = 0xFFFFFFFFFFFFFFFFLL;

    Contiguous4K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Contiguous8K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Contiguous16K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Contiguous32K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Mem4K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Mem8K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Mem16K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Mem32K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();
    Mem64K = new (ExAllocatePool(NonPagedPool, sizeof(lfqueue))) lfqueue();

    for (ULONG i = 0; i < KeQueryActiveProcessorCount(NULL); ++i) {
        for (size_t k = 0; k < 16; ++k) {
            auto m = MmAllocateContiguousMemory(0x1000, HighestAcceptableAddress);
            deallocateContiguous<0x1000>(m);
        }

        for (size_t k = 0; k < 8; ++k) {
            auto m = MmAllocateContiguousMemory(0x2000, HighestAcceptableAddress);
            deallocateContiguous<0x2000>(m);
        }

        for (size_t k = 0; k < 4; ++k) {
            auto m = MmAllocateContiguousMemory(0x4000, HighestAcceptableAddress);
            deallocateContiguous<0x4000>(m);
        }

        for (size_t k = 0; k < 2; ++k) {
            auto m = MmAllocateContiguousMemory(0x8000, HighestAcceptableAddress);
            deallocateContiguous<0x8000>(m);
        }

        for (size_t k = 0; k < 16; ++k) {
            auto m = ExAllocatePool(NonPagedPool, 0x1000);
            deallocate<0x1000>(m);
        }

        for (size_t k = 0; k < 8; ++k) {
            auto m = ExAllocatePool(NonPagedPool, 0x2000);
            deallocate<0x2000>(m);
        }

        for (size_t k = 0; k < 4; ++k) {
            auto m = ExAllocatePool(NonPagedPool, 0x4000);
            deallocate<0x4000>(m);
        }

        for (size_t k = 0; k < 2; ++k) {
            auto m = ExAllocatePool(NonPagedPool, 0x8000);
            deallocate<0x8000>(m);
        }

        for (size_t k = 0; k < 1; ++k) {
            auto m = ExAllocatePool(NonPagedPool, 0x10000);
            deallocate<0x10000>(m);
        }
    }

    size_t x = ((CalculatePML4Es<PageTranslation>(PhysicalSize) + 0x1FF) >> 9) * 3;
    for (size_t i = 0; i < x; ++i) {
        auto m = ExAllocatePool(NonPagedPool, 0x1000);
        deallocate<0x1000>(m);
    }

    x = ((CalculatePDPTEs<PageTranslation>(PhysicalSize) + 0x1FF) >> 9) * 3;
    for (size_t i = 0; i < x; ++i) {
        auto m = ExAllocatePool(NonPagedPool, 0x1000);
        deallocate<0x1000>(m);
    }

    x = ((CalculatePDEs<PageTranslation>(PhysicalSize) + 0x1FF) >> 9) * 3;
    for (size_t i = 0; i < x; ++i) {
        auto m = ExAllocatePool(NonPagedPool, 0x1000);
        deallocate<0x1000>(m);
    }

    x = ((CalculatePTEs<PageTranslation>(PhysicalSize) + 0x1FF) >> 9) * 3;
    for (size_t i = 0; i < x; ++i) {
        auto m = ExAllocatePool(NonPagedPool, 0x1000);
        deallocate<0x1000>(m);
    }

    initialize(PhysicalSize);

    PROCESSOR_NUMBER ProcessorNumber;
    GROUP_AFFINITY GroupAffinity;
    GROUP_AFFINITY UserGroupAffinity;
    ULONG ProcessorCount = KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);

    NTSTATUS Status = STATUS_SUCCESS;

    for (ULONG i = 0; i < ProcessorCount; i++) {
        Status = KeGetProcessorNumberFromIndex(i, &ProcessorNumber);
        if (!NT_SUCCESS(Status))
            break;

        GroupAffinity.Group = ProcessorNumber.Group;
        GroupAffinity.Mask = 1ULL << ProcessorNumber.Number;
        GroupAffinity.Reserved[0] = GroupAffinity.Reserved[1] = GroupAffinity.Reserved[2] = 0;
        KeSetSystemGroupAffinityThread(&GroupAffinity, &UserGroupAffinity);

        vmxon((ULONG_PTR)PsGetCurrentProcess());

        KeRevertToUserGroupAffinityThread(&UserGroupAffinity);
    }

    /**
     * 注意
     * 如果需要将代码移植至其他平台,此时必须保证获取到的CR3是系统进程的.
     **/
    ASSERT(PsGetCurrentProcessId() == (HANDLE)4);

    // if (KeIpiGenericCall(vmxon, (ULONG_PTR)PsGetCurrentProcess()))
    //     return STATUS_UNSUCCESSFUL;

    DriverObject->DriverUnload = DriverUnload;

#if 1 // 构建一个测试环境.
    LARGE_INTEGER SystemTimeA;
    LARGE_INTEGER SystemTimeB;
    LARGE_INTEGER SystemTimeC;
    LARGE_INTEGER SystemTimeD;

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    __asm_cpuid(0x99999999, &eax, &ebx, &ecx, &edx);

    uint64_t val;
    uint32_t* p = (uint32_t*)&val;
    p[0] = eax;
    p[1] = edx;

    DbgPrint("Test 1 return: 0x%llX\n", ((size_t (*)(void))val)());
    KeQuerySystemTimePrecise(&SystemTimeA);
    for (size_t i = 0; i < 0x10000; i++) {
        ((size_t (*)(void))val)();
    }
    KeQuerySystemTimePrecise(&SystemTimeB);

    DbgPrint("Test 1 elapsed: %lld ns\n", (SystemTimeB.QuadPart - SystemTimeA.QuadPart) * 100);

    __asm_cpuid(0x88888888, &eax, &ebx, &ecx, &edx);

    p[0] = eax;
    p[1] = edx;

    DbgPrint("Test 2 return: 0x%llX\n", ((size_t (*)(void))val)());
    KeQuerySystemTimePrecise(&SystemTimeC);
    for (size_t i = 0; i < 0x10000; i++) {
        ((size_t (*)(void))val)();
    }
    KeQuerySystemTimePrecise(&SystemTimeD);

    DbgPrint("Test 2 elapsed: %lld ns\n", (SystemTimeD.QuadPart - SystemTimeC.QuadPart) * 100);

#endif

    return STATUS_SUCCESS;
}
