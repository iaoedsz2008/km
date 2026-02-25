
/**
 * 富强、民主、文明、和谐
 * 自由、平等、公正、法治
 * 爱国、敬业、诚信、友善
 **/

#include <ntifs.h>

#include <ntddk.h>

#include <intrin.h>

#include "KeServiceDescriptorTable.h"
#include "Support.h"
#include "anylog.h"

#include "pshpack1.h"

#pragma warning(disable : 4127) // warning C4127: conditional expression is constant
#pragma warning(disable : 4189) //'identifier' : local variable is initialized but not referenced
#pragma warning(disable : 4214) // nonstandard extension used : bit field types other than int
#pragma warning(disable : 4390) // warning C4390: ';' : empty controlled statement found
#pragma warning(disable : 4505) // warning C4505: unreferenced local function has been removed
#pragma warning(disable : 4996) // warning C4996: 'function': was declared deprecated

#if 1

static constexpr size_t _KeServiceDescriptorTable_ = 0x0055A880; // 10.0.17763.316

#else

// FIXME: 云机专用偏移.

static constexpr size_t _KeServiceDescriptorTable_ = 0x00E018C0; // 10.0.19041.1348

#endif

typedef struct GDTR32_ {
    UINT16 limit; //
    UINT32 base;  //
} GDTR32, IDTR32;

static_assert(sizeof(GDTR32) == 0x06, "");

typedef struct GDTR64_ {
    UINT16 limit; //
    UINT64 base;  //
} GDTR64, IDTR64;

static_assert(sizeof(GDTR64) == 0x0A, "");

typedef struct IDT_GATE_DESCRIPTOR32_ {
    UINT_PTR OffsetA : 16;         //
    UINT_PTR SegmentSelector : 16; //
    UINT_PTR WhatA : 5;            //
    UINT_PTR ZeroA : 3;            //
    UINT_PTR GateType : 5;         //
    UINT_PTR DPL : 2;              //
    UINT_PTR P : 1;                //
    UINT_PTR OffsetB : 16;         //
} IDT_GATE_DESCRIPTOR32;

static_assert(sizeof(IDT_GATE_DESCRIPTOR32) == 8, "");

typedef struct IDT_GATE_DESCRIPTOR64_ {
    UINT_PTR OffsetA : 16;            //
    UINT_PTR SegmentSelector : 16;    //
    UINT_PTR InterruptStackTable : 3; //
    UINT_PTR ZeroA : 1;               //
    UINT_PTR ZeroB : 1;               //
    UINT_PTR ZeroC : 3;               //
    UINT_PTR GateType : 4;            //
    UINT_PTR ZeroD : 1;               //
    UINT_PTR DPL : 2;                 //
    UINT_PTR P : 1;                   //
    UINT_PTR OffsetB : 16;            //
    UINT_PTR OffsetC : 32;            //
    UINT_PTR WhatA : 32;              //
} IDT_GATE_DESCRIPTOR64;

static_assert(sizeof(IDT_GATE_DESCRIPTOR64) == 16, "");

typedef struct CALL_GATE_DESCRIPTOR32_ {
    UINT16 OffsetA;         //
    UINT16 SegmentSelector; //
    UINT8 ParamCount : 5;   //
    UINT8 WhatA : 3;        //
    UINT8 TypeA : 4;        // 0b01100
    UINT8 Zero : 1;         //
    UINT8 DPL : 2;          //
    UINT8 P : 1;            //
    UINT16 OffsetB;         //
} CALL_GATE_DESCRIPTOR32;

static_assert(sizeof(CALL_GATE_DESCRIPTOR32) == 8, "");

#include "poppack.h"

typedef struct RECORD32 {
    UINT32 EAX;
    UINT32 EBX;
    UINT32 ECX;
    UINT32 EDX;
    UINT32 EDI;
    UINT32 ESI;
    UINT32 EBP;
    UINT32 ESP;

    ULONG ProcessorIndex;
    UINT32 CR3;
} RECORD32;

typedef struct RECORD64 {
    UINT64 RAX;
    UINT64 RBX;
    UINT64 RCX;
    UINT64 RDX;
    UINT64 RDI;
    UINT64 RSI;
    UINT64 RBP;
    UINT64 RSP;
    UINT64 RIP;
    UINT64 R8;
    UINT64 R9;
    UINT64 R10;
    UINT64 R11;
    UINT64 R12;
    UINT64 R13;
    UINT64 R14;
    UINT64 R15;

    HANDLE ProcessId; // PsGetCurrentThread()->Cid.UniqueProcess
    HANDLE ThreadId;  // PsGetCurrentThread()->Cid.UniqueThread
    UINT64 CR3;
} RECORD64;

