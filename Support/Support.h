
/**
 * 用户为本，科技向善
 **/

#if !defined(__d51ea43e6e0790432a424e5b22f82ddd__)
#define __d51ea43e6e0790432a424e5b22f82ddd__

typedef INT8 int8_t;
typedef INT16 int16_t;
typedef INT32 int32_t;
typedef INT64 int64_t;
typedef UINT8 uint8_t;
typedef UINT16 uint16_t;
typedef UINT32 uint32_t;
typedef UINT64 uint64_t;
typedef LONG_PTR intptr_t;
typedef LONG_PTR ssize_t;
typedef ULONG_PTR uintptr_t;
typedef ULONG_PTR size_t;

#include "StringHash.h"

#if defined(__clang__) || defined(__GNUC__)

static inline void
__asm_cli(void)
{
    __asm__ __volatile__("cli" ::: "memory");
}

static inline void
__asm_sti(void)
{
    __asm__ __volatile__("sti" ::: "memory");
}

static inline void
__asm_cpuid(uint32_t leaf, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx)
{
    __asm__ __volatile__("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(leaf));
}

static inline void
__asm_cpuid_ex(uint32_t leaf, uint32_t subleaf, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx)
{
    __asm__ __volatile__("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(leaf), "c"(subleaf));
}

#if defined(__x86_64__)

static inline uint64_t
__asm_cr0(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%cr0, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr0(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%cr0" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_cr2(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%cr2, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr2(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%cr2" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_cr3(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%cr3, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr3(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%cr3" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_cr4(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%cr4, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr4(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%cr4" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_cr8(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%cr8, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr8(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%cr8" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_dr0(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%dr0, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr0(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%dr0" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_dr1(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%dr1, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr1(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%dr1" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_dr2(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%dr2, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr2(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%dr2" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_dr3(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%dr3, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr3(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%dr3" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_dr6(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%dr6, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr6(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%dr6" ::"r"(val) : "memory");
}

static inline uint64_t
__asm_dr7(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%dr7, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr7(uint64_t val)
{
    __asm__ __volatile__("mov %0, %%dr7" ::"r"(val) : "memory");
}

#else

static inline uint32_t
__asm_cr0(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%cr0, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr0(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%cr0" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_cr2(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%cr2, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr2(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%cr2" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_cr3(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%cr3, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr3(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%cr3" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_cr4(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%cr4, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr4(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%cr4" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_dr0(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%dr0, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr0(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%dr0" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_dr1(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%dr1, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr1(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%dr1" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_dr2(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%dr2, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr2(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%dr2" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_dr3(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%dr3, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr3(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%dr3" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_dr6(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%dr6, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr6(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%dr6" ::"r"(val) : "memory");
}

static inline uint32_t
__asm_dr7(void)
{
    uint32_t val;
    __asm__ __volatile__("mov %%dr7, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr7(uint32_t val)
{
    __asm__ __volatile__("mov %0, %%dr7" ::"r"(val) : "memory");
}

#endif

static inline uint16_t
__asm_cs(void)
{
    uint16_t val;
    __asm__ __volatile__("mov %%cs, %0" : "=r"(val));
    return val;
}

static inline uint16_t
__asm_ds(void)
{
    uint16_t val;
    __asm__ __volatile__("mov %%ds, %0" : "=r"(val));
    return val;
}

static inline void
__asm_ds(uint16_t val)
{
    __asm__ __volatile__("mov %0, %%ds" ::"r"(val) : "memory");
}

static inline uint16_t
__asm_es(void)
{
    uint16_t val;
    __asm__ __volatile__("mov %%es, %0" : "=r"(val));
    return val;
}

static inline void
__asm_es(uint16_t val)
{
    __asm__ __volatile__("mov %0, %%es" ::"r"(val) : "memory");
}

static inline uint16_t
__asm_fs(void)
{
    uint16_t val;
    __asm__ __volatile__("mov %%fs, %0" : "=r"(val));
    return val;
}

static inline void
__asm_fs(uint16_t val)
{
    __asm__ __volatile__("mov %0, %%fs" ::"r"(val) : "memory");
}

static inline uint16_t
__asm_gs(void)
{
    uint16_t val;
    __asm__ __volatile__("mov %%gs, %0" : "=r"(val));
    return val;
}

static inline void
__asm_gs(uint16_t val)
{
    __asm__ __volatile__("mov %0, %%gs" ::"r"(val) : "memory");
}

static inline uint16_t
__asm_ss(void)
{
    uint16_t val;
    __asm__ __volatile__("mov %%ss, %0" : "=r"(val));
    return val;
}

static inline void
__asm_ss(uint16_t val)
{
    __asm__ __volatile__("mov %0, %%ss" ::"r"(val) : "memory");
}

#if defined(__x86_64__)

static inline uint64_t
__asm_eflags(void)
{
    uint64_t val;
    __asm__ __volatile__("\n pushfq;"
                         "\n pop %0"
                         : "=r"(val));
    return val;
}

static inline uint64_t
__asm_rflags(void)
{
    uint64_t val;
    __asm__ __volatile__("\n pushfq;"
                         "\n pop %0"
                         : "=r"(val));
    return val;
}

static inline uint64_t
__asm_rip(void)
{
    uint64_t val;
    __asm__ __volatile__("lea (%%rip), %0" : "=r"(val));
    return val;
}

static inline uint64_t
__asm_rsp(void)
{
    uint64_t val;
    __asm__ __volatile__("mov %%rsp, %0" : "=r"(val));
    return val;
}

#else

static inline uint32_t
__asm_eflags(void)
{
    uint32_t val;
    __asm__ __volatile__("\n pushfl;"
                         "\n pop %0"
                         : "=r"(val));
    return val;
}

#endif

static inline void
__asm_int3(void)
{
    __asm__ __volatile__("int3");
}

static inline uint32_t
__asm_lar(uint16_t selector)
{
    uint32_t val;
    __asm__ __volatile__("lar %1, %0" : "=r"(val) : "r"(selector));
    return val;
}

typedef struct {
    uint16_t limit;
    void* base;
} __attribute__((packed)) descriptor_table_t;

static inline void
__asm_lgdt(const descriptor_table_t* gdt)
{
    __asm__ __volatile__("lgdt %0" ::"m"(*gdt) : "memory");
}

static inline void
__asm_sgdt(descriptor_table_t* gdt)
{
    __asm__ __volatile__("sgdt %0" : "=m"(*gdt));
}

static inline void
__asm_lidt(const descriptor_table_t* idt)
{
    __asm__ __volatile__("lidt %0" ::"m"(*idt) : "memory");
}

static inline void
__asm_sidt(descriptor_table_t* idt)
{
    __asm__ __volatile__("sidt %0" : "=m"(*idt));
}

static inline void
__asm_lldt(uint16_t selector)
{
    __asm__ __volatile__("lldt %0" ::"r"(selector) : "memory");
}

static inline uint16_t
__asm_sldt(void)
{
    uint16_t val;
    __asm__ __volatile__("sldt %0" : "=r"(val));
    return val;
}

static inline uint32_t
__asm_lsl(uint16_t selector)
{
    uint32_t val;
    __asm__ __volatile__("lsl %1, %0" : "=r"(val) : "r"(selector));
    return val;
}

static inline void
__asm_ltr(uint16_t selector)
{
    __asm__ __volatile__("ltr %0" ::"r"(selector) : "memory");
}

static inline uint64_t
__asm_rdmsr(uint32_t msr)
{
    uint32_t low, high;
    __asm__ __volatile__("rdmsr" : "=a"(low), "=d"(high) : "c"(msr));
    return ((uint64_t)high << 32) | low;
}

static inline void
__asm_wrmsr(uint32_t msr, uint64_t value)
{
    uint32_t low = value & 0xFFFFFFFF;
    uint32_t high = value >> 32;
    __asm__ __volatile__("wrmsr" ::"a"(low), "d"(high), "c"(msr) : "memory");
}

#if defined(__x86_64__)
static inline uint64_t
__asm_rdpid(void)
{
    uint64_t val;
    __asm__ __volatile__("rdpid %0" : "=r"(val));
    return val;
}

#else

static inline uint32_t
__asm_rdpid(void)
{
    uint32_t val;
    __asm__ __volatile__("rdpid %0" : "=r"(val));
    return val;
}

#endif

static inline uint64_t
__asm_rdpmc(uint32_t counter)
{
    uint32_t low, high;
    __asm__ __volatile__("rdpmc" : "=a"(low), "=d"(high) : "c"(counter));
    return ((uint64_t)high << 32) | low;
}

static inline uint64_t
__asm_rdtsc(void)
{
    uint32_t low, high;
    __asm__ __volatile__("rdtsc" : "=a"(low), "=d"(high));
    return ((uint64_t)high << 32) | low;
}

static inline uint64_t
__asm_rdtscp(uint32_t* aux)
{
    uint32_t low, high;
    __asm__ __volatile__("rdtscp" : "=a"(low), "=d"(high), "=c"(*aux));
    return ((uint64_t)high << 32) | low;
}

static inline uint16_t
__asm_str(void)
{
    uint16_t val;
    __asm__ __volatile__("str %0" : "=r"(val));
    return val;
}

static inline void
__asm_svm_clgi(void)
{
    __asm__ __volatile__("clgi" ::: "memory");
}

static inline void
__asm_svm_stgi(void)
{
    __asm__ __volatile__("stgi" ::: "memory");
}

#if defined(__x86_64__)
static inline void
__asm_svm_vmload(uint64_t vmcb_pa)
{
    __asm__ __volatile__("vmload %%rax" ::"a"(vmcb_pa) : "memory");
}

static inline void
__asm_svm_vmrun(uint64_t vmcb_pa)
{
    __asm__ __volatile__("vmrun %%rax" ::"a"(vmcb_pa) : "memory");
}

static inline void
__asm_svm_vmsave(uint64_t vmcb_pa)
{
    __asm__ __volatile__("vmsave %%rax" ::"a"(vmcb_pa) : "memory");
}

#else

static inline void
__asm_svm_vmload(uint32_t vmcb_pa)
{
    __asm__ __volatile__("vmload %%eax" ::"a"(vmcb_pa) : "memory");
}

static inline void
__asm_svm_vmrun(uint32_t vmcb_pa)
{
    __asm__ __volatile__("vmrun %%eax" ::"a"(vmcb_pa) : "memory");
}

static inline void
__asm_svm_vmsave(uint32_t vmcb_pa)
{
    __asm__ __volatile__("vmsave %%eax" ::"a"(vmcb_pa) : "memory");
}

#endif

#if defined(__x86_64__)

static inline uint8_t
__asm_vmx_invept(uint64_t type, const void* descriptor)
{
    uint8_t error;
    __asm__ __volatile__("\n invept %1, %2;"
                         "\n setna %0"
                         : "=q"(error)
                         : "m"(*(const uint64_t*)descriptor), "r"(type)
                         : "cc", "memory");
    return error;
}

static inline uint8_t
__asm_vmx_invvpid(uint64_t type, const void* descriptor)
{
    uint8_t error;
    __asm__ __volatile__("\n invvpid %1, %2;"
                         "\n setna %0"
                         : "=q"(error)
                         : "m"(*(const uint64_t*)descriptor), "r"(type)
                         : "cc", "memory");
    return error;
}
#endif

static inline void
__asm_vmx_vmcall(void)
{
    __asm__ __volatile__("vmcall" ::: "memory");
}

#if defined(__x86_64__)

static inline uint8_t
__asm_vmx_vmclear(uint64_t* vmcs_pa)
{
    uint8_t error;
    __asm__ __volatile__("\n vmclear %1;"
                         "\n setna %0"
                         : "=q"(error)
                         : "m"(*vmcs_pa)
                         : "cc", "memory");
    return error;
}

#else

static inline uint8_t
__asm_vmx_vmclear(uint32_t* vmcs_pa)
{
    uint8_t error;
    __asm__ __volatile__("\n vmclear %1;"
                         "\n setna %0"
                         : "=q"(error)
                         : "m"(*vmcs_pa)
                         : "cc", "memory");
    return error;
}

#endif

static inline void
__asm_vmx_vmfunc(void)
{
    __asm__ __volatile__("vmfunc" ::: "memory");
}

static inline uint8_t
__asm_vmx_vmlaunch(void)
{
    uint8_t error;
    __asm__ __volatile__("\n vmlaunch;"
                         "\n setna %0"
                         : "=q"(error)::"cc", "memory");
    return error;
}

#if defined(__x86_64__)

static inline uint8_t
__asm_vmx_vmptrld(uint64_t* vmcs_pa)
{
    uint8_t error;
    __asm__ __volatile__("\n vmptrld %1;"
                         "\n setna %0"
                         : "=q"(error)
                         : "m"(*vmcs_pa)
                         : "cc", "memory");
    return error;
}

static inline uint8_t
__asm_vmx_vmptrst(uint64_t* vmcs_pa)
{
    uint8_t error;
    __asm__ __volatile__("\n vmptrst %1;"
                         "\n setna %0"
                         : "=q"(error), "=m"(*vmcs_pa)::"cc", "memory");
    return error;
}

static inline uint8_t
__asm_vmx_vmread(uint64_t field, uint64_t* value)
{
    uint8_t error;
    __asm__ __volatile__("\n vmread %2, %1;"
                         "\n setna %0"
                         : "=q"(error), "=r"(*value)
                         : "r"(field)
                         : "cc");
    return error;
}

#else

static inline uint8_t
__asm_vmx_vmptrld(uint32_t* vmcs_pa)
{
    uint8_t error;
    __asm__ __volatile__("\n vmptrld %1;"
                         "\n setna %0"
                         : "=q"(error)
                         : "m"(*vmcs_pa)
                         : "cc", "memory");
    return error;
}

static inline uint8_t
__asm_vmx_vmptrst(uint32_t* vmcs_pa)
{
    uint8_t error;
    __asm__ __volatile__("\n vmptrst %1;"
                         "\n setna %0"
                         : "=q"(error), "=m"(*vmcs_pa)::"cc", "memory");
    return error;
}

static inline uint8_t
__asm_vmx_vmread(uint32_t field, uint32_t* value)
{
    uint8_t error;
    __asm__ __volatile__("\n vmread %2, %1;"
                         "\n setna %0"
                         : "=q"(error), "=r"(*value)
                         : "r"(field)
                         : "cc");
    return error;
}

#endif

static inline uint8_t
__asm_vmx_vmresume(void)
{
    uint8_t error;
    __asm__ __volatile__("\n vmresume;"
                         "\n setna %0"
                         : "=q"(error)::"cc", "memory");
    return error;
}

#if defined(__x86_64__)

static inline uint8_t
__asm_vmx_vmwrite(uint64_t field, uint64_t value)
{
    uint8_t error;
    __asm__ __volatile__("\n vmwrite %2, %1;"
                         "\n setna %0"
                         : "=q"(error)
                         : "r"(field), "r"(value)
                         : "cc");
    return error;
}

#else

static inline uint8_t
__asm_vmx_vmwrite(uint32_t field, uint32_t value)
{
    uint8_t error;
    __asm__ __volatile__("\n vmwrite %2, %1;"
                         "\n setna %0"
                         : "=q"(error)
                         : "r"(field), "r"(value)
                         : "cc");
    return error;
}

#endif

static inline void
__asm_vmx_vmxoff(void)
{
    __asm__ __volatile__("vmxoff" ::: "memory");
}

#if defined(__x86_64__)

static inline uint8_t
__asm_vmx_vmxon(uint64_t* vmxon_pa)
{
    uint8_t error;
    __asm__ __volatile__("\n vmxon %1;"
                         "\n setna %0"
                         : "=q"(error)
                         : "m"(*vmxon_pa)
                         : "cc", "memory");
    return error;
}

#else

static inline uint8_t
__asm_vmx_vmxon(uint32_t* vmxon_pa)
{
    uint8_t error;
    __asm__ __volatile__("\n vmxon %1;"
                         "\n setna %0"
                         : "=q"(error)
                         : "m"(*vmxon_pa)
                         : "cc", "memory");
    return error;
}

#endif

#endif

#endif // !__d51ea43e6e0790432a424e5b22f82ddd__
