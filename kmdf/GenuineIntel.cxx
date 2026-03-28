
/**
 * 用户为本，科技向善
 **/

#include "GenuineIntel.h"

#include <stddef.h>
#include <stdint.h>

// Taken: VirtualBox/include/VBox/vmm/hm_vmx.h

/** @name VMCS fields and encoding.
 *
 *  When adding a new field:
 *    - Always add it to g_aVmcsFields.
 *    - Consider if it needs to be added to VMXVVMCS.
 * @{
 */
/** 16-bit control fields.  */
#define VMX_VMCS16_VPID                            0x0000
#define VMX_VMCS16_POSTED_INT_NOTIFY_VECTOR        0x0002
#define VMX_VMCS16_EPTP_INDEX                      0x0004

/** 16-bit guest-state fields.  */
#define VMX_VMCS16_GUEST_ES_SEL                    0x0800
#define VMX_VMCS16_GUEST_CS_SEL                    0x0802
#define VMX_VMCS16_GUEST_SS_SEL                    0x0804
#define VMX_VMCS16_GUEST_DS_SEL                    0x0806
#define VMX_VMCS16_GUEST_FS_SEL                    0x0808
#define VMX_VMCS16_GUEST_GS_SEL                    0x080A
#define VMX_VMCS16_GUEST_LDTR_SEL                  0x080C
#define VMX_VMCS16_GUEST_TR_SEL                    0x080E
#define VMX_VMCS16_GUEST_INTR_STATUS               0x0810
#define VMX_VMCS16_GUEST_PML_INDEX                 0x0812

/** 16-bits host-state fields.  */
#define VMX_VMCS16_HOST_ES_SEL                     0x0C00
#define VMX_VMCS16_HOST_CS_SEL                     0x0C02
#define VMX_VMCS16_HOST_SS_SEL                     0x0C04
#define VMX_VMCS16_HOST_DS_SEL                     0x0C06
#define VMX_VMCS16_HOST_FS_SEL                     0x0C08
#define VMX_VMCS16_HOST_GS_SEL                     0x0C0A
#define VMX_VMCS16_HOST_TR_SEL                     0x0C0C

/** 64-bit control fields. */
#define VMX_VMCS64_CTRL_IO_BITMAP_A_FULL           0x2000
#define VMX_VMCS64_CTRL_IO_BITMAP_A_HIGH           0x2001
#define VMX_VMCS64_CTRL_IO_BITMAP_B_FULL           0x2002
#define VMX_VMCS64_CTRL_IO_BITMAP_B_HIGH           0x2003
#define VMX_VMCS64_CTRL_MSR_BITMAP_FULL            0x2004
#define VMX_VMCS64_CTRL_MSR_BITMAP_HIGH            0x2005
#define VMX_VMCS64_CTRL_EXIT_MSR_STORE_FULL        0x2006
#define VMX_VMCS64_CTRL_EXIT_MSR_STORE_HIGH        0x2007
#define VMX_VMCS64_CTRL_EXIT_MSR_LOAD_FULL         0x2008
#define VMX_VMCS64_CTRL_EXIT_MSR_LOAD_HIGH         0x2009
#define VMX_VMCS64_CTRL_ENTRY_MSR_LOAD_FULL        0x200A
#define VMX_VMCS64_CTRL_ENTRY_MSR_LOAD_HIGH        0x200B
#define VMX_VMCS64_CTRL_EXEC_VMCS_PTR_FULL         0x200C
#define VMX_VMCS64_CTRL_EXEC_VMCS_PTR_HIGH         0x200D
#define VMX_VMCS64_CTRL_EXEC_PML_ADDR_FULL         0x200E
#define VMX_VMCS64_CTRL_EXEC_PML_ADDR_HIGH         0x200F
#define VMX_VMCS64_CTRL_TSC_OFFSET_FULL            0x2010
#define VMX_VMCS64_CTRL_TSC_OFFSET_HIGH            0x2011
#define VMX_VMCS64_CTRL_VIRT_APIC_PAGEADDR_FULL    0x2012
#define VMX_VMCS64_CTRL_VIRT_APIC_PAGEADDR_HIGH    0x2013
#define VMX_VMCS64_CTRL_APIC_ACCESSADDR_FULL       0x2014
#define VMX_VMCS64_CTRL_APIC_ACCESSADDR_HIGH       0x2015
#define VMX_VMCS64_CTRL_POSTED_INTR_DESC_FULL      0x2016
#define VMX_VMCS64_CTRL_POSTED_INTR_DESC_HIGH      0x2017
#define VMX_VMCS64_CTRL_VMFUNC_CTRLS_FULL          0x2018
#define VMX_VMCS64_CTRL_VMFUNC_CTRLS_HIGH          0x2019
#define VMX_VMCS64_CTRL_EPTP_FULL                  0x201A
#define VMX_VMCS64_CTRL_EPTP_HIGH                  0x201B
#define VMX_VMCS64_CTRL_EOI_BITMAP_0_FULL          0x201C
#define VMX_VMCS64_CTRL_EOI_BITMAP_0_HIGH          0x201D
#define VMX_VMCS64_CTRL_EOI_BITMAP_1_FULL          0x201E
#define VMX_VMCS64_CTRL_EOI_BITMAP_1_HIGH          0x201F
#define VMX_VMCS64_CTRL_EOI_BITMAP_2_FULL          0x2020
#define VMX_VMCS64_CTRL_EOI_BITMAP_2_HIGH          0x2021
#define VMX_VMCS64_CTRL_EOI_BITMAP_3_FULL          0x2022
#define VMX_VMCS64_CTRL_EOI_BITMAP_3_HIGH          0x2023
#define VMX_VMCS64_CTRL_EPTP_LIST_FULL             0x2024
#define VMX_VMCS64_CTRL_EPTP_LIST_HIGH             0x2025
#define VMX_VMCS64_CTRL_VMREAD_BITMAP_FULL         0x2026
#define VMX_VMCS64_CTRL_VMREAD_BITMAP_HIGH         0x2027
#define VMX_VMCS64_CTRL_VMWRITE_BITMAP_FULL        0x2028
#define VMX_VMCS64_CTRL_VMWRITE_BITMAP_HIGH        0x2029
#define VMX_VMCS64_CTRL_VIRTXCPT_INFO_ADDR_FULL    0x202A
#define VMX_VMCS64_CTRL_VIRTXCPT_INFO_ADDR_HIGH    0x202B
#define VMX_VMCS64_CTRL_XSS_EXITING_BITMAP_FULL    0x202C
#define VMX_VMCS64_CTRL_XSS_EXITING_BITMAP_HIGH    0x202D
#define VMX_VMCS64_CTRL_ENCLS_EXITING_BITMAP_FULL  0x202E
#define VMX_VMCS64_CTRL_ENCLS_EXITING_BITMAP_HIGH  0x202F
#define VMX_VMCS64_CTRL_TSC_MULTIPLIER_FULL        0x2032
#define VMX_VMCS64_CTRL_TSC_MULTIPLIER_HIGH        0x2033
#define VMX_VMCS64_CTRL_PROC_EXEC3_FULL            0x2034
#define VMX_VMCS64_CTRL_PROC_EXEC3_HIGH            0x2035

/** 64-bit read-only data fields.  */
#define VMX_VMCS64_RO_GUEST_PHYS_ADDR_FULL         0x2400
#define VMX_VMCS64_RO_GUEST_PHYS_ADDR_HIGH         0x2401

/** 64-bit guest-state fields.  */
#define VMX_VMCS64_GUEST_VMCS_LINK_PTR_FULL        0x2800
#define VMX_VMCS64_GUEST_VMCS_LINK_PTR_HIGH        0x2801
#define VMX_VMCS64_GUEST_DEBUGCTL_FULL             0x2802
#define VMX_VMCS64_GUEST_DEBUGCTL_HIGH             0x2803
#define VMX_VMCS64_GUEST_PAT_FULL                  0x2804
#define VMX_VMCS64_GUEST_PAT_HIGH                  0x2805
#define VMX_VMCS64_GUEST_EFER_FULL                 0x2806
#define VMX_VMCS64_GUEST_EFER_HIGH                 0x2807
#define VMX_VMCS64_GUEST_PERF_GLOBAL_CTRL_FULL     0x2808
#define VMX_VMCS64_GUEST_PERF_GLOBAL_CTRL_HIGH     0x2809
#define VMX_VMCS64_GUEST_PDPTE0_FULL               0x280A
#define VMX_VMCS64_GUEST_PDPTE0_HIGH               0x280B
#define VMX_VMCS64_GUEST_PDPTE1_FULL               0x280C
#define VMX_VMCS64_GUEST_PDPTE1_HIGH               0x280D
#define VMX_VMCS64_GUEST_PDPTE2_FULL               0x280E
#define VMX_VMCS64_GUEST_PDPTE2_HIGH               0x280F
#define VMX_VMCS64_GUEST_PDPTE3_FULL               0x2810
#define VMX_VMCS64_GUEST_PDPTE3_HIGH               0x2811
#define VMX_VMCS64_GUEST_BNDCFGS_FULL              0x2812
#define VMX_VMCS64_GUEST_BNDCFGS_HIGH              0x2813

/** 64-bit host-state fields.  */
#define VMX_VMCS64_HOST_PAT_FULL                   0x2C00
#define VMX_VMCS64_HOST_PAT_HIGH                   0x2C01
#define VMX_VMCS64_HOST_EFER_FULL                  0x2C02
#define VMX_VMCS64_HOST_EFER_HIGH                  0x2C03
#define VMX_VMCS64_HOST_PERF_GLOBAL_CTRL_FULL      0x2C04
#define VMX_VMCS64_HOST_PERF_GLOBAL_CTRL_HIGH      0x2C05

/** 32-bit control fields.  */
#define VMX_VMCS32_CTRL_PIN_EXEC                   0x4000
#define VMX_VMCS32_CTRL_PROC_EXEC                  0x4002
#define VMX_VMCS32_CTRL_EXCEPTION_BITMAP           0x4004
#define VMX_VMCS32_CTRL_PAGEFAULT_ERROR_MASK       0x4006
#define VMX_VMCS32_CTRL_PAGEFAULT_ERROR_MATCH      0x4008
#define VMX_VMCS32_CTRL_CR3_TARGET_COUNT           0x400A
#define VMX_VMCS32_CTRL_EXIT                       0x400C
#define VMX_VMCS32_CTRL_EXIT_MSR_STORE_COUNT       0x400E
#define VMX_VMCS32_CTRL_EXIT_MSR_LOAD_COUNT        0x4010
#define VMX_VMCS32_CTRL_ENTRY                      0x4012
#define VMX_VMCS32_CTRL_ENTRY_MSR_LOAD_COUNT       0x4014
#define VMX_VMCS32_CTRL_ENTRY_INTERRUPTION_INFO    0x4016
#define VMX_VMCS32_CTRL_ENTRY_EXCEPTION_ERRCODE    0x4018
#define VMX_VMCS32_CTRL_ENTRY_INSTR_LENGTH         0x401A
#define VMX_VMCS32_CTRL_TPR_THRESHOLD              0x401C
#define VMX_VMCS32_CTRL_PROC_EXEC2                 0x401E
#define VMX_VMCS32_CTRL_PLE_GAP                    0x4020
#define VMX_VMCS32_CTRL_PLE_WINDOW                 0x4022

/** 32-bits read-only fields. */
#define VMX_VMCS32_RO_VM_INSTR_ERROR               0x4400
#define VMX_VMCS32_RO_EXIT_REASON                  0x4402
#define VMX_VMCS32_RO_EXIT_INTERRUPTION_INFO       0x4404
#define VMX_VMCS32_RO_EXIT_INTERRUPTION_ERROR_CODE 0x4406
#define VMX_VMCS32_RO_IDT_VECTORING_INFO           0x4408
#define VMX_VMCS32_RO_IDT_VECTORING_ERROR_CODE     0x440A
#define VMX_VMCS32_RO_EXIT_INSTR_LENGTH            0x440C
#define VMX_VMCS32_RO_EXIT_INSTR_INFO              0x440E

/** 32-bit guest-state fields. */
#define VMX_VMCS32_GUEST_ES_LIMIT                  0x4800
#define VMX_VMCS32_GUEST_CS_LIMIT                  0x4802
#define VMX_VMCS32_GUEST_SS_LIMIT                  0x4804
#define VMX_VMCS32_GUEST_DS_LIMIT                  0x4806
#define VMX_VMCS32_GUEST_FS_LIMIT                  0x4808
#define VMX_VMCS32_GUEST_GS_LIMIT                  0x480A
#define VMX_VMCS32_GUEST_LDTR_LIMIT                0x480C
#define VMX_VMCS32_GUEST_TR_LIMIT                  0x480E
#define VMX_VMCS32_GUEST_GDTR_LIMIT                0x4810
#define VMX_VMCS32_GUEST_IDTR_LIMIT                0x4812
#define VMX_VMCS32_GUEST_ES_ACCESS_RIGHTS          0x4814
#define VMX_VMCS32_GUEST_CS_ACCESS_RIGHTS          0x4816
#define VMX_VMCS32_GUEST_SS_ACCESS_RIGHTS          0x4818
#define VMX_VMCS32_GUEST_DS_ACCESS_RIGHTS          0x481A
#define VMX_VMCS32_GUEST_FS_ACCESS_RIGHTS          0x481C
#define VMX_VMCS32_GUEST_GS_ACCESS_RIGHTS          0x481E
#define VMX_VMCS32_GUEST_LDTR_ACCESS_RIGHTS        0x4820
#define VMX_VMCS32_GUEST_TR_ACCESS_RIGHTS          0x4822
#define VMX_VMCS32_GUEST_INT_STATE                 0x4824
#define VMX_VMCS32_GUEST_ACTIVITY_STATE            0x4826
#define VMX_VMCS32_GUEST_SMBASE                    0x4828
#define VMX_VMCS32_GUEST_SYSENTER_CS               0x482A
#define VMX_VMCS32_PREEMPT_TIMER_VALUE             0x482E

/** 32-bit host-state fields. */
#define VMX_VMCS32_HOST_SYSENTER_CS                0x4C00

/** Natural-width control fields.  */
#define VMX_VMCS_CTRL_CR0_MASK                     0x6000
#define VMX_VMCS_CTRL_CR4_MASK                     0x6002
#define VMX_VMCS_CTRL_CR0_READ_SHADOW              0x6004
#define VMX_VMCS_CTRL_CR4_READ_SHADOW              0x6006
#define VMX_VMCS_CTRL_CR3_TARGET_VAL0              0x6008
#define VMX_VMCS_CTRL_CR3_TARGET_VAL1              0x600A
#define VMX_VMCS_CTRL_CR3_TARGET_VAL2              0x600C
#define VMX_VMCS_CTRL_CR3_TARGET_VAL3              0x600E

/** Natural-width read-only data fields. */
#define VMX_VMCS_RO_EXIT_QUALIFICATION             0x6400
#define VMX_VMCS_RO_IO_RCX                         0x6402
#define VMX_VMCS_RO_IO_RSI                         0x6404
#define VMX_VMCS_RO_IO_RDI                         0x6406
#define VMX_VMCS_RO_IO_RIP                         0x6408
#define VMX_VMCS_RO_GUEST_LINEAR_ADDR              0x640A

/** Natural-width guest-state fields. */
#define VMX_VMCS_GUEST_CR0                         0x6800
#define VMX_VMCS_GUEST_CR3                         0x6802
#define VMX_VMCS_GUEST_CR4                         0x6804
#define VMX_VMCS_GUEST_ES_BASE                     0x6806
#define VMX_VMCS_GUEST_CS_BASE                     0x6808
#define VMX_VMCS_GUEST_SS_BASE                     0x680A
#define VMX_VMCS_GUEST_DS_BASE                     0x680C
#define VMX_VMCS_GUEST_FS_BASE                     0x680E
#define VMX_VMCS_GUEST_GS_BASE                     0x6810
#define VMX_VMCS_GUEST_LDTR_BASE                   0x6812
#define VMX_VMCS_GUEST_TR_BASE                     0x6814
#define VMX_VMCS_GUEST_GDTR_BASE                   0x6816
#define VMX_VMCS_GUEST_IDTR_BASE                   0x6818
#define VMX_VMCS_GUEST_DR7                         0x681A
#define VMX_VMCS_GUEST_RSP                         0x681C
#define VMX_VMCS_GUEST_RIP                         0x681E
#define VMX_VMCS_GUEST_RFLAGS                      0x6820
#define VMX_VMCS_GUEST_PENDING_DEBUG_XCPTS         0x6822
#define VMX_VMCS_GUEST_SYSENTER_ESP                0x6824
#define VMX_VMCS_GUEST_SYSENTER_EIP                0x6826

/** Natural-width host-state fields. */
#define VMX_VMCS_HOST_CR0                          0x6C00
#define VMX_VMCS_HOST_CR3                          0x6C02
#define VMX_VMCS_HOST_CR4                          0x6C04
#define VMX_VMCS_HOST_FS_BASE                      0x6C06
#define VMX_VMCS_HOST_GS_BASE                      0x6C08
#define VMX_VMCS_HOST_TR_BASE                      0x6C0A
#define VMX_VMCS_HOST_GDTR_BASE                    0x6C0C
#define VMX_VMCS_HOST_IDTR_BASE                    0x6C0E
#define VMX_VMCS_HOST_SYSENTER_ESP                 0x6C10
#define VMX_VMCS_HOST_SYSENTER_EIP                 0x6C12
#define VMX_VMCS_HOST_RSP                          0x6C14
#define VMX_VMCS_HOST_RIP                          0x6C16

typedef struct VM {
} VM;

typedef struct VMContext {
    uint64_t RAX;
    uint64_t RBX;
    uint64_t RCX;
    uint64_t RDX;
    uint64_t RDI;
    uint64_t RSI;
    uint64_t RBP;
    uint64_t RSP;
    uint64_t R8;
    uint64_t R9;
    uint64_t R10;
    uint64_t R11;
    uint64_t R12;
    uint64_t R13;
    uint64_t R14;
    uint64_t R15;
} VMContext;

typedef struct VMCpu {
    VM* VM;

    void* IoBitmap;
    void* MsrBitmap;
    void* VmcbHost;
    void* VmcbGuest;

    PHYSICAL_ADDRESS IoBitmapPa;
    PHYSICAL_ADDRESS MsrBitmapPa;
    PHYSICAL_ADDRESS VmcsHostPa;
    PHYSICAL_ADDRESS VmcsGuestPa;
} VMCpu;

static uint64_t* PML4 = {};
static uint64_t EPTP = {};
static int (*Procedures[0x100])(VMContext* ctx);

static FORCEINLINE uint32_t
__lar(uint16_t selector)
{
    uint32_t val = 0;
    uint8_t zf = 0;

    if ((selector & 0xFFF8) == 0)
        return 0;

    __asm__ __volatile__("lar %2, %0; setz %1" : "=r"(val), "=qm"(zf) : "r"(selector) : "cc");
    if (!zf)
        return 0;

    return val;
}

static size_t
__lsb(uint16_t selector)
{
    IA32_GDT_REGISTER GDTR;
    size_t SegmentBase = {};
    size_t SegmentLimit = {};

    __asm_sgdt(&GDTR);

    uint16_t RPL = (selector >> 0x00) & 0x00000003;
    uint16_t TI = (selector >> 0x02) & 0x00000001;
    uint16_t I = (selector >> 0x03) & 0x00001FFF;

    if (TI) {
        // use local descriptor table
    } else {
        // use global descriptor table
        uint64_t descriptor = ((uint64_t*)GDTR.BaseAddress)[I];

        // 3.4.5 Segment Descriptors
        auto TYPE = ((descriptor >> 0x28) & 0x0000000F); // TYPE - Segment type
        auto S = ((descriptor >> 0x2C) & 0x00000001);    // S - Descriptor type (0 = system; 1 = code or data)
        auto DPL = ((descriptor >> 0x2D) & 0x00000003);  // DPL - Descriptor privilege level
        auto P = ((descriptor >> 0x2F) & 0x00000001);    // P - Segment present
        auto AVL = ((descriptor >> 0x34) & 0x00000001);  // AVL - Available for use by system software
        auto L = ((descriptor >> 0x35) & 0x00000001);    // L - 64-bit code segment (IA-32e mode only)
        auto DB = ((descriptor >> 0x36) & 0x00000001);   // D/B - Default operation size (0 = 16-bit segment; 1 = 32-bit segment)
        auto G = ((descriptor >> 0x37) & 0x00000001);    // G - Granularity

        SegmentLimit |= ((descriptor >> 0x00) & 0x0000FFFF) << 0x00;
        SegmentLimit |= ((descriptor >> 0x30) & 0x0000000F) << 0x10;

        SegmentBase |= ((descriptor >> 0x10) & 0x0000FFFF) << 0x00;
        SegmentBase |= ((descriptor >> 0x20) & 0x000000FF) << 0x10;
        SegmentBase |= ((descriptor >> 0x38) & 0x000000FF) << 0x18;

#if defined(_M_AMD64) || defined(__x86_64__)
        if (S == 0) {
            descriptor = ((uint64_t*)GDTR.BaseAddress)[I + 1];
            SegmentBase |= (descriptor << 32) & 0xFFFFFFFF00000000;
        }
#endif
    }

    return SegmentBase;
}