// 寄存器在shellcode中的排列方式.
typedef struct TMP32 {
    UINT32 RAX;
    UINT32 RBX;
    UINT32 RCX;
    UINT32 RDX;
    UINT32 RDI;
    UINT32 RSI;
    UINT32 RBP;
    UINT32 RSP;
} TMP32;

// 寄存器在shellcode中的排列方式.
typedef struct TMP64 {
    UINT64 RAX;
    UINT64 RBX;
    UINT64 RCX;
    UINT64 RDX;
    UINT64 R8;
    UINT64 R9;
    UINT64 R10;
    UINT64 R11;
    UINT64 R12;
    UINT64 R13;
    UINT64 R14;
    UINT64 R15;
    UINT64 RDI;
    UINT64 RSI;
    UINT64 RBP;
    UINT64 RSP;
} TMP64;

typedef struct HITContext {
    UINT_PTR Cr3;
    UINT_PTR Rip;
    UINT32 Vector;
} HITContext;

#if defined(_M_IX86) || defined(__i386__)

// ISR32.asm
static unsigned char Detour32[] = {
    // clang-format off
    0x60, 0xFF, 0x74, 0x24, 0x0C, 0x68, 0x11, 0x11, 0x11, 0x11, 0xE8, 0x22, 0x22, 0x22, 0x22, 0x61,
    0xE9, 0x33, 0x33, 0x33, 0x33, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    // clang-format on
};

typedef struct ISR32 {
    unsigned char Header[sizeof(Detour32)];

    enum {
        offsetType = 0x06,
        offsetCallback = 0x0B,
        offsetProcedure = 0x11,
    };

    FORCEINLINE void
    initialize(UINT32 Vector, void(NTAPI* Callback)(UINT32, UINT32), UINT32 Procedure)
    {
        memcpy(Header, Detour32, sizeof(Detour32));

        *(UINT32*)(Header + offsetType) = Vector;
        *(UINT32*)(Header + offsetCallback) = (UINT32)Callback - ((UINT32)Header + offsetCallback + 4);    // relative address.
        *(UINT32*)(Header + offsetProcedure) = (UINT32)Procedure - ((UINT32)Header + offsetProcedure + 4); // relative address.
    }

} ISR32;

#endif

// ISR64.asm
static unsigned char Detour64[] = {
    // clang-format off
    0x50, 0x51, 0x52, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 0x53, 0x56, 0xB9, 0x11, 0x11, 0x11,
    0x11, 0x48, 0x8D, 0x54, 0x24, 0x40, 0x48, 0x89, 0xE6, 0x48, 0x81, 0xEC, 0x80, 0x00, 0x00, 0x00,
    0x48, 0x83, 0xE4, 0xF0, 0xFF, 0x15, 0x16, 0x00, 0x00, 0x00, 0x48, 0x89, 0xF4, 0x5E, 0x41, 0x5B,
    0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x58, 0xFF, 0x25, 0x09, 0x00, 0x00, 0x00, 0x90,
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
    // clang-format on
};

typedef struct ISR64 {
    unsigned char Header[sizeof(Detour64)];

    enum {
        offsetType = 0x0D,
        offsetCallback = 0x40,
        offsetProcedure = 0x48,
    };

    FORCEINLINE void
    initialize(UINT32 Vector, void(NTAPI* Callback)(UINT32, UINT64), UINT64 Procedure)
    {
        memcpy(Header, Detour64, sizeof(Detour64));

        *(UINT32*)(Header + offsetType) = Vector;
        *(VOID**)(Header + offsetCallback) = Callback;
        *(UINT64*)(Header + offsetProcedure) = Procedure;
    }

} ISR64;

typedef struct KERNELENTRY32 {
    unsigned char Header[0x20];
} KERNELENTRY32;

typedef struct KERNELENTRY64 {
    unsigned char Header[0x40];
} KERNELENTRY64;

typedef struct DebugSession {
    UINT64 Debugger;
    UINT64 Debuggee;
} DebugSession;

static DebugSession DebuggingSessions[1];
static HANDLE ContextPID = NULL;
static UINT_PTR ContextCR3 = 0;

static_assert(sizeof(UINT_PTR) == sizeof(void*), "");
static_assert(sizeof(ULONG_PTR) == sizeof(void*), "");

