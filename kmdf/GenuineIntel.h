
/**
 * 用户为本，科技向善
 **/

#if !defined(__398ab4fa7c7ae78c3d6413bc104aff31__)
#define __398ab4fa7c7ae78c3d6413bc104aff31__

#include "kmdf.h"

static constexpr uint32_t IA32_TIME_STAMP_COUNTER = 0x00000010;
static constexpr uint32_t IA32_APIC_BASE = 0x0000001B;
static constexpr uint32_t IA32_FEATURE_CONTROL = 0x0000003A;
static constexpr uint32_t IA32_TSC_ADJUST = 0x0000003B;
static constexpr uint32_t IA32_SPEC_CTRL = 0x00000048;
static constexpr uint32_t IA32_SMBASE = 0x0000009E;
static constexpr uint32_t IA32_PMC0 = 0x000000C1;
static constexpr uint32_t IA32_PMC1 = 0x000000C2;
static constexpr uint32_t IA32_PMC2 = 0x000000C3;
static constexpr uint32_t IA32_PMC3 = 0x000000C4;
static constexpr uint32_t IA32_PMC4 = 0x000000C5;
static constexpr uint32_t IA32_PMC5 = 0x000000C6;
static constexpr uint32_t IA32_PMC6 = 0x000000C7;
static constexpr uint32_t IA32_PMC7 = 0x000000C8;
static constexpr uint32_t IA32_PMC8 = 0x000000C9;
static constexpr uint32_t IA32_PMC9 = 0x000000CA;
static constexpr uint32_t IA32_CORE_CAPABILITIES = 0x000000CF;
static constexpr uint32_t IA32_MPERF = 0x000000E7;
static constexpr uint32_t IA32_APERF = 0x000000E8;
static constexpr uint32_t IA32_ARCH_CAPABILITIES = 0x0000010A;
static constexpr uint32_t IA32_SYSENTER_CS = 0x00000174;
static constexpr uint32_t IA32_SYSENTER_ESP = 0x00000175;
static constexpr uint32_t IA32_SYSENTER_EIP = 0x00000176;
static constexpr uint32_t IA32_OVERCLOCKING_STATUS = 0x00000195;
static constexpr uint32_t IA32_PERF_STATUS = 0x00000198;
static constexpr uint32_t IA32_PERF_CTL = 0x00000199;
static constexpr uint32_t IA32_MISC_ENABLE = 0x000001A0;
static constexpr uint32_t IA32_DEBUGCTL = 0x000001D9;
static constexpr uint32_t IA32_LER_FROM_IP = 0x000001DD;
static constexpr uint32_t IA32_LER_TO_IP = 0x000001DE;
static constexpr uint32_t IA32_LER_INFO = 0x000001E0;
static constexpr uint32_t IA32_SMRR_PHYSBASE = 0x000001F2;
static constexpr uint32_t IA32_SMRR_PHYSMASK = 0x000001F3;
static constexpr uint32_t IA32_MTRR_PHYSBASE0 = 0x00000200;
static constexpr uint32_t IA32_MTRR_PHYSMASK0 = 0x00000201;
static constexpr uint32_t IA32_MTRR_PHYSBASE1 = 0x00000202;
static constexpr uint32_t IA32_MTRR_PHYSMASK1 = 0x00000203;
static constexpr uint32_t IA32_MTRR_PHYSBASE2 = 0x00000204;
static constexpr uint32_t IA32_MTRR_PHYSMASK2 = 0x00000205;
static constexpr uint32_t IA32_MTRR_PHYSBASE3 = 0x00000206;
static constexpr uint32_t IA32_MTRR_PHYSMASK3 = 0x00000207;
static constexpr uint32_t IA32_MTRR_PHYSBASE4 = 0x00000208;
static constexpr uint32_t IA32_MTRR_PHYSMASK4 = 0x00000209;
static constexpr uint32_t IA32_MTRR_PHYSBASE5 = 0x0000020A;
static constexpr uint32_t IA32_MTRR_PHYSMASK5 = 0x0000020B;
static constexpr uint32_t IA32_MTRR_PHYSBASE6 = 0x0000020C;
static constexpr uint32_t IA32_MTRR_PHYSMASK6 = 0x0000020D;
static constexpr uint32_t IA32_MTRR_PHYSBASE7 = 0x0000020E;
static constexpr uint32_t IA32_MTRR_PHYSMASK7 = 0x0000020F;
static constexpr uint32_t IA32_MTRR_PHYSBASE8 = 0x00000210;
static constexpr uint32_t IA32_MTRR_PHYSMASK8 = 0x00000211;
static constexpr uint32_t IA32_MTRR_PHYSBASE9 = 0x00000212;
static constexpr uint32_t IA32_MTRR_PHYSMASK9 = 0x00000213;
static constexpr uint32_t IA32_PAT = 0x00000277;
static constexpr uint32_t IA32_PERF_CAPABILITIES = 0x00000345;
static constexpr uint32_t IA32_VMX_BASIC = 0x00000480;
static constexpr uint32_t IA32_VMX_PINBASED_CTLS = 0x00000481;
static constexpr uint32_t IA32_VMX_PROCBASED_CTLS = 0x00000482;
static constexpr uint32_t IA32_VMX_EXIT_CTLS = 0x00000483;
static constexpr uint32_t IA32_VMX_ENTRY_CTLS = 0x00000484;
static constexpr uint32_t IA32_VMX_MISC = 0x00000485;
static constexpr uint32_t IA32_VMX_CR0_FIXED0 = 0x00000486;
static constexpr uint32_t IA32_VMX_CR0_FIXED1 = 0x00000487;
static constexpr uint32_t IA32_VMX_CR4_FIXED0 = 0x00000488;
static constexpr uint32_t IA32_VMX_CR4_FIXED1 = 0x00000489;
static constexpr uint32_t IA32_VMX_VMCS_ENUM = 0x0000048A;
static constexpr uint32_t IA32_VMX_PROCBASED_CTLS2 = 0x0000048B;
static constexpr uint32_t IA32_VMX_EPT_VPID_CAP = 0x0000048C;
static constexpr uint32_t IA32_VMX_TRUE_PINBASED_CTLS = 0x0000048D;
static constexpr uint32_t IA32_VMX_TRUE_PROCBASED_CTLS = 0x0000048E;
static constexpr uint32_t IA32_VMX_TRUE_EXIT_CTLS = 0x0000048F;
static constexpr uint32_t IA32_VMX_TRUE_ENTRY_CTLS = 0x00000490;
static constexpr uint32_t IA32_VMX_VMFUNC = 0x00000491;
static constexpr uint32_t IA32_VMX_PROCBASED_CTLS3 = 0x00000492;
static constexpr uint32_t IA32_VMX_EXIT_CTLS2 = 0x00000493;
static constexpr uint32_t IA32_DEBUG_INTERFACE = 0x00000C80;
static constexpr uint32_t IA32_LBR_CTL = 0x000014CE;
static constexpr uint32_t IA32_LBR_DEPTH = 0x000014CF;
static constexpr uint32_t IA32_LBR_x_FROM_IP = 0x00001500;
static constexpr uint32_t IA32_LBR_x_TO_IP = 0x00001600;
static constexpr uint32_t IA32_EFER = 0xC0000080;
static constexpr uint32_t IA32_STAR = 0xC0000081;
static constexpr uint32_t IA32_LSTAR = 0xC0000082;
static constexpr uint32_t IA32_CSTAR = 0xC0000083;
static constexpr uint32_t IA32_FMASK = 0xC0000084;
static constexpr uint32_t IA32_FS_BASE = 0xC0000100;
static constexpr uint32_t IA32_GS_BASE = 0xC0000101;
static constexpr uint32_t IA32_KERNEL_GS_BASE = 0xC0000102;
static constexpr uint32_t IA32_TSC_AUX = 0xC0000103;

template <>
int vmxon<Hash("GenuineIntel")>(PVOID vcpu);

template <>
int vmxoff<Hash("GenuineIntel")>(PVOID vcpu);

#endif // !__398ab4fa7c7ae78c3d6413bc104aff31__
