
/**
 * 用户为本，科技向善
 **/

#if !defined(__d51ea43e6e0790432a424e5b22f82ddd__)
#define __d51ea43e6e0790432a424e5b22f82ddd__

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
    __asm__("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(leaf));
}

static inline void
__asm_cpuid_ex(uint32_t leaf, uint32_t subleaf, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx)
{
    __asm__("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(leaf), "c"(subleaf));
}

static inline size_t
__asm_cr0(void)
{
    size_t val;
    __asm__("mov %%cr0, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr0(size_t val)
{
    __asm__ __volatile__("mov %0, %%cr0" ::"r"(val) : "memory");
}

static inline size_t
__asm_cr1(void)
{
    size_t val;
    __asm__("mov %%cr1, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr1(size_t val)
{
    __asm__ __volatile__("mov %0, %%cr1" ::"r"(val) : "memory");
}

static inline size_t
__asm_cr2(void)
{
    size_t val;
    __asm__("mov %%cr2, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr2(size_t val)
{
    __asm__ __volatile__("mov %0, %%cr2" ::"r"(val) : "memory");
}

static inline size_t
__asm_cr3(void)
{
    size_t val;
    __asm__("mov %%cr3, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr3(size_t val)
{
    __asm__ __volatile__("mov %0, %%cr3" ::"r"(val) : "memory");
}

static inline size_t
__asm_cr4(void)
{
    size_t val;
    __asm__("mov %%cr4, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr4(size_t val)
{
    __asm__ __volatile__("mov %0, %%cr4" ::"r"(val) : "memory");
}

static inline size_t
__asm_cr8(void)
{
    size_t val;
    __asm__("mov %%cr8, %0" : "=r"(val));
    return val;
}

static inline void
__asm_cr8(size_t val)
{
    __asm__ __volatile__("mov %0, %%cr8" ::"r"(val) : "memory");
}

static inline size_t
__asm_dr0(void)
{
    size_t val;
    __asm__("mov %%dr0, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr0(size_t val)
{
    __asm__ __volatile__("mov %0, %%dr0" ::"r"(val) : "memory");
}

static inline size_t
__asm_dr1(void)
{
    size_t val;
    __asm__("mov %%dr1, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr1(size_t val)
{
    __asm__ __volatile__("mov %0, %%dr1" ::"r"(val) : "memory");
}

static inline size_t
__asm_dr2(void)
{
    size_t val;
    __asm__("mov %%dr2, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr2(size_t val)
{
    __asm__ __volatile__("mov %0, %%dr2" ::"r"(val) : "memory");
}

static inline size_t
__asm_dr3(void)
{
    size_t val;
    __asm__("mov %%dr3, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr3(size_t val)
{
    __asm__ __volatile__("mov %0, %%dr3" ::"r"(val) : "memory");
}

static inline size_t
__asm_dr6(void)
{
    size_t val;
    __asm__("mov %%dr6, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr6(size_t val)
{
    __asm__ __volatile__("mov %0, %%dr6" ::"r"(val) : "memory");
}

static inline size_t
__asm_dr7(void)
{
    size_t val;
    __asm__("mov %%dr7, %0" : "=r"(val));
    return val;
}

static inline void
__asm_dr7(size_t val)
{
    __asm__ __volatile__("mov %0, %%dr7" ::"r"(val) : "memory");
}

static inline uint16_t
__asm_cs(void)
{
    uint16_t val;
    __asm__("mov %%cs, %0" : "=r"(val));
    return val;
}

static inline uint16_t
__asm_ds(void)
{
    uint16_t val;
    __asm__("mov %%ds, %0" : "=r"(val));
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
    __asm__("mov %%es, %0" : "=r"(val));
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
    __asm__("mov %%fs, %0" : "=r"(val));
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
    __asm__("mov %%gs, %0" : "=r"(val));
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
    __asm__("mov %%ss, %0" : "=r"(val));
    return val;
}

static inline void
__asm_ss(uint16_t val)
{
    __asm__ __volatile__("mov %0, %%ss" ::"r"(val) : "memory");
}

static inline size_t
__asm_eflags(void)
{
    size_t val;
    __asm__("\n pushfq"
            "\n pop %0"
            : "=r"(val));
    return val;
}

static inline size_t
__asm_rflags(void)
{
    return __asm_eflags();
}

static inline void
__asm_int3(void)
{
    __asm__ __volatile__("int3");
}

typedef struct _IA32_GDT_REGISTER {
    uint16_t Limit;
    void* BaseAddress;
} __attribute__((packed)) IA32_GDT_REGISTER;
static_assert(sizeof(IA32_GDT_REGISTER) == (sizeof(uint16_t) + sizeof(size_t)), "");

typedef struct _IA32_IDT_REGISTER {
    uint16_t Limit;
    void* BaseAddress;
} __attribute__((packed)) IA32_IDT_REGISTER;
static_assert(sizeof(IA32_IDT_REGISTER) == (sizeof(uint16_t) + sizeof(size_t)), "");

static inline void
__asm_lgdt(const IA32_GDT_REGISTER* gdt)
{
    __asm__ __volatile__("lgdt %0" ::"m"(*gdt) : "memory");
}

static inline void
__asm_sgdt(IA32_GDT_REGISTER* gdt)
{
    __asm__ __volatile__("sgdt %0" : "=m"(*gdt));
}

static inline void
__asm_lidt(const IA32_IDT_REGISTER* idt)
{
    __asm__ __volatile__("lidt %0" ::"m"(*idt) : "memory");
}

static inline void
__asm_sidt(IA32_IDT_REGISTER* idt)
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
    __asm__("sldt %0" : "=r"(val));
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

static inline uint16_t
__asm_str(void)
{
    uint16_t val;
    __asm__("str %0" : "=r"(val));
    return val;
}

static inline uint64_t
__asm_rdmsr(uint32_t msr)
{
    uint64_t val;
    uint32_t* p = (uint32_t*)&val;
    __asm__("rdmsr" : "=a"(p[0]), "=d"(p[1]) : "c"(msr));
    return val;
}

static inline void
__asm_wrmsr(uint32_t msr, uint64_t value)
{
    uint32_t* p = (uint32_t*)&value;
    __asm__ __volatile__("wrmsr" ::"a"(p[0]), "d"(p[1]), "c"(msr) : "memory");
}

static inline size_t
__asm_rdpid(void)
{
    size_t val;
    __asm__("rdpid %0" : "=r"(val));
    return val;
}

static inline uint64_t
__asm_rdpmc(uint32_t counter)
{
    uint64_t val;
    uint32_t* p = (uint32_t*)&val;
    __asm__ __volatile__("rdpmc" : "=a"(p[0]), "=d"(p[1]) : "c"(counter));
    return val;
}

static inline uint64_t
__asm_rdtsc(void)
{
    uint64_t val;
    uint32_t* p = (uint32_t*)&val;
    __asm__("rdtsc" : "=a"(p[0]), "=d"(p[1]));
    return val;
}

static inline uint64_t
__asm_rdtscp(uint32_t* aux)
{
    uint64_t val;
    uint32_t* p = (uint32_t*)&val;
    __asm__("rdtscp" : "=a"(p[0]), "=d"(p[1]), "=c"(*aux));
    return val;
}

#endif

#endif // !__d51ea43e6e0790432a424e5b22f82ddd__