#if defined(_M_AMD64) || defined(__x86_64__)
static UINT64* ia32_lstar = NULL;
static UINT64* ia32_cstar = NULL;
static IDTR64* BackupIdts = NULL;
static IDTR64* MyIdts = NULL;
#endif

#if defined(_M_IX86) || defined(__i386__)
static UINT64* ia32_sysenter_cs = NULL;
static UINT64* ia32_sysenter_esp = NULL;
static UINT64* ia32_sysenter_eip = NULL;
static IDTR32* BackupIdts = NULL;
static IDTR32* MyIdts = NULL;

static UINT_PTR _KiFastCallEntry = NULL;
static UINT_PTR _KiFastCallEntryCommon = NULL;
#endif

#if defined(_M_AMD64) || defined(__x86_64__)

static const WCHAR*
SyscallId(UINT16 ID)
{
    switch (ID) {
#define XX(__no__, __api__) \
    case __no__:            \
        return L## #__api__;
#include "10.0.17763.316.def"
    }

    return L"?";
}

static void NTAPI
HandleIDT(UINT32 Vector, UINT_PTR StackFrame)
{
    UNREFERENCED_PARAMETER(Vector);
    UNREFERENCED_PARAMETER(StackFrame);

    UINT64 ExceptionCode = 0;

    // Skip Exception Error Code
    switch (Vector) {
    case 0x08: // Double Fault Exception (#DF)
    case 0x0A: // Invalid TSS Exception (#TS)
    case 0x0B: // Segment Not Present (#NP)
    case 0x0C: // Stack Fault Exception (#SS)
    case 0x0D: // General Protection Exception (#GP)
    case 0x0E: // Page-Fault Exception (#PF)
    case 0x11: // Alignment Check Exception (#AC)
    case 0x15: // Control Protection Exception (#CP)
        ExceptionCode = *(UINT64*)(StackFrame + 0x00);
        StackFrame += 0x08;
        break;
    }

    const WCHAR* Description = L"User Defined Interrupt";

    switch (Vector) {
    case 0x00:
        Description = L"Divide Error";
        break;
    case 0x01:
        Description = L"Debug Exception";
        break;
    case 0x02:
        Description = L"NMI Interrupt";
        break;
    case 0x03:
        Description = L"Breakpoint";
        break;
    case 0x04:
        Description = L"Overflow";
        break;
    case 0x05:
        Description = L"BOUND Range Exceeded";
        break;
    case 0x06:
        Description = L"Invalid Opcode";
        break;
    case 0x07:
        Description = L"Device Not Available";
        break;
    case 0x08:
        Description = L"Double Fault";
        break;
    case 0x09:
        Description = L"Coprocessor Segment Overrun";
        break;
    case 0x0A:
        Description = L"Invalid TSS";
        break;
    case 0x0B:
        Description = L"Segment Not Present";
        break;
    case 0x0C:
        Description = L"Stack-Segment Fault";
        break;
    case 0x0D:
        Description = L"General Protection";
        break;
    case 0x0E:
        Description = L"Page Fault";
        break;
    case 0x0F:
        Description = L"Intel reserved";
        break;
    case 0x10:
        Description = L"x87 FPU Floating-Point Error";
        break;
    case 0x11:
        Description = L"Alignment Check";
        break;
    case 0x12:
        Description = L"Machine Check";
        break;
    case 0x13:
        Description = L"SIMD Floating-Point Exception";
        break;
    case 0x14:
        Description = L"Virtualization Exception";
        break;
    case 0x15:
        Description = L"Control Protection Exception";
        break;
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
        Description = L"Intel reserved";
        break;
    }

    UINT64 Rip = *(UINT64*)(StackFrame + 0x00);
    UINT16 Cs = *(UINT16*)(StackFrame + 0x08);
    UINT64 Rflags = *(UINT64*)(StackFrame + 0x10);

    if ((Cs & 3) == 3) {
        UINT64 Rsp = *(UINT64*)(StackFrame + 0x18);
        UINT64 Ss = *(UINT64*)(StackFrame + 0x20);

        UNREFERENCED_PARAMETER(Rsp);
        UNREFERENCED_PARAMETER(Ss);
    }

    if (Rip > MmUserProbeAddress)
        return;

    anylogPrintfW(L"INT 0x%02X(%s), CR3=0x%016llX, RIP=0x%016llX", Vector, Description, __readcr3(), Rip);
}

