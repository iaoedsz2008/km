
/**
 * 用户为本，科技向善
 **/

#include "AuthenticAMD.h"

#include "GenuineIntel.h"

template <>
int
initialize<Hash("AuthenticAMD")>(PVOID vcpu)
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    uint64_t msr;

    __asm_cpuid(0x00000000, &eax, &ebx, &ecx, &edx);

    if (eax < 0x80000000)
        return -1;

    __asm_cpuid(0x00000001, &eax, &ebx, &ecx, &edx);

    if (ecx & (1U << 0x00)) // SSE3 - SSE3 instruction support
        ;
    if (ecx & (1U << 0x01)) // PCLMULQDQ - PCLMULQDQ instruction support
        ;
    if (ecx & (1U << 0x03)) // MONITOR - MONITOR/MWAIT instructions
        ;
    if (ecx & (1U << 0x09)) // SSSE3 - Supplemental SSE3 instruction support
        ;
    if (ecx & (1U << 0x0C)) // FMA - FMA instruction support
        ;
    if (ecx & (1U << 0x0D)) // CMPXCHG16B - CMPXCHG16B instruction support
        ;
    if (ecx & (1U << 0x13)) // SSE41 - SSE4.1 instruction support
        ;
    if (ecx & (1U << 0x14)) // SSE42 - SSE4.2 instruction support
        ;
    if (ecx & (1U << 0x15)) // x2APIC - x2APIC support
        ;
    if (ecx & (1U << 0x16)) // MOVBE - MOVBE instruction support.
        ;
    if (ecx & (1U << 0x17)) // POPCNT - POPCNT instruction
        ;
    if (ecx & (1U << 0x19)) // AES - AES instruction support
        ;
    if (ecx & (1U << 0x1A)) // XSAVE - XSAVE (and related) instructions are supported by hardware
        ;
    if (ecx & (1U << 0x1B)) // OSXSAVE - XSAVE (and related) instructions are enabled
        ;
    if (ecx & (1U << 0x1C)) // AVX - AVX instruction support
        ;
    if (ecx & (1U << 0x1D)) // F16C - Half-precision convert instruction support
        ;
    if (ecx & (1U << 0x1E)) // RDRAND - RDRAND instruction support
        ;

    if (edx & (1U << 0x00)) // FPU - x87 floating point unit on-chip
        ;
    if (edx & (1U << 0x01)) // VME - Virtual-mode enhancements
        ;
    if (edx & (1U << 0x02)) // DE - Debugging extensions
        ;
    if (edx & (1U << 0x03)) // PSE - Page-size extensions
        ;
    if (edx & (1U << 0x04)) // TSC - Time stamp counter
        ;
    if (edx & (1U << 0x05)) // MSR - AMD model-specific registers
        ;
    if (edx & (1U << 0x06)) // PAE - Physical-address extensions
        ;
    if (edx & (1U << 0x07)) // MCE - Machine check exception
        ;
    if (edx & (1U << 0x08)) // CMPXCHG8B - CMPXCHG8B instruction
        ;
    if (edx & (1U << 0x09)) // APIC - Advanced programmable interrupt controller
        ;
    if (edx & (1U << 0x0B)) // SysEnterSysExit - SYSENTER and SYSEXIT instructions
        ;
    if (edx & (1U << 0x0C)) // MTRR - Memory-type range registers
        ;
    if (edx & (1U << 0x0D)) // PGE - Page global extension
        ;
    if (edx & (1U << 0x0E)) // MCA - Machine check architecture
        ;
    if (edx & (1U << 0x0F)) // CMOV - Conditional move instructions
        ;
    if (edx & (1U << 0x10)) // PAT - Page attribute table
        ;
    if (edx & (1U << 0x11)) // PSE36 - Page-size extensions
        ;
    if (edx & (1U << 0x13)) // CLFSH - CLFLUSH instruction support
        ;
    if (edx & (1U << 0x17)) // MMX - MMX instructions.
        ;
    if (edx & (1U << 0x18)) // FXSR - FXSAVE and FXRSTOR instructions
        ;
    if (edx & (1U << 0x19)) // SSE - SSE instruction support
        ;
    if (edx & (1U << 0x1A)) // SSE2 - SSE2 instruction support
        ;
    if (edx & (1U << 0x1C)) // HTT - Hyper-threading technology
        ;

    __asm_cpuid_ex(0x00000007, 0, &eax, &ebx, &ecx, &edx);
    int MaxSubFn = eax;

    if (ebx & (1U << 0x00)) // FSGSBASE - FS and GS base read/write instruction support
        ;
    if (ebx & (1U << 0x01)) // TSCADJUST - TSC Adjust MSR (3Bh) support
        ;
    if (ebx & (1U << 0x03)) // BMI1 - Bit manipulation group 1 instruction support.
        ;
    if (ebx & (1U << 0x05)) // AVX2 - AVX2 instruction subset support.
        ;
    if (ebx & (1U << 0x07)) // SMEP - Supervisor mode execution prevention.
        ;
    if (ebx & (1U << 0x08)) // BMI2 - Bit manipulation group 2 instruction support.
        ;
    if (ebx & (1U << 0x09)) // ERMS - Enhanced REP MOVSB/STOSB support.
        ;
    if (ebx & (1U << 0x0A)) // INVPCID - INVPCID instruction support.
        ;
    if (ebx & (1U << 0x0C)) // PQM - Platform QOS Monitoring support
        ;
    if (ebx & (1U << 0x0F)) // PQE - Platform QOS Enforcement support
        ;
    if (ebx & (1U << 0x10)) // AVX512F - AVX512 Foundation
        ;
    if (ebx & (1U << 0x11)) // AVX512DQ - AVX512 Doubleword/Quadword Packed Integer instructions
        ;
    if (ebx & (1U << 0x12)) // RDSEED - RDSEED instruction support
        ;
    if (ebx & (1U << 0x13)) // ADX - ADCX, ADOX instruction support
        ;
    if (ebx & (1U << 0x14)) // SMAP - Supervisor mode access prevention.
        ;
    if (ebx & (1U << 0x15)) // AVX512_IFMA - AVX512 Integer Fused Multiply-Add instructions support
        ;
    if (ebx & (1U << 0x17)) // CLFLUSHOPT - CLFLUSHOPT instruction support.
        ;
    if (ebx & (1U << 0x18)) // CLWB - CLWB instruction support.
        ;
    if (ebx & (1U << 0x1C)) // AVX512CD - AVX512 Conflict Detection for Vectorizing Loops
        ;
    if (ebx & (1U << 0x1D)) // SHA - Secure Hash Algorithm instruction extension
        ;
    if (ebx & (1U << 0x1E)) // AVX512BW - AVX512 Byte/Word Packed Integer instructions
        ;
    if (ebx & (1U << 0x1F)) // AVX512VL - AVX512 instructions are extended to 128 and 256 bits
        ;

    if (ecx & (1U << 0x01)) // AVX512_VBMI - AVX512 vector byte permutation instructions support.
        ;
    if (ecx & (1U << 0x02)) // UMIP - User mode instruction prevention support.
        ;
    if (ecx & (1U << 0x03)) // PKU - Memory Protection Keys supported.
        ;
    if (ecx & (1U << 0x04)) // OSPKE - OS has enabled Memory Protection Keys and use of the RDPKRU/WRPKRU instructions by setting CR4.PKE=1.
        ;
    if (ecx & (1U << 0x06)) // AVX512_VBMI2 - AVX512 vector byte permutation instruction 2 support.
        ;
    if (ecx & (1U << 0x07)) // CET_SS - Shadow Stacks supported.
        ;
    if (ecx & (1U << 0x08)) // GFNI - Galois Field New instructions support.
        ;
    if (ecx & (1U << 0x09)) // VAES - VAES 256-bit instructions support.
        ;
    if (ecx & (1U << 0x0A)) // VPCMULQDQ - VPCLMULQDQ 256-bit instruction support.
        ;
    if (ecx & (1U << 0x0B)) // AVX512_VNNI - AVX512 vector neural network instructions support.
        ;
    if (ecx & (1U << 0x0C)) // AVX512_BITALG - AVX512 bit algorithm instructions VPSHUFBITQMB and VPOPCNTB/W support.
        ;
    if (ecx & (1U << 0x0E)) // AVX512_VPOPCNTDQ - AVX-512 VPOPCNTD/Q instruction support.
        ;
    if (ecx & (1U << 0x0F)) // LA57 - 5-Level paging support.
        ;
    if (ecx & (1U << 0x16)) // RDPID - RDPID instruction and TSC_AUX MSR support.
        ;
    if (ecx & (1U << 0x18)) // BUSLOCKTRAP - Bus Lock Trap (#DB) support.
        ;
    if (ecx & (1U << 0x1B)) // MOVDIRI - MOVDIRI instruction support.
        ;
    if (ecx & (1U << 0x1C)) // MOVDIR64B - MOVDIR64B instruction support.
        ;

    __asm_cpuid_ex(0x00000007, 1, &eax, &ebx, &ecx, &edx);

    if (edx & (1U << 0x04)) // AVX_VNNI - AVX Neural Network instructions
        ;
    if (edx & (1U << 0x05)) // AVX512_BF16 - AVX512 BFloat16 instructions
        ;

    __asm_cpuid(0x80000001, &eax, &ebx, &ecx, &edx);
    __asm_cpuid(0x8000000A, &eax, &ebx, &ecx, &edx);

    msr = __asm_rdmsr(IA32_EFER);
    msr = __asm_rdmsr(IA32_PAT);
    msr = __asm_rdmsr(IA32_APIC_BASE);

    msr = __asm_rdmsr(0xC0010000); // PerfEvtSel0
    msr = __asm_rdmsr(0xC0010001); // PerfEvtSel1
    msr = __asm_rdmsr(0xC0010002); // PerfEvtSel2
    msr = __asm_rdmsr(0xC0010003); // PerfEvtSel3
    msr = __asm_rdmsr(0xC0010004); // PerfCtr0
    msr = __asm_rdmsr(0xC0010005); // PerfCtr1
    msr = __asm_rdmsr(0xC0010006); // PerfCtr2
    msr = __asm_rdmsr(0xC0010007); // PerfCtr3
    msr = __asm_rdmsr(0xC0010010); // SYSCFG Memory Typing
    msr = __asm_rdmsr(0xC0010015); // HWCR System Software
    msr = __asm_rdmsr(0xC0010016); // IORRBase0
    msr = __asm_rdmsr(0xC0010017); // IORRMask0
    msr = __asm_rdmsr(0xC0010018); // IORRBase1
    msr = __asm_rdmsr(0xC0010019); // IORRMask1
    msr = __asm_rdmsr(0xC001001A); // TOP_MEM
    msr = __asm_rdmsr(0xC001001D); // TOP_MEM2
    msr = __asm_rdmsr(0xC0010056); // SMI_Trigger_IO_Cycle
    msr = __asm_rdmsr(0xC0010061); // P-State Current Limit
    msr = __asm_rdmsr(0xC0010062); // P-State Control
    msr = __asm_rdmsr(0xC0010063); // P-State Status
    msr = __asm_rdmsr(0xC0010074); // CPU_Watchdog_Timer Machine Check "CPU Watchdog Timer Register" on page 304
    msr = __asm_rdmsr(0xC0010104); // TSC Ratio SVM "TSC Ratio MSR (C000_0104h)" on page 585
    msr = __asm_rdmsr(0xC0010111); // SMBASE
    msr = __asm_rdmsr(0xC0010112); // SMM_ADDR
    msr = __asm_rdmsr(0xC0010113); // SMM_MASK
    msr = __asm_rdmsr(0xC0010114); // VM_CR SVM "SVM Related MSRs" on page 583
    msr = __asm_rdmsr(0xC0010115); // IGNNE SVM "SVM Related MSRs" on page 583
    msr = __asm_rdmsr(0xC0010116); // SMM_CTL SVM "SVM Related MSRs" on page 583
    msr = __asm_rdmsr(0xC0010117); // VM_HSAVE_PA SVM "SVM Related MSRs" on page 583
    msr = __asm_rdmsr(0xC0010118); // SVM_KEY SVM "SVM-Lock" on page 586
    msr = __asm_rdmsr(0xC0010119); // SMM_KEY SMM "SMM-Lock" on page 587
    msr = __asm_rdmsr(0xC001011A); // Local_SMI_Status SMM
    msr = __asm_rdmsr(0xC001011B); // Doorbell Register SVM "Doorbell Register" on page 579
    msr = __asm_rdmsr(0xC001011E); // VMPAGE_FLUSH SVM "Secure Encrypted Virtualization" on page 588
    msr = __asm_rdmsr(0xC001011F); // VIRT_SPEC_CTRL
    msr = __asm_rdmsr(0xC0010130); // GHCB SVM "GHCB" on page 599
    msr = __asm_rdmsr(0xC0010131); // SEV_STATUS SVM "SEV_STATUS MSR" on page 593
    msr = __asm_rdmsr(0xC0010132); // RMP_BASE SVM "Initializing the RMP" on page 604
    msr = __asm_rdmsr(0xC0010133); // RMP_END SVM "Initializing the RMP" on page 604
    msr = __asm_rdmsr(0xC0010134); // GUEST_TSC_FREQ SVM "Secure TSC" on page 616
    msr = __asm_rdmsr(0xC0010135); // VIRTUAL_TOM SVM "Virtual Top-of-Memory" on page 607
    msr = __asm_rdmsr(0xC0010136); // SEGMENTED_RMP_CFG SVM "Segmented RMP" on page 621
    msr = __asm_rdmsr(0xC0010137); // IDLE_WAKEUP_ICR SVM "Side-Channel Protection" on page 615
    msr = __asm_rdmsr(0xC0010138); // SECURE_AVIC_CTRL SVM "Secure AVIC Control MSR" on page 619
    msr = __asm_rdmsr(0xC0010140); // OSVW_ID_Length
    msr = __asm_rdmsr(0xC0010141); // OSVW Status
    msr = __asm_rdmsr(0xC0010200); // PerfEvtSel0
    msr = __asm_rdmsr(0xC0010202); // PerfEvtSel1
    msr = __asm_rdmsr(0xC0010204); // PerfEvtSel2
    msr = __asm_rdmsr(0xC0010206); // PerfEvtSel3
    msr = __asm_rdmsr(0xC0010208); // PerfEvtSel4
    msr = __asm_rdmsr(0xC001020A); // PerfEvtSel5
    msr = __asm_rdmsr(0xC0010201); // PerfCtr0
    msr = __asm_rdmsr(0xC0010203); // PerfCtr1
    msr = __asm_rdmsr(0xC0010205); // PerfCtr2
    msr = __asm_rdmsr(0xC0010207); // PerfCtr3
    msr = __asm_rdmsr(0xC0010209); // PerfCtr4
    msr = __asm_rdmsr(0xC001020B); // PerfCtr5
    msr = __asm_rdmsr(0xC0010230); // L2I_PerfEvtSel0
    msr = __asm_rdmsr(0xC0010232); // L2I_PerfEvtSel1
    msr = __asm_rdmsr(0xC0010234); // L2I_PerfEvtSel2
    msr = __asm_rdmsr(0xC0010236); // L2I_PerfEvtSel3
    msr = __asm_rdmsr(0xC0010231); // L2I_PerfCtr0
    msr = __asm_rdmsr(0xC0010233); // L2I_PerfCtr1
    msr = __asm_rdmsr(0xC0010235); // L2I_PerfCtr2
    msr = __asm_rdmsr(0xC0010237); // L2I_PerfCtr3
    msr = __asm_rdmsr(0xC0010240); // NB_PerfEvtSel0
    msr = __asm_rdmsr(0xC0010242); // NB_PerfEvtSel1
    msr = __asm_rdmsr(0xC0010244); // NB_PerfEvtSel2
    msr = __asm_rdmsr(0xC0010246); // NB_PerfEvtSel3
    msr = __asm_rdmsr(0xC0010241); // NB_PerfCtr0
    msr = __asm_rdmsr(0xC0010243); // NB_PerfCtr1
    msr = __asm_rdmsr(0xC0010245); // NB_PerfCtr2
    msr = __asm_rdmsr(0xC0010247); // NB_PerfCtr3
    msr = __asm_rdmsr(0xC00102B0); // CPPC_CAPABILITY_1 CPPC
    msr = __asm_rdmsr(0xC00102B1); // CPPC_ENABLE  CPPC
    msr = __asm_rdmsr(0xC00102B2); // CPPC_CAPABILITY_2 CPPC
    msr = __asm_rdmsr(0xC00102B3); // CPPC_REQUEST  CPPC
    msr = __asm_rdmsr(0xC00102B4); // CPPC_STATUS

    for (uint32_t i = 0; i < 0x20; ++i) {
        uint64_t LastBranchStackFromIp = __asm_rdmsr(0xC0010300 + i * 2);
        uint64_t LastBranchStackToIp = __asm_rdmsr(0xC0010301 + i * 2);

        UNREFERENCED_PARAMETER(LastBranchStackFromIp);
        UNREFERENCED_PARAMETER(LastBranchStackToIp);
    }

    msr = __asm_rdmsr(0xC0011019); // DR1_ADDR_MASK
    msr = __asm_rdmsr(0xC001101A); // DR2_ADDR_MASK
    msr = __asm_rdmsr(0xC001101B); // DR3_ADDR_MASK
    msr = __asm_rdmsr(0xC0011027); // DR0_ADDR_MASK
    msr = __asm_rdmsr(0xC0011095); // L3RangeReserveBaseAddr
    msr = __asm_rdmsr(0xC001109A); // L3RangeReserveWayMask

    CONTEXT Context;
    RtlCaptureContext(&Context);

    __asm_sidt;
    __asm_sgdt;

    return 0;
}

template <>
int
cleanup<Hash("AuthenticAMD")>(PVOID vcpu)
{
    return 0;
}