static FORCEINLINE uint32_t
__lsl(uint16_t selector)
{
    uint32_t val = 0;
    uint8_t zf = 0;

    if ((selector & 0xFFF8) == 0)
        return 0;

    __asm__ __volatile__("lsl %2, %0; setz %1" : "=r"(val), "=qm"(zf) : "r"(selector) : "cc");
    if (!zf)
        return 0;

    return val;
}

static FORCEINLINE uint64_t
vmx_format_controls(uint32_t msr, uint64_t bits)
{
    uint64_t v = __asm_rdmsr(msr);

    bits &= (v >> 32ULL);        /* bit == 0 in high word ==> must be zero */
    bits |= (v & 0xFFFFFFFFULL); /* bit == 1 in low word  ==> must be one  */

    return bits;
}

// See: Format of Access Rights
static FORCEINLINE uint32_t
vmx_format_access_rights(uint32_t access_rights)
{
    uint32_t result = {};

    if (access_rights) {
        result |= (((access_rights >> 0x08) & 0x0000000F) << 0x00); // 3:0 Segment type
        result |= (((access_rights >> 0x0C) & 0x00000001) << 0x04); // 4 S - Descriptor type (0 = system; 1 = code or data)
        result |= (((access_rights >> 0x0D) & 0x00000003) << 0x05); // 6:5 DPL - Descriptor privilege level
        result |= (((access_rights >> 0x0F) & 0x00000001) << 0x07); // 7 P - Segment present
        result |= (((access_rights >> 0x14) & 0x00000001) << 0x0C); // 12 AVL - Available for use by system software
        result |= (((access_rights >> 0x15) & 0x00000001) << 0x0D); // 13 Reserved (except for CS) L - 64-bit mode active (for CS only)
        result |= (((access_rights >> 0x16) & 0x00000001) << 0x0E); // 14 D/B - Default operation size (0 = 16-bit segment; 1 = 32-bit segment)
        result |= (((access_rights >> 0x17) & 0x00000001) << 0x0F); // 15 G - Granularity
    } else {
        result |= (1U << 0x10); // 16 Segment unusable (0 = usable; 1 = unusable)
    }

    return result;
}

template <size_t>
static uint64_t buildPML5E(uint64_t, uint64_t);

template <size_t>
static uint64_t buildPML4E(uint64_t, uint64_t);

template <size_t>
static uint64_t buildPDPTE(uint64_t, uint64_t);

template <size_t>
static uint64_t buildPDE(uint64_t, uint64_t);

template <size_t>
static uint64_t buildPTE(uint64_t, uint64_t);

uint64_t
buildEPTP(uint64_t EPT)
{
    /**
     * Format of Extended-Page-Table Pointer
     **/

    uint64_t EPTP = {};

    /**
     * EPT paging-structure memory type (see Section 31.3.7):
     *   0 = Uncacheable (UC)
     *   6 = Write-back (WB)
     * Other values are reserved.
     **/
    EPTP |= ((6ULL & 0x07) << 0x00);

    /**
     * This value is 1 less than the EPT page-walk length (see Section 31.3.2)
     **/
    EPTP |= ((3ULL & 0x07) << 0x03);

    /**
     * Setting this control to 1 enables accessed and dirty flags for EPT (see Section 31.3.5)
     **/
    EPTP |= (0ULL << 0x06);

    /**
     * Setting this control to 1 enables enforcement of access rights for supervisor shadow-stack pages (see Section 31.3.3.2)
     **/
    EPTP |= (0ULL << 0x07);

    /**
     * Bits M–1:12 of the physical address of the 4-KByte aligned EPT paging-structure (an EPT PML4 table with 4-level EPT and an EPT PML5 table with 5-level EPT)
     **/
    EPTP |= ((uint64_t)EPT & 0x0000FFFFFFFFF000);

    return EPTP;
}

template <>
uint64_t
buildPML5E<0x1000>(uint64_t PML4, uint64_t)
{
    uint64_t PML5E = {};

    /**
     * Format of an EPT PML5 Entry (PML5E) that References an EPT PML4 Table
     **/

    /**
     * 0 Read access; indicates whether reads are allowed from the 256-TByte region controlled by this entry.
     **/
    PML5E |= (1ULL << 0x00);

    /**
     * 1 Write access; indicates whether writes are allowed to the 256-TByte region controlled by this entry.
     **/
    PML5E |= (1ULL << 0x01);

    /**
     * 2
     * If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether instruction fetches are allowed from the 256-TByte region controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are allowed from supervisor-mode linear addresses in the 256-TByte region controlled by this entry.
     **/
    PML5E |= (1ULL << 0x02);

    /**
     * 8 If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 256-TByte region controlled by this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PML5E |= (1ULL << 0x08);

    /**
     * 10
     * Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control is 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 256-TByte region controlled by this entry.
     * If that control is 0, this bit is ignored.
     **/
    PML5E |= (1ULL << 0x0A);

    /**
     * M–1:12 Physical address of 4-KByte aligned EPT PML4 table referenced by this entry.
     **/
    PML5E |= ((uint64_t)PML4 & 0xFFFFFFFFFFFFF000);

    /**
     * 51:M Reserved (must be 0).
     **/

    return PML5E;
}

template <>
uint64_t
buildPML4E<0x1000>(uint64_t PDPT, uint64_t)
{
    uint64_t PML4E = {};

    /**
     * Format of an EPT PML4 Entry (PML4E) that References an EPT Page-Directory-Pointer Table
     **/

    /**
     * 0 Read access; indicates whether reads are allowed from the 512-GByte region controlled by this entry.
     **/
    PML4E |= (1ULL << 0x00);

    /**
     * 1 Write access; indicates whether writes are allowed to the 512-GByte region controlled by this entry.
     **/
    PML4E |= (1ULL << 0x01);

    /**
     * 2
     * If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether instruction
     * fetches are allowed from the 512-GByte region controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 512-GByte region controlled by this entry.
     **/
    PML4E |= (1ULL << 0x02);

    /**
     * 7:3 Reserved (must be 0).
     **/

    /**
     * 8
     * If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 512-GByte region
     * controlled by this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PML4E |= (1ULL << 0x08);

    /**
     * 10
     * Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control is 1,
     * indicates whether instruction fetches are allowed from user-mode linear addresses in the 512-GByte region
     * controlled by this entry. If that control is 0, this bit is ignored.
     **/
    PML4E |= (1ULL << 0x0A);

    /**
     * M–1:12 Physical address of 4-KByte aligned EPT page-directory-pointer table referenced by this entry.
     **/
    PML4E |= ((uint64_t)PDPT & 0x0000FFFFFFFFF000);

    /**
     * 51:M Reserved (must be 0).
     **/

    return PML4E;
}

template <>
uint64_t
buildPDPTE<0x1000>(uint64_t PD, uint64_t)
{
    uint64_t PDPTE = {};

    /**
     * Format of an EPT Page-Directory-Pointer-Table Entry (PDPTE) that References an EPT Page Directory
     **/

    /**
     * 0 Read access; indicates whether reads are allowed from the 1-GByte region controlled by this entry.
     **/
    PDPTE |= (1ULL << 0x00);

    /**
     * 1 Write access; indicates whether writes are allowed to the 1-GByte region controlled by this entry.
     **/
    PDPTE |= (1ULL << 0x01);

    /**
     * 2
     * If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether instruction
     * fetches are allowed from the 1-GByte region controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 1-GByte region controlled by this entry.
     **/
    PDPTE |= (1ULL << 0x02);

    /**
     * 7:3 Reserved (must be 0).
     **/

    /**
     * 8
     * If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 1-GByte region controlled
     * by this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PDPTE |= (1ULL << 0x08);

    /**
     * 10 Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control is 1,
     * indicates whether instruction fetches are allowed from user-mode linear addresses in the 1-GByte region
     * controlled by this entry. If that control is 0, this bit is ignored.
     **/
    PDPTE |= (1ULL << 0x0A);

    /**
     * M–1:12 Physical address of 4-KByte aligned EPT page directory referenced by this entry.
     **/
    PDPTE |= ((uint64_t)PD & 0x0000FFFFFFFFF000);

    /**
     * 51:M Reserved (must be 0).
     **/

    return PDPTE;
}

template <>
uint64_t
buildPDE<0x1000>(uint64_t PT, uint64_t)
{
    uint64_t PDE = {};

    /**
     * Format of an EPT Page-Directory Entry (PDE) that References an EPT Page Table
     **/

    /**
     * 0 Read access; indicates whether reads are allowed from the 2-MByte region controlled by this entry.
     **/
    PDE |= (1ULL << 0x00);

    /**
     * 1 Write access; indicates whether writes are allowed to the 2-MByte region controlled by this entry.
     **/
    PDE |= (1ULL << 0x01);

    /**
     * 2
     * If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether instruction
     * fetches are allowed from the 2-MByte region controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 2-MByte region controlled by this entry.
     **/
    PDE |= (1ULL << 0x02);

    /**
     * 6:3 Reserved (must be 0).
     **/

    /**
     * 7 Must be 0 (otherwise, this entry maps a 2-MByte page).
     **/

    /**
     * 8 If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 2-MByte region controlled
     * by this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PDE |= (1ULL << 0x08);

    /**
     * 10 Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control is 1,
     * indicates whether instruction fetches are allowed from user-mode linear addresses in the 2-MByte region
     * controlled by this entry. If that control is 0, this bit is ignored.
     **/
    PDE |= (1ULL << 0x0A);

    /**
     * M–1:12 Physical address of 4-KByte aligned EPT page table referenced by this entry.
     **/
    PDE |= ((uint64_t)PT & 0x0000FFFFFFFFF000);

    /**
     * 51:M Reserved (must be 0).
     **/

    return PDE;
}

template <>
uint64_t
buildPTE<0x1000>(uint64_t M, uint64_t MT)
{
    uint64_t PTE = {};

    /**
     * Format of an EPT Page-Table Entry that Maps a 4-KByte Page
     **/

    /**
     * 0 Read access; indicates whether reads are allowed from the 4-KByte page referenced by this entry.
     **/
    PTE |= (1ULL << 0x00);

    /**
     * 1 Write access; indicates whether writes are allowed to the 4-KByte page referenced by this entry.
     **/
    PTE |= (1ULL << 0x01);

    /**
     * 2
     * If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether
     * instruction fetches are allowed from the 4-KByte page controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 4-KByte page controlled by this entry.
     **/
    PTE |= (1ULL << 0x02);

    /**
     * 5:3 EPT memory type for this 4-KByte page (see Section 31.3.7).
     **/
    PTE |= ((MT & 0x7) << 0x03);

    /**
     * 6 Ignore PAT memory type for this 4-KByte page (see Section 31.3.7).
     **/
    PTE |= (1ULL << 0x06);

    /**
     * 8
     * If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 4-KByte page referenced
     * by this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PTE |= (1ULL << 0x08);

    /**
     * 9
     * If bit 6 of EPTP is 1, dirty flag for EPT; indicates whether software has written to the 4-KByte page referenced by
     * this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PTE |= (1ULL << 0x09);

    /**
     * 10
     * Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control is
     * 1, indicates whether instruction fetches are allowed from user-mode linear addresses in the 4-KByte page controlled
     * by this entry. If that control is 0, this bit is ignored.
     **/
    PTE |= (1ULL << 0x0A);

    /**
     * M–1:12 Physical address of the 4-KByte page referenced by this entry.
     **/
    PTE |= ((uint64_t)M & 0x0000FFFFFFFFF000);

    /**
     * 51:M Reserved (must be 0).
     **/

    /**
     * 57
     * Verify guest paging. If the "guest-paging verification" VM-execution control is 1, indicates limits on the guest paging
     * structures used to access the 4-KByte page controlled by this entry (see Section 31.3.3.2). If that control is 0, this
     * bit is ignored.
     **/
    PTE |= (1ULL << 0x39);

    /**
     * 58
     * Paging-write access. If the "EPT paging-write control" VM-execution control is 1, indicates that guest paging may
     * update the 4-KByte page controlled by this entry (see Section 31.3.3.2). If that control is 0, this bit is ignored.
     **/
    PTE |= (1ULL << 0x3A);

    /**
     * 60
     * Supervisor shadow stack. If bit 7 of EPTP is 1, indicates whether supervisor shadow stack accesses are allowed to
     * guest-physical addresses in the 4-KByte page mapped by this entry (see Section 31.3.3.2).
     * Ignored if bit 7 of EPTP is 0.
     **/
    PTE |= (1ULL << 0x3C);

    /**
     * 61
     * Sub-page write permissions. If the "sub-page write permissions for EPT" VM-execution control is 1, writes to
     * individual 128-byte regions of the 4-KByte page referenced by this entry may be allowed even if the page would
     * normally not be writable (see Section 31.3.4). If "sub-page write permissions for EPT" VM-execution control is 0, this
     * bit is ignored.
     **/
    PTE |= (1ULL << 0x3D);

    /**
     * 63
     * Suppress #VE. If the "EPT-violation #VE" VM-execution control is 1, EPT violations caused by accesses to this page
     * are convertible to virtualization exceptions only if this bit is 0 (see Section 28.5.7.1). If "EPT-violation #VE" VM-
     * execution control is 0, this bit is ignored.
     **/
    PTE |= (1ULL << 0x3F);

    return PTE;
}

template <>
uint64_t
buildPML5E<0x200000>(uint64_t PML4, uint64_t MT)
{
    return buildPML5E<0x1000>(PML4, MT);
}

template <>
uint64_t
buildPML4E<0x200000>(uint64_t PDPT, uint64_t MT)
{
    return buildPML4E<0x1000>(PDPT, MT);
}

template <>
uint64_t
buildPDPTE<0x200000>(uint64_t PD, uint64_t MT)
{
    return buildPDPTE<0x1000>(PD, MT);
}

template <>
uint64_t
buildPDE<0x200000>(uint64_t PT, uint64_t MT)
{
    uint64_t PDE = {};

    /**
     * Format of an EPT Page-Directory Entry (PDE) that Maps a 2-MByte Page
     **/

    /**
     * 0 Read access; indicates whether reads are allowed from the 2-MByte page referenced by this entry.
     **/
    PDE |= (1ULL << 0x00);

    /**
     * 1 Write access; indicates whether writes are allowed to the 2-MByte page referenced by this entry.
     **/
    PDE |= (1ULL << 0x01);

    /**
     * 2
     * If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether instruction fetches are allowed from the 2-MByte page controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are allowed from supervisor-mode linear addresses in the 2-MByte page controlled by this entry.
     **/
    PDE |= (1ULL << 0x02);

    /**
     * 5:3 EPT memory type for this 2-MByte page (see Section 31.3.7).
     **/
    PDE |= ((MT & 0x7) << 0x03);

    /**
     * 6 Ignore PAT memory type for this 2-MByte page (see Section 31.3.7).
     **/
    PDE |= (0ULL << 0x06);

    /**
     * 7 Must be 1 (otherwise, this entry references an EPT page table).
     **/
    PDE |= (1ULL << 0x07);

    /**
     * 8
     * If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 2-MByte page referenced
     * by this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PDE |= (0ULL << 0x08);

    /**
     * 9
     * If bit 6 of EPTP is 1, dirty flag for EPT; indicates whether software has written to the 2-MByte page referenced by
     * this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PDE |= (0ULL << 0x09);

    /**
     * 10
     * Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control is 1,
     * indicates whether instruction fetches are allowed from user-mode linear addresses in the 2-MByte page controlled
     * by this entry. If that control is 0, this bit is ignored.
     **/
    PDE |= (1ULL << 0x0A);

    /**
     * 20:12 Reserved (must be 0).
     **/

    /**
     * M–1:21 Physical address of the 2-MByte page referenced by this entry.
     **/
    PDE |= ((uint64_t)PT & 0x0000FFFFFFE00000);

    /**
     * 51:M Reserved (must be 0).
     **/

    /**
     * 57
     * Verify guest paging. If the "guest-paging verification" VM-execution control is 1, indicates limits on the guest paging
     * structures used to access the 2-MByte page controlled by this entry (see Section 31.3.3.2). If that control is 0, this
     * bit is ignored.
     **/
    PDE |= (0ULL << 0x39);

    /**
     * 58
     * Paging-write access. If the "EPT paging-write control" VM-execution control is 1, indicates that guest paging may
     * update the 2-MByte page controlled by this entry (see Section 31.3.3.2). If that control is 0, this bit is ignored.
     **/
    PDE |= (0ULL << 0x3A);

    /**
     * 60
     * Supervisor shadow stack. If bit 7 of EPTP is 1, indicates whether supervisor shadow stack accesses are allowed to
     * guest-physical addresses in the 2-MByte page mapped by this entry (see Section 31.3.3.2).
     * Ignored if bit 7 of EPTP is 0.
     **/
    PDE |= (0ULL << 0x3C);

    /**
     * 63
     * Suppress #VE. If the "EPT-violation #VE" VM-execution control is 1, EPT violations caused by accesses to this page
     * are convertible to virtualization exceptions only if this bit is 0 (see Section 28.5.7.1). If "EPT-violation #VE" VM-
     * execution control is 0, this bit is ignored.
     **/
    PDE |= (0ULL << 0x3F);

    return PDE;
}

template <>
uint64_t buildPTE<0x200000>(uint64_t, uint64_t);

template <>
uint64_t
buildPML5E<0x40000000>(uint64_t PML4, uint64_t MT)
{
    return buildPML5E<0x1000>(PML4, MT);
}

template <>
uint64_t
buildPML4E<0x40000000>(uint64_t PDPT, uint64_t MT)
{
    return buildPML4E<0x1000>(PDPT, MT);
}

template <>
uint64_t
buildPDPTE<0x40000000>(uint64_t PD, uint64_t MT)
{
    uint64_t PDPTE = {};

    /**
     * Format of an EPT Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page
     **/

    /**
     * 0 Read access; indicates whether reads are allowed from the 1-GByte page referenced by this entry.
     **/
    PDPTE |= (1ULL << 0x00);

    /**
     * 1 Write access; indicates whether writes are allowed to the 1-GByte page referenced by this entry.
     **/
    PDPTE |= (1ULL << 0x01);

    /**
     * 2
     * If the "mode-based execute control for EPT" VM-execution control is 0, execute access; indicates whether
     * instruction fetches are allowed from the 1-GByte page controlled by this entry.
     * If that control is 1, execute access for supervisor-mode linear addresses; indicates whether instruction fetches are
     * allowed from supervisor-mode linear addresses in the 1-GByte page controlled by this entry.
     **/
    PDPTE |= (1ULL << 0x02);

    /**
     * 5:3 EPT memory type for this 1-GByte page (see Section 31.3.7).
     **/
    PDPTE |= ((MT & 0x7) << 0x03);

    /**
     * 6 Ignore PAT memory type for this 1-GByte page (see Section 31.3.7).
     **/
    PDPTE |= (0ULL << 0x06);

    /**
     * 7 Must be 1 (otherwise, this entry references an EPT page directory).
     **/
    PDPTE |= (1ULL << 0x07);

    /**
     * 8
     * If bit 6 of EPTP is 1, accessed flag for EPT; indicates whether software has accessed the 1-GByte page referenced
     * by this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PDPTE |= (0ULL << 0x08);

    /**
     * 9
     * If bit 6 of EPTP is 1, dirty flag for EPT; indicates whether software has written to the 1-GByte page referenced by
     * this entry (see Section 31.3.5). Ignored if bit 6 of EPTP is 0.
     **/
    PDPTE |= (0ULL << 0x09);

    /**
     * 10
     * Execute access for user-mode linear addresses. If the "mode-based execute control for EPT" VM-execution control is 1,
     * indicates whether instruction fetches are allowed from user-mode linear addresses in the 1-GByte page controlled
     * by this entry. If that control is 0, this bit is ignored.
     **/
    PDPTE |= (1ULL << 0x0A);

    /**
     * 29:12 Reserved (must be 0).
     **/

    /**
     * M–1:30 Physical address of the 1-GByte page referenced by this entry.
     **/
    PDPTE |= ((uint64_t)PD & 0xFFFFFFFFC0000000);

    /**
     * 51:M Reserved (must be 0).
     **/

    /**
     * 57
     * Verify guest paging. If the "guest-paging verification" VM-execution control is 1, indicates limits on the guest paging
     * structures used to access the 1-GByte page controlled by this entry (see Section 31.3.3.2). If that control is 0, this
     * bit is ignored.
     **/
    PDPTE |= (0ULL << 0x39);

    /**
     * 58
     * Paging-write access. If the "EPT paging-write control" VM-execution control is 1, indicates that guest paging may
     * update the 1-GByte page controlled by this entry (see Section 31.3.3.2). If that control is 0, this bit is ignored.
     **/
    PDPTE |= (0ULL << 0x3A);

    /**
     * 60
     * Supervisor shadow stack. If bit 7 of EPTP is 1, indicates whether supervisor shadow stack accesses are allowed to
     * guest-physical addresses in the 1-GByte page mapped by this entry (see Section 31.3.3.2).
     * Ignored if bit 7 of EPTP is 0.
     **/
    PDPTE |= (0ULL << 0x3C);

    /**
     * 63
     * Suppress #VE. If the "EPT-violation #VE" VM-execution control is 1, EPT violations caused by accesses to this page
     * are convertible to virtualization exceptions only if this bit is 0 (see Section 28.5.7.1). If "EPT-violation #VE" VM-
     * execution control is 0, this bit is ignored.
     **/
    PDPTE |= (0ULL << 0x3F);

    return PDPTE;
}

