
/**
 * 用户为本，科技向善
 **/

#include "GenuineIntel.h"

#include "kmdf.h"

int
GenuineIntel::initialize()
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    __asm_cpuid(1, &eax, &ebx, &ecx, &edx);

    if (ecx & 0x00000001) //
        ;

    if (ecx & 0x00000002) //
        ;

    if (ecx & 0x00000004) //
        ;

    if (ecx & 0x00000008) //
        ;

    if (ecx & 0x00000010) //
        ;

    if ((ecx & 0x00000020) == 0) // If 1, supports the Virtual Machine Extensions.
        return -1;

    if (ecx & 0x00000040) // If 1, supports Safer Mode Extensions.
        ;

    if (ecx & 0x00000080) //
        ;

    if (ecx & 0x00000100) //
        ;

    if (ecx & 0x00000200) //
        ;

    if (ecx & 0x00000400) //
        ;

    if (ecx & 0x00000800) // If 1, supports IA32_DEBUG_INTERFACE MSR for silicon debug.
        ;

    if (ecx & 0x00080000) // If 1, supports SSE4.1.
        ;

    if (ecx & 0x00100000) // If 1, supports SSE4.2.
        ;

    if (ecx & 0x00200000) // If 1, supports x2APIC feature.
        ;

    if (ecx & 0x00400000) // If 1, supports MOVBE instruction.
        ;

    if (ecx & 0x00800000) // If 1, supports the POPCNT instruction.
        ;

    if (ecx & 0x10000000) // If 1, supports the AVX instruction extensions.
        ;

    if (ecx & 0x40000000) // If 1, supports RDRAND instruction.
        ;

    __asm_cpuid(0x00000003, &eax, &ebx, &ecx, &edx); // Processor Serial Number

    __asm_cpuid_ex(0x00000007, 0x00000000, &eax, &ebx, &ecx, &edx); // Structured Extended Feature Flags Main Sub-Leaf

    if (ebx & 0x00000001) // If 1, supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE.
        ;
    if (ebx & 0x00000002) // If 1, the IA32_TSC_ADJUST MSR is supported.
        ;
    if (ebx & 0x00000004) // If 1, supports Intel® Software Guard Extensions (Intel® SGX Extensions).
        ;
    if (ebx & 0x00000008) // If 1, supports the BMI1 instructions.
        ;
    if (ebx & 0x00000010) // If 1, supports the Hardware Lock Elision instruction set.
        ;
    if (ebx & 0x00000020) // If 1, supports Intel® Advanced Vector Extensions 2 (Intel® AVX2).
        ;
    if (ebx & 0x00000040) //
        ;
    if (ebx & 0x00000080) // If 1, supports Supervisor-Mode Execution Prevention.
        ;
    if (ebx & 0x00000100) // If 1, supports the BMI2 instructions.
        ;
    if (ebx & 0x00000200) //
        ;
    if (ebx & 0x00000400) // If 1, supports INVPCID instruction for system software that manages process-context identifiers.
        ;
    if (ebx & 0x00000800) // If 1, supports the Restricted Transactional Memory instruction set.
        ;
    if (ebx & 0x00001000) // If 1, supports Intel® Resource Director Technology (Intel® RDT) Monitoring capability.
        ;
    if (ebx & 0x00002000) //
        ;
    if (ebx & 0x00004000) // If 1, supports Intel® Memory Protection Extensions.
        ;
    if (ebx & 0x00008000) //
        ;
    if (ebx & 0x00010000) // If 1, supports the AVX512F instructions.
        ;
    if (ebx & 0x00020000) // If 1, supports the AVX512DQ instructions.
        ;
    if (ebx & 0x00040000) // If 1, supports the RDSEED instruction.
        ;
    if (ebx & 0x00080000) // If 1, supports the ADX instructions.
        ;
    if (ebx & 0x00100000) // If 1, supports Supervisor-Mode Access Prevention and the CLAC/STAC instructions.
        ;
    if (ebx & 0x00200000) // If 1, supports the AVX512_IFMA instructions.
        ;
    if (ebx & 0x00400000) //
        ;
    if (ebx & 0x00800000) // If 1, supports the CLFLUSHOPT instruction.
        ;
    if (ebx & 0x01000000) // If 1, supports the CLWB instruction.
        ;
    if (ebx & 0x02000000) // If 1, supports Intel® Processor Trace.
        ;
    if (ebx & 0x04000000) // If 1, supports the AVX512PF instructions.(Intel® Xeon Phi™ only.)
        ;
    if (ebx & 0x08000000) // If 1, supports the AVX512ER instructions.(Intel® Xeon Phi™ only.)
        ;
    if (ebx & 0x10000000) // If 1, supports the AVX512CD instructions.
        ;
    if (ebx & 0x20000000) // If 1, supports Intel® Secure Hash Algorithm Extensions (Intel® SHA Extensions).
        ;
    if (ebx & 0x40000000) // If 1, supports the AVX512BW instructions.
        ;
    if (ebx & 0x80000000) // If 1, supports the AVX512VL instructions.
        ;

    if (ecx & 0x00000001) // If 1, supports the PREFETCHWT1 instruction.(Intel® Xeon Phi™ only.)
        ;
    if (ecx & 0x00000002) // If 1, supports the AVX512_VBMI instructions.
        ;
    if (ecx & 0x00000004) // If 1, supports user-mode instruction prevention.
        ;
    if (ecx & 0x00000008) // If 1, supports protection keys for user-mode pages.
        ;
    if (ecx & 0x00000010) // If 1, the OS has set CR4.PKE to enable protection keys and the RDPKRU/WRPKRU instructions.
        ;
    if (ecx & 0x00000020) // If 1, supports the TPAUSE, UMONITOR, and UMWAIT instructions.
        ;
    if (ecx & 0x00000040) // If 1, supports the AVX512_VBMI2 instructions.
        ;
    if (ecx & 0x00000080) // If 1, supports CET shadow stack features.
        ;
    if (ecx & 0x00000100) // If 1, supports the GFNI instruction set.
        ;
    if (ecx & 0x00000200) // If 1 and Intel AVX supported, supports the VEX-encoded AES instruction set.
        ;
    if (ecx & 0x00000400) // If 1 and Intel AVX supported, supports the VPCLMULQDQ instruction.
        ;
    if (ecx & 0x00000800) // If 1, supports the AVX512_VNNI instructions.
        ;
    if (ecx & 0x00001000) // If 1, supports the AVX512_BITALG instructions.
        ;
    if (ecx & 0x00002000) // If 1, the following MSRs are supported:IA32_TME_CAPABILITY,IA32_TME_ACTIVATE,IA32_TME_EXCLUDE_MASK, and IA32_TME_EXCLUDE_BASE.
        ;
    if (ecx & 0x00004000) // If 1, supports the AVX512_VPOPCNTDQ instructions.
        ;
    if (ecx & 0x00008000) //
        ;
    if (ecx & 0x00010000) // If 1, supports 57-bit linear addresses and five-level paging.
        ;
    if (ecx & 0b00000000001111100000000000000000) // The value of MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode.
        ;
    if (ecx & 0x00400000) // If 1, RDPID and the IA32_TSC_AUX MSR are available.
        ;
    if (ecx & 0x00800000) // If 1, supports Key Locker.
        ;
    if (ecx & 0x01000000) // If 1, indicates support for OS bus-lock detection.
        ;
    if (ecx & 0x02000000) // If 1, supports cache line demote.
        ;
    if (ecx & 0x04000000) //
        ;
    if (ecx & 0x08000000) // If 1, supports the MOVDIRI instruction.
        ;
    if (ecx & 0x10000000) // If 1, supports the MOVDIR64B instruction.
        ;
    if (ecx & 0x20000000) // If 1, supports Enqueue Stores.
        ;
    if (ecx & 0x40000000) // If 1, supports SGX Launch Configuration.
        ;
    if (ecx & 0x80000000) // If 1, supports protection keys for supervisor-mode pages.
        ;

    __asm_cpuid_ex(0x0000000D, 0x00000001, &eax, &ebx, &ecx, &edx); // Feature and Supervisor State Sub-Leaf

    if (ecx & 0x00008000) // LBR state (only for the architectural LBR feature).
        ;

    __asm_cpuid(0x80000001, &eax, &ebx, &ecx, &edx); // Extended Processor Signature and Feature Bits

    if (ecx & 0x00100000) // If 1, supports Execute Disable Bit.
        ;

    if (ecx & 0x04000000) // If 1, supports 1-GByte pages.
        ;

    if (ecx & 0x08000000) // If 1, supports RDTSCP and IA32_TSC_AUX.
        ;

    uint64_t msr;
    msr = __asm_rdmsr(0x00000480 /* IA32_VMX_BASIC */);
    msr = __asm_rdmsr(0x00000481 /* IA32_VMX_PINBASED_CTLS */);
    msr = __asm_rdmsr(0x00000482 /* IA32_VMX_PROCBASED_CTLS */);
    msr = __asm_rdmsr(0x00000483 /* IA32_VMX_EXIT_CTLS */);
    msr = __asm_rdmsr(0x00000484 /* IA32_VMX_ENTRY_CTLS */);
    msr = __asm_rdmsr(0x00000485 /* IA32_VMX_MISC */);
    msr = __asm_rdmsr(0x00000486 /* IA32_VMX_CR0_FIXED0 */);
    msr = __asm_rdmsr(0x00000487 /* IA32_VMX_CR0_FIXED1 */);
    msr = __asm_rdmsr(0x00000488 /* IA32_VMX_CR4_FIXED0 */);
    msr = __asm_rdmsr(0x00000489 /* IA32_VMX_CR4_FIXED1 */);
    msr = __asm_rdmsr(0x0000048A /* IA32_VMX_VMCS_ENUM */);
    msr = __asm_rdmsr(0x0000048B /* IA32_VMX_PROCBASED_CTLS2 */);
    msr = __asm_rdmsr(0x0000048C /* IA32_VMX_EPT_VPID_CAP */);

    if (msr & (1ULL << 0)) // If bit 0 is read as 1, the processor supports execute-only translations by EPT.
        ;

    if (msr & (1ULL << 6)) // Bit 6 indicates support for a page-walk length of 4.
        ;

    if (msr & (1ULL << 7)) // Bit 7 indicates support for a page-walk length of 5.
        ;

    if (msr & (1ULL << 8)) // If bit 8 is read as 1, the logical processor allows software to configure the EPT paging-structure memory type to be uncacheable (UC)
        ;

    if (msr & (1ULL << 14)) // If bit 14 is read as 1, the logical processor allows software to configure the EPT paging-structure memory type to be write-back (WB)
        ;

    if (msr & (1ULL << 16)) // If bit 16 is read as 1, the logical processor allows software to configure a EPT PDE to map a 2-Mbyte page (by setting bit 7 in the EPT PDE).
        ;

    if (msr & (1ULL << 17)) // If bit 17 is read as 1, the logical processor allows software to configure a EPT PDPTE to map a 1-Gbyte page (by setting bit 7 in the EPT PDPTE).
        ;

    if (msr & (1ULL << 20)) // If bit 20 is read as 1, the INVEPT instruction is supported.
        ;

    if (msr & (1ULL << 21)) // If bit 21 is read as 1, accessed and dirty flags for EPT are supported
        ;

    if (msr & (1ULL << 22)) // If bit 22 is read as 1, the processor reports advanced VM-exit information for EPT violations. This reporting is done only if this bit is read as 1.
        ;

    if (msr & (1ULL << 23)) // If bit 23 is read as 1, supervisor shadow-stack control is supported
        ;

    if (msr & (1ULL << 25)) // If bit 25 is read as 1, the single-context INVEPT type is supported.
        ;

    if (msr & (1ULL << 26)) // If bit 26 is read as 1, the all-context INVEPT type is supported.
        ;

    if (msr & (1ULL << 32)) // If bit 32 is read as 1, the INVVPID instruction is supported.
        ;

    if (msr & (1ULL << 40)) // If bit 40 is read as 1, the individual-address INVVPID type is supported.
        ;

    if (msr & (1ULL << 41)) // If bit 41 is read as 1, the single-context INVVPID type is supported.
        ;

    if (msr & (1ULL << 42)) // If bit 42 is read as 1, the all-context INVVPID type is supported.
        ;

    if (msr & (1ULL << 43)) // If bit 43 is read as 1, the single-context-retaining-globals INVVPID type is supported.
        ;

    msr = __asm_rdmsr(0x0000048D /* IA32_VMX_TRUE_PINBASED_CTLS */);
    msr = __asm_rdmsr(0x0000048E /* IA32_VMX_TRUE_PROCBASED_CTLS */);
    msr = __asm_rdmsr(0x0000048F /* IA32_VMX_TRUE_EXIT_CTLS */);
    msr = __asm_rdmsr(0x00000490 /* IA32_VMX_TRUE_ENTRY_CTLS */);
    msr = __asm_rdmsr(0x00000491 /* IA32_VMX_VMFUNC */);
    msr = __asm_rdmsr(0x00000492 /* IA32_VMX_PROCBASED_CTLS3 */);
    msr = __asm_rdmsr(0x00000493 /* IA32_VMX_EXIT_CTLS2 */);

    return 0;
}
