
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