void
HandleSYSCALL(TMP64* Context)
{
    UINT16 AX = (UINT16)Context->RAX;

    if (AX >= 0x1000)
        return;

    ULONG64 RIP = *(&(Context->RSP) + 2); // FIXME: trick.

    anylogUpdate(PsGetCurrentProcessId(), __readcr3());

    anylogPrintfW(L"SYSCALL 0x%02X(%s), CR3=0x%016llX, RIP=0x%016llX", AX, SyscallId(AX), __readcr3(), RIP);
}

#endif

#if defined(_M_IX86) || defined(__i386__)

static void NTAPI
HandleIDT(UINT32 Vector, UINT_PTR StackFrame)
{
    UNREFERENCED_PARAMETER(Vector);
    UNREFERENCED_PARAMETER(StackFrame);

    if (ContextCR3 != __readcr3())
        return;

    UINT32 ExceptionCode = 0;

    // Skip Exception Error Code
    switch (Vector) {
    case 0x08: // Double Fault Exception (#DF)
    case 0x0A: // Invalid TSS Exception (#TS)
    case 0x0B: // Segment Not Present (#NP)
    case 0x0C: // Stack Fault Exception (#SS)
    case 0x0D: // General Protection Exception (#GP)
    case 0x0E: // Page-Fault Exception (#PF)
    case 0x11: // Alignment Check Exception (#AC)
    case 0x15: // Control Protection Exception (#CP)
        ExceptionCode = *(UINT32*)(StackFrame + 0x00);
        StackFrame += 0x04;
        break;
    }

    UINT32 Eip = *(UINT32*)(StackFrame + 0x00);
    UINT16 Cs = *(UINT16*)(StackFrame + 0x04);
    UINT32 Eflags = *(UINT32*)(StackFrame + 0x08);

    if ((Cs & 3) == 3) {
        UINT32 Esp = *(UINT32*)(StackFrame + 0x0C);
        UINT32 Ss = *(UINT32*)(StackFrame + 0x10);

        UNREFERENCED_PARAMETER(Esp);
        UNREFERENCED_PARAMETER(Ss);
    }

    if (Eip > MmUserProbeAddress)
        return;

    ULONG i = (ULONG)InterlockedExchangeAdd((LONG*)&Current.High1Time, 1) % MAX_RECORDS;
    ContextBuckets[i].Rip = Eip;
    ContextBuckets[i].Vector = Vector;
    ContextBuckets[i].Cr3 = ContextCR3; // finished.
}

void
HandleSYSENTER()
{
    ULONG CurrentProcessorIndex = KeGetCurrentProcessorIndex();
}

#endif

// clang-format off

static UINT8 shellcode32[] = {
    0xB9, 0x23, 0x00, 0x00, 0x00, 0x6A, 0x30, 0x0F, 0xA1, 0x8E, 0xD9, 0x8E, 0xC1, 0x33, 0xC9, 0x8E, // KiFastCallEntry
    0xE9, 0x64, 0x8B, 0x0D, 0x40, 0x00, 0x00, 0x00, 0x8B, 0x61, 0x04, 0x6A, 0x23, 0x52, 0x9C,       // KiFastCallEntry

    0x50,
    0x53,
    0x51,
    0x52,
    0x57,
    0x56,
    0x55,
    0x89, 0xE6,
    0x83, 0xEC, 0x20,
    0x83, 0xE4, 0xF0,
    0xE8, 0x88, 0x88, 0x88, 0x88,
    0x89, 0xF4,
    0x5D,
    0x5E,
    0x5F,
    0x5A,
    0x59,
    0x5B,
    0x58,
    0xE9, 0x88, 0x88, 0x88, 0x88,
};

static UINT8 shellcode64[] = {
    0x0F, 0x01, 0xF8, 0x65, 0x48, 0x89, 0x24, 0x25, 0x10, 0x00, 0x00, 0x00, 0x65, 0x48, 0x8B, 0x24, // KiSystemCall64
    0x25, 0xA8, 0x01, 0x00, 0x00, 0x6A, 0x2B, 0x65, 0xFF, 0x34, 0x25, 0x10, 0x00, 0x00, 0x00, 0x41, // KiSystemCall64
    0x53, 0x6A, 0x33, 0x51, 0x49, 0x8B, 0xCA,                                                       // KiSystemCall64

    // launchpad64.asm
    0x9C, 0x54, 0x55, 0x56, 0x57, 0x41, 0x57, 0x41, 0x56, 0x41, 0x55, 0x41, 0x54, 0x41, 0x53, 0x41,
    0x52, 0x41, 0x51, 0x41, 0x50, 0x52, 0x51, 0x53, 0x50, 0x48, 0x89, 0xE6, 0x48, 0x89, 0xE1, 0x48,
    0x83, 0xEC, 0x20, 0x48, 0x83, 0xE4, 0xF0, 0xFF, 0x15, 0x22, 0x00, 0x00, 0x00, 0x48, 0x89, 0xF4,
    0x58, 0x5B, 0x59, 0x5A, 0x41, 0x58, 0x41, 0x59, 0x41, 0x5A, 0x41, 0x5B, 0x41, 0x5C, 0x41, 0x5D,
    0x41, 0x5E, 0x41, 0x5F, 0x5F, 0x5E, 0x5D, 0x5C, 0x9D, 0xFF, 0x25, 0x08, 0x00, 0x00, 0x00, 0x88,
    0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88
};

