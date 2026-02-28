
/**
 * 用户为本，科技向善
 **/

#include "GenuineIntel.h"

template <>
int
initialize<Hash("GenuineIntel")>()
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    __asm_cpuid(1, &eax, &ebx, &ecx, &edx);

    if (ecx & (1U << 0x00))
        ;
    if (ecx & (1U << 0x01))
        ;
    if (ecx & (1U << 0x02))
        ;
    if (ecx & (1U << 0x03))
        ;
    if (ecx & (1U << 0x04))
        ;
    if ((ecx & (1U << 0x05)) == 0) // If 1, supports the Virtual Machine Extensions.
        return -1;
    if (ecx & (1U << 0x06)) // If 1, supports Safer Mode Extensions.cal
        ;
    if (ecx & (1U << 0x07))
        ;
    if (ecx & (1U << 0x08))
        ;
    if (ecx & (1U << 0x09))
        ;
    if (ecx & (1U << 0x0A))
        ;
    if (ecx & (1U << 0x0B)) // If 1, supports IA32_DEBUG_INTERFACE MSR for silicon debug.
        ;
    if (ecx & (1U << 0x0C))
        ;
    if (ecx & (1U << 0x0D))
        ;
    if (ecx & (1U << 0x0E))
        ;
    if (ecx & (1U << 0x0F))
        ;
    if (ecx & (1U << 0x10))
        ;
    if (ecx & (1U << 0x11))
        ;
    if (ecx & (1U << 0x12))
        ;
    if (ecx & (1U << 0x13)) // If 1, supports SSE4.1.
        ;
    if (ecx & (1U << 0x14)) // If 1, supports SSE4.2.
        ;
    if (ecx & (1U << 0x15)) // If 1, supports x2APIC feature.
        ;
    if (ecx & (1U << 0x16)) // If 1, supports MOVBE instruction.
        ;
    if (ecx & (1U << 0x17)) // If 1, supports the POPCNT instruction.
        ;
    if (ecx & (1U << 0x18))
        ;
    if (ecx & (1U << 0x19))
        ;
    if (ecx & (1U << 0x1A))
        ;
    if (ecx & (1U << 0x1B))
        ;
    if (ecx & (1U << 0x1C)) // If 1, supports the AVX instruction extensions.
        ;
    if (ecx & (1U << 0x1D))
        ;
    if (ecx & (1U << 0x1E)) // If 1, supports RDRAND instruction.
        ;
    if (ecx & (1U << 0x1F))
        ;

    __asm_cpuid(0x00000003, &eax, &ebx, &ecx, &edx); // Processor Serial Number

    __asm_cpuid_ex(0x00000007, 0x00000000, &eax, &ebx, &ecx, &edx); // Structured Extended Feature Flags Main Sub-Leaf

    if (ebx & (1U << 0x00)) // If 1, supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE.
        ;
    if (ebx & (1U << 0x01)) // If 1, the IA32_TSC_ADJUST MSR is supported.
        ;
    if (ebx & (1U << 0x02)) // If 1, supports Intel® Software Guard Extensions (Intel® SGX Extensions).
        ;
    if (ebx & (1U << 0x03)) // If 1, supports the BMI1 instructions.
        ;
    if (ebx & (1U << 0x04)) // If 1, supports the Hardware Lock Elision instruction set.
        ;
    if (ebx & (1U << 0x05)) // If 1, supports Intel® Advanced Vector Extensions 2 (Intel® AVX2).
        ;
    if (ebx & (1U << 0x06)) //
        ;
    if (ebx & (1U << 0x07)) // If 1, supports Supervisor-Mode Execution Prevention.
        ;
    if (ebx & (1U << 0x08)) // If 1, supports the BMI2 instructions.
        ;
    if (ebx & (1U << 0x09)) //
        ;
    if (ebx & (1U << 0x0A)) // If 1, supports INVPCID instruction for system software that manages process-context identifiers.
        ;
    if (ebx & (1U << 0x0B)) // If 1, supports the Restricted Transactional Memory instruction set.
        ;
    if (ebx & (1U << 0x0C)) // If 1, supports Intel® Resource Director Technology (Intel® RDT) Monitoring capability.
        ;
    if (ebx & (1U << 0x0D)) //
        ;
    if (ebx & (1U << 0x0E)) // If 1, supports Intel® Memory Protection Extensions.
        ;
    if (ebx & (1U << 0x0F)) //
        ;
    if (ebx & (1U << 0x10)) // If 1, supports the AVX512F instructions.
        ;
    if (ebx & (1U << 0x11)) // If 1, supports the AVX512DQ instructions.
        ;
    if (ebx & (1U << 0x12)) // If 1, supports the RDSEED instruction.
        ;
    if (ebx & (1U << 0x13)) // If 1, supports the ADX instructions.
        ;
    if (ebx & (1U << 0x14)) // If 1, supports Supervisor-Mode Access Prevention and the CLAC/STAC instructions.
        ;
    if (ebx & (1U << 0x15)) // If 1, supports the AVX512_IFMA instructions.
        ;
    if (ebx & (1U << 0x16)) //
        ;
    if (ebx & (1U << 0x17)) // If 1, supports the CLFLUSHOPT instruction.
        ;
    if (ebx & (1U << 0x18)) // If 1, supports the CLWB instruction.
        ;
    if (ebx & (1U << 0x19)) // If 1, supports Intel® Processor Trace.
        ;
    if (ebx & (1U << 0x1A)) // If 1, supports the AVX512PF instructions.(Intel® Xeon Phi™ only.)
        ;
    if (ebx & (1U << 0x1B)) // If 1, supports the AVX512ER instructions.(Intel® Xeon Phi™ only.)
        ;
    if (ebx & (1U << 0x1C)) // If 1, supports the AVX512CD instructions.
        ;
    if (ebx & (1U << 0x1D)) // If 1, supports Intel® Secure Hash Algorithm Extensions (Intel® SHA Extensions).
        ;
    if (ebx & (1U << 0x1E)) // If 1, supports the AVX512BW instructions.
        ;
    if (ebx & (1U << 0x1F)) // If 1, supports the AVX512VL instructions.
        ;

    if (ecx & (1U << 0x00)) // If 1, supports the PREFETCHWT1 instruction.(Intel® Xeon Phi™ only.)
        ;
    if (ecx & (1U << 0x01)) // If 1, supports the AVX512_VBMI instructions.
        ;
    if (ecx & (1U << 0x02)) // If 1, supports user-mode instruction prevention.
        ;
    if (ecx & (1U << 0x03)) // If 1, supports protection keys for user-mode pages.
        ;
    if (ecx & (1U << 0x04)) // If 1, the OS has set CR4.PKE to enable protection keys and the RDPKRU/WRPKRU instructions.
        ;
    if (ecx & (1U << 0x05)) // If 1, supports the TPAUSE, UMONITOR, and UMWAIT instructions.
        ;
    if (ecx & (1U << 0x06)) // If 1, supports the AVX512_VBMI2 instructions.
        ;
    if (ecx & (1U << 0x07)) // If 1, supports CET shadow stack features.
        ;
    if (ecx & (1U << 0x08)) // If 1, supports the GFNI instruction set.
        ;
    if (ecx & (1U << 0x09)) // If 1 and Intel AVX supported, supports the VEX-encoded AES instruction set.
        ;
    if (ecx & (1U << 0x0A)) // If 1 and Intel AVX supported, supports the VPCLMULQDQ instruction.
        ;
    if (ecx & (1U << 0x0B)) // If 1, supports the AVX512_VNNI instructions.
        ;
    if (ecx & (1U << 0x0C)) // If 1, supports the AVX512_BITALG instructions.
        ;
    if (ecx & (1U << 0x0D)) // If 1, the following MSRs are supported:IA32_TME_CAPABILITY,IA32_TME_ACTIVATE,IA32_TME_EXCLUDE_MASK, and IA32_TME_EXCLUDE_BASE.
        ;
    if (ecx & (1U << 0x0E)) // If 1, supports the AVX512_VPOPCNTDQ instructions.
        ;
    if (ecx & (1U << 0x0F)) //
        ;
    if (ecx & (1U << 0x10)) // If 1, supports 57-bit linear addresses and five-level paging.
        ;
    if (ecx & 0b00000000001111100000000000000000) // The value of MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode.
        ;
    if (ecx & (1U << 0x16)) // If 1, RDPID and the IA32_TSC_AUX MSR are available.
        ;
    if (ecx & (1U << 0x17)) // If 1, supports Key Locker.
        ;
    if (ecx & (1U << 0x18)) // If 1, indicates support for OS bus-lock detection.
        ;
    if (ecx & (1U << 0x19)) // If 1, supports cache line demote.
        ;
    if (ecx & (1U << 0x1A)) //
        ;
    if (ecx & (1U << 0x1B)) // If 1, supports the MOVDIRI instruction.
        ;
    if (ecx & (1U << 0x1C)) // If 1, supports the MOVDIR64B instruction.
        ;
    if (ecx & (1U << 0x1D)) // If 1, supports Enqueue Stores.
        ;
    if (ecx & (1U << 0x1E)) // If 1, supports SGX Launch Configuration.
        ;
    if (ecx & (1U << 0x1F)) // If 1, supports protection keys for supervisor-mode pages.
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

    msr = __asm_rdmsr(0x00000010 /* IA32_TIME_STAMP_COUNTER */);
    msr = __asm_rdmsr(0x0000001B /* IA32_APIC_BASE */);
    msr = __asm_rdmsr(0x0000003A /* IA32_FEATURE_CONTROL */); // Control Features in Intel 64 Processor (R/W)

    CONTEXT Context;
    RtlCaptureContext(&Context);

    /**
     * If this bit is clear, VMXON causes a general-protection exception.
     * If the lock bit is set, WRMSR to this MSR causes a general-protection exception;
     **/
    if ((msr & (1ULL << 0x00)) == 0) // Lock bit (R/WO): (1 = locked).
        __asm_wrmsr(0x0000003A, msr | 1);
    if (msr & (1ULL << 0x01)) // Enable VMX inside SMX operation (R/WL) This bit enables a system executive to use VMX in conjunction with SMX to support Intel® Trusted Execution Technology.
        ;
    if ((msr & (1ULL << 0x02)) == 0) // Enable VMX outside SMX operation (R/WL) This bit enables VMX for a system executive that does not require SMX.
        return -1;
    if (msr & (1ULL << 0x03))
        ;
    if (msr & (1ULL << 0x04))
        ;
    if (msr & (1ULL << 0x05))
        ;
    if (msr & (1ULL << 0x06))
        ;
    if (msr & (1ULL << 0x07))
        ;
    if (msr & (1ULL << 0x08))
        ;
    if (msr & (1ULL << 0x09))
        ;
    if (msr & (1ULL << 0x0A))
        ;
    if (msr & (1ULL << 0x0B))
        ;
    if (msr & (1ULL << 0x0C))
        ;
    if (msr & (1ULL << 0x0D))
        ;
    if (msr & (1ULL << 0x0E))
        ;
    if (msr & (1ULL << 0x0F))
        ;
    if (msr & (1ULL << 0x10))
        ;
    if (msr & (1ULL << 0x11))
        ;
    if (msr & (1ULL << 0x12))
        ;
    if (msr & (1ULL << 0x13))
        ;
    if (msr & (1ULL << 0x14))
        ;
    if (msr & (1ULL << 0x15))
        ;
    if (msr & (1ULL << 0x16))
        ;
    if (msr & (1ULL << 0x17))
        ;
    if (msr & (1ULL << 0x18))
        ;
    if (msr & (1ULL << 0x19))
        ;
    if (msr & (1ULL << 0x1A))
        ;
    if (msr & (1ULL << 0x1B))
        ;
    if (msr & (1ULL << 0x1C))
        ;
    if (msr & (1ULL << 0x1D))
        ;
    if (msr & (1ULL << 0x1E))
        ;
    if (msr & (1ULL << 0x1F))
        ;
    msr = __asm_rdmsr(0x0000003B /* IA32_TSC_ADJUST */);
    msr = __asm_rdmsr(0x00000048 /* IA32_SPEC_CTRL */);
    msr = __asm_rdmsr(0x0000009E /* IA32_SMBASE */);
    msr = __asm_rdmsr(0x000000C1 /* IA32_PMC0 (PERFCTR0) */);
    msr = __asm_rdmsr(0x000000C2 /* IA32_PMC1 (PERFCTR1) */);
    msr = __asm_rdmsr(0x000000C3 /* IA32_PMC2 */);
    msr = __asm_rdmsr(0x000000C4 /* IA32_PMC3 */);
    msr = __asm_rdmsr(0x000000C5 /* IA32_PMC4 */);
    msr = __asm_rdmsr(0x000000C6 /* IA32_PMC5 */);
    msr = __asm_rdmsr(0x000000C7 /* IA32_PMC6 */);
    msr = __asm_rdmsr(0x000000C8 /* IA32_PMC7 */);
    msr = __asm_rdmsr(0x000000C9 /* IA32_PMC8 */);
    msr = __asm_rdmsr(0x000000CA /* IA32_PMC9 */);

    msr = __asm_rdmsr(0x000000CF /* IA32_CORE_CAPABILITIES */);
    msr = __asm_rdmsr(0x000000E7 /* IA32_MPERF */);
    msr = __asm_rdmsr(0x000000E8 /* IA32_APERF */);

    msr = __asm_rdmsr(0x0000010A /* IA32_ARCH_CAPABILITIES */);

    msr = __asm_rdmsr(0x00000198 /* IA32_PERF_STATUS */);
    msr = __asm_rdmsr(0x00000199 /* IA32_PERF_CTL */);

    msr = __asm_rdmsr(0x000001A0 /* IA32_MISC_ENABLE */);

    msr = __asm_rdmsr(0x000001D9 /* IA32_DEBUGCTL (MSR_DEBUGCTLA, MSR_DEBUGCTLB) */);

    msr = __asm_rdmsr(0x000001F2 /* IA32_SMRR_PHYSBASE */);
    msr = __asm_rdmsr(0x000001F3 /* IA32_SMRR_PHYSMASK */);

    msr = __asm_rdmsr(0x00000200 /* IA32_MTRR_PHYSBASE0 */);
    msr = __asm_rdmsr(0x00000201 /* IA32_MTRR_PHYSMASK0 */);
    msr = __asm_rdmsr(0x00000202 /* IA32_MTRR_PHYSBASE1 */);
    msr = __asm_rdmsr(0x00000203 /* IA32_MTRR_PHYSMASK1 */);
    msr = __asm_rdmsr(0x00000204 /* IA32_MTRR_PHYSBASE2 */);
    msr = __asm_rdmsr(0x00000205 /* IA32_MTRR_PHYSMASK2 */);
    msr = __asm_rdmsr(0x00000206 /* IA32_MTRR_PHYSBASE3 */);
    msr = __asm_rdmsr(0x00000207 /* IA32_MTRR_PHYSMASK3 */);
    msr = __asm_rdmsr(0x00000208 /* IA32_MTRR_PHYSBASE4 */);
    msr = __asm_rdmsr(0x00000209 /* IA32_MTRR_PHYSMASK4 */);
    msr = __asm_rdmsr(0x0000020A /* IA32_MTRR_PHYSBASE5 */);
    msr = __asm_rdmsr(0x0000020B /* IA32_MTRR_PHYSMASK5 */);
    msr = __asm_rdmsr(0x0000020C /* IA32_MTRR_PHYSBASE6 */);
    msr = __asm_rdmsr(0x0000020D /* IA32_MTRR_PHYSMASK6 */);
    msr = __asm_rdmsr(0x0000020E /* IA32_MTRR_PHYSBASE7 */);
    msr = __asm_rdmsr(0x0000020F /* IA32_MTRR_PHYSMASK7 */);
    msr = __asm_rdmsr(0x00000210 /* IA32_MTRR_PHYSBASE8 */);
    msr = __asm_rdmsr(0x00000211 /* IA32_MTRR_PHYSMASK8 */);
    msr = __asm_rdmsr(0x00000212 /* IA32_MTRR_PHYSBASE9 */);
    msr = __asm_rdmsr(0x00000213 /* IA32_MTRR_PHYSMASK9 */);

    msr = __asm_rdmsr(0x00000345 /* IA32_PERF_CAPABILITIES */);

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
    if ((msr & (1ULL << 6)) == 0) // Bit 6 indicates support for a page-walk length of 4.
        return -1;
    if (msr & (1ULL << 7)) // Bit 7 indicates support for a page-walk length of 5.
        ;
    if (msr & (1ULL << 8)) // If bit 8 is read as 1, the logical processor allows software to configure the EPT paging-structure memory type to be uncacheable (UC)
        ;
    if ((msr & (1ULL << 14)) == 0) // If bit 14 is read as 1, the logical processor allows software to configure the EPT paging-structure memory type to be write-back (WB)
        return -1;
    if (msr & (1ULL << 16)) // If bit 16 is read as 1, the logical processor allows software to configure a EPT PDE to map a 2-Mbyte page (by setting bit 7 in the EPT PDE).
        ;
    if (msr & (1ULL << 17)) // If bit 17 is read as 1, the logical processor allows software to configure a EPT PDPTE to map a 1-Gbyte page (by setting bit 7 in the EPT PDPTE).
        ;
    if ((msr & (1ULL << 20)) == 0) // If bit 20 is read as 1, the INVEPT instruction is supported.
        return -1;
    if (msr & (1ULL << 21)) // If bit 21 is read as 1, accessed and dirty flags for EPT are supported
        ;
    if (msr & (1ULL << 22)) // If bit 22 is read as 1, the processor reports advanced VM-exit information for EPT violations. This reporting is done only if this bit is read as 1.
        ;
    if (msr & (1ULL << 23)) // If bit 23 is read as 1, supervisor shadow-stack control is supported
        ;
    if ((msr & (1ULL << 25)) == 0) // If bit 25 is read as 1, the single-context INVEPT type is supported.
        return -1;
    if ((msr & (1ULL << 26)) == 0) // If bit 26 is read as 1, the all-context INVEPT type is supported.
        return -1;
    if ((msr & (1ULL << 32)) == 0) // If bit 32 is read as 1, the INVVPID instruction is supported.
        return -1;
    if ((msr & (1ULL << 40)) == 0) // If bit 40 is read as 1, the individual-address INVVPID type is supported.
        return -1;
    if ((msr & (1ULL << 41)) == 0) // If bit 41 is read as 1, the single-context INVVPID type is supported.
        return -1;
    if ((msr & (1ULL << 42)) == 0) // If bit 42 is read as 1, the all-context INVVPID type is supported.
        return -1;
    if ((msr & (1ULL << 43)) == 0) // If bit 43 is read as 1, the single-context-retaining-globals INVVPID type is supported.
        return -1;

    msr = __asm_rdmsr(0x0000048D /* IA32_VMX_TRUE_PINBASED_CTLS */);
    msr = __asm_rdmsr(0x0000048E /* IA32_VMX_TRUE_PROCBASED_CTLS */);
    msr = __asm_rdmsr(0x0000048F /* IA32_VMX_TRUE_EXIT_CTLS */);
    msr = __asm_rdmsr(0x00000490 /* IA32_VMX_TRUE_ENTRY_CTLS */);
    msr = __asm_rdmsr(0x00000491 /* IA32_VMX_VMFUNC */);
    msr = __asm_rdmsr(0x00000492 /* IA32_VMX_PROCBASED_CTLS3 */);
    msr = __asm_rdmsr(0x00000493 /* IA32_VMX_EXIT_CTLS2 */);

    msr = __asm_rdmsr(0x00000C80 /* IA32_DEBUG_INTERFACE */);

    msr = __asm_rdmsr(0x000014CE /* IA32_LBR_CTL */);
    msr = __asm_rdmsr(0x000014CF /* IA32_LBR_DEPTH */);

    for (uint32_t i = 0; i < 0x20; ++i) {
        msr = __asm_rdmsr(0x00001500 + i /* IA32_LBR_x_FROM_IP */);
        msr = __asm_rdmsr(0x00001600 + i /* IA32_LBR_x_TO_IP */);
    }

    msr = __asm_rdmsr(0xC0000080 /* IA32_EFER */);
    msr = __asm_rdmsr(0xC0000081 /* IA32_STAR */);
    msr = __asm_rdmsr(0xC0000082 /* IA32_LSTAR */);
    msr = __asm_rdmsr(0xC0000083 /* IA32_CSTAR */);
    msr = __asm_rdmsr(0xC0000084 /* IA32_FMASK */);

    msr = __asm_rdmsr(0xC0000100 /* IA32_FS_BASE */);
    msr = __asm_rdmsr(0xC0000101 /* IA32_GS_BASE */);
    msr = __asm_rdmsr(0xC0000102 /* IA32_KERNEL_GS_BASE */);
    msr = __asm_rdmsr(0xC0000103 /* IA32_TSC_AUX */);

    msr = __asm_rdmsr(0x0000003A /* IA32_FEATURE_CONTROL */);    // Control Features in Intel 64 Processor (R/W)
    __asm_wrmsr(0x0000003A /* IA32_FEATURE_CONTROL */, msr | 1); // lock

    uint64_t ia32_vmx_cr0_fixed0 = __asm_rdmsr(0x00000486 /* IA32_VMX_CR0_FIXED0 */);
    uint64_t ia32_vmx_cr0_fixed1 = __asm_rdmsr(0x00000487 /* IA32_VMX_CR0_FIXED1 */);
    uint64_t ia32_vmx_cr4_fixed0 = __asm_rdmsr(0x00000488 /* IA32_VMX_CR4_FIXED0 */);
    uint64_t ia32_vmx_cr4_fixed1 = __asm_rdmsr(0x00000489 /* IA32_VMX_CR4_FIXED1 */);

    __asm_cr0((__asm_cr0() & ia32_vmx_cr0_fixed1) | ia32_vmx_cr0_fixed0);
    __asm_cr4(((__asm_cr4() | 0x00002000 /*VMXE*/) & ia32_vmx_cr4_fixed1) | ia32_vmx_cr4_fixed0);

    KdBreakPoint();

    auto x = allocate<0x1000>();
    deallocate<0x1000>(x);

    MmGetPhysicalAddress;

    __asm_vmx_vmxon;
    __asm_vmx_vmclear;
    __asm_vmx_vmptrld;
    __asm_vmx_vmptrst;

    __asm_vmx_vmwrite;
    // __asm_vmx_vmread(0x4400 /*VMX_VMCS32_RO_VM_INSTR_ERROR*/, NULL);

    return 0;
}
