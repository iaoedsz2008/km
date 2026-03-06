
/**
 * 用户为本，科技向善
 **/

#include "AuthenticAMD.h"

#include "GenuineIntel.h"

template <>
int
initialize<Hash("AuthenticAMD")>(PVOID vcpu)
{
    do {
        uint32_t eax;
        uint32_t ebx;
        uint32_t ecx;
        uint32_t edx;

        int LFuncStd; // Largest standard function
        int LFuncExt; // Largest extended function

        __asm_cpuid(0x00000000, &eax, &ebx, &ecx, &edx);
        LFuncStd = eax;

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
        if (ecx & (1U << 0x16)) // MOVBE - MOVBE instruction support
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
        if (edx & (1U << 0x17)) // MMX - MMX instructions
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
        if (ebx & (1U << 0x03)) // BMI1 - Bit manipulation group 1 instruction support
            ;
        if (ebx & (1U << 0x05)) // AVX2 - AVX2 instruction subset support
            ;
        if (ebx & (1U << 0x07)) // SMEP - Supervisor mode execution prevention
            ;
        if (ebx & (1U << 0x08)) // BMI2 - Bit manipulation group 2 instruction support
            ;
        if (ebx & (1U << 0x09)) // ERMS - Enhanced REP MOVSB/STOSB support
            ;
        if (ebx & (1U << 0x0A)) // INVPCID - INVPCID instruction support
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
        if (ebx & (1U << 0x14)) // SMAP - Supervisor mode access prevention
            ;
        if (ebx & (1U << 0x15)) // AVX512_IFMA - AVX512 Integer Fused Multiply-Add instructions support
            ;
        if (ebx & (1U << 0x17)) // CLFLUSHOPT - CLFLUSHOPT instruction support
            ;
        if (ebx & (1U << 0x18)) // CLWB - CLWB instruction support
            ;
        if (ebx & (1U << 0x1C)) // AVX512CD - AVX512 Conflict Detection for Vectorizing Loops
            ;
        if (ebx & (1U << 0x1D)) // SHA - Secure Hash Algorithm instruction extension
            ;
        if (ebx & (1U << 0x1E)) // AVX512BW - AVX512 Byte/Word Packed Integer instructions
            ;
        if (ebx & (1U << 0x1F)) // AVX512VL - AVX512 instructions are extended to 128 and 256 bits
            ;

        if (ecx & (1U << 0x01)) // AVX512_VBMI - AVX512 vector byte permutation instructions support
            ;
        if (ecx & (1U << 0x02)) // UMIP - User mode instruction prevention support
            ;
        if (ecx & (1U << 0x03)) // PKU - Memory Protection Keys supported
            ;
        if (ecx & (1U << 0x04)) // OSPKE - OS has enabled Memory Protection Keys and use of the RDPKRU/WRPKRU instructions by setting CR4.PKE=1
            ;
        if (ecx & (1U << 0x06)) // AVX512_VBMI2 - AVX512 vector byte permutation instruction 2 support
            ;
        if (ecx & (1U << 0x07)) // CET_SS - Shadow Stacks supported
            ;
        if (ecx & (1U << 0x08)) // GFNI - Galois Field New instructions support
            ;
        if (ecx & (1U << 0x09)) // VAES - VAES 256-bit instructions support
            ;
        if (ecx & (1U << 0x0A)) // VPCMULQDQ - VPCLMULQDQ 256-bit instruction support
            ;
        if (ecx & (1U << 0x0B)) // AVX512_VNNI - AVX512 vector neural network instructions support
            ;
        if (ecx & (1U << 0x0C)) // AVX512_BITALG - AVX512 bit algorithm instructions VPSHUFBITQMB and VPOPCNTB/W support
            ;
        if (ecx & (1U << 0x0E)) // AVX512_VPOPCNTDQ - AVX-512 VPOPCNTD/Q instruction support
            ;
        if (ecx & (1U << 0x0F)) // LA57 - 5-Level paging support
            ;
        if (ecx & (1U << 0x16)) // RDPID - RDPID instruction and TSC_AUX MSR support
            ;
        if (ecx & (1U << 0x18)) // BUSLOCKTRAP - Bus Lock Trap (#DB) support
            ;
        if (ecx & (1U << 0x1B)) // MOVDIRI - MOVDIRI instruction support
            ;
        if (ecx & (1U << 0x1C)) // MOVDIR64B - MOVDIR64B instruction support
            ;

        __asm_cpuid_ex(0x00000007, 1, &eax, &ebx, &ecx, &edx);

        if (edx & (1U << 0x04)) // AVX_VNNI - AVX Neural Network instructions
            ;
        if (edx & (1U << 0x05)) // AVX512_BF16 - AVX512 BFloat16 instructions
            ;

        __asm_cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
        LFuncExt = eax;

        if (LFuncExt < 0x00000001)
            break;

        __asm_cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

        if (ecx & (1U << 0x00)) // LahfSahf - LAHF and SAHF instruction support in 64-bit mode
            ;
        if (ecx & (1U << 0x01)) // CmpLegacy - Core multi-processing legacy mode
            ;
        if (ecx & (1U << 0x02)) // SVM - Secure virtual machine
            ;
        if (ecx & (1U << 0x03)) // ExtApicSpace - Extended APIC space
            ;
        if (ecx & (1U << 0x04)) // AltMovCr8 - LOCK MOV CR0 means MOV CR8
            ;
        if (ecx & (1U << 0x05)) // ABM - Advanced bit manipulation
            ;
        if (ecx & (1U << 0x06)) // SSE4A - EXTRQ, INSERTQ, MOVNTSS, and MOVNTSD instruction support
            ;
        if (ecx & (1U << 0x07)) // MisAlignSse - Misaligned SSE mode
            ;
        if (ecx & (1U << 0x08)) // 3DNowPrefetch - PREFETCH and PREFETCHW instruction support
            ;
        if (ecx & (1U << 0x09)) // OSVW - OS visible workaround
            ;
        if (ecx & (1U << 0x0A)) // IBS - Instruction based sampling
            ;
        if (ecx & (1U << 0x0B)) // XOP - Extended operation support
            ;
        if (ecx & (1U << 0x0C)) // SKINIT - SKINIT and STGI are supported
            ;
        if (ecx & (1U << 0x0D)) // WDT - Watchdog timer support
            ;
        if (ecx & (1U << 0x0E))
            ;
        if (ecx & (1U << 0x0F)) // LWP - Lightweight profiling support
            ;
        if (ecx & (1U << 0x10)) // FMA4 - Four-operand FMA instruction support
            ;
        if (ecx & (1U << 0x11)) // TCE -  Translation Cache Extension support
            ;
        if (ecx & (1U << 0x12))
            ;
        if (ecx & (1U << 0x13))
            ;
        if (ecx & (1U << 0x14))
            ;
        if (ecx & (1U << 0x15)) // TBM - Trailing bit manipulation instruction support
            ;
        if (ecx & (1U << 0x16)) // TopologyExtensions - Topology extensions support
            ;
        if (ecx & (1U << 0x17)) // PerfCtrExtCore - Processor performance counter extensions support
            ;
        if (ecx & (1U << 0x18)) // PerfCtrExtNB - NB performance counter extensions support
            ;
        if (ecx & (1U << 0x19))
            ;
        if (ecx & (1U << 0x1A)) // DataBkptExt - Data access breakpoint extension
            ;
        if (ecx & (1U << 0x1B)) // PerfTsc - Performance time-stamp counter
            ;
        if (ecx & (1U << 0x1C)) // PerfCtrExtLLC - Support for L3 performance counter extension
            ;
        if (ecx & (1U << 0x1D)) // MONITORX - Support for MWAITX and MONITORX instructions
            ;
        if (ecx & (1U << 0x1E)) // AddrMaskExt - Breakpoint Addressing masking extended to bit 31
            ;
        if (ecx & (1U << 0x1F))
            ;

        if (edx & (1U << 0x00))
            ;
        if (edx & (1U << 0x01))
            ;
        if (edx & (1U << 0x02))
            ;
        if (edx & (1U << 0x03))
            ;
        if (edx & (1U << 0x04))
            ;
        if (edx & (1U << 0x05))
            ;
        if (edx & (1U << 0x06))
            ;
        if (edx & (1U << 0x07))
            ;
        if (edx & (1U << 0x08))
            ;
        if (edx & (1U << 0x09))
            ;
        if (edx & (1U << 0x0A))
            ;
        if (edx & (1U << 0x0B))
            ;
        if (edx & (1U << 0x0C))
            ;
        if (edx & (1U << 0x0D))
            ;
        if (edx & (1U << 0x0E))
            ;
        if (edx & (1U << 0x0F))
            ;
        if (edx & (1U << 0x10))
            ;
        if (edx & (1U << 0x11))
            ;
        if (edx & (1U << 0x12))
            ;
        if (edx & (1U << 0x13))
            ;
        if (edx & (1U << 0x14))
            ;
        if (edx & (1U << 0x15))
            ;
        if (edx & (1U << 0x16))
            ;
        if (edx & (1U << 0x17))
            ;
        if (edx & (1U << 0x18))
            ;
        if (edx & (1U << 0x19))
            ;
        if (edx & (1U << 0x1A))
            ;
        if (edx & (1U << 0x1B))
            ;
        if (edx & (1U << 0x1C))
            ;
        if (edx & (1U << 0x1D))
            ;
        if (edx & (1U << 0x1E))
            ;
        if (edx & (1U << 0x1F))
            ;

        if (LFuncExt < 0x00000006)
            break;

        __asm_cpuid(0x80000005, &eax, &ebx, &ecx, &edx); // L1 Cache and TLB Information
        __asm_cpuid(0x80000006, &eax, &ebx, &ecx, &edx); // L2 Cache and TLB and L3 Cache Information

        if (LFuncExt < 0x0000000A)
            break;

        __asm_cpuid(0x80000007, &eax, &ebx, &ecx, &edx); // Processor Power Management and RAS Capabilities
        __asm_cpuid(0x80000008, &eax, &ebx, &ecx, &edx); // Processor Capacity Parameters and Extended Feature Identification

        __asm_cpuid(0x8000000A, &eax, &ebx, &ecx, &edx); // SVM Features

        uint8_t SvmRev = (uint8_t)eax; // SvmRev - SVM revision number
        int NASID = (int)ebx;          // NASID - Number of available address space identifiers (ASID)

        if (ecx & (1U << 0x06)) // x2AVIC_EXT - 4096 vCPUs supported in x2AVIC mode
            ;

        if (edx & (1U << 0x00)) // NP - Nested paging
            ;
        if (edx & (1U << 0x01)) // LbrVirt - LBR virtualization
            ;
        if (edx & (1U << 0x02)) // SVML - SVM lock
            ;
        if (edx & (1U << 0x03)) // NRIPS - NRIP save
            ;
        if (edx & (1U << 0x04)) // TscRateMsr - MSR based TSC rate control
            ;
        if (edx & (1U << 0x05)) // VmcbClean - VMCB clean bits
            ;
        if (edx & (1U << 0x06)) // FlushByAsid - Flush by ASID
            ;
        if (edx & (1U << 0x07)) // DecodeAssists - Decode assists
            ;
        if (edx & (1U << 0x08)) // PmcVirt - PMC virtualization
            ;
        if (edx & (1U << 0x09))
            ;
        if (edx & (1U << 0x0A)) // PauseFilter - Pause intercept filter
            ;
        if (edx & (1U << 0x0B))
            ;
        if (edx & (1U << 0x0C)) // PauseFilterThreshold - PAUSE filter threshold
            ;
        if (edx & (1U << 0x0D)) // AVIC - Support for the AMD advanced virtual interrupt controller
            ;
        if (edx & (1U << 0x0E))
            ;
        if (edx & (1U << 0x0F)) // VMSAVEvirt - VMSAVE and VMLOAD virtualization
            ;
        if (edx & (1U << 0x10)) // VGIF - Virtualize the Global Interrupt Flag
            ;
        if (edx & (1U << 0x11)) // GMET - Guest Mode Execution Trap
            ;
        if (edx & (1U << 0x12)) // x2AVIC - Support for the AMD advanced virtual interrupt controller for x2APIC mode
            ;
        if (edx & (1U << 0x13)) // SSSCheck - SVM supervisor shadow stack restrictions
            ;
        if (edx & (1U << 0x14)) // SpecCtrl - SPEC_CTRL virtualization
            ;
        if (edx & (1U << 0x15)) // ROGPT - Read-Only Guest Page Table feature support
            ;
        if (edx & (1U << 0x16))
            ;
        if (edx & (1U << 0x17)) // HOST_MCE_OVERRIDE - When host CR4.MCE=1 and guest CR4.MCE=0, machine check exceptions (#MC) in a guest do not cause shutdown and are always intercepted
            ;
        if (edx & (1U << 0x18)) // TlbiCtl - INVLPGB/TLBSYNC hypervisor enable in VMCB and TLBSYNC intercept support
            ;
        if (edx & (1U << 0x19)) // VNMI - NMI Virtualization
            ;
        if (edx & (1U << 0x1A)) // IbsVirt - IBS Virtualization
            ;
        if (edx & (1U << 0x1B)) // ExtLvtAvicAccessChg - Extended Interrupt Local Vector Table Register AVIC Access changes
            ;
        if (edx & (1U << 0x1C)) // NestedVirtVmcbAddrChk - Guest VMCB address check
            ;
        if (edx & (1U << 0x1D)) // BusLockThreshold - Bus Lock Threshold
            ;
        if (edx & (1U << 0x1E)) // IdleHltIntercept - Idle HLT intercept
            ;
        if (edx & (1U << 0x1F))
            ;

        __asm_cpuid(0x80000019, &eax, &ebx, &ecx, &edx); // TLB Characteristics for 1GB pages
        __asm_cpuid(0x8000001A, &eax, &ebx, &ecx, &edx); // Instruction Optimizations
        __asm_cpuid(0x8000001B, &eax, &ebx, &ecx, &edx); // Instruction-Based Sampling Capabilities
        __asm_cpuid(0x8000001C, &eax, &ebx, &ecx, &edx); // Lightweight Profiling Capabilities
        __asm_cpuid(0x8000001D, &eax, &ebx, &ecx, &edx); // Cache Topology Information
        __asm_cpuid(0x8000001E, &eax, &ebx, &ecx, &edx); // Processor Topology Information
        __asm_cpuid(0x8000001F, &eax, &ebx, &ecx, &edx); // SEV Capabilities
        __asm_cpuid(0x80000020, &eax, &ebx, &ecx, &edx); // PQOS Extended Features
        __asm_cpuid(0x80000021, &eax, &ebx, &ecx, &edx); // Extended Feature Identification 2
        __asm_cpuid(0x80000022, &eax, &ebx, &ecx, &edx); // Extended Performance Monitoring and Debug
        __asm_cpuid(0x80000023, &eax, &ebx, &ecx, &edx); // Multi-Key Encrypted Memory Capabilities
        __asm_cpuid(0x80000024, &eax, &ebx, &ecx, &edx); //
        __asm_cpuid(0x80000025, &eax, &ebx, &ecx, &edx); // SEV Capabilities 2
        __asm_cpuid(0x80000026, &eax, &ebx, &ecx, &edx); // Extended CPU Topology
    } while (0);

    do {
        uint64_t CR0 = __asm_cr0();
        // uint64_t CR1 = __asm_cr1();
        uint64_t CR2 = __asm_cr2(); // Page-Fault Linear Address
        uint64_t CR3 = __asm_cr3();
        uint64_t CR4 = __asm_cr4();

        if (CR0 & (1U << 0x00)) // CR0.PE Protection Enable (bit 0 of CR0)
            ;
        if (CR0 & (1U << 0x01)) // CR0.MP Monitor Coprocessor (bit 1 of CR0)
            ;
        if (CR0 & (1U << 0x02)) // CR0.EM Emulation (bit 2 of CR0)
            ;
        if (CR0 & (1U << 0x03)) // CR0.TS Task Switched (bit 3 of CR0)
            ;
        if (CR0 & (1U << 0x04)) // CR0.ET Extension Type (bit 4 of CR0)
            ;
        if (CR0 & (1U << 0x05)) // CR0.NE Numeric Error (bit 5 of CR0)
            ;
        if (CR0 & (1U << 0x10)) // CR0.WP Write Protect (bit 16 of CR0)
            ;
        if (CR0 & (1U << 0x12)) // CR0.AM Alignment Mask (bit 18 of CR0)
            ;
        if (CR0 & (1U << 0x1D)) // CR0.NW Not Write-through (bit 29 of CR0)
            ;
        if (CR0 & (1U << 0x1E)) // CR0.CD Cache Disable (bit 30 of CR0)
            ;
        if (CR0 & (1U << 0x1F)) // CR0.PG Paging (bit 31 of CR0)
            ;

        if (CR3 & (1ULL << 0x03)) // CR3.PWT Page-level Write-Through (bit 3 of CR3)
            ;
        if (CR3 & (1ULL << 0x04)) // CR3.PCD Page-level Cache Disable (bit 4 of CR3)
            ;

        if (CR4 & (1ULL << 0x00)) // CR4.VME Virtual-8086 Mode Extensions (bit 0 of CR4)
            ;
        if (CR4 & (1ULL << 0x01)) // CR4.PVI Protected-Mode Virtual Interrupts (bit 1 of CR4)
            ;
        if (CR4 & (1ULL << 0x02)) // CR4.TSD Time Stamp Disable (bit 2 of CR4)
            ;
        if (CR4 & (1ULL << 0x03)) // CR4.DE Debugging Extensions (bit 3 of CR4)
            ;
        if (CR4 & (1ULL << 0x04)) // CR4.PSE Page Size Extensions (bit 4 of CR4)
            ;
        if (CR4 & (1ULL << 0x05)) // CR4.PAE Physical Address Extension (bit 5 of CR4)
            ;
        if (CR4 & (1ULL << 0x06)) // CR4.MCE Machine-Check Enable (bit 6 of CR4)
            ;
        if (CR4 & (1ULL << 0x07)) // CR4.PGE Page Global Enable (bit 7 of CR4)
            ;
        if (CR4 & (1ULL << 0x08)) // CR4.PCE Performance-Monitoring Counter Enable (bit 8 of CR4)
            ;
        if (CR4 & (1ULL << 0x09)) // CR4.OSFXSR Operating System Support for FXSAVE and FXRSTOR instructions (bit 9 of CR4)
            ;
        if (CR4 & (1ULL << 0x0A)) // CR4.OSXMMEXCPT Operating System Support for Unmasked SIMD Floating-Point Exceptions (bit 10 of CR4)
            ;
        if (CR4 & (1ULL << 0x0B)) // CR4.UMIP User-Mode Instruction Prevention (bit 11 of CR4)
            ;
        if (CR4 & (1ULL << 0x0C)) // CR4.LA57 57-bit linear addresses (bit 12 of CR4)
            ;
        if (CR4 & (1ULL << 0x10)) // CR4.FSGSBASE FSGSBASE-Enable Bit (bit 16 of CR4)
            ;
        if (CR4 & (1ULL << 0x11)) // CR4.PCIDE PCID-Enable Bit (bit 17 of CR4)
            ;
        if (CR4 & (1ULL << 0x12)) // CR4.OSXSAVE XSAVE and Processor Extended States-Enable Bit (bit 18 of CR4)
            ;
        if (CR4 & (1ULL << 0x14)) // CR4.SMEP SMEP-Enable Bit (bit 20 of CR4)
            ;
        if (CR4 & (1ULL << 0x15)) // CR4.SMAP SMAP-Enable Bit (bit 21 of CR4)
            ;
        if (CR4 & (1ULL << 0x16)) // CR4.PKE Enable protection keys for user-mode pages (bit 22 of CR4)
            ;
        if (CR4 & (1ULL << 0x17)) // CR4.CET Control-flow Enforcement Technology (bit 23 of CR4)
            ;

    } while (0);

    do {
        uint64_t msr;

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
    } while (0);

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