template <>
uint64_t buildPDE<0x40000000>(uint64_t, uint64_t);

template <>
uint64_t buildPTE<0x40000000>(uint64_t, uint64_t);

static inline void
buildEPT(uint64_t* PML4, uint64_t PA, uint64_t MT)
{
    uint64_t I = (PA >> 0x27) & 0x00000000000001FF;
    uint64_t II = (PA >> 0x1E) & 0x00000000000001FF;
    uint64_t III = (PA >> 0x15) & 0x00000000000001FF;
    PHYSICAL_ADDRESS Pa;

    if (PML4[I] == 0) {
        uint64_t* p = (uint64_t*)allocate<0x1000>();
        ASSERT(p);
        memset(p, 0, 0x1000);
        Pa = MmGetPhysicalAddress(p);
        uint64_t PML4E = buildPML4E<0x200000>(Pa.QuadPart, MT);
        if (InterlockedCompareExchange64((LONG64*)&PML4[I], PML4E, 0))
            deallocate<0x1000>(p);
    }

    Pa.QuadPart = PML4[I] & 0xFFFFFFFFFFFFF000;
    uint64_t* PDPT = (uint64_t*)MmGetVirtualForPhysical(Pa);
    if (PDPT[II] == 0) {
        uint64_t* p = (uint64_t*)allocate<0x1000>();
        ASSERT(p);
        memset(p, 0, 0x1000);
        Pa = MmGetPhysicalAddress(p);
        uint64_t PDPTE = buildPDPTE<0x200000>(Pa.QuadPart, MT);
        if (InterlockedCompareExchange64((LONG64*)&PDPT[II], PDPTE, 0))
            deallocate<0x1000>(p);
    }

    Pa.QuadPart = PDPT[II] & 0xFFFFFFFFFFFFF000;
    uint64_t* PD = (uint64_t*)MmGetVirtualForPhysical(Pa);
    if (PD[III] == 0) {
        uint64_t PDE = buildPDE<0x200000>(PA & 0xFFFFFFFFFFE00000, MT);
        InterlockedCompareExchange64((LONG64*)&PD[III], PDE, 0);
    }
}

template <int e>
static int
procedure(VMContext*)
{
    __asm__ __volatile__("int3" :::);
    return 0;
}

// 0 Exception or non-maskable interrupt (NMI)
template <>
int
procedure<0x0000>(VMContext*)
{
    size_t e;
    __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
    __asm_int3();
    e = 0x0000;
    return 0;
}

// 1 External interrupt. An external interrupt arrived and the "external-interrupt exiting" VM-execution control was 1.
template <>
int
procedure<0x0001>(VMContext*)
{
    return 0;
}

// 2 Triple fault. The logical processor encountered an exception while attempting to call the double-fault handler and that exception did not itself cause a VM exit due to the exception bitmap.
template <>
int
procedure<0x0002>(VMContext*)
{
    size_t e;
    __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
    __asm_int3();
    e = 0x0002;
    return 0;
}

// 3 INIT signal. An INIT signal arrived
template <>
int
procedure<0x0003>(VMContext*)
{
    return 0;
}

// 4 Start-up IPI (SIPI). A SIPI arrived while the logical processor was in the "wait-for-SIPI" state.
template <>
int
procedure<0x0004>(VMContext*)
{
    return 0;
}

// 5 I/O system-management interrupt (SMI). An SMI arrived immediately after retirement of an I/O instruction and caused an SMM VM exit
template <>
int
procedure<0x0005>(VMContext*)
{
    return 0;
}

// 6 Other SMI. An SMI arrived and caused an SMM VM exit (see Section 34.15.2) but not immediately after retirement of an I/O instruction.
template <>
int
procedure<0x0006>(VMContext*)
{
    return 0;
}

// 7 Interrupt window. At the beginning of an instruction, RFLAGS.IF was 1; events were not blocked by STI or by MOV SS; and the "interrupt-window exiting" VM-execution control was 1.
template <>
int
procedure<0x0007>(VMContext*)
{
    return 0;
}

// 8 NMI window. At the beginning of an instruction, there was no virtual-NMI blocking; events were not blocked by MOV SS; and the "NMI-window exiting" VM-execution control was 1.
template <>
int
procedure<0x0008>(VMContext*)
{
    return 0;
}

// 9 Task switch. Guest software attempted a task switch.
template <>
int
procedure<0x0009>(VMContext*)
{
    /**
     * Exit Qualification for Task Switches
     **/
    return 0;
}

// 10 CPUID. Guest software attempted to execute CPUID.
template <>
int
procedure<0x000A>(VMContext* ctx)
{
    __asm__("cpuid" : "=a"(ctx->RAX), "=b"(ctx->RBX), "=c"(ctx->RCX), "=d"(ctx->RDX) : "a"(ctx->RAX), "c"(ctx->RCX));
    return 0;
}

// 11 GETSEC. Guest software attempted to execute GETSEC.
template <>
int
procedure<0x000B>(VMContext*)
{
    return 0;
}

// 12 HLT. Guest software attempted to execute HLT and the "HLT exiting" VM-execution control was 1.
template <>
int
procedure<0x000C>(VMContext*)
{
    return 0;
}

// 13 INVD. Guest software attempted to execute INVD.
template <>
int
procedure<0x000D>(VMContext*)
{
    return 0;
}

// 14 INVLPG. Guest software attempted to execute INVLPG and the "INVLPG exiting" VM-execution control was 1.
template <>
int
procedure<0x000E>(VMContext*)
{
    return 0;
}

// 15 RDPMC. Guest software attempted to execute RDPMC and the "RDPMC exiting" VM-execution control was 1.
template <>
int
procedure<0x000F>(VMContext*)
{
    return 0;
}

// 16 RDTSC. Guest software attempted to execute RDTSC and the "RDTSC exiting" VM-execution control was 1.
template <>
int
procedure<0x0010>(VMContext*)
{
    return 0;
}

// 17 RSM. Guest software attempted to execute RSM in SMM.
template <>
int
procedure<0x0011>(VMContext*)
{
    return 0;
}

// 18 VMCALL. VMCALL was executed either by guest software (causing an ordinary VM exit) or by the executive monitor (causing an SMM VM exit; see Section 34.15.2).
template <>
int
procedure<0x0012>(VMContext*)
{
    return 0;
}

// 19 VMCLEAR. Guest software attempted to execute VMCLEAR.
template <>
int
procedure<0x0013>(VMContext*)
{
    return 0;
}

// 20 VMLAUNCH. Guest software attempted to execute VMLAUNCH.
template <>
int
procedure<0x0014>(VMContext*)
{
    return 0;
}

// 21 VMPTRLD. Guest software attempted to execute VMPTRLD.
template <>
int
procedure<0x0015>(VMContext*)
{
    return 0;
}

// 22 VMPTRST. Guest software attempted to execute VMPTRST.
template <>
int
procedure<0x0016>(VMContext*)
{
    return 0;
}

// 23 VMREAD. Guest software attempted to execute VMREAD.
template <>
int
procedure<0x0017>(VMContext*)
{
    return 0;
}

// 24 VMRESUME. Guest software attempted to execute VMRESUME.
template <>
int
procedure<0x0018>(VMContext*)
{
    return 0;
}

// 25 VMWRITE. Guest software attempted to execute VMWRITE.
template <>
int
procedure<0x0019>(VMContext*)
{
    return 0;
}

// 26 VMXOFF. Guest software attempted to execute VMXOFF.
template <>
int
procedure<0x001A>(VMContext*)
{
    return 0;
}

// 27 VMXON. Guest software attempted to execute VMXON.
template <>
int
procedure<0x001B>(VMContext*)
{
    return 0;
}

// 28 Control-register accesses. Guest software attempted to access CR0, CR3, CR4, or CR8 using CLTS, LMSW, or MOV CR and the VM-execution control fields indicate that a VM exit should occur
template <>
int
procedure<0x001C>(VMContext*)
{
    /**
     * Exit Qualification for Control-Register Accesses
     **/
    return 0;
}

// 29 MOV DR. Guest software attempted a MOV to or from a debug register and the "MOV-DR exiting" VM-execution control was 1.
template <>
int
procedure<0x001D>(VMContext*)
{
    /**
     * Exit Qualification for MOV DR
     **/
    return 0;
}

// 30 I/O instruction. Guest software attempted to execute an I/O instruction
template <>
int
procedure<0x001E>(VMContext*)
{
    /**
     * Exit Qualification for I/O Instructions
     **/
    return 0;
}

// 31 RDMSR. Guest software attempted to execute RDMSR
template <>
int
procedure<0x001F>(VMContext* ctx)
{
    uint64_t val = __asm_rdmsr(ctx->RCX);
    ctx->RAX = ((uint32_t*)&val)[0];
    ctx->RDX = ((uint32_t*)&val)[1];
    return 0;
}

// 32 WRMSR or WRMSRNS. Guest software attempted to execute either WRMSR or WRMSRNS
template <>
int
procedure<0x0020>(VMContext*)
{
    return 0;
}

// 33 VM-entry failure due to invalid guest state. A VM entry failed one of the checks identified in Section 29.3.1.
template <>
int
procedure<0x0021>(VMContext*)
{
    size_t e;
    __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
    __asm_int3();
    e = 0x0021;
    return 0;
}

// 34 VM-entry failure due to MSR loading. A VM entry failed in an attempt to load MSRs. See Section 29.4.
template <>
int
procedure<0x0022>(VMContext*)
{
    size_t e;
    __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
    __asm_int3();
    e = 0x0022;
    return 0;
}

template <>
int
procedure<0x0023>(VMContext*)
{
    return 0;
}

// 36 MWAIT. Guest software attempted to execute MWAIT and the "MWAIT exiting" VM-execution control was 1.
template <>
int
procedure<0x0024>(VMContext*)
{
    return 0;
}

// 37 Monitor trap flag. A VM exit occurred due to the 1-setting of the "monitor trap flag" VM-execution control (see Section 28.5.2) or VM entry injected a pending MTF VM exit as part of VM entry (see Section 29.6.2).
template <>
int
procedure<0x0025>(VMContext*)
{
    return 0;
}

template <>
int
procedure<0x0026>(VMContext*)
{
    return 0;
}

// 39 MONITOR. Guest software attempted to execute MONITOR and the "MONITOR exiting" VM-execution control was 1.
template <>
int
procedure<0x0027>(VMContext*)
{
    return 0;
}

// 40 PAUSE. Either guest software attempted to execute PAUSE and the "PAUSE exiting" VM-execution control was 1 or the "PAUSE-loop exiting" VM-execution control was 1 and guest software executed a PAUSE loop with execution time exceeding PLE_Window
template <>
int
procedure<0x0028>(VMContext*)
{
    return 0;
}

// 41 VM-entry failure due to machine-check event. A machine-check event occurred during VM entry
template <>
int
procedure<0x0029>(VMContext*)
{
    size_t e;
    __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
    __asm_int3();
    e = 0x0029;
    return 0;
}

template <>
int
procedure<0x002A>(VMContext*)
{
    return 0;
}

/**
 * 43 TPR below threshold. The logical processor determined that the value of bits 7:4 of the byte at offset 080H on the
 * virtual-APIC page was below that of the TPR threshold VM-execution control field while the "use TPR shadow" VM-
 * execution control was 1 either as part of TPR virtualization (Section 32.1.2) or VM entry (Section 29.7.7).
 **/
template <>
int
procedure<0x002B>(VMContext*)
{
    return 0;
}

// 44 APIC access. Guest software attempted to access memory at a physical address on the APIC-access page and the "virtualize APIC accesses" VM-execution control was 1 (see Section 32.4).
template <>
int
procedure<0x002C>(VMContext*)
{
    /**
     * Exit Qualification for APIC-Access VM Exits from Linear Accesses and Guest-Physical Accesses
     **/
    return 0;
}

// 45 Virtualized EOI. EOI virtualization was performed for a virtual interrupt whose vector indexed a bit set in the EOI-exit bitmap.
template <>
int
procedure<0x002D>(VMContext*)
{
    return 0;
}

// 46 Access to GDTR or IDTR. Guest software attempted to execute LGDT, LIDT, SGDT, or SIDT and the "descriptor-table exiting" VM-execution control was 1.
template <>
int
procedure<0x002E>(VMContext*)
{
    return 0;
}

// 47 Access to LDTR or TR. Guest software attempted to execute LLDT, LTR, SLDT, or STR and the "descriptor-table exiting" VM-execution control was 1.
template <>
int
procedure<0x002F>(VMContext*)
{
    return 0;
}

// 48 EPT violation. An attempt to access memory with a guest-physical address was disallowed by the configuration of the EPT paging structures.
template <>
int
procedure<0x0030>(VMContext*)
{
    size_t ExitQualification = {};
    size_t GuestPhysicalAddress = {};
    size_t GuestLinearAddress = {};

    bool ViolationR = {};
    bool ViolationW = {};
    bool ViolationX = {};
    bool EptR = {};
    bool EptW = {};
    bool EptX = {};

    __asm_vmx_vmread(VMX_VMCS_RO_EXIT_QUALIFICATION, &ExitQualification);
    __asm_vmx_vmread(VMX_VMCS64_RO_GUEST_PHYS_ADDR_FULL, &GuestPhysicalAddress);
    __asm_vmx_vmread(VMX_VMCS_RO_GUEST_LINEAR_ADDR, &GuestLinearAddress);

    /**
     * Exit Qualification for EPT Violations
     **/

    /**
     * 0 Set if the access causing the EPT violation was a data read.
     **/
    if (ExitQualification & (1ULL << 0x00))
        ViolationR = true;

    /**
     * 1 Set if the access causing the EPT violation was a data write.
     **/
    if (ExitQualification & (1ULL << 0x01))
        ViolationW = true;

    /**
     * 2 Set if the access causing the EPT violation was an instruction fetch.
     **/
    if (ExitQualification & (1ULL << 0x02))
        ViolationX = true;

    /**
     * 3
     * The logical-AND of bit 0 in the EPT paging-structure entries used to translate the guest-physical address of the
     * access causing the EPT violation (indicates whether the guest-physical address was readable).
     **/
    if (ExitQualification & (1ULL << 0x03))
        EptR = true;

    /**
     * 4
     * The logical-AND of bit 1 in the EPT paging-structure entries used to translate the guest-physical address of the
     * access causing the EPT violation (indicates whether the guest-physical address was writeable).
     **/
    if (ExitQualification & (1ULL << 0x04))
        EptW = true;

    /**
     * 5
     * The logical-AND of bit 2 in the EPT paging-structure entries used to translate the guest-physical address of the
     * access causing the EPT violation.
     * If the "mode-based execute control for EPT" VM-execution control is 0, this indicates whether the guest-physical
     * address was executable. If that control is 1, this indicates whether the guest-physical address was executable
     * for supervisor-mode linear addresses.
     **/
    if (ExitQualification & (1ULL << 0x05))
        EptX = true;

    /**
     * 6
     * If the "mode-based execute control" VM-execution control is 0, the value of this bit is undefined. If that control is
     * 1, this bit is the logical-AND of bit 10 in the EPT paging-structure entries used to translate the guest-physical
     * address of the access causing the EPT violation. In this case, it indicates whether the guest-physical address was
     * executable for user-mode linear addresses.
     **/
    if (ExitQualification & (1ULL << 0x06))
        ;

    /**
     * 7
     * Set if the guest linear-address field is valid.
     * The guest linear-address field is valid for all EPT violations except those resulting from an attempt to load the
     * guest PDPTEs as part of the execution of the MOV CR instruction and those due to trace-address pre-translation
     **/
    if (ExitQualification & (1ULL << 0x07))
        ;

    /**
     * 8
     * If bit 7 is 1:
     * • Set if the access causing the EPT violation is to a guest-physical address that is the translation of a linear
     * address.
     * • Clear if the access causing the EPT violation is to a paging-structure entry as part of a page walk or the
     * update of an accessed or dirty bit.
     * Reserved if bit 7 is 0 (cleared to 0).
     **/
    if (ExitQualification & (1ULL << 0x08))
        ;

    /**
     * 9
     * If bit 7 is 1, bit 8 is 1, and the processor supports advanced VM-exit information for EPT violations, 4 this bit is 0
     * if the linear address is a supervisor-mode linear address and 1 if it is a user-mode linear address. (If CR0.PG = 0,
     * the translation of every linear address is a user-mode linear address and thus this bit will be 1.) Otherwise, this
     * bit is undefined.
     **/
    if (ExitQualification & (1ULL << 0x09))
        ;

    /**
     * 10
     * If bit 7 is 1, bit 8 is 1, and the processor supports advanced VM-exit information for EPT violations, 4 this bit is 0
     * if paging translates the linear address to a read-only page and 1 if it translates to a read/write page. (If CR0.PG = 0,
     * every linear address is read/write and thus this bit will be 1.) Otherwise, this bit is undefined.
     **/
    if (ExitQualification & (1ULL << 0x0A))
        ;

    /**
     * 11
     * If bit 7 is 1, bit 8 is 1, and the processor supports advanced VM-exit information for EPT violations, 4 this bit is 0
     * if paging translates the linear address to an executable page and 1 if it translates to an execute-disable page. (If
     * CR0.PG = 0, CR4.PAE = 0, or IA32_EFER.NXE = 0, every linear address is executable and thus this bit will be 0.)
     * Otherwise, this bit is undefined.
     **/
    if (ExitQualification & (1ULL << 0x0B))
        ;

    /**
     * 12 NMI unblocking due to IRET (see Section 30.2.3).
     **/
    if (ExitQualification & (1ULL << 0x0C))
        ;

    /**
     * 13 Set if the access causing the EPT violation was a shadow-stack access.
     **/
    if (ExitQualification & (1ULL << 0x0D))
        ;

    /**
     * 14
     * If supervisor shadow-stack control is enabled (by setting bit 7 of EPTP), this bit is the same as bit 60 in the EPT
     * paging-structure entry that maps the page of the guest-physical address of the access causing the EPT violation.
     * Otherwise (or if translation of the guest-physical address terminates before reaching an EPT paging-structure
     * entry that maps a page), this bit is undefined.
     **/
    if (ExitQualification & (1ULL << 0x0E))
        ;

    /**
     * 15 This bit is set if the EPT violation was caused as a result of guest-paging verification.
     **/
    if (ExitQualification & (1ULL << 0x0F))
        ;

    /**
     * 16
     * This bit is set if the access was asynchronous to instruction execution not the result of event delivery. The bit is
     * set if the access is related to trace output by Intel PT (see Section 28.5.4), accesses related to PEBS on
     * processors with the "EPT-friendly" enhancement (see Section 22.9.5), or to user-interrupt delivery (see Section
     * 9.4.2). Otherwise, this bit is cleared.
     **/
    if (ExitQualification & (1ULL << 0x10))
        ;

    buildEPT(PML4, GuestPhysicalAddress & 0xFFFFFFFFFFE00000, 0); // 动态补充的物理页一律视为MMIO内存,不允许缓存.

    // The INVEPT descriptor comprises 128 bits and contains a 64-bit EPTP value in bits 63:0
    struct {
        uint64_t eptp;
        uint64_t reserved;
    } descriptor;
    descriptor.eptp = EPTP;
    descriptor.reserved = 0;
    __asm_vmx_invept(1, &descriptor);

    return 0;
}

// 49 EPT misconfiguration. An attempt to access memory with a guest-physical address encountered a misconfigured EPT paging-structure entry.
template <>
int
procedure<0x0031>(VMContext*)
{
    size_t ExitQualification = {};
    size_t GuestPhysicalAddress = {};
    size_t GuestLinearAddress = {};

    __asm_vmx_vmread(VMX_VMCS_RO_EXIT_QUALIFICATION, &ExitQualification);
    __asm_vmx_vmread(VMX_VMCS64_RO_GUEST_PHYS_ADDR_FULL, &GuestPhysicalAddress);
    __asm_vmx_vmread(VMX_VMCS_RO_GUEST_LINEAR_ADDR, &GuestLinearAddress);

    __asm_int3();
    return 0;
}

// 50 INVEPT. Guest software attempted to execute INVEPT.
template <>
int
procedure<0x0032>(VMContext*)
{
    return 0;
}

// 51 RDTSCP. Guest software attempted to execute RDTSCP and the "enable RDTSCP" and "RDTSC exiting" VM-execution controls were both 1.
template <>
int
procedure<0x0033>(VMContext*)
{
    return 0;
}

// 52 VMX-preemption timer expired. The preemption timer counted down to zero.
template <>
int
procedure<0x0034>(VMContext*)
{
    return 0;
}

