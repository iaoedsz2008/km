
/**
 * 用户为本，科技向善
 **/

#include "GenuineIntel.h"

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

static KSPIN_LOCK kSpinLock;

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
vmx_format_access_rights(uint64_t access_rights)
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

static __attribute__((naked)) void
vmx_vmexit(void)
{
    __asm__ __volatile__("int3\n\t"
                         "ret" ::
                             :);
}

static void
initializeEPT()
{
}

template <>
int
initialize<Hash("GenuineIntel")>(PVOID vcpu)
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
     * If this bit is clear, VMXON causes a general-protection exception.
     * If the lock bit is set, WRMSR to this MSR causes a general-protection exception;
     **/
    if ((ia32_feature_control & (1ULL << 0x00)) == 0) // Lock bit (R/WO): (1 = locked).
        __asm_wrmsr(IA32_FEATURE_CONTROL, ia32_feature_control | 1);
    if (ia32_feature_control & (1ULL << 0x01)) // Enable VMX inside SMX operation (R/WL) This bit enables a system executive to use VMX in conjunction with SMX to support Intel® Trusted Execution Technology.
        ;
    if ((ia32_feature_control & (1ULL << 0x02)) == 0) // Enable VMX outside SMX operation (R/WL) This bit enables VMX for a system executive that does not require SMX.
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

    if (ia32_vmx_ept_vpid_cap & (1ULL << 0)) // If bit 0 is read as 1, the processor supports execute-only translations by EPT.
        ;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 6)) == 0) // Bit 6 indicates support for a page-walk length of 4.
        return -1;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 7)) // Bit 7 indicates support for a page-walk length of 5.
        ;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 8)) // If bit 8 is read as 1, the logical processor allows software to configure the EPT paging-structure memory type to be uncacheable (UC)
        ;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 14)) == 0) // If bit 14 is read as 1, the logical processor allows software to configure the EPT paging-structure memory type to be write-back (WB)
        return -1;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 16)) // If bit 16 is read as 1, the logical processor allows software to configure a EPT PDE to map a 2-Mbyte page (by setting bit 7 in the EPT PDE).
        ;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 17)) // If bit 17 is read as 1, the logical processor allows software to configure a EPT PDPTE to map a 1-Gbyte page (by setting bit 7 in the EPT PDPTE).
        ;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 20)) == 0) // If bit 20 is read as 1, the INVEPT instruction is supported.
        return -1;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 21)) // If bit 21 is read as 1, accessed and dirty flags for EPT are supported
        ;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 22)) // If bit 22 is read as 1, the processor reports advanced VM-exit information for EPT violations. This reporting is done only if this bit is read as 1.
        ;
    if (ia32_vmx_ept_vpid_cap & (1ULL << 23)) // If bit 23 is read as 1, supervisor shadow-stack control is supported
        ;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 25)) == 0) // If bit 25 is read as 1, the single-context INVEPT type is supported.
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 26)) == 0) // If bit 26 is read as 1, the all-context INVEPT type is supported.
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 32)) == 0) // If bit 32 is read as 1, the INVVPID instruction is supported.
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 40)) == 0) // If bit 40 is read as 1, the individual-address INVVPID type is supported.
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 41)) == 0) // If bit 41 is read as 1, the single-context INVVPID type is supported.
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 42)) == 0) // If bit 42 is read as 1, the all-context INVVPID type is supported.
        return -1;
    if ((ia32_vmx_ept_vpid_cap & (1ULL << 43)) == 0) // If bit 43 is read as 1, the single-context-retaining-globals INVVPID type is supported.
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

    CONTEXT Context;
    RtlCaptureContext(&Context);

    KdBreakPoint();

    __asm_cr0((CR0 & ia32_vmx_cr0_fixed1) | ia32_vmx_cr0_fixed0);
    __asm_cr4(((CR4 | 0x00002000 /*VMXE*/) & ia32_vmx_cr4_fixed1) | ia32_vmx_cr4_fixed0);

    CR0 = __asm_cr0();
    CR4 = __asm_cr4();

    KeAcquireSpinLockAtDpcLevel(&kSpinLock);
    initializeEPT();
    KeReleaseSpinLockFromDpcLevel(&kSpinLock);

    PVOID vmcsGuest = allocateContiguous<0x1000>();
    PVOID vmcsHost = allocateContiguous<0x1000>();

    if ((SIZE_T)vmcsGuest & 0xFFF)
        return -1;

    if ((SIZE_T)vmcsHost & 0xFFF)
        return -1;

    memset(vmcsGuest, 0, 0x1000);
    memset(vmcsHost, 0, 0x1000);

    /**
     * Bits 30:0: VMCS revision identifier
     * Bit 31: shadow-VMCS indicator (see Section 27.10)
     **/
    *(uint32_t*)vmcsGuest = (uint32_t)ia32_vmx_basic & 0x7FFFFFFF;
    *(uint32_t*)vmcsHost = (uint32_t)ia32_vmx_basic & 0x7FFFFFFF;

    PHYSICAL_ADDRESS vmcsGuestPA = MmGetPhysicalAddress(vmcsGuest);
    PHYSICAL_ADDRESS vmcsHostPA = MmGetPhysicalAddress(vmcsHost);

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

    Status = __asm_vmx_vmxon((uint64_t*)&vmcsHostPA.QuadPart);
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

        // If bit 55 in the IA32_VMX_BASIC MSR is read as 1, all information about the allowed settings of the pin-based VM-execution controls is contained in the IA32_VMX_TRUE_PINBASED_CTLS MSR. Assuming that software knows that the default1 class of pin-based VM-execution controls contains bits 1, 2, and 4, there is no need for software to consult the IA32_VMX_PINBASED_CTLS MSR.
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
        // PrimaryProcessorBasedVmExecutionControls |= (1ULL << 0x1C); // Use MSR bitmaps
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
        // SecondaryProcessorBasedVmExecutionControls |= (1ULL << 0x01); // Enable EPT
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
        if (PrimaryProcessorBasedVmExecutionControls & (1ULL << 0x19)) // Use I/O bitmaps
            ;

        if (PrimaryProcessorBasedVmExecutionControls & (1ULL << 0x1C)) // Use MSR bitmaps
            ;

        if (SecondaryProcessorBasedVmExecutionControls & (1ULL << 0x01)) // Enable EPT
            ;

        if (SecondaryProcessorBasedVmExecutionControls & (1ULL << 0x05)) // Enable VPID
            Status |= __asm_vmx_vmwrite(VMX_VMCS16_VPID, __asm_rdpid() + 1);

        Status |= __asm_vmx_vmwrite(VMX_VMCS32_CTRL_EXCEPTION_BITMAP, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_CTRL_CR0_MASK, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_CTRL_CR4_MASK, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_CTRL_CR0_READ_SHADOW, CR0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_CTRL_CR4_READ_SHADOW, CR4);
    }

    KdBreakPoint();

    // Host Fields
    {
        size_t stack = (size_t)allocate<0x8000>();

        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_RSP, stack + 0x8000 - 0x20);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_RIP, (uint64_t)&vmx_vmexit);

        // RPL and TI have to be 0
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_CS_SEL, CS & 0xF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_DS_SEL, DS & 0xF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_ES_SEL, ES & 0xF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_FS_SEL, FS & 0xF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_GS_SEL, GS & 0xF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_SS_SEL, SS & 0xF8);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_HOST_TR_SEL, TR & 0xF8);

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
        Status |= __asm_vmx_vmwrite(VMX_VMCS_HOST_CR3, CR3);
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

        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_VMCS_LINK_PTR_HIGH, 0xFFFFFFFFFFFFFFFF);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_VMCS_LINK_PTR_FULL, 0xFFFFFFFFFFFFFFFF);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_DEBUGCTL_HIGH, 0xFFFFFFFFFFFFFFFF);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_DEBUGCTL_FULL, ia32_debugctl);

        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_CS_SEL, CS);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_DS_SEL, DS);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_ES_SEL, ES);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_FS_SEL, FS);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_GS_SEL, GS);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_SS_SEL, SS);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_LDTR_SEL, LDTR);
        Status |= __asm_vmx_vmwrite(VMX_VMCS16_GUEST_TR_SEL, TR);

