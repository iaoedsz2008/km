
/**
 * 富强、民主、文明、和谐
 * 自由、平等、公正、法治
 * 爱国、敬业、诚信、友善
 **/

#include "ZwCreateSection.h"

#include <ntifs.h>

#include <ntddk.h>
#include <ntstrsafe.h>

#include "Support.h"
#include "lfqueue.h"

#pragma warning(disable : 4996) // warning C4996: 'function': was declared deprecated

typedef struct _PRIVATE_CACHE {
    HANDLE Section;
    PVOID BaseAddress;   // 用户空间映射，供 ZwUnmapViewOfSection 使用
    PVOID KernelAddress; // 内核空间映射，供 DISPATCH_LEVEL 访问
    PMDL Mdl;
    PVOID Opaque;
} PRIVATE_CACHE, *PPRIVATE_CACHE;

static LONG64* SynchronizationA = {}; // 正在填充的索引.
static LONG64* SynchronizationB = {}; // 已填充的索引.
static char* Descriptions = {};       // 每一段有固定长度.
static constexpr int DESCRIPTION_MAX_LENGTH = 0x100;
static constexpr int DESCRIPTION_MAX_COUNT = 0x1000;

static PRIVATE_CACHE PrivateCache[0x100];

static lfqueue* allocated = {};
static lfqueue* unallocated = {};

void*
operator new(SIZE_T size, void* ptr) noexcept
{
    UNREFERENCED_PARAMETER(size);
    return ptr;
}

static PVOID
ExampleZwMapViewOfSection(UNICODE_STRING* ObjectName, LARGE_INTEGER* MaximumSize)
{
    NTSTATUS Status = {};
    PVOID BaseAddress = {};

    PRIVATE_CACHE* Cache = CONTAINING_RECORD(unallocated->pop(), PRIVATE_CACHE, Opaque);
    if (Cache == NULL)
        return NULL;

    memset(Cache, 0, sizeof(*Cache));

    do {
        OBJECT_ATTRIBUTES ObjectAttributes = {};
        SIZE_T ViewSize = {};
        SECURITY_DESCRIPTOR sd = {};

#if 1 // 如果需要用户层也能打开这个Section,就需要加上允许用户访问的SD.
        RtlCreateSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
        RtlSetDaclSecurityDescriptor(&sd, TRUE, NULL, FALSE);
#endif

        InitializeObjectAttributes(&ObjectAttributes, ObjectName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, &sd);

        Status = ZwCreateSection(&Cache->Section, SECTION_MAP_READ | SECTION_MAP_WRITE, &ObjectAttributes, MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL);
        if (!NT_SUCCESS(Status))
            break;

        ViewSize = 0;

        Status = ZwMapViewOfSection(Cache->Section, NtCurrentProcess(), &Cache->BaseAddress, 0, 0, NULL, &ViewSize, ViewUnmap, 0, PAGE_READWRITE);
        if (!NT_SUCCESS(Status))
            break;

        Cache->Mdl = IoAllocateMdl(Cache->BaseAddress, (ULONG)ViewSize, FALSE, FALSE, NULL);

        if (!Cache->Mdl)
            break;

        /**
         * ZwMapViewOfSection返回的地址是处于用户地址空间内(0x0000000000000000 - 0x00007FFFFFFFFFFF)
         * 这导致即使使用MmProbeAndLockPages将内存页锁定在内存中,也不能让高IRQL的代码安全访问.
         * 所以这里还需要使用MmMapLockedPagesSpecifyCache将这块儿内存映射到内核地址空间内才行.
         **/
        __try {
            MmProbeAndLockPages(Cache->Mdl, KernelMode, IoModifyAccess);
            Cache->KernelAddress = MmMapLockedPagesSpecifyCache(Cache->Mdl, KernelMode, MmCached, NULL, 0, NormalPagePriority);
            if (Cache->KernelAddress == NULL)
                Status = STATUS_INSUFFICIENT_RESOURCES;
            else
                BaseAddress = Cache->KernelAddress;
        } __except (EXCEPTION_EXECUTE_HANDLER) {
            Status = STATUS_UNSUCCESSFUL;
        }

    } while (0);

    allocated->push(&Cache->Opaque);

    return BaseAddress;
}