// 53 INVVPID. Guest software attempted to execute INVVPID.
template <>
int
procedure<0x0035>(VMContext*)
{
    return 0;
}

// 54 WBINVD or WBNOINVD. Guest software attempted to execute WBINVD or WBNOINVD and the "WBINVD exiting" VM-execution control was 1.
template <>
int
procedure<0x0036>(VMContext*)
{
    return 0;
}

// 55 XSETBV. Guest software attempted to execute XSETBV.
template <>
int
procedure<0x0037>(VMContext*)
{
    return 0;
}

// 56 APIC write. Guest software completed a write to the virtual-APIC page that must be virtualized by VMM software
template <>
int
procedure<0x0038>(VMContext*)
{
    return 0;
}

// 57 RDRAND. Guest software attempted to execute RDRAND and the "RDRAND exiting" VM-execution control was 1.
template <>
int
procedure<0x0039>(VMContext*)
{
    return 0;
}

// 58 INVPCID. Guest software attempted to execute INVPCID and the "enable INVPCID" and "INVLPG exiting" VM-execution controls were both 1.
template <>
int
procedure<0x003A>(VMContext*)
{
    return 0;
}

// 59 VMFUNC. Guest software invoked a VM function with the VMFUNC instruction and the VM function either was not enabled or generated a function-specific condition causing a VM exit.
template <>
int
procedure<0x003B>(VMContext*)
{
    return 0;
}

/**
 * 60 ENCLS. Guest software attempted to execute ENCLS, "enable ENCLS exiting" VM-execution control was 1, and either
 * (1) EAX < 63 and the corresponding bit in the ENCLS-exiting bitmap is 1; or (2) EAX ? 63 and bit 63 in the ENCLS-exiting bitmap is 1.
 **/
template <>
int
procedure<0x003C>(VMContext*)
{
    return 0;
}

// 61 RDSEED. Guest software attempted to execute RDSEED and the "RDSEED exiting" VM-execution control was 1.
template <>
int
procedure<0x003D>(VMContext*)
{
    return 0;
}

// 62 Page-modification log full. The processor attempted to create a page-modification log entry and the value of the PML index was not in the range 0–511.
template <>
int
procedure<0x003E>(VMContext*)
{
    return 0;
}

// 63 XSAVES. Guest software attempted to execute XSAVES, the "enable XSAVES/XRSTORS" was 1, and a bit was set in the logical-AND of the following three values: EDX:EAX, the IA32_XSS MSR, and the XSS-exiting bitmap.
template <>
int
procedure<0x003F>(VMContext*)
{
    return 0;
}

// 64 XRSTORS. Guest software attempted to execute XRSTORS, the "enable XSAVES/XRSTORS" was 1, and a bit was set in the logical-AND of the following three values: EDX:EAX, the IA32_XSS MSR, and the XSS-exiting bitmap.
template <>
int
procedure<0x0040>(VMContext*)
{
    return 0;
}

/**
 * 65 PCONFIG. Guest software attempted to execute PCONFIG, "enable PCONFIG" VM-execution control was 1, and either
 * (1) EAX < 63 and the corresponding bit in the PCONFIG-exiting bitmap is 1; or (2) EAX ? 63 and bit 63 in the
 * PCONFIG-exiting bitmap is 1.
 **/
template <>
int
procedure<0x0041>(VMContext*)
{
    return 0;
}

// 66 SPP-related event. The processor attempted to determine an access's sub-page write permission and encountered an SPP miss or an SPP misconfiguration.
template <>
int
procedure<0x0042>(VMContext*)
{
    return 0;
}

// 67 UMWAIT. Guest software attempted to execute UMWAIT and the "enable user wait and pause" and "RDTSC exiting" VM-execution controls were both 1.
template <>
int
procedure<0x0043>(VMContext*)
{
    return 0;
}

// 68 TPAUSE. Guest software attempted to execute TPAUSE and the "enable user wait and pause" and "RDTSC exiting" VM-execution controls were both 1.
template <>
int
procedure<0x0044>(VMContext*)
{
    return 0;
}

// 69 LOADIWKEY. Guest software attempted to execute LOADIWKEY and the "LOADIWKEY exiting" VM-execution control was 1.
template <>
int
procedure<0x0045>(VMContext*)
{
    return 0;
}

template <>
int
procedure<0x0046>(VMContext*)
{
    return 0;
}

template <>
int
procedure<0x0047>(VMContext*)
{
    return 0;
}

/**
 * 72  ENQCMD PASID translation failure. A VM exit occurred during PASID translation because the present bit was clear
 * in a PASID-directory entry, the valid bit was clear in a PASID-table entry, or one of the entries set a reserved bit.
 **/
template <>
int
procedure<0x0048>(VMContext*)
{
    return 0;
}

/**
 * 73 ENQCMDS PASID translation failure. A VM exit occurred during PASID translation because the present bit was clear
 * in a PASID-directory entry, the valid bit was clear in a PASID-table entry, or one of the entries set a reserved bit.
 **/
template <>
int
procedure<0x0049>(VMContext*)
{
    return 0;
}

/**
 * 74 Bus lock. The processor asserted a bus lock while the "bus-lock detection" VM-execution control was 1. (Such
 * VM exits will also set bit 26 of the exit-reason field.)
 **/
template <>
int
procedure<0x004A>(VMContext*)
{
    return 0;
}

/**
 * 75 Instruction timeout. The "instruction timeout" VM-execution control was 1 and certain operations prevented the
 * processor from reaching an instruction boundary within the amount of time specified by the instruction-timeout control.
 **/
template <>
int
procedure<0x004B>(VMContext*)
{
    return 0;
}

/**
 * 76 SEAMCALL. Guest software attempted to execute SEAMCALL.
 **/
template <>
int
procedure<0x004C>(VMContext*)
{
    return 0;
}

/**
 * 77 TDCALL. Guest software attempted to execute TDCALL.
 **/
template <>
int
procedure<0x004D>(VMContext*)
{
    return 0;
}

/**
 * 78 RDMSRLIST. Guest software attempted to execute RDMSRLIST and either the "use MSR bitmaps" VM-execution control was 0 or any of the following holds for the index an MSR being accessed:
 * The index is neither in the range 00000000H – 00001FFFH nor in the range C0000000H – C0001FFFH.
 * The index is in the range 00000000H – 00001FFFH and the n th bit in read bitmap for low MSRs is 1, where n is the index.
 * The index is in the range C0000000H – C0001FFFH and the n th bit in read bitmap for high MSRs is 1, where n is the logical AND of the index and the value 00001FFFH.
 **/
template <>
int
procedure<0x004E>(VMContext*)
{
    return 0;
}

/**
 * 79 WRMSRLIST. Guest software attempted to execute WRMSRLIST and either the "use MSR bitmaps" VM-execution control was 0 or any of the following holds for the index an MSR being accessed:
 * The index is neither in the range 00000000H – 00001FFFH nor in the range C0000000H – C0001FFFH.
 * The index is in the range 00000000H – 00001FFFH and the n th bit in write bitmap for low MSRs is 1, where n is the index.
 * The index is in the range C0000000H – C0001FFFH and the n th bit in write bitmap for high MSRs is 1, where n is the logical AND of the index and the value 00001FFFH.
 **/
template <>
int
procedure<0x004F>(VMContext*)
{
    return 0;
}

static __attribute__((naked)) void
vmx_vmexit(void)
{
    __asm__ __volatile__("\n push %%r15"
                         "\n push %%r14"
                         "\n push %%r13"
                         "\n push %%r12"
                         "\n push %%r11"
                         "\n push %%r10"
                         "\n push %%r9"
                         "\n push %%r8"
                         "\n push %%r8" // VMContext.RSP
                         "\n push %%rbp"
                         "\n push %%rsi"
                         "\n push %%rdi"
                         "\n push %%rdx"
                         "\n push %%rcx"
                         "\n push %%rbx"
                         "\n push %%rax"

                         "\n mov $0x4402, %%rcx"  // VMX_VMCS32_RO_EXIT_REASON
                         "\n vmread %%rcx, %%rax" //
                         "\n and $0xFFFF, %%rax"  // Bits 15:0 of this field contain the basic exit reason.

                         "\n lea %0, %%rbx"
                         "\n mov (%%rbx, %%rax, 8), %%rdx"
                         "\n mov %%rsp, %%rcx"
                         "\n call *%%rdx"

                         "\n mov $0x681E, %%rcx" // VMX_VMCS_GUEST_RIP
                         "\n vmread %%rcx, %%rax"
                         "\n mov $0x440C, %%rcx" // VMX_VMCS32_RO_EXIT_INSTR_LENGTH
                         "\n vmread %%rcx, %%rdx"
                         "\n add %%rdx, %%rax"
                         "\n mov $0x681E, %%rcx" // VMX_VMCS_GUEST_RIP
                         "\n vmwrite %%rax, %%rcx"

                         "\n pop %%rax"
                         "\n pop %%rbx"
                         "\n pop %%rcx"
                         "\n pop %%rdx"
                         "\n pop %%rdi"
                         "\n pop %%rsi"
                         "\n pop %%rbp"
                         "\n pop %%r8" // VMContext.RSP
                         "\n pop %%r8"
                         "\n pop %%r9"
                         "\n pop %%r10"
                         "\n pop %%r11"
                         "\n pop %%r12"
                         "\n pop %%r13"
                         "\n pop %%r14"
                         "\n pop %%r15"

                         "\n vmresume"

                         "\n int3" // unreachable.
                         :
                         : "m"(Procedures)
                         : "memory");
}

static void
IOPM_STI(void* PermissionsMap, uint16_t Port)
{
    uint8_t* Bitmap = (uint8_t*)PermissionsMap;
    uint32_t Offset = Port / 8;
    uint32_t Shift = Port % 8;

    uint8_t val = Bitmap[Offset];
    val |= 1U << Shift;

    Bitmap[Offset] = val;
}

static void
IOPM_CLI(void* PermissionsMap, uint16_t Port)
{
    uint8_t* Bitmap = (uint8_t*)PermissionsMap;
    uint32_t Offset = Port / 8;
    uint32_t Shift = Port % 8;

    uint8_t val = Bitmap[Offset];
    val &= ~(1U << Shift);

    Bitmap[Offset] = val;
}

// See: MSR-Bitmap Address
// Read bitmap for low MSRs (located at the MSR-bitmap address). This contains one bit for each MSR address in the range 00000000H to 00001FFFH. The bit determines whether an execution of RDMSR applied to that MSR causes a VM exit.
// Read bitmap for high MSRs (located at the MSR-bitmap address plus 1024). This contains one bit for each MSR address in the range C0000000H toC0001FFFH. The bit determines whether an execution of RDMSR applied to that MSR causes a VM exit.
// Write bitmap for low MSRs (located at the MSR-bitmap address plus 2048). This contains one bit for each MSR address in the range 00000000H to 00001FFFH. The bit determines whether an execution of WRMSR applied to that MSR causes a VM exit.
// Write bitmap for high MSRs (located at the MSR-bitmap address plus 3072). This contains one bit for each MSR address in the range C0000000H toC0001FFFH.The bit determines whether an execution of WRMSR applied to that MSR causes a VM  exit.

static void
MSRPM_STI(void* PermissionsMap, uint32_t MSR)
{
    uint8_t* BitmapR = {};
    uint8_t* BitmapW = {};
    uint32_t Offset = {};
    uint32_t Shift = {};

    if (MSR <= 0x00001FFF) {
        BitmapR = (uint8_t*)PermissionsMap + 0;
        BitmapW = (uint8_t*)PermissionsMap + 0x800;
        Offset = MSR - 0x00000000;
    }

    if (MSR >= 0xC0000000 && MSR <= 0xC0001FFF) {
        BitmapR = (uint8_t*)PermissionsMap + 0x400;
        BitmapW = (uint8_t*)PermissionsMap + 0xC00;
        Offset = MSR - 0xC0000000;
    }

    Shift = Offset % 8;
    Offset /= 8;

    if (BitmapR) {
        uint8_t val = BitmapR[Offset];
        val |= 1U << Shift;

        BitmapR[Offset] = val;
    }

    if (BitmapW) {
        uint8_t val = BitmapW[Offset];
        val |= 1U << Shift;

        BitmapW[Offset] = val;
    }
}

static void
MSRPM_CLI(void* PermissionsMap, uint32_t MSR)
{
    uint8_t* BitmapR = {};
    uint8_t* BitmapW = {};
    uint32_t Offset = {};
    uint32_t Shift = {};

    if (MSR <= 0x00001FFF) {
        BitmapR = (uint8_t*)PermissionsMap + 0;
        BitmapW = (uint8_t*)PermissionsMap + 0x800;
        Offset = MSR - 0x00000000;
    }

    if (MSR >= 0xC0000000 && MSR <= 0xC0001FFF) {
        BitmapR = (uint8_t*)PermissionsMap + 0x400;
        BitmapW = (uint8_t*)PermissionsMap + 0xC00;
        Offset = MSR - 0xC0000000;
    }

    Shift = Offset % 8;
    Offset /= 8;

    if (BitmapR) {
        uint8_t val = BitmapR[Offset];
        val &= ~(1U << Shift);

        BitmapR[Offset] = val;
    }

    if (BitmapW) {
        uint8_t val = BitmapW[Offset];
        val &= ~(1U << Shift);

        BitmapW[Offset] = val;
    }
}

static void
initializeEPT()
{
    KdBreakPoint();

    PML4 = (uint64_t*)allocate<0x1000>();
    ASSERT(PML4);
    memset(PML4, 0, 0x1000);

    for (size_t i = 0; i < 0x80000000; i += 0x200000) {
        buildEPT(PML4, i, 6);
    }

    EPTP = buildEPTP(MmGetPhysicalAddress(PML4).QuadPart);
}

template <>
void
initialize<Hash("GenuineIntel")>()
{
    Procedures[0x0000] = &procedure<0x0000>;
    Procedures[0x0001] = &procedure<0x0001>;
    Procedures[0x0002] = &procedure<0x0002>;
    Procedures[0x0003] = &procedure<0x0003>;
    Procedures[0x0004] = &procedure<0x0004>;
    Procedures[0x0005] = &procedure<0x0005>;
    Procedures[0x0006] = &procedure<0x0006>;
    Procedures[0x0007] = &procedure<0x0007>;
    Procedures[0x0008] = &procedure<0x0008>;
    Procedures[0x0009] = &procedure<0x0009>;
    Procedures[0x000A] = &procedure<0x000A>;
    Procedures[0x000B] = &procedure<0x000B>;
    Procedures[0x000C] = &procedure<0x000C>;
    Procedures[0x000D] = &procedure<0x000D>;
    Procedures[0x000E] = &procedure<0x000E>;
    Procedures[0x000F] = &procedure<0x000F>;
    Procedures[0x0010] = &procedure<0x0010>;
    Procedures[0x0011] = &procedure<0x0011>;
    Procedures[0x0012] = &procedure<0x0012>;
    Procedures[0x0013] = &procedure<0x0013>;
    Procedures[0x0014] = &procedure<0x0014>;
    Procedures[0x0015] = &procedure<0x0015>;
    Procedures[0x0016] = &procedure<0x0016>;
    Procedures[0x0017] = &procedure<0x0017>;
    Procedures[0x0018] = &procedure<0x0018>;
    Procedures[0x0019] = &procedure<0x0019>;
    Procedures[0x001A] = &procedure<0x001A>;
    Procedures[0x001B] = &procedure<0x001B>;
    Procedures[0x001C] = &procedure<0x001C>;
    Procedures[0x001D] = &procedure<0x001D>;
    Procedures[0x001E] = &procedure<0x001E>;
    Procedures[0x001F] = &procedure<0x001F>;
    Procedures[0x0020] = &procedure<0x0020>;
    Procedures[0x0021] = &procedure<0x0021>;
    Procedures[0x0022] = &procedure<0x0022>;
    Procedures[0x0023] = &procedure<0x0023>;
    Procedures[0x0024] = &procedure<0x0024>;
    Procedures[0x0025] = &procedure<0x0025>;
    Procedures[0x0026] = &procedure<0x0026>;
    Procedures[0x0027] = &procedure<0x0027>;
    Procedures[0x0028] = &procedure<0x0028>;
    Procedures[0x0029] = &procedure<0x0029>;
    Procedures[0x002A] = &procedure<0x002A>;
    Procedures[0x002B] = &procedure<0x002B>;
    Procedures[0x002C] = &procedure<0x002C>;
    Procedures[0x002D] = &procedure<0x002D>;
    Procedures[0x002E] = &procedure<0x002E>;
    Procedures[0x002F] = &procedure<0x002F>;
    Procedures[0x0030] = &procedure<0x0030>;
    Procedures[0x0031] = &procedure<0x0031>;
    Procedures[0x0032] = &procedure<0x0032>;
    Procedures[0x0033] = &procedure<0x0033>;
    Procedures[0x0034] = &procedure<0x0034>;
    Procedures[0x0035] = &procedure<0x0035>;
    Procedures[0x0036] = &procedure<0x0036>;
    Procedures[0x0037] = &procedure<0x0037>;
    Procedures[0x0038] = &procedure<0x0038>;
    Procedures[0x0039] = &procedure<0x0039>;
    Procedures[0x003A] = &procedure<0x003A>;
    Procedures[0x003B] = &procedure<0x003B>;
    Procedures[0x003C] = &procedure<0x003C>;
    Procedures[0x003D] = &procedure<0x003D>;
    Procedures[0x003E] = &procedure<0x003E>;
    Procedures[0x003F] = &procedure<0x003F>;
    Procedures[0x0040] = &procedure<0x0040>;
    Procedures[0x0041] = &procedure<0x0041>;
    Procedures[0x0042] = &procedure<0x0042>;
    Procedures[0x0043] = &procedure<0x0043>;
    Procedures[0x0044] = &procedure<0x0044>;
    Procedures[0x0045] = &procedure<0x0045>;
    Procedures[0x0046] = &procedure<0x0046>;
    Procedures[0x0047] = &procedure<0x0047>;
    Procedures[0x0048] = &procedure<0x0048>;
    Procedures[0x0049] = &procedure<0x0049>;
    Procedures[0x004A] = &procedure<0x004A>;
    Procedures[0x004B] = &procedure<0x004B>;
    Procedures[0x004C] = &procedure<0x004C>;
    Procedures[0x004D] = &procedure<0x004D>;
    Procedures[0x004E] = &procedure<0x004E>;
    Procedures[0x004F] = &procedure<0x004F>;

    initializeEPT();
}