// clang-format on

static ULONG_PTR
AttachSyscall(_In_ ULONG_PTR Argument)
{
    UNREFERENCED_PARAMETER(Argument);

    ULONG CurrentProcessorIndex = KeGetCurrentProcessorIndex();

#if defined(_M_AMD64) || defined(__x86_64__)

    UINT64 ia32_time_stamp_counter = __readmsr(0x00000010 /*IA32_TIME_STAMP_COUNTER*/);
    UINT64 ia32_apic_base = __readmsr(0x0000001B /*IA32_APIC_BASE*/);
    UINT64 ia32_feature_control = __readmsr(0x0000003A /*IA32_FEATURE_CONTROL*/);
    UINT64 ia32_tsc_adjust = __readmsr(0x0000003B /*IA32_TSC_ADJUST*/);
    UINT64 ia32_smm_monitor_ctl = __readmsr(0x0000009B /*IA32_SMM_MONITOR_CTL*/);
    UINT64 ia32_smbase = __readmsr(0x0000009E /*IA32_SMBASE*/);
    UINT64 ia32_core_capabilities = __readmsr(0x000000CF /*IA32_CORE_CAPABILITIES*/);
    UINT64 ia32_arch_capabilities = __readmsr(0x0000010A /*IA32_ARCH_CAPABILITIES*/);
    UINT64 ia32_debugctl = __readmsr(0x000001D9 /*IA32_DEBUGCTL*/);
    UINT64 ia32_efer = __readmsr(0xC0000080 /*IA32_EFER*/);
    UINT64 ia32_star = __readmsr(0xC0000081 /*IA32_STAR*/);
    ia32_lstar[CurrentProcessorIndex] = __readmsr(0xC0000082 /*IA32_LSTAR*/);
    ia32_cstar[CurrentProcessorIndex] = __readmsr(0xC0000083 /*IA32_CSTAR*/);
    UINT64 ia32_fmask = __readmsr(0xC0000084 /*IA32_FMASK*/);
    UINT64 ia32_fs_base = __readmsr(0xC0000100 /*IA32_FS_BASE*/);
    UINT64 ia32_gs_base = __readmsr(0xC0000101 /*IA32_GS_BASE*/);
    UINT64 ia32_kernel_gs_base = __readmsr(0xC0000102 /*IA32_KERNEL_GS_BASE*/);

    UINT64 rip = ia32_lstar[CurrentProcessorIndex];
    UINT16 cs = (ia32_star >> 0x20) & 0xFFFF;
    UINT16 ss = cs + 0x08;

    UINT8 ia32_efer_sce = (ia32_efer >> 0x00) & 1; // R/W
    UINT8 ia32_efer_lme = (ia32_efer >> 0x08) & 1; // R/W
    UINT8 ia32_efer_lma = (ia32_efer >> 0x0A) & 1; // R
    UINT8 ia32_efer_nxe = (ia32_efer >> 0x0B) & 1; // R/W

    UINT8* syscall = (UINT8*)ExAllocatePool(NonPagedPoolExecute, 0x1000);

    memcpy(syscall, shellcode64, sizeof(shellcode64));

    UINT8* RelA = syscall + 0x27 + 0x4F;
    UINT8* RelB = syscall + 0x27 + 0x57;

    *(UINT_PTR*)(RelA) = (UINT_PTR)&HandleSYSCALL;
    *(UINT_PTR*)(RelB) = rip + 0x27;

    __writemsr(0xC0000082 /*IA32_LSTAR*/, (UINT64)syscall);

#endif

#if defined(_M_IX86) || defined(__i386__)

    ia32_sysenter_cs[CurrentProcessorIndex] = __readmsr(0x0174 /*IA32_SYSENTER_CS*/);
    ia32_sysenter_esp[CurrentProcessorIndex] = __readmsr(0x0175 /*IA32_SYSENTER_ESP*/);
    ia32_sysenter_eip[CurrentProcessorIndex] = __readmsr(0x0176 /*IA32_SYSENTER_EIP*/);

    UINT8* sysenter = (UINT8*)ExAllocatePool(NonPagedPoolExecute, 0x1000);

    memcpy(sysenter, shellcode32, sizeof(shellcode32));

    UINT8* RelA = sysenter + 0x2E;
    UINT8* RelB = sysenter + 0x3C;

    *(UINT32*)(RelA + 0x01) = (UINT32)((UINT_PTR)&HandleSYSENTER - (UINT_PTR)RelA - 5);
    *(UINT32*)(RelB + 0x01) = (UINT32)((UINT_PTR)_KiFastCallEntryCommon - (UINT_PTR)RelB - 5); // TODO: KiFastCallEntryCommon符号在windows7中被隐藏.

    __writemsr(0x0176 /*IA32_SYSENTER_EIP*/, (UINT64)sysenter);
#endif

    return 0;
}

