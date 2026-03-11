
/**
 * 用户为本，科技向善
 **/

#include "AuthenticAMD.h"

#include "GenuineIntel.h"

static KSPIN_LOCK kSpinLock;

static int (*Procedures[0x800])(void);

static FORCEINLINE size_t
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

static FORCEINLINE uint16_t
svm_format_access_rights(uint32_t access_rights)
{
    uint16_t result = {};

    result |= (((access_rights >> 0x08) & 0x0000000F) << 0x00); // Segment type
    result |= (((access_rights >> 0x0C) & 0x00000001) << 0x04); // S - Descriptor type (0 = system; 1 = code or data)
    result |= (((access_rights >> 0x0D) & 0x00000003) << 0x05); // DPL - Descriptor privilege level
    result |= (((access_rights >> 0x0F) & 0x00000001) << 0x07); // P - Segment present
    result |= (((access_rights >> 0x14) & 0x00000001) << 0x08); // AVL - Available for use by system software
    result |= (((access_rights >> 0x15) & 0x00000001) << 0x09); // Reserved (except for CS) L - 64-bit mode active (for CS only)
    result |= (((access_rights >> 0x16) & 0x00000001) << 0x0A); // D/B - Default operation size (0 = 16-bit segment; 1 = 32-bit segment)
    result |= (((access_rights >> 0x17) & 0x00000001) << 0x0B); // G - Granularity

    return result;
}

template <int e>
static int
procedure(void)
{
    return 0;
}

template <>
int
procedure<0x0000>(void)
{
    return 0;
}

static void
initializeNPT()
{
}