template <>
int
vmxon<Hash("GenuineIntel")>(PVOID DirectoryTableBase)
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    int max_leaf;
    int max_extended_leaf;

    __asm_cpuid(0, &eax, &ebx, &ecx, &edx);
    max_leaf = eax & 0x7FFFFFFF;

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
    if ((ecx & (1U << 0x05)) == 0) // If 1, supports the Virtual Machine Extensions
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
    if (ecx & (1U << 0x0B)) // If 1, supports IA32_DEBUG_INTERFACE MSR for silicon debug
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
    if (ecx & (1U << 0x13)) // If 1, supports SSE4.1
        ;
    if (ecx & (1U << 0x14)) // If 1, supports SSE4.2
        ;
    if (ecx & (1U << 0x15)) // If 1, supports x2APIC feature
        ;
    if (ecx & (1U << 0x16)) // If 1, supports MOVBE instruction
        ;
    if (ecx & (1U << 0x17)) // If 1, supports the POPCNT instruction
        ;
    if (ecx & (1U << 0x18))
        ;
    if (ecx & (1U << 0x19))
        ;
    if (ecx & (1U << 0x1A))
        ;
    if (ecx & (1U << 0x1B))
        ;
    if (ecx & (1U << 0x1C)) // If 1, supports the AVX instruction extensions
        ;
    if (ecx & (1U << 0x1D))
        ;
    if (ecx & (1U << 0x1E)) // If 1, supports RDRAND instruction
        ;
    if (ecx & (1U << 0x1F))
        ;

    __asm_cpuid(0x00000003, &eax, &ebx, &ecx, &edx); // Processor Serial Number

    __asm_cpuid_ex(0x00000007, 0x00000000, &eax, &ebx, &ecx, &edx); // Structured Extended Feature Flags Main Sub-Leaf

    if (ebx & (1U << 0x00)) // If 1, supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE
        ;
    if (ebx & (1U << 0x01)) // If 1, the IA32_TSC_ADJUST MSR is supported
        ;
    if (ebx & (1U << 0x02)) // If 1, supports Intel® Software Guard Extensions (Intel® SGX Extensions)
        ;
    if (ebx & (1U << 0x03)) // If 1, supports the BMI1 instructions
        ;
    if (ebx & (1U << 0x04)) // If 1, supports the Hardware Lock Elision instruction set
        ;
    if (ebx & (1U << 0x05)) // If 1, supports Intel® Advanced Vector Extensions 2 (Intel® AVX2)
        ;
    if (ebx & (1U << 0x06)) //
        ;
    if (ebx & (1U << 0x07)) // If 1, supports Supervisor-Mode Execution Prevention
        ;
    if (ebx & (1U << 0x08)) // If 1, supports the BMI2 instructions
        ;
    if (ebx & (1U << 0x09)) //
        ;
    if (ebx & (1U << 0x0A)) // If 1, supports INVPCID instruction for system software that manages process-context identifiers
        ;
    if (ebx & (1U << 0x0B)) // If 1, supports the Restricted Transactional Memory instruction set
        ;
    if (ebx & (1U << 0x0C)) // If 1, supports Intel® Resource Director Technology (Intel® RDT) Monitoring capability
        ;
    if (ebx & (1U << 0x0D)) //
        ;
    if (ebx & (1U << 0x0E)) // If 1, supports Intel® Memory Protection Extensions
        ;
    if (ebx & (1U << 0x0F)) //
        ;
    if (ebx & (1U << 0x10)) // If 1, supports the AVX512F instructions
        ;
    if (ebx & (1U << 0x11)) // If 1, supports the AVX512DQ instructions
        ;
    if (ebx & (1U << 0x12)) // If 1, supports the RDSEED instruction
        ;
    if (ebx & (1U << 0x13)) // If 1, supports the ADX instructions
        ;
    if (ebx & (1U << 0x14)) // If 1, supports Supervisor-Mode Access Prevention and the CLAC/STAC instructions
        ;
    if (ebx & (1U << 0x15)) // If 1, supports the AVX512_IFMA instructions
        ;
    if (ebx & (1U << 0x16)) //
        ;
    if (ebx & (1U << 0x17)) // If 1, supports the CLFLUSHOPT instruction
        ;
    if (ebx & (1U << 0x18)) // If 1, supports the CLWB instruction
        ;
    if (ebx & (1U << 0x19)) // If 1, supports Intel® Processor Trace
        ;
    if (ebx & (1U << 0x1A)) // If 1, supports the AVX512PF instructions.(Intel® Xeon Phi™ only.)
        ;
    if (ebx & (1U << 0x1B)) // If 1, supports the AVX512ER instructions.(Intel® Xeon Phi™ only.)
        ;
    if (ebx & (1U << 0x1C)) // If 1, supports the AVX512CD instructions
        ;
    if (ebx & (1U << 0x1D)) // If 1, supports Intel® Secure Hash Algorithm Extensions (Intel® SHA Extensions)
        ;
    if (ebx & (1U << 0x1E)) // If 1, supports the AVX512BW instructions
        ;
    if (ebx & (1U << 0x1F)) // If 1, supports the AVX512VL instructions
        ;

    if (ecx & (1U << 0x00)) // If 1, supports the PREFETCHWT1 instruction.(Intel® Xeon Phi™ only.)
        ;
    if (ecx & (1U << 0x01)) // If 1, supports the AVX512_VBMI instructions
        ;
    if (ecx & (1U << 0x02)) // If 1, supports user-mode instruction prevention
        ;
    if (ecx & (1U << 0x03)) // If 1, supports protection keys for user-mode pages
        ;
    if (ecx & (1U << 0x04)) // If 1, the OS has set CR4.PKE to enable protection keys and the RDPKRU/WRPKRU instructions
        ;
    if (ecx & (1U << 0x05)) // If 1, supports the TPAUSE, UMONITOR, and UMWAIT instructions
        ;
    if (ecx & (1U << 0x06)) // If 1, supports the AVX512_VBMI2 instructions
        ;
    if (ecx & (1U << 0x07)) // If 1, supports CET shadow stack features
        ;
    if (ecx & (1U << 0x08)) // If 1, supports the GFNI instruction set
        ;
    if (ecx & (1U << 0x09)) // If 1 and Intel AVX supported, supports the VEX-encoded AES instruction set
        ;
    if (ecx & (1U << 0x0A)) // If 1 and Intel AVX supported, supports the VPCLMULQDQ instruction
        ;
    if (ecx & (1U << 0x0B)) // If 1, supports the AVX512_VNNI instructions
        ;
    if (ecx & (1U << 0x0C)) // If 1, supports the AVX512_BITALG instructions
        ;
    if (ecx & (1U << 0x0D)) // If 1, the following MSRs are supported:IA32_TME_CAPABILITY,IA32_TME_ACTIVATE,IA32_TME_EXCLUDE_MASK, and IA32_TME_EXCLUDE_BASE
        ;
    if (ecx & (1U << 0x0E)) // If 1, supports the AVX512_VPOPCNTDQ instructions
        ;
    if (ecx & (1U << 0x0F)) //
        ;
    if (ecx & (1U << 0x10)) // If 1, supports 57-bit linear addresses and five-level paging
        ;
    if (ecx & 0b00000000001111100000000000000000) // The value of MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode
        ;
    if (ecx & (1U << 0x16)) // If 1, RDPID and the IA32_TSC_AUX MSR are available
        ;
    if (ecx & (1U << 0x17)) // If 1, supports Key Locker
        ;
    if (ecx & (1U << 0x18)) // If 1, indicates support for OS bus-lock detection
        ;
    if (ecx & (1U << 0x19)) // If 1, supports cache line demote
        ;
    if (ecx & (1U << 0x1A)) //
        ;
    if (ecx & (1U << 0x1B)) // If 1, supports the MOVDIRI instruction
        ;
    if (ecx & (1U << 0x1C)) // If 1, supports the MOVDIR64B instruction
        ;
    if (ecx & (1U << 0x1D)) // If 1, supports Enqueue Stores
        ;
    if (ecx & (1U << 0x1E)) // If 1, supports SGX Launch Configuration
        ;
    if (ecx & (1U << 0x1F)) // If 1, supports protection keys for supervisor-mode pages
        ;

    __asm_cpuid_ex(0x0000000D, 0x00000001, &eax, &ebx, &ecx, &edx); // Feature and Supervisor State Sub-Leaf

    if (ecx & 0x00008000) // LBR state (only for the architectural LBR feature)
        ;

    __asm_cpuid(0x80000000, &eax, &ebx, &ecx, &edx); // Maximum Input Value for Extended Function CPUID Information

    max_extended_leaf = eax & 0x7FFFFFFF;

    __asm_cpuid(0x80000001, &eax, &ebx, &ecx, &edx); // Extended Processor Signature and Feature Bits

    if (ecx & (1U << 0x00)) // LAHF_SAHF_64 If 1, supports the LAHF/SAHF instructions in 64-bit mode.
        ;
    if (ecx & (1U << 0x05)) // LZCNT If 1, supports the LZCNT instruction.
        ;
    if (ecx & (1U << 0x08)) // PREFETCHW If 1, supports the PREFETCHW instruction.
        ;

    if (edx & (1U << 0x0B)) // SYSCALL_SYSRET_64 If 1, supports SYSCALL/SYSRET.
        ;
    if (edx & (1U << 0x14)) // EXECUTE_DIS If 1, supports Execute Disable Bit.
        ;
    if (edx & (1U << 0x1A)) // PAGE_1GB If 1, supports 1-GByte pages.
        ;
    if (edx & (1U << 0x1B)) // RDTSCP If 1, supports RDTSCP and IA32_TSC_AUX.
        ;
    if (edx & (1U << 0x1D)) // INTEL64 If 1, supports Intel® 64 Architecture.
        ;

    uint64_t CR0 = __asm_cr0();
    // uint64_t CR1 = __asm_cr1();
    uint64_t CR2 = __asm_cr2(); // Page-Fault Linear Address
    uint64_t CR3 = __asm_cr3();
    uint64_t CR4 = __asm_cr4();

    if (CR0 & (1ULL << 0x00)) // CR0.PE Protection Enable (bit 0 of CR0)
        ;
    if (CR0 & (1ULL << 0x01)) // CR0.MP Monitor Coprocessor (bit 1 of CR0)
        ;
    if (CR0 & (1ULL << 0x02)) // CR0.EM Emulation (bit 2 of CR0)
        ;
    if (CR0 & (1ULL << 0x03)) // CR0.TS Task Switched (bit 3 of CR0)
        ;
    if (CR0 & (1ULL << 0x04)) // CR0.ET Extension Type (bit 4 of CR0)
        ;
    if (CR0 & (1ULL << 0x05)) // CR0.NE Numeric Error (bit 5 of CR0)
        ;
    if (CR0 & (1ULL << 0x10)) // CR0.WP Write Protect (bit 16 of CR0)
        ;
    if (CR0 & (1ULL << 0x12)) // CR0.AM Alignment Mask (bit 18 of CR0)
        ;
    if (CR0 & (1ULL << 0x1D)) // CR0.NW Not Write-through (bit 29 of CR0)
        ;
    if (CR0 & (1ULL << 0x1E)) // CR0.CD Cache Disable (bit 30 of CR0)
        ;
    if (CR0 & (1ULL << 0x1F)) // CR0.PG Paging (bit 31 of CR0)
        ;

    if (CR3 & (1ULL << 0x03)) // CR3.PWT Page-level Write-Through (bit 3 of CR3)
        ;
    if (CR3 & (1ULL << 0x04)) // CR3.PCD Page-level Cache Disable (bit 4 of CR3)
        ;
    if (CR3 & (1ULL << 0x3D)) // CR3.LAM_U57 User LAM57 enable (bit 61 of CR3)
        ;
    if (CR3 & (1ULL << 0x3E)) // CR3.LAM_U48 User LAM48 enable (bit 62 of CR3)
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
    if (CR4 & (1ULL << 0x0D)) // CR4.VMXE VMX-Enable Bit (bit 13 of CR4)
        ;
    if (CR4 & (1ULL << 0x0E)) // CR4.SMXE SMX-Enable Bit (bit 14 of CR4)
        ;
    if (CR4 & (1ULL << 0x0F))
        ;
    if (CR4 & (1ULL << 0x10)) // CR4.FSGSBASE FSGSBASE-Enable Bit (bit 16 of CR4)
        ;
    if (CR4 & (1ULL << 0x11)) // CR4.PCIDE PCID-Enable Bit (bit 17 of CR4)
        ;
    if (CR4 & (1ULL << 0x12)) // CR4.OSXSAVE XSAVE and Processor Extended States-Enable Bit (bit 18 of CR4)
        ;
    if (CR4 & (1ULL << 0x13)) // CR4.KL Key-Locker-Enable Bit (bit 19 of CR4)
        ;
    if (CR4 & (1ULL << 0x14)) // CR4.SMEP SMEP-Enable Bit (bit 20 of CR4)
        ;
    if (CR4 & (1ULL << 0x15)) // CR4.SMAP SMAP-Enable Bit (bit 21 of CR4)
        ;
    if (CR4 & (1ULL << 0x16)) // CR4.PKE Enable protection keys for user-mode pages (bit 22 of CR4)
        ;
    if (CR4 & (1ULL << 0x17)) // CR4.CET Control-flow Enforcement Technology (bit 23 of CR4)
        ;
    if (CR4 & (1ULL << 0x18)) // CR4.PKS Enable protection keys for supervisor-mode pages (bit 24 of CR4)
        ;
    if (CR4 & (1ULL << 0x19)) // CR4.UINTR User Interrupts Enable Bit (bit 25 of CR4)
        ;
    if (CR4 & (1ULL << 0x1A))
        ;
    if (CR4 & (1ULL << 0x1B)) // CR4.LASS Linear-address-space Separation (bit 27 of CR4)
        ;
    if (CR4 & (1ULL << 0x1C)) // CR4.LAM_SUP Supervisor LAM enable (bit 28 of CR4)
        ;
    if (CR4 & (1ULL << 0x1D))
        ;
    if (CR4 & (1ULL << 0x1E))
        ;
    if (CR4 & (1ULL << 0x1F))
        ;
    if (CR4 & (1ULL << 0x20)) // CR4.FRED FRED enable (bit 32 of CR4)
        ;

    uint16_t CS = __asm_cs();
    uint16_t DS = __asm_ds();
    uint16_t ES = __asm_es();
    uint16_t FS = __asm_fs();
    uint16_t GS = __asm_gs();
    uint16_t SS = __asm_ss();
    uint16_t TR = __asm_str();
    uint16_t LDTR = __asm_sldt();

    IA32_GDT_REGISTER GDTR;
    IA32_IDT_REGISTER IDTR;

    __asm_sgdt(&GDTR);
    __asm_sidt(&IDTR);

    uint64_t ia32_time_stamp_counter = __asm_rdmsr(IA32_TIME_STAMP_COUNTER);
    uint64_t ia32_apic_base = __asm_rdmsr(IA32_APIC_BASE);
    uint64_t ia32_feature_control = __asm_rdmsr(IA32_FEATURE_CONTROL); // Control Features in Intel 64 Processor (R/W)

    /**
     * If this bit is clear, VMXON causes a general-protection exception
     * If the lock bit is set, WRMSR to this MSR causes a general-protection exception;
     **/
    if ((ia32_feature_control & (1ULL << 0x00)) == 0) // Lock bit (R/WO): (1 = locked)
        __asm_wrmsr(IA32_FEATURE_CONTROL, ia32_feature_control | 1);
    if (ia32_feature_control & (1ULL << 0x01)) // Enable VMX inside SMX operation (R/WL) This bit enables a system executive to use VMX in conjunction with SMX to support Intel® Trusted Execution Technology
        ;
    if ((ia32_feature_control & (1ULL << 0x02)) == 0) // Enable VMX outside SMX operation (R/WL) This bit enables VMX for a system executive that does not require SMX
        return -1;
    if (ia32_feature_control & (1ULL << 0x03))
        ;
    if (ia32_feature_control & (1ULL << 0x04))
        ;
    if (ia32_feature_control & (1ULL << 0x05))
        ;
    if (ia32_feature_control & (1ULL << 0x06))
        ;
    if (ia32_feature_control & (1ULL << 0x07))
        ;
    if (ia32_feature_control & (1ULL << 0x08))
        ;
    if (ia32_feature_control & (1ULL << 0x09))
        ;
    if (ia32_feature_control & (1ULL << 0x0A))
        ;
    if (ia32_feature_control & (1ULL << 0x0B))
        ;
    if (ia32_feature_control & (1ULL << 0x0C))
        ;
    if (ia32_feature_control & (1ULL << 0x0D))
        ;
    if (ia32_feature_control & (1ULL << 0x0E))
        ;
    if (ia32_feature_control & (1ULL << 0x0F))
        ;
    if (ia32_feature_control & (1ULL << 0x10))
        ;
    if (ia32_feature_control & (1ULL << 0x11))
        ;
    if (ia32_feature_control & (1ULL << 0x12))
        ;
    if (ia32_feature_control & (1ULL << 0x13))
        ;
    if (ia32_feature_control & (1ULL << 0x14))
        ;
    if (ia32_feature_control & (1ULL << 0x15))
        ;
    if (ia32_feature_control & (1ULL << 0x16))
        ;
    if (ia32_feature_control & (1ULL << 0x17))
        ;
    if (ia32_feature_control & (1ULL << 0x18))
        ;
    if (ia32_feature_control & (1ULL << 0x19))
        ;
    if (ia32_feature_control & (1ULL << 0x1A))
        ;
    if (ia32_feature_control & (1ULL << 0x1B))
        ;
    if (ia32_feature_control & (1ULL << 0x1C))
        ;
    if (ia32_feature_control & (1ULL << 0x1D))
        ;
    if (ia32_feature_control & (1ULL << 0x1E))
        ;
    if (ia32_feature_control & (1ULL << 0x1F))
        ;
    uint64_t ia32_tsc_adjust = __asm_rdmsr(IA32_TSC_ADJUST);
    uint64_t ia32_spec_ctrl = __asm_rdmsr(IA32_SPEC_CTRL);
    uint64_t ia32_smbase = __asm_rdmsr(IA32_SMBASE);
    uint64_t ia32_pmc0 = __asm_rdmsr(IA32_PMC0);
    uint64_t ia32_pmc1 = __asm_rdmsr(IA32_PMC1);
    uint64_t ia32_pmc2 = __asm_rdmsr(IA32_PMC2);
    uint64_t ia32_pmc3 = __asm_rdmsr(IA32_PMC3);
    uint64_t ia32_pmc4 = __asm_rdmsr(IA32_PMC4);
    uint64_t ia32_pmc5 = __asm_rdmsr(IA32_PMC5);
    uint64_t ia32_pmc6 = __asm_rdmsr(IA32_PMC6);
    uint64_t ia32_pmc7 = __asm_rdmsr(IA32_PMC7);
    uint64_t ia32_pmc8 = __asm_rdmsr(IA32_PMC8);
    uint64_t ia32_pmc9 = __asm_rdmsr(IA32_PMC9);

    uint64_t ia32_core_capabilities = __asm_rdmsr(IA32_CORE_CAPABILITIES);
    uint64_t ia32_mperf = __asm_rdmsr(IA32_MPERF);
    uint64_t ia32_aperf = __asm_rdmsr(IA32_APERF);

    uint64_t ia32_arch_capabilities = __asm_rdmsr(IA32_ARCH_CAPABILITIES);

    uint64_t ia32_sysenter_cs = __asm_rdmsr(IA32_SYSENTER_CS);
    uint64_t ia32_sysenter_esp = __asm_rdmsr(IA32_SYSENTER_ESP);
    uint64_t ia32_sysenter_eip = __asm_rdmsr(IA32_SYSENTER_EIP);

    uint64_t ia32_perf_status = __asm_rdmsr(IA32_PERF_STATUS);
    uint64_t ia32_perf_ctl = __asm_rdmsr(IA32_PERF_CTL);

    uint64_t ia32_misc_enable = __asm_rdmsr(IA32_MISC_ENABLE);

    uint64_t ia32_debugctl = __asm_rdmsr(IA32_DEBUGCTL);

    uint64_t ia32_smrr_physbase = __asm_rdmsr(IA32_SMRR_PHYSBASE);
    uint64_t ia32_smrr_physmask = __asm_rdmsr(IA32_SMRR_PHYSMASK);

    uint64_t ia32_mtrr_physbase0 = __asm_rdmsr(IA32_MTRR_PHYSBASE0);
    uint64_t ia32_mtrr_physmask0 = __asm_rdmsr(IA32_MTRR_PHYSMASK0);
    uint64_t ia32_mtrr_physbase1 = __asm_rdmsr(IA32_MTRR_PHYSBASE1);
    uint64_t ia32_mtrr_physmask1 = __asm_rdmsr(IA32_MTRR_PHYSMASK1);
    uint64_t ia32_mtrr_physbase2 = __asm_rdmsr(IA32_MTRR_PHYSBASE2);
    uint64_t ia32_mtrr_physmask2 = __asm_rdmsr(IA32_MTRR_PHYSMASK2);
    uint64_t ia32_mtrr_physbase3 = __asm_rdmsr(IA32_MTRR_PHYSBASE3);
    uint64_t ia32_mtrr_physmask3 = __asm_rdmsr(IA32_MTRR_PHYSMASK3);
    uint64_t ia32_mtrr_physbase4 = __asm_rdmsr(IA32_MTRR_PHYSBASE4);
    uint64_t ia32_mtrr_physmask4 = __asm_rdmsr(IA32_MTRR_PHYSMASK4);
    uint64_t ia32_mtrr_physbase5 = __asm_rdmsr(IA32_MTRR_PHYSBASE5);
    uint64_t ia32_mtrr_physmask5 = __asm_rdmsr(IA32_MTRR_PHYSMASK5);
    uint64_t ia32_mtrr_physbase6 = __asm_rdmsr(IA32_MTRR_PHYSBASE6);
    uint64_t ia32_mtrr_physmask6 = __asm_rdmsr(IA32_MTRR_PHYSMASK6);
    uint64_t ia32_mtrr_physbase7 = __asm_rdmsr(IA32_MTRR_PHYSBASE7);
    uint64_t ia32_mtrr_physmask7 = __asm_rdmsr(IA32_MTRR_PHYSMASK7);
    uint64_t ia32_mtrr_physbase8 = __asm_rdmsr(IA32_MTRR_PHYSBASE8);
    uint64_t ia32_mtrr_physmask8 = __asm_rdmsr(IA32_MTRR_PHYSMASK8);
    uint64_t ia32_mtrr_physbase9 = __asm_rdmsr(IA32_MTRR_PHYSBASE9);
    uint64_t ia32_mtrr_physmask9 = __asm_rdmsr(IA32_MTRR_PHYSMASK9);

    uint64_t ia32_perf_capabilities = __asm_rdmsr(IA32_PERF_CAPABILITIES);

    uint64_t ia32_vmx_basic = __asm_rdmsr(IA32_VMX_BASIC);
    uint64_t ia32_vmx_pinbased_ctls = __asm_rdmsr(IA32_VMX_PINBASED_CTLS);
    uint64_t ia32_vmx_procbased_ctls = __asm_rdmsr(IA32_VMX_PROCBASED_CTLS);
    uint64_t ia32_vmx_exit_ctls = __asm_rdmsr(IA32_VMX_EXIT_CTLS);
    uint64_t ia32_vmx_entry_ctls = __asm_rdmsr(IA32_VMX_ENTRY_CTLS);
    uint64_t ia32_vmx_misc = __asm_rdmsr(IA32_VMX_MISC);
    uint64_t ia32_vmx_cr0_fixed0 = __asm_rdmsr(IA32_VMX_CR0_FIXED0);
    uint64_t ia32_vmx_cr0_fixed1 = __asm_rdmsr(IA32_VMX_CR0_FIXED1);
    uint64_t ia32_vmx_cr4_fixed0 = __asm_rdmsr(IA32_VMX_CR4_FIXED0);
    uint64_t ia32_vmx_cr4_fixed1 = __asm_rdmsr(IA32_VMX_CR4_FIXED1);
    uint64_t ia32_vmx_vmcs_enum = __asm_rdmsr(IA32_VMX_VMCS_ENUM);
    uint64_t ia32_vmx_procbased_ctls2 = __asm_rdmsr(IA32_VMX_PROCBASED_CTLS2);
    uint64_t ia32_vmx_ept_vpid_cap = __asm_rdmsr(IA32_VMX_EPT_VPID_CAP);

    if (ia32_vmx_ept_vpid_cap & (1ULL << 0)) // If bit 0 is read as 1, the processor supports execute-only translations by EPT
        ;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 6)) == 0) // Bit 6 indicates support for a page-walk length of 4
        return -1;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 7)) // Bit 7 indicates support for a page-walk length of 5
        ;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 8)) // If bit 8 is read as 1, the logical processor allows software to configure the EPT paging-structure memory type to be uncacheable (UC)
        ;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 14)) == 0) // If bit 14 is read as 1, the logical processor allows software to configure the EPT paging-structure memory type to be write-back (WB)
        return -1;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 16)) // If bit 16 is read as 1, the logical processor allows software to configure a EPT PDE to map a 2-Mbyte page (by setting bit 7 in the EPT PDE)
        ;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 17)) // If bit 17 is read as 1, the logical processor allows software to configure a EPT PDPTE to map a 1-Gbyte page (by setting bit 7 in the EPT PDPTE)
        ;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 20)) == 0) // If bit 20 is read as 1, the INVEPT instruction is supported
        return -1;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 21)) // If bit 21 is read as 1, accessed and dirty flags for EPT are supported
        ;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 22)) // If bit 22 is read as 1, the processor reports advanced VM-exit information for EPT violations. This reporting is done only if this bit is read as 1
        ;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 23)) // If bit 23 is read as 1, supervisor shadow-stack control is supported
        ;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 25)) == 0) // If bit 25 is read as 1, the single-context INVEPT type is supported
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 26)) == 0) // If bit 26 is read as 1, the all-context INVEPT type is supported
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 32)) == 0) // If bit 32 is read as 1, the INVVPID instruction is supported
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 40)) == 0) // If bit 40 is read as 1, the individual-address INVVPID type is supported
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 41)) == 0) // If bit 41 is read as 1, the single-context INVVPID type is supported
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 42)) == 0) // If bit 42 is read as 1, the all-context INVVPID type is supported
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 43)) == 0) // If bit 43 is read as 1, the single-context-retaining-globals INVVPID type is supported
        return -1;

    uint64_t ia32_vmx_true_pinbased_ctls = __asm_rdmsr(IA32_VMX_TRUE_PINBASED_CTLS);
    uint64_t ia32_vmx_true_procbased_ctls = __asm_rdmsr(IA32_VMX_TRUE_PROCBASED_CTLS);
    uint64_t ia32_vmx_true_exit_ctls = __asm_rdmsr(IA32_VMX_TRUE_EXIT_CTLS);
    uint64_t ia32_vmx_true_entry_ctls = __asm_rdmsr(IA32_VMX_TRUE_ENTRY_CTLS);
    uint64_t ia32_vmx_vmfunc = __asm_rdmsr(IA32_VMX_VMFUNC);
    uint64_t ia32_vmx_procbased_ctls3 = __asm_rdmsr(IA32_VMX_PROCBASED_CTLS3);
    uint64_t ia32_vmx_exit_ctls2 = __asm_rdmsr(IA32_VMX_EXIT_CTLS2);

    uint64_t ia32_debug_interface = __asm_rdmsr(IA32_DEBUG_INTERFACE);

    uint64_t ia32_lbr_ctl = __asm_rdmsr(IA32_LBR_CTL);
    uint64_t ia32_lbr_depth = __asm_rdmsr(IA32_LBR_DEPTH);

    for (uint32_t i = 0; i < 0x20; ++i) {
        uint64_t msr;
        msr = __asm_rdmsr(IA32_LBR_x_FROM_IP + i);
        msr = __asm_rdmsr(IA32_LBR_x_TO_IP + i);

        UNREFERENCED_PARAMETER(msr);
    }

    uint64_t ia32_efer = __asm_rdmsr(IA32_EFER);
    uint64_t ia32_star = __asm_rdmsr(IA32_STAR);
    uint64_t ia32_lstar = __asm_rdmsr(IA32_LSTAR);
    uint64_t ia32_cstar = __asm_rdmsr(IA32_CSTAR);
    uint64_t ia32_fmask = __asm_rdmsr(IA32_FMASK);

    uint64_t ia32_fs_base = __asm_rdmsr(IA32_FS_BASE);
    uint64_t ia32_gs_base = __asm_rdmsr(IA32_GS_BASE);
    uint64_t ia32_kernel_gs_base = __asm_rdmsr(IA32_KERNEL_GS_BASE);
    uint64_t ia32_tsc_aux = __asm_rdmsr(IA32_TSC_AUX);

    if (ia32_efer & (1ULL << 0x00)) // 0 SYSCALL Enable: IA32_EFER.SCE (R/W)
        ;
    if (ia32_efer & (1ULL << 0x01))
        ;
    if (ia32_efer & (1ULL << 0x02))
        ;
    if (ia32_efer & (1ULL << 0x03))
        ;
    if (ia32_efer & (1ULL << 0x04))
        ;
    if (ia32_efer & (1ULL << 0x05))
        ;
    if (ia32_efer & (1ULL << 0x06))
        ;
    if (ia32_efer & (1ULL << 0x07))
        ;
    if (ia32_efer & (1ULL << 0x08)) // 8 IA-32e Mode Enable: IA32_EFER.LME (R/W)
        ;
    if (ia32_efer & (1ULL << 0x09))
        ;
    if (ia32_efer & (1ULL << 0x0A)) // 10 IA-32e Mode Active: IA32_EFER.LMA (R)
        ;
    if (ia32_efer & (1ULL << 0x0B)) // 11 Execute Disable Bit Enable: IA32_EFER.NXE (R/W)
        ;

    CONTEXT Context;
    RtlCaptureContext(&Context);

    if (Context.Rip == 0x12345678)
        return 0;

    __asm_cr0((CR0 & ia32_vmx_cr0_fixed1) | ia32_vmx_cr0_fixed0);
    __asm_cr4(((CR4 | 0x00002000 /*VMXE*/) & ia32_vmx_cr4_fixed1) | ia32_vmx_cr4_fixed0);

    CR0 = __asm_cr0();
    CR4 = __asm_cr4();

    PVOID iopm = allocate<0x2000>(); // 文档中不要求两个页在物理上连续.
    PVOID msrpm = allocateContiguous<0x1000>();
    PVOID vmcsGuest = allocateContiguous<0x1000>();
    PVOID vmxonRegion = allocateContiguous<0x1000>();

    ASSERT(iopm);
    ASSERT(vmcsGuest);
    ASSERT(vmxonRegion);
    ASSERT(msrpm);

    if ((SIZE_T)iopm & 0xFFF)
        return -1;

    if ((SIZE_T)msrpm & 0xFFF)
        return -1;

    if ((SIZE_T)vmcsGuest & 0xFFF)
        return -1;

    if ((SIZE_T)vmxonRegion & 0xFFF)
        return -1;

    memset(iopm, 0, 0x2000);
    memset(msrpm, 0, 0x1000);
    memset(vmcsGuest, 0, 0x1000);
    memset(vmxonRegion, 0, 0x1000);

    /**
     * Bits 30:0: VMCS revision identifier
     * Bit 31: shadow-VMCS indicator (see Section 27.10)
     **/
    *(uint32_t*)vmcsGuest = (uint32_t)ia32_vmx_basic & 0x7FFFFFFF;
    *(uint32_t*)vmxonRegion = (uint32_t)ia32_vmx_basic & 0x7FFFFFFF;

    PHYSICAL_ADDRESS iopmPA[2] = {MmGetPhysicalAddress(iopm), MmGetPhysicalAddress((uint8_t*)iopm + 0x1000)};
    PHYSICAL_ADDRESS vmcsGuestPA = MmGetPhysicalAddress(vmcsGuest);
    PHYSICAL_ADDRESS vmxonRegionPA = MmGetPhysicalAddress(vmxonRegion);
    PHYSICAL_ADDRESS msrpmPA = MmGetPhysicalAddress(msrpm);

    size_t Status = {};

