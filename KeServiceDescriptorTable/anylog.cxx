
/**
 * 富强、民主、文明、和谐
 * 自由、平等、公正、法治
 * 爱国、敬业、诚信、友善
 **/

#include <ntifs.h> //SECURITY_DESCRIPTOR

#include <ntddk.h>

#include <intrin.h>
#include <ntstrsafe.h>
#include <stdarg.h>

#include "anylog.h"

#include "Support.h"
#include "lfqueue.h"

typedef struct _PRIVATE_CACHE {
    HANDLE Section;
    PVOID BaseAddress;   // 用户空间映射，供 ZwUnmapViewOfSection 使用
    PVOID KernelAddress; // 内核空间映射，供 DISPATCH_LEVEL 访问
    PMDL Mdl;
    PVOID Opaque;
} PRIVATE_CACHE, *PPRIVATE_CACHE;

static LONG64* SynchronizationA = {}; // 正在填充的索引.
static LONG64* SynchronizationB = {}; // 已填充的索引.
static ULONG64* PIDA = {};            // PID A
static ULONG64* PIDB = {};            // PID B
static ULONG64* CR3A = {};            //
static ULONG64* CR3B = {};            //
static WCHAR* Descriptions = {};      // 每一段有固定长度.

static PRIVATE_CACHE PrivateCache[0x100];

static lfqueue* allocated = {};
static lfqueue* unallocated = {};

#pragma warning(disable : 4996) // warning C4996: 'function': was declared deprecated

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

void
anylogPrintfW(const WCHAR* pszFormat, ...)
{
    do {
        if (*CR3A == __readcr3())
            break;

        if (*CR3B == __readcr3())
            break;

        return;
    } while (0);

    LONG64 initialValue = InterlockedExchangeAdd64((LONG64*)SynchronizationA, 1);
    LONG64 i = initialValue % DESCRIPTION_MAX_COUNT;

    WCHAR* s = Descriptions + (DESCRIPTION_MAX_LENGTH * i);

    va_list args;
    va_start(args, pszFormat);
    RtlStringCbVPrintfW(s, DESCRIPTION_MAX_LENGTH, pszFormat, args);
    va_end(args);

    InterlockedIncrement64((LONG64*)SynchronizationB);
}

NTSTATUS
anylogInit()
{
    PVOID a = ExAllocatePool(NonPagedPool, sizeof(lfqueue));
    PVOID b = ExAllocatePool(NonPagedPool, sizeof(lfqueue));

    allocated = new (a) lfqueue();
    unallocated = new (b) lfqueue();

    for (size_t i = 0; i < sizeof(PrivateCache) / sizeof(*PrivateCache); ++i) {
        auto* e = PrivateCache + i;
        unallocated->push(&e->Opaque);
    }

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
    PIDA = ((ULONG64*)BaseAddress) + 2;
    PIDB = ((ULONG64*)BaseAddress) + 3;
    CR3A = ((ULONG64*)BaseAddress) + 4;
    CR3B = ((ULONG64*)BaseAddress) + 5;

    MaximumSize.QuadPart = (DESCRIPTION_MAX_COUNT * DESCRIPTION_MAX_LENGTH * sizeof(WCHAR));
    RtlInitUnicodeString(&ObjectName, L"\\BaseNamedObjects\\578117d97cbb471f3e3e115330f0e614");
    BaseAddress = ExampleZwMapViewOfSection(&ObjectName, &MaximumSize);
    if (BaseAddress == NULL)
        return STATUS_UNSUCCESSFUL;

    Descriptions = (WCHAR*)BaseAddress;

    return STATUS_SUCCESS;
}

NTSTATUS
anylogCleanup()
{
    ExampleZwUnmapViewOfSection();

    return STATUS_SUCCESS;
}

void
anylogUpdate(HANDLE Pid, ULONG64 CR3)
{
    // TODO: 可以监测到PID为0的进程触发.

    if (*PIDA && *PIDA == (ULONG64)Pid)
        *CR3A = CR3;

    if (*PIDB && *PIDB == (ULONG64)Pid)
        *CR3B = CR3;
}