static ULONG_PTR
DetachSyscall(_In_ ULONG_PTR Argument)
{
    UNREFERENCED_PARAMETER(Argument);

    ULONG CurrentProcessorIndex = KeGetCurrentProcessorIndex();

#if defined(_M_AMD64) || defined(__x86_64__)
    __writemsr(0xC0000082 /*IA32_LSTAR*/, ia32_lstar[CurrentProcessorIndex]);
    __writemsr(0xC0000083 /*IA32_CSTAR*/, ia32_cstar[CurrentProcessorIndex]);
#endif

#if defined(_M_IX86) || defined(__i386__)
    __writemsr(0x0176 /*IA32_SYSENTER_EIP*/, ia32_sysenter_eip[CurrentProcessorIndex]);
#endif

    return 0;
}

static ULONG_PTR
AttachIDT(_In_ ULONG_PTR Argument)
{
    UNREFERENCED_PARAMETER(Argument);

    ULONG CurrentProcessorIndex = KeGetCurrentProcessorIndex();

    PsGetCurrentProcessId();
    PsGetCurrentThreadId();

    __sidt(&BackupIdts[CurrentProcessorIndex]);

#if defined(_M_IX86) || defined(__i386__)
    IDT_GATE_DESCRIPTOR32* idt = (IDT_GATE_DESCRIPTOR32*)ExAllocatePool(NonPagedPool, 0x1000);
    ISR32* procedures = (ISR32*)ExAllocatePool(NonPagedPoolExecute, sizeof(ISR32) * 0x100);

    memcpy(idt, (PVOID)BackupIdts[CurrentProcessorIndex].base, 0x800);

    MyIdts[CurrentProcessorIndex].base = (UINT32)idt;
    MyIdts[CurrentProcessorIndex].limit = BackupIdts[CurrentProcessorIndex].limit;
#endif

#if defined(_M_AMD64) || defined(__x86_64__)
    IDT_GATE_DESCRIPTOR64* idt = (IDT_GATE_DESCRIPTOR64*)ExAllocatePool(NonPagedPool, 0x1000);
    ISR64* procedures = (ISR64*)ExAllocatePool(NonPagedPoolExecute, sizeof(ISR64) * 0x100);

    memcpy(idt, (PVOID)BackupIdts[CurrentProcessorIndex].base, 0x1000);

    MyIdts[CurrentProcessorIndex].base = (UINT64)idt;
    MyIdts[CurrentProcessorIndex].limit = BackupIdts[CurrentProcessorIndex].limit;
#endif

    DbgPrint("CurrentProcessorIndex:%d, procedures: 0x%p\n", CurrentProcessorIndex, procedures);

    KdBreakPoint();

#if defined(_M_IX86) || defined(__i386__)
    for (UINT16 i = 0; i < 0x100; ++i) {
        IDT_GATE_DESCRIPTOR32* gate = idt + i;
        UINT_PTR procedure = (UINT_PTR)(gate->OffsetA | (gate->OffsetB << 16));

        UINT_PTR handler = (UINT_PTR)(procedures + i);
        procedures[i].initialize(i, HandleIDT, procedure);
        gate->OffsetA = handler;
        gate->OffsetB = handler >> 16;

        switch (gate->GateType) {
        case 0x05:
            DbgPrint("Task Gate: 0x%p\n", procedure);
            break;
        case 0x06:
            DbgPrint("Interrupt Gate(16bits): 0x%p\n", procedure);
            break;
        case 0x0E:
            DbgPrint("Interrupt Gate(32bits): 0x%p\n", procedure);
            break;
        case 0x07:
            DbgPrint("Trap Gate(16bits): 0x%p\n", procedure);
            break;
        case 0x0F:
            DbgPrint("Trap Gate(32bits): 0x%p\n", procedure);
            break;
        default:
            DbgPrint("0x%p\n", procedure);
            break;
        }
    }
#endif

#if defined(_M_AMD64) || defined(__x86_64__)
    for (UINT16 i = 0; i < 0x100; ++i) {
        IDT_GATE_DESCRIPTOR64* gate = idt + i;
        UINT_PTR procedure = (UINT_PTR)(gate->OffsetA | (gate->OffsetB << 16) | (gate->OffsetC << 32));
        UINT_PTR handler = (UINT_PTR)(procedures + i);
        procedures[i].initialize(i, HandleIDT, procedure);
        gate->OffsetA = handler;
        gate->OffsetB = handler >> 16;
        gate->OffsetC = handler >> 32;

        switch (gate->GateType) {
        case 0x05:
            DbgPrint("Task Gate: 0x%p\n", procedure);
            break;
        case 0x06:
            DbgPrint("Interrupt Gate(16bits): 0x%p\n", procedure);
            break;
        case 0x0E:
            DbgPrint("Interrupt Gate(32bits): 0x%p\n", procedure);
            break;
        case 0x07:
            DbgPrint("Trap Gate(16bits): 0x%p\n", procedure);
            break;
        case 0x0F:
            DbgPrint("Trap Gate(32bits): 0x%p\n", procedure);
            break;
        default:
            DbgPrint("0x%p\n", procedure);
            break;
        }
    }
#endif

    MmUserProbeAddress;
    MmHighestUserAddress;

    KdBreakPoint();
    __lidt(&MyIdts[CurrentProcessorIndex]);

    return 0;
}