#define EFLAGS_CF_MASK   (1 << 0x00)
#define EFLAGS_PF_MASK   (1 << 0x02)
#define EFLAGS_AF_MASK   (1 << 0x04)
#define EFLAGS_ZF_MASK   (1 << 0x06)
#define EFLAGS_SF_MASK   (1 << 0x07)
#define EFLAGS_TF_MASK   (1 << 0x08)
#define EFLAGS_IF_MASK   (1 << 0x09)
#define EFLAGS_DF_MASK   (1 << 0x0A)
#define EFLAGS_OF_MASK   (1 << 0x0B)
#define EFLAGS_IOPL_MASK (0x3000)
#define EFLAGS_NT_MASK   (1 << 0x0E)
#define EFLAGS_RF_MASK   (1 << 0x10)
#define EFLAGS_VM_MASK   (1 << 0x11)
#define EFLAGS_AC_MASK   (1 << 0x12)
#define EFLAGS_VIF_MASK  (1 << 0x13)
#define EFLAGS_VIP_MASK  (1 << 0x14)
#define EFLAGS_ID_MASK   (1 << 0x15)

    Status = __asm_vmx_vmxon((uint64_t*)&vmxonRegionPA.QuadPart);
    if (Status & EFLAGS_ZF_MASK) {
        size_t e;
        __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
        e = 0;
        return -1;
    }

    Status = __asm_vmx_vmclear((uint64_t*)&vmcsGuestPA.QuadPart);
    if (Status & EFLAGS_ZF_MASK) {
        size_t e;
        __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
        e = 0;
        return -1;
    }

    Status = __asm_vmx_vmptrld((uint64_t*)&vmcsGuestPA.QuadPart);
    if (Status & EFLAGS_ZF_MASK) {
        size_t e;
        __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
        e = 0;
        return -1;
    }

    uint64_t PinBasedVmExecutionControls = {};
    uint64_t PrimaryProcessorBasedVmExecutionControls = {};
    uint64_t SecondaryProcessorBasedVmExecutionControls = {};
    uint64_t TertiaryProcessorBasedVmExecutionControls = {};
    uint64_t PrimaryVmExitControls = {};
    uint64_t SecondaryVmExitControls = {};
    uint64_t VmEntryControls = {};

    // A.3.1 Pin-Based VM-Execution Controls
    {
        // PinBasedVmExecutionControls |= (1ULL << 0); // External-interrupt exiting
        // PinBasedVmExecutionControls |= (1ULL << 3); // NMI exiting
        // PinBasedVmExecutionControls |= (1ULL << 5); // Virtual NMIs
        // PinBasedVmExecutionControls |= (1ULL << 6); // Activate VMX-preemption timer
        // PinBasedVmExecutionControls |= (1ULL << 7); // Process posted interrupts

        // If bit 55 in the IA32_VMX_BASIC MSR is read as 1, all information about the allowed settings of the pin-based VM-execution controls is contained in the IA32_VMX_TRUE_PINBASED_CTLS MSR. Assuming that software knows that the default1 class of pin-based VM-execution controls contains bits 1, 2, and 4, there is no need for software to consult the IA32_VMX_PINBASED_CTLS MSR
        if (ia32_vmx_basic & (1ULL << 55))
            PinBasedVmExecutionControls = vmx_format_controls(IA32_VMX_TRUE_PINBASED_CTLS, PinBasedVmExecutionControls);
        else
            PinBasedVmExecutionControls = vmx_format_controls(IA32_VMX_PINBASED_CTLS, PinBasedVmExecutionControls);

        Status |= __asm_vmx_vmwrite(VMX_VMCS32_CTRL_PIN_EXEC, PinBasedVmExecutionControls);
    }

    // A.3.2 Primary Processor-Based VM-Execution Controls
    {
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x02); // Interrupt-window exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x03); // Use TSC offsetting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x07); // HLT exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x09); // INVLPG exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x0A); // MWAIT exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x0B); // RDPMC exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x0C); // RDTSC exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x0F); // CR3-load exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x10); // CR3-store exiting

        PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x11); // Activate tertiary controls

        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x13); // CR8-load exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x14); // CR8-store exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x15); // Use TPR shadow
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x16); // NMI-window exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x17); // MOV-DR exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x18); // Unconditional I/O exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x19); // Use I/O bitmaps
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x1B); // Monitor trap flag

        PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x1C); // Use MSR bitmaps

        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x1D); // MONITOR exiting
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x1E); // PAUSE exiting

        PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x1F); // Activate secondary controls

        if (ia32_vmx_basic & (1ULL << 55))
            PrimaryProcessorBasedVmExecutionControls = (uint32_t)vmx_format_controls(IA32_VMX_TRUE_PROCBASED_CTLS, PrimaryProcessorBasedVmExecutionControls);
        else
            PrimaryProcessorBasedVmExecutionControls = (uint32_t)vmx_format_controls(IA32_VMX_PROCBASED_CTLS, PrimaryProcessorBasedVmExecutionControls);
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_CTRL_PROC_EXEC, PrimaryProcessorBasedVmExecutionControls);
    }

    // A.3.3 Secondary Processor-Based VM-Execution Controls
    if (PrimaryProcessorBasedVmExecutionControls & (1ULL << 0x1F)) { // Activate secondary controls

        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x00); // Virtualize APIC accesses

        SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x01); // Enable EPT

        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x02); // Descriptor-table exiting

        SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x03); // Enable RDTSCP

        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x04); // Virtualize x2APIC mode

        SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x05); // Enable VPID

        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x06); // WBINVD exiting
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x07); // Unrestricted guest
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x08); // APIC-register virtualization
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x09); // Virtual-interrupt delivery
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x0A); // PAUSE-loop exiting
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x0B); // RDRAND exiting

        SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x0C); // Enable INVPCID

        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x0D); // Enable VM functions
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x0E); // VMCS shadowing
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x0F); // Enable ENCLS exiting
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x10); // RDSEED exiting
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x11); // Enable PML
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x12); // EPT-violation #VE
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x13); // Conceal VMX from PT

        SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x14); // Enable XSAVES/XRSTORS

        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x15); // PASID translation
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x16); // Mode-based execute control for EPT
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x17); // Sub-page write permissions for EPT
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x18); // Intel PT uses guest physical addresses
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x19); // Use TSC scaling
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x1A); // Enable user wait and pause
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x1B); // Enable PCONFIG
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x1C); //
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x1D); //
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x1E); // VMM bus-lock detection
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x1F); // Instruction timeout

        SecondaryProcessorBasedVmExecutionControls = (uint32_t)vmx_format_controls(IA32_VMX_PROCBASED_CTLS2, SecondaryProcessorBasedVmExecutionControls);
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_CTRL_PROC_EXEC2, SecondaryProcessorBasedVmExecutionControls);
    }

    // A.3.4 Tertiary Processor-Based VM-Execution Controls
    if (PrimaryProcessorBasedVmExecutionControls & (1ULL << 0x11)) { // Activate tertiary controls

        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x00); // LOADIWKEY exiting
        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x01); // Enable HLAT
        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x02); // EPT paging-write control
        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x03); // Guest-paging verification
        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x04); // IPI virtualization
        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x05); // SEAM guest-physical address width
        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x06); // Enable MSR-list instructions
        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x07); // Virtualize IA32_SPEC_CTRL
        // TertiaryProcessorBasedVmExecutionControls |= (1ULL << 0x09); // Enable PBNDKB

        TertiaryProcessorBasedVmExecutionControls = (uint32_t)vmx_format_controls(IA32_VMX_PROCBASED_CTLS3, TertiaryProcessorBasedVmExecutionControls);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_CTRL_PROC_EXEC3_FULL, TertiaryProcessorBasedVmExecutionControls);
    }

    // A.4.1 Primary VM-Exit Controls
    {
        // PrimaryVmExitControls |= (1ULL << 0x02); // Save debug controls
#if defined(_M_AMD64) || defined(__x86_64__)
        PrimaryVmExitControls |= (1ULL << 0x09); // Host address-space size
#endif
        // PrimaryVmExitControls |= (1ULL << 0x0C); // Load IA32_PERF_GLOBAL_CTRL
        // PrimaryVmExitControls |= (1ULL << 0x0F); // Acknowledge interrupt on exit
        // PrimaryVmExitControls |= (1ULL << 0x12); // Save IA32_PAT
        // PrimaryVmExitControls |= (1ULL << 0x13); // Load IA32_PAT
        // PrimaryVmExitControls |= (1ULL << 0x14); // Save IA32_EFER
        // PrimaryVmExitControls |= (1ULL << 0x15); // Load IA32_EFER
        // PrimaryVmExitControls |= (1ULL << 0x16); // Save VMX-preemption timer value
        // PrimaryVmExitControls |= (1ULL << 0x17); // Clear IA32_BNDCFGS
        // PrimaryVmExitControls |= (1ULL << 0x18); // Conceal VMX from PT
        // PrimaryVmExitControls |= (1ULL << 0x19); // Clear IA32_RTIT_CTL
        // PrimaryVmExitControls |= (1ULL << 0x1A); // Clear IA32_LBR_CTL
        // PrimaryVmExitControls |= (1ULL << 0x1B); // Clear UINV
        // PrimaryVmExitControls |= (1ULL << 0x1C); // Load CET state
        // PrimaryVmExitControls |= (1ULL << 0x1D); // Load PKRS
        // PrimaryVmExitControls |= (1ULL << 0x1E); // Save IA32_PERF_GLOBAL_CTL
        PrimaryVmExitControls |= (1ULL << 0x1F); // Activate secondary controls

        if (ia32_vmx_basic & (1ULL << 55))
            PrimaryVmExitControls = (uint32_t)vmx_format_controls(IA32_VMX_TRUE_EXIT_CTLS, PrimaryVmExitControls);
        else
            PrimaryVmExitControls = (uint32_t)vmx_format_controls(IA32_VMX_EXIT_CTLS, PrimaryVmExitControls);
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_CTRL_EXIT, PrimaryVmExitControls);
    }

    // A.4.2 Secondary VM-Exit Controls
    if (PrimaryVmExitControls & (1ULL << 0x1F)) { // Activate secondary controls

        // SecondaryVmExitControls |= (1ULL << 0x00); // Save FRED
        // SecondaryVmExitControls |= (1ULL << 0x01); // Load FRED
        // SecondaryVmExitControls |= (1ULL << 0x03); // Prematurely busy shadow stack

        SecondaryVmExitControls = (uint32_t)vmx_format_controls(IA32_VMX_EXIT_CTLS2, SecondaryVmExitControls);
        Status |= __asm_vmx_vmwrite(0x00002044 /*Secondary VM-exit controls (full)*/, SecondaryVmExitControls);
    }

    // A.5 VM-ENTRY CONTROLS
    {
        VmEntryControls |= (1ULL << 0x02); // 2 Load debug controls
#if defined(_M_AMD64) || defined(__x86_64__)
        VmEntryControls |= (1ULL << 0x09); // 9 IA-32e mode guest
#endif
        // VmEntryControls |= (1ULL << 0x0A); // 10 Entry to SMM
        // VmEntryControls |= (1ULL << 0x0B); // 11 Deactivate dual-monitor treatment
        // VmEntryControls |= (1ULL << 0x0D); // 13 Load IA32_PERF_GLOBAL_CTRL
        // VmEntryControls |= (1ULL << 0x0E); // 14 Load IA32_PAT
        // VmEntryControls |= (1ULL << 0x0F); // 15 Load IA32_EFER
        // VmEntryControls |= (1ULL << 0x10); // 16 Load IA32_BNDCFGS
        // VmEntryControls |= (1ULL << 0x11); // 17 Conceal VMX from PT
        // VmEntryControls |= (1ULL << 0x12); // 18 Load IA32_RTIT_CTL
        // VmEntryControls |= (1ULL << 0x13); // 19 Load UINV
        // VmEntryControls |= (1ULL << 0x14); // 20 Load CET state
        // VmEntryControls |= (1ULL << 0x15); // 21 Load guest IA32_LBR_CTL
        // VmEntryControls |= (1ULL << 0x16); // 22 Load PKRS
        // VmEntryControls |= (1ULL << 0x17); // 23 Load FRED
        // VmEntryControls |= (1ULL << 0x19); // 25 Allow SEAM-guest telemetry

        if (ia32_vmx_basic & (1ULL << 55))
            VmEntryControls = (uint32_t)vmx_format_controls(IA32_VMX_TRUE_ENTRY_CTLS, VmEntryControls);
        else
            VmEntryControls = (uint32_t)vmx_format_controls(IA32_VMX_ENTRY_CTLS, VmEntryControls);
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_CTRL_ENTRY, VmEntryControls);
    }

    // Control Fields
    {
        if (PrimaryProcessorBasedVmExecutionControls & (1ULL << 0x19)) { // Use I/O bitmaps
            __asm_vmx_vmwrite(0x00002000, iopmPA[0].QuadPart);           // Address of I/O bitmap A (full)
            __asm_vmx_vmwrite(0x00002002, iopmPA[1].QuadPart);           // Address of I/O bitmap B (full)
        }

        if (PrimaryProcessorBasedVmExecutionControls & (1ULL << 0x1C)) // Use MSR bitmaps
            Status |= __asm_vmx_vmwrite(VMX_VMCS64_CTRL_MSR_BITMAP_FULL, msrpmPA.QuadPart);

        if (SecondaryProcessorBasedVmExecutionControls & (1ULL << 0x01)) // Enable EPT
            Status |= __asm_vmx_vmwrite(VMX_VMCS64_CTRL_EPTP_FULL, EPTP);

        if (SecondaryProcessorBasedVmExecutionControls & (1ULL << 0x05)) // Enable VPID
            Status |= __asm_vmx_vmwrite(VMX_VMCS16_VPID, __asm_rdpid() + 1);

        Status |= __asm_vmx_vmwrite(VMX_VMCS32_CTRL_EXCEPTION_BITMAP, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_CTRL_CR0_MASK, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_CTRL_CR4_MASK, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_CTRL_CR0_READ_SHADOW, CR0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_CTRL_CR4_READ_SHADOW, CR4);
    }

    // Host Fields
    {
        size_t stack = (size_t)allocate<0x8000>();
        ASSERT(stack);

        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_RSP, stack + 0x8000 - 0x20);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_RIP, (uint64_t)&vmx_vmexit);

        // RPL and TI have to be 0
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_CS_SEL, CS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_DS_SEL, DS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_ES_SEL, ES & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_FS_SEL, FS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_GS_SEL, GS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_SS_SEL, SS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_TR_SEL, TR & 0xFFF8);