#if defined(_M_AMD64) || defined(__x86_64__)
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_CS_BASE, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_DS_BASE, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_ES_BASE, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_FS_BASE, ia32_fs_base);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_GS_BASE, ia32_gs_base);
        Status |= __asm_vmx_vmwrite(VMX_VMCS_GUEST_SS_BASE, 0);
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

        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_CS_LIMIT, __asm_lsl(CS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_DS_LIMIT, __asm_lsl(DS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_ES_LIMIT, __asm_lsl(ES));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_FS_LIMIT, __asm_lsl(FS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_GS_LIMIT, __asm_lsl(GS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_SS_LIMIT, __asm_lsl(SS));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_LDTR_LIMIT, __asm_lsl(LDTR));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_TR_LIMIT, __asm_lsl(TR));

        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_CS_ACCESS_RIGHTS, vmx_format_access_rights(__asm_lar(CS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_DS_ACCESS_RIGHTS, vmx_format_access_rights(__asm_lar(DS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_ES_ACCESS_RIGHTS, vmx_format_access_rights(__asm_lar(ES)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_FS_ACCESS_RIGHTS, vmx_format_access_rights(__asm_lar(FS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_GS_ACCESS_RIGHTS, vmx_format_access_rights(__asm_lar(GS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_SS_ACCESS_RIGHTS, vmx_format_access_rights(__asm_lar(SS)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_LDTR_ACCESS_RIGHTS, vmx_format_access_rights(__asm_lar(LDTR)));
        Status |= __asm_vmx_vmwrite(VMX_VMCS32_GUEST_TR_ACCESS_RIGHTS, vmx_format_access_rights(__asm_lar(TR)));

        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_PDPTE0_FULL, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_PDPTE1_FULL, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_PDPTE2_FULL, 0);
        Status |= __asm_vmx_vmwrite(VMX_VMCS64_GUEST_PDPTE3_FULL, 0);
    }

    // Natural-Width Control Fields
    {
    }
    // Natural-Width Read-Only Data Field
    {
    }
    // Natural-Width Guest-State Fields
    {
    }
    // Natural-Width Host-State Fields
    {
    }

    // 64-Bit Control Fields
    {
    }
    // 64-Bit Read-Only Data Field
    {
    }
    // 64-Bit Guest-State Fields
    {
    }
    // 64-Bit Host-State Fields
    {
    }

    // 32-Bit Control Fields
    {
    }
    // 32-Bit Read-Only Data Field
    {
    }
    // 32-Bit Guest-State Fields
    {
    }
    // 32-Bit Host-State Fields
    {
    }

    // 16-Bit Control Fields
    {
    }
    // 16-Bit Guest-State Fields
    {
    }
    // 16-Bit Host-State Fields
    {
    }

    KdBreakPoint();

    Status = __asm_vmx_vmlaunch();

    if (Status & EFLAGS_ZF_MASK) {
        size_t e;
        __asm_vmx_vmread(VMX_VMCS32_RO_VM_INSTR_ERROR, &e);
        e = 0;

        return -1;
    }

    return 0;
}

template <>
int
cleanup<Hash("GenuineIntel")>(PVOID vcpu)
{
    __asm_vmx_vmxoff();
    return 0;
}