static void
initializeProcedures()
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
    Procedures[0x0050] = &procedure<0x0050>;
    Procedures[0x0051] = &procedure<0x0051>;
    Procedures[0x0052] = &procedure<0x0052>;
    Procedures[0x0053] = &procedure<0x0053>;
    Procedures[0x0054] = &procedure<0x0054>;
    Procedures[0x0055] = &procedure<0x0055>;
    Procedures[0x0056] = &procedure<0x0056>;
    Procedures[0x0057] = &procedure<0x0057>;
    Procedures[0x0058] = &procedure<0x0058>;
    Procedures[0x0059] = &procedure<0x0059>;
    Procedures[0x005A] = &procedure<0x005A>;
    Procedures[0x005B] = &procedure<0x005B>;
    Procedures[0x005C] = &procedure<0x005C>;
    Procedures[0x005D] = &procedure<0x005D>;
    Procedures[0x005E] = &procedure<0x005E>;
    Procedures[0x005F] = &procedure<0x005F>;
    Procedures[0x0060] = &procedure<0x0060>;
    Procedures[0x0061] = &procedure<0x0061>;
    Procedures[0x0062] = &procedure<0x0062>;
    Procedures[0x0063] = &procedure<0x0063>;
    Procedures[0x0064] = &procedure<0x0064>;
    Procedures[0x0065] = &procedure<0x0065>;
    Procedures[0x0066] = &procedure<0x0066>;
    Procedures[0x0067] = &procedure<0x0067>;
    Procedures[0x0068] = &procedure<0x0068>;
    Procedures[0x0069] = &procedure<0x0069>;
    Procedures[0x006A] = &procedure<0x006A>;
    Procedures[0x006B] = &procedure<0x006B>;
    Procedures[0x006C] = &procedure<0x006C>;
    Procedures[0x006D] = &procedure<0x006D>;
    Procedures[0x006E] = &procedure<0x006E>;
    Procedures[0x006F] = &procedure<0x006F>;
    Procedures[0x0070] = &procedure<0x0070>;
    Procedures[0x0071] = &procedure<0x0071>;
    Procedures[0x0072] = &procedure<0x0072>;
    Procedures[0x0073] = &procedure<0x0073>;
    Procedures[0x0074] = &procedure<0x0074>;
    Procedures[0x0075] = &procedure<0x0075>;
    Procedures[0x0076] = &procedure<0x0076>;
    Procedures[0x0077] = &procedure<0x0077>;
    Procedures[0x0078] = &procedure<0x0078>;
    Procedures[0x0079] = &procedure<0x0079>;
    Procedures[0x007A] = &procedure<0x007A>;
    Procedures[0x007B] = &procedure<0x007B>;
    Procedures[0x007C] = &procedure<0x007C>;
    Procedures[0x007D] = &procedure<0x007D>;
    Procedures[0x007E] = &procedure<0x007E>;
    Procedures[0x007F] = &procedure<0x007F>;
    Procedures[0x0080] = &procedure<0x0080>;
    Procedures[0x0081] = &procedure<0x0081>;
    Procedures[0x0082] = &procedure<0x0082>;
    Procedures[0x0083] = &procedure<0x0083>;
    Procedures[0x0084] = &procedure<0x0084>;
    Procedures[0x0085] = &procedure<0x0085>;
    Procedures[0x0086] = &procedure<0x0086>;
    Procedures[0x0087] = &procedure<0x0087>;
    Procedures[0x0088] = &procedure<0x0088>;
    Procedures[0x0089] = &procedure<0x0089>;
    Procedures[0x008A] = &procedure<0x008A>;
    Procedures[0x008B] = &procedure<0x008B>;
    Procedures[0x008C] = &procedure<0x008C>;
    Procedures[0x008D] = &procedure<0x008D>;
    Procedures[0x008E] = &procedure<0x008E>;
    Procedures[0x008F] = &procedure<0x008F>;
    Procedures[0x0090] = &procedure<0x0090>;
    Procedures[0x0091] = &procedure<0x0091>;
    Procedures[0x0092] = &procedure<0x0092>;
    Procedures[0x0093] = &procedure<0x0093>;
    Procedures[0x0094] = &procedure<0x0094>;
    Procedures[0x0095] = &procedure<0x0095>;
    Procedures[0x0096] = &procedure<0x0096>;
    Procedures[0x0097] = &procedure<0x0097>;
    Procedures[0x0098] = &procedure<0x0098>;
    Procedures[0x0099] = &procedure<0x0099>;
    Procedures[0x009A] = &procedure<0x009A>;
    Procedures[0x009B] = &procedure<0x009B>;
    Procedures[0x009C] = &procedure<0x009C>;
    Procedures[0x009D] = &procedure<0x009D>;
    Procedures[0x009E] = &procedure<0x009E>;
    Procedures[0x009F] = &procedure<0x009F>;
    Procedures[0x00A0] = &procedure<0x00A0>;
    Procedures[0x00A1] = &procedure<0x00A1>;
    Procedures[0x00A2] = &procedure<0x00A2>;
    Procedures[0x00A3] = &procedure<0x00A3>;
    Procedures[0x00A4] = &procedure<0x00A4>;
    Procedures[0x00A5] = &procedure<0x00A5>;
    Procedures[0x00A6] = &procedure<0x00A6>;
    Procedures[0x00A7] = &procedure<0x00A7>;
    Procedures[0x00A8] = &procedure<0x00A8>;
    Procedures[0x00A9] = &procedure<0x00A9>;
    Procedures[0x00AA] = &procedure<0x00AA>;
    Procedures[0x00AB] = &procedure<0x00AB>;
    Procedures[0x00AC] = &procedure<0x00AC>;
    Procedures[0x00AD] = &procedure<0x00AD>;
    Procedures[0x00AE] = &procedure<0x00AE>;
    Procedures[0x00AF] = &procedure<0x00AF>;
    Procedures[0x00B0] = &procedure<0x00B0>;
    Procedures[0x00B1] = &procedure<0x00B1>;
    Procedures[0x00B2] = &procedure<0x00B2>;
    Procedures[0x00B3] = &procedure<0x00B3>;
    Procedures[0x00B4] = &procedure<0x00B4>;
    Procedures[0x00B5] = &procedure<0x00B5>;
    Procedures[0x00B6] = &procedure<0x00B6>;
    Procedures[0x00B7] = &procedure<0x00B7>;
    Procedures[0x00B8] = &procedure<0x00B8>;
    Procedures[0x00B9] = &procedure<0x00B9>;
    Procedures[0x00BA] = &procedure<0x00BA>;
    Procedures[0x00BB] = &procedure<0x00BB>;
    Procedures[0x00BC] = &procedure<0x00BC>;
    Procedures[0x00BD] = &procedure<0x00BD>;
    Procedures[0x00BE] = &procedure<0x00BE>;
    Procedures[0x00BF] = &procedure<0x00BF>;
    Procedures[0x00C0] = &procedure<0x00C0>;
    Procedures[0x00C1] = &procedure<0x00C1>;
    Procedures[0x00C2] = &procedure<0x00C2>;
    Procedures[0x00C3] = &procedure<0x00C3>;
    Procedures[0x00C4] = &procedure<0x00C4>;
    Procedures[0x00C5] = &procedure<0x00C5>;
    Procedures[0x00C6] = &procedure<0x00C6>;
    Procedures[0x00C7] = &procedure<0x00C7>;
    Procedures[0x00C8] = &procedure<0x00C8>;
    Procedures[0x00C9] = &procedure<0x00C9>;
    Procedures[0x00CA] = &procedure<0x00CA>;
    Procedures[0x00CB] = &procedure<0x00CB>;
    Procedures[0x00CC] = &procedure<0x00CC>;
    Procedures[0x00CD] = &procedure<0x00CD>;
    Procedures[0x00CE] = &procedure<0x00CE>;
    Procedures[0x00CF] = &procedure<0x00CF>;
    Procedures[0x00D0] = &procedure<0x00D0>;
    Procedures[0x00D1] = &procedure<0x00D1>;
    Procedures[0x00D2] = &procedure<0x00D2>;
    Procedures[0x00D3] = &procedure<0x00D3>;
    Procedures[0x00D4] = &procedure<0x00D4>;
    Procedures[0x00D5] = &procedure<0x00D5>;
    Procedures[0x00D6] = &procedure<0x00D6>;
    Procedures[0x00D7] = &procedure<0x00D7>;
    Procedures[0x00D8] = &procedure<0x00D8>;
    Procedures[0x00D9] = &procedure<0x00D9>;
    Procedures[0x00DA] = &procedure<0x00DA>;
    Procedures[0x00DB] = &procedure<0x00DB>;
    Procedures[0x00DC] = &procedure<0x00DC>;
    Procedures[0x00DD] = &procedure<0x00DD>;
    Procedures[0x00DE] = &procedure<0x00DE>;
    Procedures[0x00DF] = &procedure<0x00DF>;
    Procedures[0x00E0] = &procedure<0x00E0>;
    Procedures[0x00E1] = &procedure<0x00E1>;
    Procedures[0x00E2] = &procedure<0x00E2>;
    Procedures[0x00E3] = &procedure<0x00E3>;
    Procedures[0x00E4] = &procedure<0x00E4>;
    Procedures[0x00E5] = &procedure<0x00E5>;
    Procedures[0x00E6] = &procedure<0x00E6>;
    Procedures[0x00E7] = &procedure<0x00E7>;
    Procedures[0x00E8] = &procedure<0x00E8>;
    Procedures[0x00E9] = &procedure<0x00E9>;
    Procedures[0x00EA] = &procedure<0x00EA>;
    Procedures[0x00EB] = &procedure<0x00EB>;
    Procedures[0x00EC] = &procedure<0x00EC>;
    Procedures[0x00ED] = &procedure<0x00ED>;
    Procedures[0x00EE] = &procedure<0x00EE>;
    Procedures[0x00EF] = &procedure<0x00EF>;
    Procedures[0x00F0] = &procedure<0x00F0>;
    Procedures[0x00F1] = &procedure<0x00F1>;
    Procedures[0x00F2] = &procedure<0x00F2>;
    Procedures[0x00F3] = &procedure<0x00F3>;
    Procedures[0x00F4] = &procedure<0x00F4>;
    Procedures[0x00F5] = &procedure<0x00F5>;
    Procedures[0x00F6] = &procedure<0x00F6>;
    Procedures[0x00F7] = &procedure<0x00F7>;
    Procedures[0x00F8] = &procedure<0x00F8>;
    Procedures[0x00F9] = &procedure<0x00F9>;
    Procedures[0x00FA] = &procedure<0x00FA>;
    Procedures[0x00FB] = &procedure<0x00FB>;
    Procedures[0x00FC] = &procedure<0x00FC>;
    Procedures[0x00FD] = &procedure<0x00FD>;
    Procedures[0x00FE] = &procedure<0x00FE>;
    Procedures[0x00FF] = &procedure<0x00FF>;

    Procedures[0x0400] = &procedure<0x0400>;
    Procedures[0x0401] = &procedure<0x0401>;
    Procedures[0x0402] = &procedure<0x0402>;
    Procedures[0x0403] = &procedure<0x0403>;
}

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
        LFuncStd = eax & 0x7FFFFFFF;

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
        LFuncExt = eax & 0x7FFFFFFF;

        if (LFuncExt < 0x00000001)
            break;

        __asm_cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

        if (ecx & (1U << 0x00)) // LahfSahf - LAHF and SAHF instruction support in 64-bit mode
            ;
        if (ecx & (1U << 0x01)) // CmpLegacy - Core multi-processing legacy mode
            ;
        if ((ecx & (1U << 0x02)) == 0) // SVM - Secure virtual machine
            return -1;
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
        if (ecx & (1U << 0x11)) // TCE - Translation Cache Extension support
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

        if (edx & (1U << 0x00)) // FPU - x87 floating-point unit on-chip. Same as CPUID Fn0000_0001_EDX [FPU].
            ;
        if (edx & (1U << 0x01)) // VME - Virtual-mode enhancements. Same as CPUID Fn0000_0001_EDX [VME].
            ;
        if (edx & (1U << 0x02)) // DE - Debugging extensions. Same as CPUID Fn0000_0001_EDX [DE].
            ;
        if (edx & (1U << 0x03)) // PSE - Page-size extensions. Same as CPUID Fn0000_0001_EDX [PSE].
            ;
        if (edx & (1U << 0x04)) // TSC - Time stamp counter. Same as CPUID Fn0000_0001_EDX [TSC].
            ;
        if (edx & (1U << 0x05)) // MSR - AMD model-specific registers. Same as CPUID Fn0000_0001_EDX [MSR].
            ;
        if (edx & (1U << 0x06)) // PAE - Physical-address extensions. Same as CPUID Fn0000_0001_EDX [PAE].
            ;
        if (edx & (1U << 0x07)) // MCE - Machine check exception. Same as CPUID Fn0000_0001_EDX [MCE].
            ;
        if (edx & (1U << 0x08)) // CMPXCHG8B - CMPXCHG8B instruction. Same as CPUID Fn0000_0001_EDX [CMPXCHG8B].
            ;
        if (edx & (1U << 0x09)) // APIC - Advanced programmable interrupt controller. Same as CPUID Fn0000_0001_EDX [APIC].
            ;
        if (edx & (1U << 0x0A))
            ;
        if (edx & (1U << 0x0B)) // SysCallSysRet - SYSCALL and SYSRET instructions
            ;
        if (edx & (1U << 0x0C)) // MTRR - Memory-type range registers. Same as CPUID Fn0000_0001_EDX [MTRR].
            ;
        if (edx & (1U << 0x0D)) // PGE - Page global extension. Same as CPUID Fn0000_0001_EDX [PGE].
            ;
        if (edx & (1U << 0x0E)) // MCA - Machine check architecture. Same as CPUID Fn0000_0001_EDX [MCA].
            ;
        if (edx & (1U << 0x0F)) // CMOV - Conditional move instructions. Same as CPUID Fn0000_0001_EDX [CMOV].
            ;
        if (edx & (1U << 0x10)) // PAT - Page attribute table. Same as CPUID Fn0000_0001_EDX [PAT].
            ;
        if (edx & (1U << 0x11)) // PSE36 - Page-size extensions. Same as CPUID Fn0000_0001_EDX [PSE36].
            ;
        if (edx & (1U << 0x12))
            ;
        if (edx & (1U << 0x13))
            ;
        if (edx & (1U << 0x14)) // NX - No-execute page protection. See “Page Translation and Protection” in APM Volume 2.
            ;
        if (edx & (1U << 0x15))
            ;
        if (edx & (1U << 0x16)) // MmxExt - AMD extensions to MMX instructions
            ;
        if (edx & (1U << 0x17)) // MMX - MMX™ instructions. Same as CPUID Fn0000_0001_EDX [MMX].
            ;
        if (edx & (1U << 0x18)) // FXSR - FXSAVE and FXRSTOR instructions. Same as CPUID Fn0000_0001_EDX [FXSR].
            ;
        if (edx & (1U << 0x19)) // FFXSR - FXSAVE and FXRSTOR instruction optimizations. See “FXSAVE” and “FXRSTOR” in APM Volume 5.
            ;
        if (edx & (1U << 0x1A)) // Page1GB - 1-GB large page support
            ;
        if (edx & (1U << 0x1B)) // RDTSCP - RDTSCP instruction
            ;
        if (edx & (1U << 0x1C))
            ;
        if (edx & (1U << 0x1D)) // LM - Long mode.
            ;
        if (edx & (1U << 0x1E)) // 3DNowExt - AMD extensions to 3DNow! instructions
            ;
        if (edx & (1U << 0x1F)) // 3DNow - 3DNow!™ instructions
            ;

        if (LFuncExt < 0x00000006)
            break;

        __asm_cpuid(0x80000005, &eax, &ebx, &ecx, &edx); // L1 Cache and TLB Information

        uint16_t L1ITlb2and4MSize = ((eax >> 0x00) & 0x000000FF);  // L1ITlb2and4MSize - Instruction TLB number of entries for 2-MB and 4-MB pages.
        uint16_t L1ITlb2and4MAssoc = ((eax >> 0x08) & 0x000000FF); // L1ITlb2and4MAssoc - Instruction TLB associativity for 2-MB and 4-MB pages
        uint16_t L1DTlb2and4MSize = ((eax >> 0x10) & 0x000000FF);  // L1DTlb2and4MSize - Data TLB number of entries for 2-MB and 4-MB pages
        uint16_t L1DTlb2and4MAssoc = ((eax >> 0x18) & 0x000000FF); // L1DTlb2and4MAssoc - Data TLB associativity for 2-MB and 4-MB pages

        uint16_t L1ITlb4KSize = ((ebx >> 0x00) & 0x000000FF);  // L1ITlb4KSize - Instruction TLB number of entries for 4 KB pages.
        uint16_t L1ITlb4KAssoc = ((ebx >> 0x08) & 0x000000FF); // L1ITlb4KAssoc - Instruction TLB associativity for 4 KB pages
        uint16_t L1DTlb4KSize = ((ebx >> 0x10) & 0x000000FF);  // L1DTlb4KSize - Data TLB number of entries for 4 KB pages.
        uint16_t L1DTlb4KAssoc = ((ebx >> 0x18) & 0x000000FF); // L1DTlb4KAssoc - Data TLB associativity for 4 KB pages

        uint16_t L1DcLineSize = ((ecx >> 0x00) & 0x000000FF);    // L1DcLineSize - L1 data cache line size in bytes.
        uint16_t L1DcLinesPerTag = ((ecx >> 0x08) & 0x000000FF); // L1DcLinesPerTag - L1 data cache lines per tag.
        uint16_t L1DcAssoc = ((ecx >> 0x10) & 0x000000FF);       // L1DcAssoc - L1 data cache associativity.
        uint16_t L1DcSize = ((ecx >> 0x18) & 0x000000FF);        // L1DcSize - L1 data cache size in KB.

        uint16_t L1IcLineSize = ((edx >> 0x00) & 0x000000FF);    // L1IcLineSize - L1 instruction cache line size in bytes.
        uint16_t L1IcLinesPerTag = ((edx >> 0x08) & 0x000000FF); // L1IcLinesPerTag - L1 instruction cache lines per tag.
        uint16_t L1IcAssoc = ((edx >> 0x10) & 0x000000FF);       // L1IcAssoc - L1 instruction cache associativity.
        uint16_t L1IcSize = ((edx >> 0x18) & 0x000000FF);        // L1IcSize - L1 instruction cache size KB.

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

        if ((edx & (1U << 0x00)) == 0) // NP - Nested paging
            return -1;
        if (edx & (1U << 0x01)) // LbrVirt - LBR virtualization
            ;
        if ((edx & (1U << 0x02)) == 0) // SVML - SVM lock
            return -1;
        if ((edx & (1U << 0x03)) == 0) // NRIPS - NRIP save
            return -1;
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

        if (LFuncExt < 0x00000026)
            break;

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
        __asm_cpuid(0x80000025, &eax, &ebx, &ecx, &edx); // SEV Capabilities 2
        __asm_cpuid(0x80000026, &eax, &ebx, &ecx, &edx); // Extended CPU Topology
    } while (0);

    IA32_GDT_REGISTER GDTR;
    IA32_IDT_REGISTER IDTR;

    __asm_sgdt(&GDTR);
    __asm_sidt(&IDTR);

    uint64_t CR0 = __asm_cr0();
    uint64_t CR2 = __asm_cr2(); // Page-Fault Linear Address
    uint64_t CR3 = __asm_cr3();
    uint64_t CR4 = __asm_cr4();

    uint16_t CS = __asm_cs();
    uint16_t DS = __asm_ds();
    uint16_t ES = __asm_es();
    uint16_t FS = __asm_fs();
    uint16_t GS = __asm_gs();
    uint16_t SS = __asm_ss();
    uint16_t TR = __asm_str();
    uint16_t LDTR = __asm_sldt();

    do {
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

    uint64_t ia32_time_stamp_counter = __asm_rdmsr(IA32_TIME_STAMP_COUNTER);
    uint64_t ia32_apic_base = __asm_rdmsr(IA32_APIC_BASE);

    uint64_t ia32_mperf = __asm_rdmsr(IA32_MPERF);
    uint64_t ia32_aperf = __asm_rdmsr(IA32_APERF);

    uint64_t ia32_sysenter_cs = __asm_rdmsr(IA32_SYSENTER_CS);
    uint64_t ia32_sysenter_esp = __asm_rdmsr(IA32_SYSENTER_ESP);
    uint64_t ia32_sysenter_eip = __asm_rdmsr(IA32_SYSENTER_EIP);

    uint64_t ia32_debugctl = __asm_rdmsr(IA32_DEBUGCTL);

    uint64_t ia32_pat = __asm_rdmsr(IA32_PAT);

    uint64_t ia32_efer = __asm_rdmsr(IA32_EFER);
    uint64_t ia32_star = __asm_rdmsr(IA32_STAR);
    uint64_t ia32_lstar = __asm_rdmsr(IA32_LSTAR);
    uint64_t ia32_cstar = __asm_rdmsr(IA32_CSTAR);
    uint64_t ia32_fmask = __asm_rdmsr(IA32_FMASK);

    uint64_t ia32_fs_base = __asm_rdmsr(IA32_FS_BASE);
    uint64_t ia32_gs_base = __asm_rdmsr(IA32_GS_BASE);
    uint64_t ia32_kernel_gs_base = __asm_rdmsr(IA32_KERNEL_GS_BASE);
    uint64_t ia32_tsc_aux = __asm_rdmsr(IA32_TSC_AUX);

    do {
        uint64_t msr;

        ia32_efer |= 1ULL << 0x0C; // SVME - Secure Virtual Machine Enable
        __asm_wrmsr(IA32_EFER, ia32_efer);

        if (ia32_efer & (1ULL << 0x00)) // 0 SCE - System Call Extensions R/W
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
        if (ia32_efer & (1ULL << 0x08)) // 8 LME - Long Mode Enable R/W
            ;
        if (ia32_efer & (1ULL << 0x09))
            ;
        if (ia32_efer & (1ULL << 0x0A)) // 10 LMA - Long Mode Active R/W
            ;
        if (ia32_efer & (1ULL << 0x0B)) // 11 NXE - No-Execute Enable R/W
            ;
        if (ia32_efer & (1ULL << 0x0C)) // 12 SVME - Secure Virtual Machine Enable R/W
            ;
        if (ia32_efer & (1ULL << 0x0D)) // 13 LMSLE - Long Mode Segment Limit Enable R/W
            ;
        if (ia32_efer & (1ULL << 0x0E)) // 14 FFXSR - Fast FXSAVE/FXRSTOR R/W
            ;
        if (ia32_efer & (1ULL << 0x0F)) // 15 TCE - Translation Cache Extension R/W
            ;
        if (ia32_efer & (1ULL << 0x10))
            ;
        if (ia32_efer & (1ULL << 0x11)) // 17 MCOMMIT - Enable MCOMMIT instruction R/W
            ;
        if (ia32_efer & (1ULL << 0x12)) // 18 INTWB - Interruptible WBINVD/WBNOINVD enable R/W
            ;
        if (ia32_efer & (1ULL << 0x13))
            ;
        if (ia32_efer & (1ULL << 0x14)) // 20 UAIE - Upper Address Ignore Enable R/W
            ;
        if (ia32_efer & (1ULL << 0x15)) // 21 AIBRSE - Automatic IBRS Enable R/W
            ;

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

        if (msr & (1ULL << 0x00)) // DPD - Bit 0. If set, disables the external hardware debug port and certain internal debug features.
            ;
        if (msr & (1ULL << 0x01)) // R_INIT - Bit 1. If set, non-intercepted INIT signals are converted into an #SX exception.
            ;
        if (msr & (1ULL << 0x02)) // DIS_A20M - Bit 2. If set, disables A20 masking.
            ;
        if (msr & (1ULL << 0x03)) // LOCK - Bit 3. When this bit is set, writes to LOCK and SVMDIS are silently ignored. When this bit is clear, VM_CR bits 3 and 4 can be written. Once set, LOCK can only be cleared using the SVM_KEY MSR (See Section 15.31.) This bit is not affected by INIT or SKINIT.
            ;
        if (msr & (1ULL << 0x04)) // SVMDIS - Bit 4. When this bit is set, writes to EFER treat the SVME bit as MBZ. When this bit is clear, EFER.SVME can be written normally. This bit does not prevent CPUID from reporting that SVM is available. Setting SVMDIS while EFER.SVME is 1 generates a #GP fault, regardless of the current state of VM_CR.LOCK. This bit is not affected by SKINIT. It is cleared by INIT when LOCK is cleared to 0; otherwise, it is not affected.
            return -1;

        msr = __asm_rdmsr(0xC0010115); // IGNNE SVM "SVM Related MSRs" on page 583
        msr = __asm_rdmsr(0xC0010116); // SMM_CTL SVM "SVM Related MSRs" on page 583

        if (msr & (1ULL << 0x00))
            ;
        if (msr & (1ULL << 0x01))
            ;
        if (msr & (1ULL << 0x02))
            ;
        if (msr & (1ULL << 0x03))
            ;
        if (msr & (1ULL << 0x04))
            ;

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
        msr = __asm_rdmsr(0xC00102B1); // CPPC_ENABLE CPPC
        msr = __asm_rdmsr(0xC00102B2); // CPPC_CAPABILITY_2 CPPC
        msr = __asm_rdmsr(0xC00102B3); // CPPC_REQUEST CPPC
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

    KeAcquireSpinLockAtDpcLevel(&kSpinLock);
    initializeNPT();
    initializeProcedures();
    KeReleaseSpinLockFromDpcLevel(&kSpinLock);

    void* vmcb = allocate<0x1000>();
    void* HostStateSaveArea = allocate<0x1000>();
    void* msrpm = allocateContiguous<0x2000>();
    void* iopm = allocateContiguous<0x2000>();

    memset(vmcb, 0, 0x1000);
    memset(HostStateSaveArea, 0, 0x1000);
    memset(msrpm, 0, 0x1000);
    memset(iopm, 0, 0x1000);

    PHYSICAL_ADDRESS IOPM_BASE_PA = MmGetPhysicalAddress(iopm);
    PHYSICAL_ADDRESS MSRPM_BASE_PA = MmGetPhysicalAddress(msrpm);
    PHYSICAL_ADDRESS hostPa = MmGetPhysicalAddress(HostStateSaveArea);
    PHYSICAL_ADDRESS guestPa = MmGetPhysicalAddress(vmcb);

    CONTEXT Context;
    RtlCaptureContext(&Context);

    if (Context.Rip == 0x12345678)
        return 0;

    KdBreakPoint();

    *(uint16_t*)((uint8_t*)vmcb + 0x0000) = 0; // Intercept reads of CR0–15, respectively
    *(uint16_t*)((uint8_t*)vmcb + 0x0002) = 0; // Intercept writes of CR0–15, respectively
    *(uint16_t*)((uint8_t*)vmcb + 0x0004) = 0; // Intercept reads of DR0–15, respectively
    *(uint16_t*)((uint8_t*)vmcb + 0x0006) = 0; // Intercept writes of DR0–15, respectively.
    *(uint32_t*)((uint8_t*)vmcb + 0x0008) = 0; // Intercept exception vectors 0–31, respectively

    *(uint32_t*)((uint8_t*)vmcb + 0x000C) = 0;
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x00; // Intercept INTR (physical maskable interrupt)
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x01; // Intercept NMI
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x02; // Intercept SMI
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x03; // Intercept INIT
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x04; // Intercept VINTR (virtual maskable interrupt)
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x05; // Intercept CR0 writes that change bits other than CR0.TS or CR0.MP
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x06; // Intercept reads of IDTR
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x07; // Intercept reads of GDTR
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x08; // Intercept reads of LDTR
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x09; // Intercept reads of TR
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x0A; // Intercept writes of IDTR
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x0B; // Intercept writes of GDTR
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x0C; // Intercept writes of LDTR
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x0D; // Intercept writes of TR
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x0E; // Intercept RDTSC instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x0F; // Intercept RDPMC instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x10; // Intercept PUSHF instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x11; // Intercept POPF instruction

    *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x12; // Intercept CPUID instruction

    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x13; // Intercept RSM instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x14; // Intercept IRET instruction
    *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x15; // Intercept INTn instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x16; // Intercept INVD instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x17; // Intercept PAUSE instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x18; // Intercept HLT instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x19; // Intercept INVLPG instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x1A; // Intercept INVLPGA instruction
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x1B; // IOIO_PROT - Intercept IN/OUT accesses to selected ports
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x1C; // MSR_PROT - intercept RDMSR or WRMSR accesses to selected MSRs
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x1D; // Intercept task switches
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x1E; // FERR_FREEZE: intercept processor “freezing” during legacy FERR handling
    // *(uint32_t*)((uint8_t*)vmcb + 0x000C) |= 1U << 0x1F; // Intercept shutdown events

    *(uint16_t*)((uint8_t*)vmcb + 0x0010) = 0;
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x00; // Intercept VMRUN instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x01; // Intercept VMMCALL instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x02; // Intercept VMLOAD instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x03; // Intercept VMSAVE instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x04; // Intercept STGI instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x05; // Intercept CLGI instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x06; // Intercept SKINIT instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x07; // Intercept RDTSCP instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x08; // Intercept ICEBP instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x09; // Intercept WBINVD and WBNOINVD instructions
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x0A; // Intercept MONITOR/MONITORX instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x0B; // Intercept MWAIT/MWAITX instruction unconditionally
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x0C; // Intercept MWAIT/MWAITX instruction if monitor hardware is armed
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x0D; // Intercept XSETBV instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x0E; // Intercept RDPRU instruction
    *(uint16_t*)((uint8_t*)vmcb + 0x0010) |= 1U << 0x0F; // Intercept writes of EFER (occurs after guest instruction finishes)

    *(uint16_t*)((uint8_t*)vmcb + 0x0012) = 0; ////Intercept writes of CR0-15 (occurs after guest instruction finishes)

    *(uint32_t*)((uint8_t*)vmcb + 0x0014) = 0;
    *(uint32_t*)((uint8_t*)vmcb + 0x0014) |= 1U << 0x00; // Intercept all INVLPGB instructions
    *(uint32_t*)((uint8_t*)vmcb + 0x0014) |= 1U << 0x01; // Intercept only illegally specified INVLPGB instructions
    *(uint32_t*)((uint8_t*)vmcb + 0x0014) |= 1U << 0x02; // Intercept INVPCID instruction
    *(uint32_t*)((uint8_t*)vmcb + 0x0014) |= 1U << 0x03; // Intercept MCOMMIT instruction
    *(uint32_t*)((uint8_t*)vmcb + 0x0014) |= 1U << 0x04; // Intercept TLBSYNC instruction. Presence of this bit is indicated by CPUID Fn8000_000A, EDX[24] = 1.
    *(uint32_t*)((uint8_t*)vmcb + 0x0014) |= 1U << 0x05; // Intercept bus lock operations when Bus Lock Threshold Counter is 0 (occurs before guest instruction executes).
    *(uint32_t*)((uint8_t*)vmcb + 0x0014) |= 1U << 0x06; // Intercept HLT instruction if a virtual interrupt is not pending.

    *(uint16_t*)((uint8_t*)vmcb + 0x003C) = 0;                      // PAUSE Filter Threshold
    *(uint16_t*)((uint8_t*)vmcb + 0x003E) = 0;                      // PAUSE Filter Count
    *(uint64_t*)((uint8_t*)vmcb + 0x0040) = IOPM_BASE_PA.QuadPart;  // IOPM_BASE_PA - Physical base address of IOPM (bits 11:0 are ignored)
    *(uint64_t*)((uint8_t*)vmcb + 0x0048) = MSRPM_BASE_PA.QuadPart; // MSRPM_BASE_PA - Physical base address of MSRPM (bits 11:0 are ignored)
    *(uint64_t*)((uint8_t*)vmcb + 0x0050) = 0;                      // TSC_OFFSET - To be added in RDTSC and RDTSCP

    *(uint32_t*)((uint8_t*)vmcb + 0x0058) = 1; // Guest ASID

    /**
     * TLB_CONTROL
     * 00h—Do nothing
     * 01h—Flush entire TLB (all entries, all ASIDs) on VMRUN Should only be used by legacy hypervisors
     * 03h—Flush this guest’s TLB entries
     * 07h—Flush this guest’s non-global TLB entries
     **/
    *(uint8_t*)((uint8_t*)vmcb + 0x005C) = 0;

    *(uint8_t*)((uint8_t*)vmcb + 0x005D) = 0;
    *(uint8_t*)((uint8_t*)vmcb + 0x005D) |= 1U << 0x00; // ALLOW_LARGER_RAP
    *(uint8_t*)((uint8_t*)vmcb + 0x005D) |= 1U << 0x01; // CLEAR_RAP

    *(uint64_t*)((uint8_t*)vmcb + 0x0060) = 0;
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= (1ULL & 0x000000FF) << 0x08; // 7:0 V_TPR—The virtual TPR for the guest. Bits 3:0 are used for a 4-bit virtual TPR value; bits 7:4 are SBZ.
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x08;                // 8 V_IRQ—If nonzero, virtual INTR is pending
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x09;                // 9 VGIF value (0 – Virtual interrupts are masked, 1 – Virtual Interrupts are unmasked)
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x0B;                // 11 V_NMI - If nonzero, virtual NMI is pending
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x0C;                // 12 V_NMI_MASK - if nonzero, virtual NMI is masked
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x10;                // 19:16 V_INTR_PRIO—Priority for virtual interrupt
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x14;                // 20 V_IGN_TPR—If nonzero, the current virtual interrupt ignores the (virtual) TPR
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x15;                //
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x18;                // 24 V_INTR_MASKING—Virtualize masking of INTR interrupts
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x19;                // 25 AMD Virtual GIF enabled for this guest
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x1A;                // 26 V_NMI_ENABLE - NMI Virtualization Enable
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x1E;                // 30 x2AVIC Enable
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= 1ULL << 0x1F;                // 31 AVIC Enable
    //*(uint64_t*)((uint8_t*)vmcb + 0x0060) |= (1ULL & 0x000000FF) << 0x20; // 39:32 V_INTR_VECTOR—Vector to use for this interrupt

    *(uint64_t*)((uint8_t*)vmcb + 0x0068) = 0; //
    *(uint64_t*)((uint8_t*)vmcb + 0x0070) = 0; // EXITCODE
    *(uint64_t*)((uint8_t*)vmcb + 0x0078) = 0; // EXITINFO1
    *(uint64_t*)((uint8_t*)vmcb + 0x0080) = 0; // EXITINFO2
    *(uint64_t*)((uint8_t*)vmcb + 0x0088) = 0; // EXITINTINFO

    *(uint8_t*)((uint8_t*)vmcb + 0x0090) = 0;
    //*(uint8_t*)((uint8_t*)vmcb + 0x0090) |= 1U << 0x00; // NP_ENABLE - Enable nested paging.
    //*(uint8_t*)((uint8_t*)vmcb + 0x0090) |= 1U << 0x01; // Enable Secure Encrypted Virtualization
    //*(uint8_t*)((uint8_t*)vmcb + 0x0090) |= 1U << 0x02; // Enable Encrypted State for Secure Encrypted Virtualization
    //*(uint8_t*)((uint8_t*)vmcb + 0x0090) |= 1U << 0x03; // Guest Mode Execute Trap
    //*(uint8_t*)((uint8_t*)vmcb + 0x0090) |= 1U << 0x04; // SSSCheckEn - Enable supervisor shadow stack restrictions in nested page tables. Support for this feature is indicated by CPUID Fn8000_000A_EDX[19] (SSSCheck)
    //*(uint8_t*)((uint8_t*)vmcb + 0x0090) |= 1U << 0x05; // Virtual Transparent Encryption.
    //*(uint8_t*)((uint8_t*)vmcb + 0x0090) |= 1U << 0x06; // Enable Read Only Guest Page Tables
    //*(uint8_t*)((uint8_t*)vmcb + 0x0090) |= 1U << 0x07; // Enable INVLPGB/TLBSYNC.

    *(uint64_t*)((uint8_t*)vmcb + 0x0098) = 0; //
    *(uint64_t*)((uint8_t*)vmcb + 0x00A0) = 0; // Guest physical address of GHCB
    *(uint64_t*)((uint8_t*)vmcb + 0x00A8) = 0; // EVENTINJ - Event injection
    *(uint64_t*)((uint8_t*)vmcb + 0x00B0) = 0; // N_CR3 - Nested page table CR3 to use for nested paging

    *(uint64_t*)((uint8_t*)vmcb + 0x00B8) = 0;
    //*(uint64_t*)((uint8_t*)vmcb + 0x00B8) |= 1U << 0x00; // LBR Virtualization Enable
    //*(uint64_t*)((uint8_t*)vmcb + 0x00B8) |= 1U << 0x01; // VMSAVE/VMLOAD Virtualization Enable
    //*(uint64_t*)((uint8_t*)vmcb + 0x00B8) |= 1U << 0x02; // IBS Virtualization Enable
    //*(uint64_t*)((uint8_t*)vmcb + 0x00B8) |= 1U << 0x03; // PMC Virtualization Enable

    *(uint32_t*)((uint8_t*)vmcb + 0x00C0) = 0; // VMCB Clean Bits.
    *(uint16_t*)((uint8_t*)vmcb + 0x00C8) = 0; // nRIP - Next sequential instruction pointer
    *(uint16_t*)((uint8_t*)vmcb + 0x00D0) = 0; //
    *(uint16_t*)((uint8_t*)vmcb + 0x00F0) = 0; //
    *(uint16_t*)((uint8_t*)vmcb + 0x00F8) = 0; //
    *(uint64_t*)((uint8_t*)vmcb + 0x0108) = 0; //
    *(uint64_t*)((uint8_t*)vmcb + 0x0110) = 0; // VMGEXIT_RAX
    *(uint8_t*)((uint8_t*)vmcb + 0x0118) = 0;  // VMGEXIT_CPL
    *(uint16_t*)((uint8_t*)vmcb + 0x0120) = 0; // Bus Lock Threshold Counter
    *(uint64_t*)((uint8_t*)vmcb + 0x0134) = 0; //
    *(uint64_t*)((uint8_t*)vmcb + 0x0138) = 0; //
    *(uint64_t*)((uint8_t*)vmcb + 0x0140) = 0; //
    *(uint64_t*)((uint8_t*)vmcb + 0x0148) = 0; //
    *(uint64_t*)((uint8_t*)vmcb + 0x0150) = 0; //

    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0000) = ES;                                      // ES selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0002) = svm_format_access_rights(__asm_lar(ES)); // ES attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0004) = __asm_lsl(ES);                           // ES limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0008) = __lsb(ES);                               // ES base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0010) = CS;                                      // CS selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0012) = svm_format_access_rights(__asm_lar(CS)); // CS attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0014) = __asm_lsl(CS);                           // CS limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0018) = __lsb(CS);                               // CS base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0020) = SS;                                      // SS selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0022) = svm_format_access_rights(__asm_lar(SS)); // SS attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0024) = __asm_lsl(SS);                           // SS limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0028) = __lsb(SS);                               // SS base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0030) = DS;                                      // DS selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0032) = svm_format_access_rights(__asm_lar(DS)); // DS attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0034) = __asm_lsl(DS);                           // DS limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0038) = __lsb(DS);                               // DS base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0040) = 0;                                       // FS selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0042) = 0;                                       // FS attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0044) = 0;                                       // FS limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0048) = 0;                                       // FS base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0050) = 0;                                       // GS selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0052) = 0;                                       // GS attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0054) = 0;                                       // GS limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0058) = 0;                                       // GS base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0060) = 0;                                       // GDTR selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0062) = 0;                                       // GDTR attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0064) = GDTR.Limit;                              // GDTR limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0068) = (uint64_t)GDTR.BaseAddress;              // GDTR base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0070) = 0;                                       // LDTR selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0072) = 0;                                       // LDTR attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0074) = 0;                                       // LDTR limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0078) = 0;                                       // LDTR base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0080) = 0;                                       // IDTR selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0082) = 0;                                       // IDTR attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0084) = IDTR.Limit;                              // IDTR limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0088) = (uint64_t)IDTR.BaseAddress;              // IDTR base
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0090) = 0;                                       // TR selector
    *(uint16_t*)((uint8_t*)vmcb + 0x400 + 0x0092) = 0;                                       // TR attrib
    *(uint32_t*)((uint8_t*)vmcb + 0x400 + 0x0094) = 0;                                       // TR limit
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0098) = 0;                                       // TR base

    *(uint8_t*)((uint8_t*)vmcb + 0x400 + 0x00CB) = 0;                              // CPL If the guest is real-mode then the CPL is forced to 0; if the guest is virtual-mode then the CPL is forced to 3
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x00D0) = (ia32_efer & ~(1ULL << 0x0C)); // EFER
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x00D0) = ia32_efer;                     // EFER
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x00E0) = 0;                             // PERF_CTL0
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x00E8) = 0;                             // PERF_CTR0
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x00F0) = 0;                             // PERF_CTL1
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x00F8) = 0;                             // PERF_CTR1
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0100) = 0;                             // PERF_CTL2
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0108) = 0;                             // PERF_CTR2
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0110) = 0;                             // PERF_CTL3
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0118) = 0;                             // PERF_CTR3
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0120) = 0;                             // PERF_CTL4
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0128) = 0;                             // PERF_CTR4
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0130) = 0;                             // PERF_CTL5
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0138) = 0;                             // PERF_CTR5
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0148) = CR4;                           // CR4
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0150) = CR3;                           // CR3
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0158) = CR0;                           // CR0
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0160) = 0;                             // DR7
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0168) = 0;                             // DR6
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0170) = Context.EFlags;                // RFLAGS
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0178) = Context.Rip;                   // RIP
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x01C0) = 0;                             // INSTR_RETIRED_CTR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x01C8) = 0;                             // PERF_CTR_GLOBAL_STS
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x01D0) = 0;                             // PERF_CTR_GLOBAL_CTL
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x01D8) = Context.Rsp;                   // RSP
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x01E0) = 0;                             // S_CET
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x01E8) = 0;                             // SSP
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x01F0) = 0;                             // ISST_ADDR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x01F8) = 1;                             // RAX

    // *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0200) = ia32_star;                     // STAR
    // *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0208) = ia32_lstar;                    // LSTAR
    // *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0210) = ia32_cstar;                    // CSTAR
    // *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0218) = 0;                             // SFMASK
    // *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0220) = ia32_kernel_gs_base;           // KernelGsBase
    // *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0228) = ia32_sysenter_cs;              // SYSENTER_CS
    // *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0230) = ia32_sysenter_esp;             // SYSENTER_ESP
    // *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0238) = ia32_sysenter_eip;             // SYSENTER_EIP

    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0240) = CR2;           // CR2
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0268) = 0;             // G_PAT Guest PAT - only used if nested paging enabled
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0270) = ia32_debugctl; // DBGCTL Guest DebugCtl MSR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0278) = 0;             // BR_FROM Guest LastBranchFromIP MSR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0280) = 0;             // BR_TO Guest LastBranchToIP MSR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0288) = 0;             // LASTEXCPFROM Guest LastIntFromIP MSR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0290) = 0;             // LASTEXCPTO Guest LastIntToIP MSR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0298) = 0;             // DBGEXTNCTL Guest DebugExtnCtl MSR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x02E0) = 0;             // SPEC_CTRL
    *(uint8_t*)((uint8_t*)vmcb + 0x400 + 0x0670) = 0;              // 256 bytes LBR_STACK_FROM LBR_STACK_TO
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0770) = 0;             // LBR_SELECT
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0778) = 0;             // IBS_FETCH_CTL
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0780) = 0;             // IBS_FETCH_LINADDR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0788) = 0;             // IBS_OP_CTL
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0790) = 0;             // IBS_OP_RIP
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x0798) = 0;             // IBS_OP_DATA
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x07A0) = 0;             // IBS_OP_DATA2
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x07A8) = 0;             // IBS_OP_DATA3
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x07B0) = 0;             // IBS_DC_LINADDR
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x07B8) = 0;             // BP_IBSTGT_RIP
    *(uint64_t*)((uint8_t*)vmcb + 0x400 + 0x07C0) = 0;             // IC_IBS_EXTD_CTL

    __asm_wrmsr(0xC0010117, hostPa.QuadPart);

    KdBreakPoint();

    Context.Rip = 0x12345678;

    __asm_svm_vmsave(guestPa.QuadPart);
    __asm_svm_vmsave(hostPa.QuadPart);

    __asm_svm_clgi();
    while (1) {
        // __asm_svm_vmrun(guestPa.QuadPart);

        __asm__ __volatile__("\n vmrun" ::"a"(guestPa.QuadPart) : "memory");

        int64_t EXITCODE = *(int64_t*)((uint8_t*)vmcb + 0x0070);      // EXITCODE
        uint64_t EXITINFO1 = *(uint64_t*)((uint8_t*)vmcb + 0x0078);   // EXITINFO1
        uint64_t EXITINFO2 = *(uint64_t*)((uint8_t*)vmcb + 0x0080);   // EXITINFO2
        uint64_t EXITINTINFO = *(uint64_t*)((uint8_t*)vmcb + 0x0088); // EXITINTINFO

        if (EXITCODE < 0)
            break;

        Procedures[EXITCODE]();

        UNREFERENCED_PARAMETER(EXITCODE);
        UNREFERENCED_PARAMETER(EXITINFO1);
        UNREFERENCED_PARAMETER(EXITINFO2);
        UNREFERENCED_PARAMETER(EXITINTINFO);
    }
    __asm_svm_stgi();

    return 0;
}

template <>
int
cleanup<Hash("AuthenticAMD")>(PVOID vcpu)
{
    return 0;
}