static ULONG_PTR
DetachIDT(_In_ ULONG_PTR Argument)
{
    UNREFERENCED_PARAMETER(Argument);

    ULONG CurrentProcessorIndex = KeGetCurrentProcessorIndex();

    __lidt(&BackupIdts[CurrentProcessorIndex]);

    return 0;
}

static VOID
_CreateProcessNotifyRoutine(_In_ HANDLE ParentId, _In_ HANDLE ProcessId, _In_ BOOLEAN Create)
{
    UNREFERENCED_PARAMETER(ParentId);
    UNREFERENCED_PARAMETER(ProcessId);
    UNREFERENCED_PARAMETER(Create);

    PUNICODE_STRING ProcessName;

    if (!Create)
        return;

    PEPROCESS Process;
    if (!NT_SUCCESS(PsLookupProcessByProcessId(ProcessId, &Process)))
        return;

    do {

        if (!NT_SUCCESS(SeLocateProcessImageName(Process, &ProcessName)))
            break;

        if (ProcessName->Length == 0)
            break;

        if (wcsstr(ProcessName->Buffer, L"notepad.exe") == NULL)
            break;

        ContextPID = ProcessId;
#if defined(_M_AMD64) || defined(__x86_64__)
        UINT64 DirectoryTableBase = *(UINT64*)((UINT8*)Process + 0x28);
#endif
#if defined(_M_IX86) || defined(__i386__)
        UINT32 DirectoryTableBase = *(UINT32*)((UINT8*)Process + 0x18);
#endif
        ContextCR3 = DirectoryTableBase;
    } while (0);

    ObDereferenceObject(Process);
}

VOID
_LoadImageNotifyRoutine(_In_opt_ PUNICODE_STRING FullImageName, _In_ HANDLE ProcessId, _In_ PIMAGE_INFO ImageInfo)
{
    UNREFERENCED_PARAMETER(ImageInfo);

    if (FullImageName) {
        anylogPrintfW(L"LoadImageNotifyRoutine PID: %p, %s", ProcessId, FullImageName->Buffer);
    } else {
        anylogPrintfW(L"LoadImageNotifyRoutine PID: %p, (null name)", ProcessId);
    }
}