#if defined(_M_AMD64) || defined(__x86_64__)
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_FS_BASE, ia32_fs_base);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_GS_BASE, ia32_gs_base);
#endif

#if defined(_M_IX86) || defined(__i386__)
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_FS_BASE, __lsb(FS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_GS_BASE, __lsb(GS));
#endif

        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_TR_BASE, __lsb(TR));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_GDTR_BASE, (size_t)GDTR.BaseAddress); // 竟然没有设置limit的接口...
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_IDTR_BASE, (size_t)IDTR.BaseAddress); // 竟然没有设置limit的接口...

        Status |= __asm_vmx_vmwrite(VMX_VMCS32_HOST_SYSENTER_CS, ia32_sysenter_cs);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_SYSENTER_ESP, ia32_sysenter_esp);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_SYSENTER_EIP, ia32_sysenter_eip);

        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_CR0, CR0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_CR3, (size_t)DirectoryTableBase);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_CR4, CR4);
    }

    // Guest Fields
    {
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_SYSENTER_CS, ia32_sysenter_cs);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_SYSENTER_ESP, ia32_sysenter_esp);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_SYSENTER_EIP, ia32_sysenter_eip);

        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_RSP, Context.Rsp);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_RIP, Context.Rip);

        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_RFLAGS, Context.EFlags);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_CR0, CR0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_CR3, CR3);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_CR4, CR4);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_DR7, __asm_dr7());

        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_VMCS_LINK_PTR_FULL, 0xFFFFFFFFFFFFFFFF);

        if (VmEntryControls & (1ULL << 0x02)) // 2 Load debug controls
            Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_DEBUGCTL_FULL, 0);

        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_EFER_FULL, ia32_efer);

        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_CS_SEL, CS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_DS_SEL, DS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_ES_SEL, ES & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_FS_SEL, FS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_GS_SEL, GS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_SS_SEL, SS & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_LDTR_SEL, LDTR & 0xFFF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_TR_SEL, TR & 0xFFF8);

#if defined(_M_AMD64) || defined(__x86_64__)
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_CS_BASE, __lsb(CS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_DS_BASE, __lsb(DS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_ES_BASE, __lsb(ES));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_FS_BASE, ia32_fs_base);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_GS_BASE, ia32_gs_base);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_SS_BASE, __lsb(SS));
#endif