void
ExampleZwUnmapViewOfSection(VOID)
{
    while (PVOID* Node = allocated->pop()) {
        PRIVATE_CACHE* Cache = CONTAINING_RECORD(Node, PRIVATE_CACHE, Opaque);

        if (Cache->KernelAddress)
            MmUnmapLockedPages(Cache->KernelAddress, Cache->Mdl);

        if (Cache->Mdl) {
            MmUnlockPages(Cache->Mdl);
            IoFreeMdl(Cache->Mdl);
        }

        if (Cache->BaseAddress)
            ZwUnmapViewOfSection(NtCurrentProcess(), Cache->BaseAddress);

        if (Cache->Section)
            ZwClose(Cache->Section);
    }

    ExFreePool(allocated);
    ExFreePool(unallocated);
}

static VOID
DeferredRoutine(_In_ KDPC* Dpc, _In_opt_ PVOID DeferredContext, _In_opt_ PVOID SystemArgument1, _In_opt_ PVOID SystemArgument2)
{
    UNREFERENCED_PARAMETER(Dpc);
    UNREFERENCED_PARAMETER(DeferredContext);
    UNREFERENCED_PARAMETER(SystemArgument1);
    UNREFERENCED_PARAMETER(SystemArgument2);

    LONG64 initialValue = InterlockedExchangeAdd64((LONG64*)SynchronizationA, 1);
    LONG64 Index = initialValue % DESCRIPTION_MAX_COUNT;

    char* s = Descriptions + (DESCRIPTION_MAX_LENGTH * Index);
    RtlStringCbPrintfA(s, DESCRIPTION_MAX_LENGTH, "Hello %lld", initialValue);

    InterlockedIncrement64((LONG64*)SynchronizationB);
}

static KTIMER kTimer;
static KDPC kDpc;

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    KeCancelTimer(&kTimer);
    KeFlushQueuedDpcs();

    ExampleZwUnmapViewOfSection();
}

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    PVOID a = ExAllocatePool(NonPagedPool, sizeof(lfqueue));
    PVOID b = ExAllocatePool(NonPagedPool, sizeof(lfqueue));

    allocated = new (a) lfqueue();
    unallocated = new (b) lfqueue();

    for (size_t i = 0; i < sizeof(PrivateCache) / sizeof(*PrivateCache); ++i) {
        auto* e = PrivateCache + i;
        unallocated->push(&e->Opaque);
    }

    KdBreakPoint();

    UNICODE_STRING ObjectName;
    LARGE_INTEGER MaximumSize;
    PVOID BaseAddress;

    MaximumSize.QuadPart = 0x1000;
    RtlInitUnicodeString(&ObjectName, L"\\BaseNamedObjects\\5997e7fa485a968be13ffbc93f2ec6d0");
    BaseAddress = ExampleZwMapViewOfSection(&ObjectName, &MaximumSize);
    if (BaseAddress == NULL)
        return STATUS_UNSUCCESSFUL;

    SynchronizationA = ((LONG64*)BaseAddress) + 0;
    SynchronizationB = ((LONG64*)BaseAddress) + 1;

    MaximumSize.QuadPart = 0x100000;
    RtlInitUnicodeString(&ObjectName, L"\\BaseNamedObjects\\578117d97cbb471f3e3e115330f0e614");
    BaseAddress = ExampleZwMapViewOfSection(&ObjectName, &MaximumSize);
    if (BaseAddress == NULL)
        return STATUS_UNSUCCESSFUL;

    Descriptions = (char*)BaseAddress;

    KeInitializeTimerEx(&kTimer, SynchronizationTimer); // 或 NotificationTimer
    KeInitializeDpc(&kDpc, DeferredRoutine, NULL);

    LARGE_INTEGER DueTime;
    DueTime.QuadPart = -100000;
    KeSetTimerEx(&kTimer, DueTime, 10, &kDpc);

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}