void
HelloKeServiceDescriptorTable(UINT8* DllBase)
{
    UINT8* KeServiceDescriptorTable = *(UINT8**)(DllBase + _KeServiceDescriptorTable_);
    UNREFERENCED_PARAMETER(KeServiceDescriptorTable);

    KdBreakPoint();

#if defined(_M_AMD64) || defined(__x86_64__)

    ia32_lstar = (UINT_PTR*)ExAllocatePool(NonPagedPoolExecute, 0x1000);
    ia32_cstar = (UINT_PTR*)ExAllocatePool(NonPagedPoolExecute, 0x1000);

    // MmMapViewInSystemSpace();//System Ptes区域
    // MmAllocateContiguousMemory();//System Ptes区域
    // IoAllocateMdl();//System Ptes区域
    //
    // MmLockPagableCodeSection();
    // MmLockPagableSectionByHandle();
    // MmMapViewInSystemSpace();
    // MmMapViewOfSection();
    // __segmentlimit();

    BackupIdts = (IDTR64*)ExAllocatePool(NonPagedPool, sizeof(IDTR64) * 0x100);
    MyIdts = (IDTR64*)ExAllocatePool(NonPagedPool, sizeof(IDTR64) * 0x100);

#endif

#if defined(_M_IX86) || defined(__i386__)

    _KiFastCallEntry = (UINT_PTR)(DllBase + _KiFastCallEntry_);
    _KiFastCallEntryCommon = (UINT_PTR)(DllBase + _KiFastCallEntryCommon_);

    ia32_sysenter_cs = (UINT64*)ExAllocatePool(NonPagedPool, 0x1000);
    ia32_sysenter_esp = (UINT64*)ExAllocatePool(NonPagedPool, 0x1000);
    ia32_sysenter_eip = (UINT64*)ExAllocatePool(NonPagedPool, 0x1000);

    BackupIdts = (IDTR32*)ExAllocatePool(NonPagedPool, sizeof(IDTR32) * 0x100);
    MyIdts = (IDTR32*)ExAllocatePool(NonPagedPool, sizeof(IDTR32) * 0x100);

#endif

    KeIpiGenericCall(AttachSyscall, 0);
    KeIpiGenericCall(AttachIDT, 0);

    PsSetCreateProcessNotifyRoutine(_CreateProcessNotifyRoutine, FALSE);
    PsSetLoadImageNotifyRoutine(_LoadImageNotifyRoutine);
}

void
GoodbyeKeServiceDescriptorTable(UINT8* DllBase)
{
    UNREFERENCED_PARAMETER(DllBase);

    PsRemoveLoadImageNotifyRoutine(_LoadImageNotifyRoutine);
    PsSetCreateProcessNotifyRoutine(_CreateProcessNotifyRoutine, TRUE);

    KeIpiGenericCall(DetachSyscall, 0);
    KeIpiGenericCall(DetachIDT, 0);

    ExFreePool(MyIdts);
    ExFreePool(BackupIdts);
}

EXTERN_C VOID
DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    GoodbyeKeServiceDescriptorTable(NULL);

    anylogCleanup();
}

typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;
    LIST_ENTRY HashLinks;
    ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

EXTERN_C NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

#if 1 // Bypass /INTEGRITYCHECK linker option

#if defined(_M_AMD64) || defined(__x86_64__)
    ULONG* Flags = (ULONG*)(((SIZE_T)DriverObject->DriverSection) + 0x68);
#endif

#if defined(_M_IX86) || defined(__i386__)
    ULONG* Flags = (ULONG*)(((SIZE_T)DriverObject->DriverSection) + 0x34);
#endif

    *Flags |= 0x20;

#endif

    UINT8* DllBase = NULL;

    KdBreakPoint();

    const LIST_ENTRY* head = &((LDR_DATA_TABLE_ENTRY*)DriverObject->DriverSection)->InLoadOrderLinks;
    for (const LIST_ENTRY* item = head->Flink; item != head; item = item->Flink) {
        LDR_DATA_TABLE_ENTRY* ldr = CONTAINING_RECORD(item, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

        if ((UINT8*)&PsGetVersion < (UINT8*)ldr->DllBase)
            continue;

        if ((UINT8*)&PsGetVersion >= (UINT8*)ldr->DllBase + ldr->SizeOfImage)
            continue;

        DllBase = (UINT8*)ldr->DllBase;
        break;
    }

    if (DllBase == NULL)
        return STATUS_NOT_FOUND;

    anylogInit();

    DriverObject->DriverUnload = DriverUnload;

    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = NULL;

    HelloKeServiceDescriptorTable(DllBase);

    return STATUS_SUCCESS;
}