#if defined(_M_IX86) || defined(__i386__)
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_CS_BASE, __lsb(CS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_DS_BASE, __lsb(DS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_ES_BASE, __lsb(ES));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_FS_BASE, __lsb(FS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_GS_BASE, __lsb(GS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_SS_BASE, __lsb(SS));
#endif

        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_LDTR_BASE, __lsb(LDTR));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_TR_BASE, __lsb(TR));
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_GDTR_BASE, (size_t)GDTR.BaseAddress);
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_GDTR_LIMIT, GDTR.Limit);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_IDTR_BASE, (size_t)IDTR.BaseAddress);
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_IDTR_LIMIT, IDTR.Limit);

        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_CS_LIMIT, __lsl(CS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_DS_LIMIT, __lsl(DS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_ES_LIMIT, __lsl(ES));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_FS_LIMIT, __lsl(FS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_GS_LIMIT, __lsl(GS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_SS_LIMIT, __lsl(SS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_LDTR_LIMIT, __lsl(LDTR));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_TR_LIMIT, __lsl(TR));

        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_CS_ACCESS_RIGHTS, vmx_format_access_rights(__lar(CS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_DS_ACCESS_RIGHTS, vmx_format_access_rights(__lar(DS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_ES_ACCESS_RIGHTS, vmx_format_access_rights(__lar(ES)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_FS_ACCESS_RIGHTS, vmx_format_access_rights(__lar(FS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_GS_ACCESS_RIGHTS, vmx_format_access_rights(__lar(GS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_SS_ACCESS_RIGHTS, vmx_format_access_rights(__lar(SS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_LDTR_ACCESS_RIGHTS, vmx_format_access_rights(__lar(LDTR)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_TR_ACCESS_RIGHTS, vmx_format_access_rights(__lar(TR)));

        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_PDPTE0_FULL, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_PDPTE1_FULL, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_PDPTE2_FULL, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_PDPTE3_FULL, 0);
    }

    if (Status & EFLAGS_ZF_MASK)
        __asm__ __volatile__(".byte 0xEB, 0xFE" ::: "memory");

    // 16-Bit Control Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00000000, &eee); // Virtual-processor identifier (VPID)
        __asm_vmx_vmread(0x00000001, &eee); //
        __asm_vmx_vmread(0x00000002, &eee); // Posted-interrupt notification vector
        __asm_vmx_vmread(0x00000003, &eee); //
        __asm_vmx_vmread(0x00000004, &eee); // EPTP index
        __asm_vmx_vmread(0x00000005, &eee); //
        __asm_vmx_vmread(0x00000006, &eee); // HLAT prefix size
        __asm_vmx_vmread(0x00000007, &eee); //
        __asm_vmx_vmread(0x00000008, &eee); // Last PID-pointer index
        __asm_vmx_vmread(0x00000009, &eee); //
    }

    // 16-Bit Guest-State Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00000800, &eee); // Guest ES selector
        __asm_vmx_vmread(0x00000801, &eee); //
        __asm_vmx_vmread(0x00000802, &eee); // Guest CS selector
        __asm_vmx_vmread(0x00000803, &eee); //
        __asm_vmx_vmread(0x00000804, &eee); // Guest SS selector
        __asm_vmx_vmread(0x00000805, &eee); //
        __asm_vmx_vmread(0x00000806, &eee); // Guest DS selector
        __asm_vmx_vmread(0x00000807, &eee); //
        __asm_vmx_vmread(0x00000808, &eee); // Guest FS selector
        __asm_vmx_vmread(0x00000809, &eee); //
        __asm_vmx_vmread(0x0000080A, &eee); // Guest GS selector
        __asm_vmx_vmread(0x0000080B, &eee); //
        __asm_vmx_vmread(0x0000080C, &eee); // Guest LDTR selector
        __asm_vmx_vmread(0x0000080D, &eee); //
        __asm_vmx_vmread(0x0000080E, &eee); // Guest TR selector
        __asm_vmx_vmread(0x0000080F, &eee); //
        __asm_vmx_vmread(0x00000810, &eee); // Guest interrupt status
        __asm_vmx_vmread(0x00000811, &eee); //
        __asm_vmx_vmread(0x00000812, &eee); // PML index
        __asm_vmx_vmread(0x00000813, &eee); //
        __asm_vmx_vmread(0x00000814, &eee); // Guest UINV
        __asm_vmx_vmread(0x00000815, &eee); //
    }

    // 16-Bit Host-State Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00000C00, &eee); // Host ES selector
        __asm_vmx_vmread(0x00000C01, &eee); //
        __asm_vmx_vmread(0x00000C02, &eee); // Host CS selector
        __asm_vmx_vmread(0x00000C03, &eee); //
        __asm_vmx_vmread(0x00000C04, &eee); // Host SS selector
        __asm_vmx_vmread(0x00000C05, &eee); //
        __asm_vmx_vmread(0x00000C06, &eee); // Host DS selector
        __asm_vmx_vmread(0x00000C07, &eee); //
        __asm_vmx_vmread(0x00000C08, &eee); // Host FS selector
        __asm_vmx_vmread(0x00000C09, &eee); //
        __asm_vmx_vmread(0x00000C0A, &eee); // Host GS selector
        __asm_vmx_vmread(0x00000C0B, &eee); //
        __asm_vmx_vmread(0x00000C0C, &eee); // Host TR selector
        __asm_vmx_vmread(0x00000C0D, &eee); //
    }

    // 64-Bit Control Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00002000, &eee); // Address of I/O bitmap A (full)
        __asm_vmx_vmread(0x00002001, &eee); // Address of I/O bitmap A (high)
        __asm_vmx_vmread(0x00002002, &eee); // Address of I/O bitmap B (full)
        __asm_vmx_vmread(0x00002003, &eee); // Address of I/O bitmap B (high)
        __asm_vmx_vmread(0x00002004, &eee); // Address of MSR bitmaps (full)
        __asm_vmx_vmread(0x00002005, &eee); // Address of MSR bitmaps (high)
        __asm_vmx_vmread(0x00002006, &eee); // VM-exit MSR-store address (full)
        __asm_vmx_vmread(0x00002007, &eee); // VM-exit MSR-store address (high)
        __asm_vmx_vmread(0x00002008, &eee); // VM-exit MSR-load address (full)
        __asm_vmx_vmread(0x00002009, &eee); // VM-exit MSR-load address (high)
        __asm_vmx_vmread(0x0000200A, &eee); // VM-entry MSR-load address (full)
        __asm_vmx_vmread(0x0000200B, &eee); // VM-entry MSR-load address (high)
        __asm_vmx_vmread(0x0000200C, &eee); // Executive-VMCS pointer (full)
        __asm_vmx_vmread(0x0000200D, &eee); // Executive-VMCS pointer (high)
        __asm_vmx_vmread(0x0000200E, &eee); // PML address (full)
        __asm_vmx_vmread(0x0000200F, &eee); // PML address (high)
        __asm_vmx_vmread(0x00002010, &eee); // TSC offset (full)
        __asm_vmx_vmread(0x00002011, &eee); // TSC offset (high)
        __asm_vmx_vmread(0x00002012, &eee); // Virtual-APIC address (full)
        __asm_vmx_vmread(0x00002013, &eee); // Virtual-APIC address (high)
        __asm_vmx_vmread(0x00002014, &eee); // APIC-access address (full)
        __asm_vmx_vmread(0x00002015, &eee); // APIC-access address (high)
        __asm_vmx_vmread(0x00002016, &eee); // Posted-interrupt descriptor address (full)
        __asm_vmx_vmread(0x00002017, &eee); // Posted-interrupt descriptor address (high)
        __asm_vmx_vmread(0x00002018, &eee); // VM-function controls (full)
        __asm_vmx_vmread(0x00002019, &eee); // VM-function controls (high)
        __asm_vmx_vmread(0x0000201A, &eee); // EPT pointer (EPTP; full)
        __asm_vmx_vmread(0x0000201B, &eee); // EPT pointer (EPTP; high)
        __asm_vmx_vmread(0x0000201C, &eee); // EOI-exit bitmap 0 (EOI_EXIT0; full)
        __asm_vmx_vmread(0x0000201D, &eee); // EOI-exit bitmap 0 (EOI_EXIT0; high)
        __asm_vmx_vmread(0x0000201E, &eee); // EOI-exit bitmap 1 (EOI_EXIT1; full)
        __asm_vmx_vmread(0x0000201F, &eee); // EOI-exit bitmap 1 (EOI_EXIT1; high)
        __asm_vmx_vmread(0x00002020, &eee); // EOI-exit bitmap 2 (EOI_EXIT2; full)
        __asm_vmx_vmread(0x00002021, &eee); // EOI-exit bitmap 2 (EOI_EXIT2; high)
        __asm_vmx_vmread(0x00002022, &eee); // EOI-exit bitmap 3 (EOI_EXIT3; full)
        __asm_vmx_vmread(0x00002023, &eee); // EOI-exit bitmap 3 (EOI_EXIT3; high)
        __asm_vmx_vmread(0x00002024, &eee); // EPTP-list address (full)
        __asm_vmx_vmread(0x00002025, &eee); // EPTP-list address (high)
        __asm_vmx_vmread(0x00002026, &eee); // VMREAD-bitmap address (full)
        __asm_vmx_vmread(0x00002027, &eee); // VMREAD-bitmap address (high)
        __asm_vmx_vmread(0x00002028, &eee); // VMWRITE-bitmap address (full)
        __asm_vmx_vmread(0x00002029, &eee); // VMWRITE-bitmap address (high)
        __asm_vmx_vmread(0x0000202A, &eee); // Virtualization-exception information address (full)
        __asm_vmx_vmread(0x0000202B, &eee); // Virtualization-exception information address (high)
        __asm_vmx_vmread(0x0000202C, &eee); // XSS-exiting bitmap (full)
        __asm_vmx_vmread(0x0000202D, &eee); // XSS-exiting bitmap (high)
        __asm_vmx_vmread(0x0000202E, &eee); // ENCLS-exiting bitmap (full)
        __asm_vmx_vmread(0x0000202F, &eee); // ENCLS-exiting bitmap (high)
        __asm_vmx_vmread(0x00002030, &eee); // Sub-page-permission-table pointer (full)
        __asm_vmx_vmread(0x00002031, &eee); // Sub-page-permission-table pointer (high)
        __asm_vmx_vmread(0x00002032, &eee); // TSC multiplier (full)
        __asm_vmx_vmread(0x00002033, &eee); // TSC multiplier (high)
        __asm_vmx_vmread(0x00002034, &eee); // Tertiary processor-based VM-execution controls (full)
        __asm_vmx_vmread(0x00002035, &eee); // Tertiary processor-based VM-execution controls (high)
        __asm_vmx_vmread(0x00002036, &eee); //
        __asm_vmx_vmread(0x00002037, &eee); //
        __asm_vmx_vmread(0x00002038, &eee); // Low PASID directory address (full)
        __asm_vmx_vmread(0x00002039, &eee); // Low PASID directory address (high)
        __asm_vmx_vmread(0x0000203A, &eee); // High PASID directory address (full)
        __asm_vmx_vmread(0x0000203B, &eee); // High PASID directory address (high)
        __asm_vmx_vmread(0x0000203C, &eee); // SEAM shared EPT pointer (full)
        __asm_vmx_vmread(0x0000203D, &eee); // SEAM shared EPT pointer (high)
        __asm_vmx_vmread(0x0000203E, &eee); // PCONFIG-exiting bitmap (full)
        __asm_vmx_vmread(0x0000203F, &eee); // PCONFIG-exiting bitmap (high)
        __asm_vmx_vmread(0x00002040, &eee); // Hypervisor-managed linear-address translation pointer (HLATP; full)
        __asm_vmx_vmread(0x00002041, &eee); // HLATP (high)
        __asm_vmx_vmread(0x00002042, &eee); // PID-pointer table address (full)
        __asm_vmx_vmread(0x00002043, &eee); // PID-pointer table address (high)
        __asm_vmx_vmread(0x00002044, &eee); // Secondary VM-exit controls (full)
        __asm_vmx_vmread(0x00002045, &eee); // Secondary VM-exit controls (high)
        __asm_vmx_vmread(0x00002046, &eee); //
        __asm_vmx_vmread(0x00002047, &eee); //
        __asm_vmx_vmread(0x00002048, &eee); //
        __asm_vmx_vmread(0x00002049, &eee); //
        __asm_vmx_vmread(0x0000204A, &eee); // IA32_SPEC_CTRL mask (full)
        __asm_vmx_vmread(0x0000204B, &eee); // IA32_SPEC_CTRL mask (high)
        __asm_vmx_vmread(0x0000204C, &eee); // IA32_SPEC_CTRL shadow (full)
        __asm_vmx_vmread(0x0000204D, &eee); // IA32_SPEC_CTRL shadow (high)
        __asm_vmx_vmread(0x0000204E, &eee); //
        __asm_vmx_vmread(0x0000204F, &eee); //
        __asm_vmx_vmread(0x00002050, &eee); //
        __asm_vmx_vmread(0x00002051, &eee); //
        __asm_vmx_vmread(0x00002052, &eee); // Injected-event data (full)
        __asm_vmx_vmread(0x00002053, &eee); // Injected-event data (high)
    }

    // 64-Bit Read-Only Data Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00002400, &eee); // Guest-physical address (full)
        __asm_vmx_vmread(0x00002401, &eee); // Guest-physical address (high)
        __asm_vmx_vmread(0x00002402, &eee); // MSR data (full)
        __asm_vmx_vmread(0x00002403, &eee); // MSR data (high)
        __asm_vmx_vmread(0x00002404, &eee); // Original-event data (full)
        __asm_vmx_vmread(0x00002405, &eee); // Original-event data (high)
    }

    // 64-Bit Guest-State Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00002800, &eee); // VMCS link pointer (full)
        __asm_vmx_vmread(0x00002801, &eee); // VMCS link pointer (high)
        __asm_vmx_vmread(0x00002802, &eee); // Guest IA32_DEBUGCTL (full)
        __asm_vmx_vmread(0x00002803, &eee); // Guest IA32_DEBUGCTL (high)
        __asm_vmx_vmread(0x00002804, &eee); // Guest IA32_PAT (full)
        __asm_vmx_vmread(0x00002805, &eee); // Guest IA32_PAT (high)
        __asm_vmx_vmread(0x00002806, &eee); // Guest IA32_EFER (full)
        __asm_vmx_vmread(0x00002807, &eee); // Guest IA32_EFER (high)
        __asm_vmx_vmread(0x00002808, &eee); // Guest IA32_PERF_GLOBAL_CTRL (full)
        __asm_vmx_vmread(0x00002809, &eee); // Guest IA32_PERF_GLOBAL_CTRL (high)
        __asm_vmx_vmread(0x0000280A, &eee); // Guest PDPTE0 (full)
        __asm_vmx_vmread(0x0000280B, &eee); // Guest PDPTE0 (high)
        __asm_vmx_vmread(0x0000280C, &eee); // Guest PDPTE1 (full)
        __asm_vmx_vmread(0x0000280D, &eee); // Guest PDPTE1 (high)
        __asm_vmx_vmread(0x0000280E, &eee); // Guest PDPTE2 (full)
        __asm_vmx_vmread(0x0000280F, &eee); // Guest PDPTE2 (high)
        __asm_vmx_vmread(0x00002810, &eee); // Guest PDPTE3 (full)
        __asm_vmx_vmread(0x00002811, &eee); // Guest PDPTE3 (high)
        __asm_vmx_vmread(0x00002812, &eee); // Guest IA32_BNDCFGS (full)
        __asm_vmx_vmread(0x00002813, &eee); // Guest IA32_BNDCFGS (high)
        __asm_vmx_vmread(0x00002814, &eee); // Guest IA32_RTIT_CTL (full)
        __asm_vmx_vmread(0x00002815, &eee); // Guest IA32_RTIT_CTL (high)
        __asm_vmx_vmread(0x00002816, &eee); // Guest IA32_LBR_CTL (full)
        __asm_vmx_vmread(0x00002817, &eee); // Guest IA32_LBR_CTL (high)
        __asm_vmx_vmread(0x00002818, &eee); // Guest IA32_PKRS (full)
        __asm_vmx_vmread(0x00002819, &eee); // Guest IA32_PKRS (high)
        __asm_vmx_vmread(0x0000281A, &eee); // Guest IA32_FRED_CONFIG (full)
        __asm_vmx_vmread(0x0000281B, &eee); // Guest IA32_FRED_CONFIG (high)
        __asm_vmx_vmread(0x0000281C, &eee); // Guest IA32_FRED_RSP1 (full)
        __asm_vmx_vmread(0x0000281D, &eee); // Guest IA32_FRED_RSP1 (high)
        __asm_vmx_vmread(0x0000281E, &eee); // Guest IA32_FRED_RSP2 (full)
        __asm_vmx_vmread(0x0000281F, &eee); // Guest IA32_FRED_RSP2 (high)
        __asm_vmx_vmread(0x00002820, &eee); // Guest IA32_FRED_RSP3 (full)
        __asm_vmx_vmread(0x00002821, &eee); // Guest IA32_FRED_RSP3 (high)
        __asm_vmx_vmread(0x00002822, &eee); // Guest IA32_FRED_STKLVLS (full)
        __asm_vmx_vmread(0x00002823, &eee); // Guest IA32_FRED_STKLVLS (high)
        __asm_vmx_vmread(0x00002824, &eee); // Guest IA32_FRED_SSP1 (full)
        __asm_vmx_vmread(0x00002825, &eee); // Guest IA32_FRED_SSP1 (high)
        __asm_vmx_vmread(0x00002826, &eee); // Guest IA32_FRED_SSP2 (full)
        __asm_vmx_vmread(0x00002827, &eee); // Guest IA32_FRED_SSP2 (high)
        __asm_vmx_vmread(0x00002828, &eee); // Guest IA32_FRED_SSP3 (full)
        __asm_vmx_vmread(0x00002829, &eee); // Guest IA32_FRED_SSP3 (high)
    }

    // 64-Bit Host-State Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00002C00, &eee); // Host IA32_PAT (full)
        __asm_vmx_vmread(0x00002C01, &eee); // Host IA32_PAT (high)
        __asm_vmx_vmread(0x00002C02, &eee); // Host IA32_EFER (full)
        __asm_vmx_vmread(0x00002C03, &eee); // Host IA32_EFER (high)
        __asm_vmx_vmread(0x00002C04, &eee); // Host IA32_PERF_GLOBAL_CTRL (full)
        __asm_vmx_vmread(0x00002C05, &eee); // Host IA32_PERF_GLOBAL_CTRL (high)
        __asm_vmx_vmread(0x00002C06, &eee); // Host IA32_PKRS (full)
        __asm_vmx_vmread(0x00002C07, &eee); // Host IA32_PKRS (high)
        __asm_vmx_vmread(0x00002C08, &eee); // Host IA32_FRED_CONFIG (full)
        __asm_vmx_vmread(0x00002C09, &eee); // Host IA32_FRED_CONFIG (high)
        __asm_vmx_vmread(0x00002C0A, &eee); // Host IA32_FRED_RSP1 (full)
        __asm_vmx_vmread(0x00002C0B, &eee); // Host IA32_FRED_RSP1 (high)
        __asm_vmx_vmread(0x00002C0C, &eee); // Host IA32_FRED_RSP2 (full)
        __asm_vmx_vmread(0x00002C0D, &eee); // Host IA32_FRED_RSP2 (high)
        __asm_vmx_vmread(0x00002C0E, &eee); // Host IA32_FRED_RSP3 (full)
        __asm_vmx_vmread(0x00002C0F, &eee); // Host IA32_FRED_RSP3 (high)
        __asm_vmx_vmread(0x00002C10, &eee); // Host IA32_FRED_STKLVLS (full)
        __asm_vmx_vmread(0x00002C11, &eee); // Host IA32_FRED_STKLVLS (high)
        __asm_vmx_vmread(0x00002C12, &eee); // Host IA32_FRED_SSP1 (full)
        __asm_vmx_vmread(0x00002C13, &eee); // Host IA32_FRED_SSP1 (high)
        __asm_vmx_vmread(0x00002C14, &eee); // Host IA32_FRED_SSP2 (full)
        __asm_vmx_vmread(0x00002C15, &eee); // Host IA32_FRED_SSP2 (high)
        __asm_vmx_vmread(0x00002C16, &eee); // Host IA32_FRED_SSP3 (full)
        __asm_vmx_vmread(0x00002C17, &eee); // Host IA32_FRED_SSP3 (high)
    }

    // 32-Bit Control Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00004000, &eee); // Pin-based VM-execution controls
        __asm_vmx_vmread(0x00004001, &eee); //
        __asm_vmx_vmread(0x00004002, &eee); // Primary processor-based VM-execution controls
        __asm_vmx_vmread(0x00004003, &eee); //
        __asm_vmx_vmread(0x00004004, &eee); // Exception bitmap
        __asm_vmx_vmread(0x00004005, &eee); //
        __asm_vmx_vmread(0x00004006, &eee); // Page-fault error-code mask
        __asm_vmx_vmread(0x00004007, &eee); //
        __asm_vmx_vmread(0x00004008, &eee); // Page-fault error-code match
        __asm_vmx_vmread(0x00004009, &eee); //
        __asm_vmx_vmread(0x0000400A, &eee); // CR3-target count
        __asm_vmx_vmread(0x0000400B, &eee); //
        __asm_vmx_vmread(0x0000400C, &eee); // Primary VM-exit controls
        __asm_vmx_vmread(0x0000400D, &eee); //
        __asm_vmx_vmread(0x0000400E, &eee); // VM-exit MSR-store count
        __asm_vmx_vmread(0x0000400F, &eee); //
        __asm_vmx_vmread(0x00004010, &eee); // VM-exit MSR-load count
        __asm_vmx_vmread(0x00004011, &eee); //
        __asm_vmx_vmread(0x00004012, &eee); // VM-entry controls
        __asm_vmx_vmread(0x00004013, &eee); //
        __asm_vmx_vmread(0x00004014, &eee); // VM-entry MSR-load count
        __asm_vmx_vmread(0x00004015, &eee); //
        __asm_vmx_vmread(0x00004016, &eee); // Injected-event identification
        __asm_vmx_vmread(0x00004017, &eee); //
        __asm_vmx_vmread(0x00004018, &eee); // Injected-event error code
        __asm_vmx_vmread(0x00004019, &eee); //
        __asm_vmx_vmread(0x0000401A, &eee); // VM-entry instruction length
        __asm_vmx_vmread(0x0000401B, &eee); //
        __asm_vmx_vmread(0x0000401C, &eee); // TPR threshold
        __asm_vmx_vmread(0x0000401D, &eee); //
        __asm_vmx_vmread(0x0000401E, &eee); // Secondary processor-based VM-execution controls
        __asm_vmx_vmread(0x0000401F, &eee); //
        __asm_vmx_vmread(0x00004020, &eee); // PLE_Gap
        __asm_vmx_vmread(0x00004021, &eee); //
        __asm_vmx_vmread(0x00004022, &eee); // PLE_Window
        __asm_vmx_vmread(0x00004023, &eee); //
        __asm_vmx_vmread(0x00004024, &eee); // Instruction-timeout control
        __asm_vmx_vmread(0x00004025, &eee); //
        __asm_vmx_vmread(0x00004026, &eee); // SEAM-guest KeyID
        __asm_vmx_vmread(0x00004027, &eee); //
    }

    // 32-Bit Read-Only Data Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00004400, &eee); // VM-instruction error
        __asm_vmx_vmread(0x00004401, &eee); //
        __asm_vmx_vmread(0x00004402, &eee); // Exit reason
        __asm_vmx_vmread(0x00004403, &eee); //
        __asm_vmx_vmread(0x00004404, &eee); // Exiting-event identification
        __asm_vmx_vmread(0x00004405, &eee); //
        __asm_vmx_vmread(0x00004406, &eee); // Exiting-event error code
        __asm_vmx_vmread(0x00004407, &eee); //
        __asm_vmx_vmread(0x00004408, &eee); // Original-event identification
        __asm_vmx_vmread(0x00004409, &eee); //
        __asm_vmx_vmread(0x0000440A, &eee); // Original-event error code
        __asm_vmx_vmread(0x0000440B, &eee); //
        __asm_vmx_vmread(0x0000440C, &eee); // VM-exit instruction length
        __asm_vmx_vmread(0x0000440D, &eee); //
        __asm_vmx_vmread(0x0000440E, &eee); // VM-exit instruction information
        __asm_vmx_vmread(0x0000440F, &eee); //
    }

    // 32-Bit Guest-State Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00004800, &eee); // Guest ES limit
        __asm_vmx_vmread(0x00004801, &eee); //
        __asm_vmx_vmread(0x00004802, &eee); // Guest CS limit
        __asm_vmx_vmread(0x00004803, &eee); //
        __asm_vmx_vmread(0x00004804, &eee); // Guest SS limit
        __asm_vmx_vmread(0x00004805, &eee); //
        __asm_vmx_vmread(0x00004806, &eee); // Guest DS limit
        __asm_vmx_vmread(0x00004807, &eee); //
        __asm_vmx_vmread(0x00004808, &eee); // Guest FS limit
        __asm_vmx_vmread(0x00004809, &eee); //
        __asm_vmx_vmread(0x0000480A, &eee); // Guest GS limit
        __asm_vmx_vmread(0x0000480B, &eee); //
        __asm_vmx_vmread(0x0000480C, &eee); // Guest LDTR limit
        __asm_vmx_vmread(0x0000480D, &eee); //
        __asm_vmx_vmread(0x0000480E, &eee); // Guest TR limit
        __asm_vmx_vmread(0x0000480F, &eee); //
        __asm_vmx_vmread(0x00004810, &eee); // Guest GDTR limit
        __asm_vmx_vmread(0x00004811, &eee); //
        __asm_vmx_vmread(0x00004812, &eee); // Guest IDTR limit
        __asm_vmx_vmread(0x00004813, &eee); //
        __asm_vmx_vmread(0x00004814, &eee); // Guest ES access rights
        __asm_vmx_vmread(0x00004815, &eee); //
        __asm_vmx_vmread(0x00004816, &eee); // Guest CS access rights
        __asm_vmx_vmread(0x00004817, &eee); //
        __asm_vmx_vmread(0x00004818, &eee); // Guest SS access rights
        __asm_vmx_vmread(0x00004819, &eee); //
        __asm_vmx_vmread(0x0000481A, &eee); // Guest DS access rights
        __asm_vmx_vmread(0x0000481B, &eee); //
        __asm_vmx_vmread(0x0000481C, &eee); // Guest FS access rights
        __asm_vmx_vmread(0x0000481D, &eee); //
        __asm_vmx_vmread(0x0000481E, &eee); // Guest GS access rights
        __asm_vmx_vmread(0x0000481F, &eee); //
        __asm_vmx_vmread(0x00004820, &eee); // Guest LDTR access rights
        __asm_vmx_vmread(0x00004821, &eee); //
        __asm_vmx_vmread(0x00004822, &eee); // Guest TR access rights
        __asm_vmx_vmread(0x00004823, &eee); //
        __asm_vmx_vmread(0x00004824, &eee); // Guest interruptibility state
        __asm_vmx_vmread(0x00004825, &eee); //
        __asm_vmx_vmread(0x00004826, &eee); // Guest activity state
        __asm_vmx_vmread(0x00004827, &eee); //
        __asm_vmx_vmread(0x00004828, &eee); // Guest SMBASE
        __asm_vmx_vmread(0x00004829, &eee); //
        __asm_vmx_vmread(0x0000482A, &eee); // Guest IA32_SYSENTER_CS
        __asm_vmx_vmread(0x0000482B, &eee); //
        __asm_vmx_vmread(0x0000482C, &eee); //
        __asm_vmx_vmread(0x0000482D, &eee); //
        __asm_vmx_vmread(0x0000482E, &eee); // VMX-preemption timer value
        __asm_vmx_vmread(0x0000482F, &eee); //
    }

    // 32-Bit Host-State Field
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00004C00, &eee); // Host IA32_SYSENTER_CS
    }

    // Natural-Width Control Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00006000, &eee); // CR0 guest/host mask
        __asm_vmx_vmread(0x00006001, &eee); //
        __asm_vmx_vmread(0x00006002, &eee); // CR4 guest/host mask
        __asm_vmx_vmread(0x00006003, &eee); //
        __asm_vmx_vmread(0x00006004, &eee); // CR0 read shadow
        __asm_vmx_vmread(0x00006005, &eee); //
        __asm_vmx_vmread(0x00006006, &eee); // CR4 read shadow
        __asm_vmx_vmread(0x00006007, &eee); //
        __asm_vmx_vmread(0x00006008, &eee); // CR3-target value 0
        __asm_vmx_vmread(0x00006009, &eee); //
        __asm_vmx_vmread(0x0000600A, &eee); // CR3-target value 1
        __asm_vmx_vmread(0x0000600B, &eee); //
        __asm_vmx_vmread(0x0000600C, &eee); // CR3-target value 2
        __asm_vmx_vmread(0x0000600D, &eee); //
        __asm_vmx_vmread(0x0000600E, &eee); // CR3-target value 3
        __asm_vmx_vmread(0x0000600F, &eee); //
    }

    // Natural-Width Read-Only Data Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00006400, &eee); // Exit qualification
        __asm_vmx_vmread(0x00006401, &eee); //
        __asm_vmx_vmread(0x00006402, &eee); // I/O RCX
        __asm_vmx_vmread(0x00006403, &eee); //
        __asm_vmx_vmread(0x00006404, &eee); // I/O RSI
        __asm_vmx_vmread(0x00006405, &eee); //
        __asm_vmx_vmread(0x00006406, &eee); // I/O RDI
        __asm_vmx_vmread(0x00006407, &eee); //
        __asm_vmx_vmread(0x00006408, &eee); // I/O RIP
        __asm_vmx_vmread(0x00006409, &eee); //
        __asm_vmx_vmread(0x0000640A, &eee); // Guest-linear address
        __asm_vmx_vmread(0x0000640B, &eee); //
    }

    // Natural-Width Guest-State Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00006800, &eee); // Guest CR0
        __asm_vmx_vmread(0x00006801, &eee); //
        __asm_vmx_vmread(0x00006802, &eee); // Guest CR3
        __asm_vmx_vmread(0x00006803, &eee); //
        __asm_vmx_vmread(0x00006804, &eee); // Guest CR4
        __asm_vmx_vmread(0x00006805, &eee); //
        __asm_vmx_vmread(0x00006806, &eee); // Guest ES base
        __asm_vmx_vmread(0x00006807, &eee); //
        __asm_vmx_vmread(0x00006808, &eee); // Guest CS base
        __asm_vmx_vmread(0x00006809, &eee); //
        __asm_vmx_vmread(0x0000680A, &eee); // Guest SS base
        __asm_vmx_vmread(0x0000680B, &eee); //
        __asm_vmx_vmread(0x0000680C, &eee); // Guest DS base
        __asm_vmx_vmread(0x0000680D, &eee); //
        __asm_vmx_vmread(0x0000680E, &eee); // Guest FS base
        __asm_vmx_vmread(0x0000680F, &eee); //
        __asm_vmx_vmread(0x00006810, &eee); // Guest GS base
        __asm_vmx_vmread(0x00006811, &eee); //
        __asm_vmx_vmread(0x00006812, &eee); // Guest LDTR base
        __asm_vmx_vmread(0x00006813, &eee); //
        __asm_vmx_vmread(0x00006814, &eee); // Guest TR base
        __asm_vmx_vmread(0x00006815, &eee); //
        __asm_vmx_vmread(0x00006816, &eee); // Guest GDTR base
        __asm_vmx_vmread(0x00006817, &eee); //
        __asm_vmx_vmread(0x00006818, &eee); // Guest IDTR base
        __asm_vmx_vmread(0x00006819, &eee); //
        __asm_vmx_vmread(0x0000681A, &eee); // Guest DR7
        __asm_vmx_vmread(0x0000681B, &eee); //
        __asm_vmx_vmread(0x0000681C, &eee); // Guest RSP
        __asm_vmx_vmread(0x0000681D, &eee); //
        __asm_vmx_vmread(0x0000681E, &eee); // Guest RIP
        __asm_vmx_vmread(0x0000681F, &eee); //
        __asm_vmx_vmread(0x00006820, &eee); // Guest RFLAGS
        __asm_vmx_vmread(0x00006821, &eee); //
        __asm_vmx_vmread(0x00006822, &eee); // Guest pending debug exceptions
        __asm_vmx_vmread(0x00006823, &eee); //
        __asm_vmx_vmread(0x00006824, &eee); // Guest IA32_SYSENTER_ESP
        __asm_vmx_vmread(0x00006825, &eee); //
        __asm_vmx_vmread(0x00006826, &eee); // Guest IA32_SYSENTER_EIP
        __asm_vmx_vmread(0x00006827, &eee); //
        __asm_vmx_vmread(0x00006828, &eee); // Guest IA32_S_CET
        __asm_vmx_vmread(0x00006829, &eee); //
        __asm_vmx_vmread(0x0000682A, &eee); // Guest SSP
        __asm_vmx_vmread(0x0000682B, &eee); //
        __asm_vmx_vmread(0x0000682C, &eee); // Guest IA32_INTERRUPT_SSP_TABLE_ADDR
        __asm_vmx_vmread(0x0000682D, &eee); //
    }

    // Natural-Width Host-State Fields
    {
        size_t eee = {};
        __asm_vmx_vmread(0x00006C00, &eee); // Host CR0
        __asm_vmx_vmread(0x00006C01, &eee); //
        __asm_vmx_vmread(0x00006C02, &eee); // Host CR3
        __asm_vmx_vmread(0x00006C03, &eee); //
        __asm_vmx_vmread(0x00006C04, &eee); // Host CR4
        __asm_vmx_vmread(0x00006C05, &eee); //
        __asm_vmx_vmread(0x00006C06, &eee); // Host FS base
        __asm_vmx_vmread(0x00006C07, &eee); //
        __asm_vmx_vmread(0x00006C08, &eee); // Host GS base
        __asm_vmx_vmread(0x00006C09, &eee); //
        __asm_vmx_vmread(0x00006C0A, &eee); // Host TR base
        __asm_vmx_vmread(0x00006C0B, &eee); //
        __asm_vmx_vmread(0x00006C0C, &eee); // Host GDTR base
        __asm_vmx_vmread(0x00006C0D, &eee); //
        __asm_vmx_vmread(0x00006C0E, &eee); // Host IDTR base
        __asm_vmx_vmread(0x00006C0F, &eee); //
        __asm_vmx_vmread(0x00006C10, &eee); // Host IA32_SYSENTER_ESP
        __asm_vmx_vmread(0x00006C11, &eee); //
        __asm_vmx_vmread(0x00006C12, &eee); // Host IA32_SYSENTER_EIP
        __asm_vmx_vmread(0x00006C13, &eee); //
        __asm_vmx_vmread(0x00006C14, &eee); // Host RSP
        __asm_vmx_vmread(0x00006C15, &eee); //
        __asm_vmx_vmread(0x00006C16, &eee); // Host RIP
        __asm_vmx_vmread(0x00006C17, &eee); //
        __asm_vmx_vmread(0x00006C18, &eee); // Host IA32_S_CET
        __asm_vmx_vmread(0x00006C19, &eee); //
        __asm_vmx_vmread(0x00006C1A, &eee); // Host SSP
        __asm_vmx_vmread(0x00006C1B, &eee); //
        __asm_vmx_vmread(0x00006C1C, &eee); // Host IA32_INTERRUPT_SSP_TABLE_ADDR
        __asm_vmx_vmread(0x00006C1D, &eee); //
    }

    Context.Rip = 0x12345678;

    KdBreakPoint();

    __asm__ __volatile__("\n mov %0, %%r15"
                         "\n mov %c1(%%r15), %%rax"
                         "\n mov %c2(%%r15), %%rbx"
                         "\n mov %c3(%%r15), %%rcx"
                         "\n mov %c4(%%r15), %%rdx"
                         "\n mov %c5(%%r15), %%rsi"
                         "\n mov %c6(%%r15), %%rdi"
                         "\n mov %c7(%%r15), %%rbp"
                         "\n mov %c8(%%r15), %%r8"
                         "\n mov %c9(%%r15), %%r9"
                         "\n mov %c10(%%r15), %%r10"
                         "\n mov %c11(%%r15), %%r11"
                         "\n mov %c12(%%r15), %%r12"
                         "\n mov %c13(%%r15), %%r13"
                         "\n mov %c14(%%r15), %%r14"
                         "\n mov %c15(%%r15), %%r15"
                         "\n vmlaunch"
                         :
                         : "r"(&Context), "i"(offsetof(CONTEXT, Rax)), "i"(offsetof(CONTEXT, Rbx)), "i"(offsetof(CONTEXT, Rcx)), "i"(offsetof(CONTEXT, Rdx)), "i"(offsetof(CONTEXT, Rsi)), "i"(offsetof(CONTEXT, Rdi)), "i"(offsetof(CONTEXT, Rbp)), "i"(offsetof(CONTEXT, R8)), "i"(offsetof(CONTEXT, R9)), "i"(offsetof(CONTEXT, R10)), "i"(offsetof(CONTEXT, R11)), "i"(offsetof(CONTEXT, R12)), "i"(offsetof(CONTEXT, R13)), "i"(offsetof(CONTEXT, R14)), "i"(offsetof(CONTEXT, R15))
                         : "memory");

    __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &Status);

    __asm__ __volatile__(".byte 0xEB, 0xFE" ::: "memory");

    return -1;
}

template <>
int
vmxoff<Hash("GenuineIntel")>(PVOID)
{
    __asm_vmx_vmxoff();
    return 0;
}
