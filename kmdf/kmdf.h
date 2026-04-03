
/**
 * 用户为本，科技向善
 **/

#if !defined(__3a1c6fd0f7b982d2d5718381b6ebc2dc__)
#define __3a1c6fd0f7b982d2d5718381b6ebc2dc__

#include <ntifs.h>

#include <ntddk.h>

#include <stddef.h>
#include <stdint.h>

#include "StringHash.h"
#include "Support.h"
#include "lfqueue.h"

static constexpr size_t PageTranslation = 0x200000;

template <size_t>
static FORCEINLINE size_t CalculatePTEs(size_t PhysicalSize);
template <size_t>
static FORCEINLINE size_t CalculatePDEs(size_t PhysicalSize);
template <size_t>
static FORCEINLINE size_t CalculatePDPTEs(size_t PhysicalSize);
template <size_t>
static FORCEINLINE size_t CalculatePML4Es(size_t PhysicalSize);
template <size_t>
static FORCEINLINE size_t CalculatePML5Es(size_t PhysicalSize);

template <>
FORCEINLINE size_t
CalculatePTEs<0x1000>(size_t PhysicalSize)
{
    return (PhysicalSize + 0xFFF) >> 12;
}

template <>
FORCEINLINE size_t
CalculatePDEs<0x1000>(size_t PhysicalSize)
{
    return (CalculatePTEs<0x1000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
FORCEINLINE size_t
CalculatePDPTEs<0x1000>(size_t PhysicalSize)
{
    return (CalculatePDEs<0x1000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
FORCEINLINE size_t
CalculatePML4Es<0x1000>(size_t PhysicalSize)
{
    return (CalculatePDPTEs<0x1000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
FORCEINLINE size_t
CalculatePML5Es<0x1000>(size_t PhysicalSize)
{
    return (CalculatePML4Es<0x1000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
FORCEINLINE size_t
CalculatePTEs<0x200000>(size_t)
{
    return 0;
}

template <>
FORCEINLINE size_t
CalculatePDEs<0x200000>(size_t PhysicalSize)
{
    return (PhysicalSize + 0x1FFFFF) >> 21;
}

template <>
FORCEINLINE size_t
CalculatePDPTEs<0x200000>(size_t PhysicalSize)
{
    return (CalculatePDEs<0x200000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
FORCEINLINE size_t
CalculatePML4Es<0x200000>(size_t PhysicalSize)
{
    return (CalculatePDPTEs<0x200000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
FORCEINLINE size_t
CalculatePTEs<0x40000000>(size_t)
{
    return 0;
}

template <>
FORCEINLINE size_t
CalculatePDEs<0x40000000>(size_t)
{
    return 0;
}

template <>
FORCEINLINE size_t
CalculatePDPTEs<0x40000000>(size_t PhysicalSize)
{
    return (PhysicalSize + 0x3FFFFFFF) >> 30;
}

template <>
FORCEINLINE size_t
CalculatePML4Es<0x40000000>(size_t PhysicalSize)
{
    return (CalculatePDPTEs<0x40000000>(PhysicalSize) + 0x1FF) >> 9;
}

extern lfqueue* Mem4K;
extern lfqueue* Mem8K;
extern lfqueue* Mem16K;
extern lfqueue* Mem32K;
extern lfqueue* Mem64K;

extern lfqueue* Contiguous4K;
extern lfqueue* Contiguous8K;
extern lfqueue* Contiguous16K;
extern lfqueue* Contiguous32K;

template <size_t>
FORCEINLINE PVOID allocate();

template <size_t>
FORCEINLINE void deallocate(PVOID);

template <size_t>
FORCEINLINE PVOID allocateContiguous();

template <size_t>
FORCEINLINE void deallocateContiguous(PVOID);

template <>
FORCEINLINE PVOID
allocate<0x1000>()
{
    return Mem4K->pop();
}

template <>
FORCEINLINE void
deallocate<0x1000>(PVOID Mem)
{
    Mem4K->push(Mem);
}

template <>
FORCEINLINE PVOID
allocate<0x2000>()
{
    return Mem8K->pop();
}

template <>
FORCEINLINE void
deallocate<0x2000>(PVOID Mem)
{
    Mem8K->push(Mem);
}

template <>
FORCEINLINE PVOID
allocate<0x4000>()
{
    return Mem16K->pop();
}

template <>
FORCEINLINE void
deallocate<0x4000>(PVOID Mem)
{
    Mem16K->push(Mem);
}

template <>
FORCEINLINE PVOID
allocate<0x8000>()
{
    return Mem32K->pop();
}

template <>
FORCEINLINE void
deallocate<0x8000>(PVOID Mem)
{
    Mem32K->push(Mem);
}

template <>
FORCEINLINE PVOID
allocate<0x10000>()
{
    return Mem64K->pop();
}

template <>
FORCEINLINE void
deallocate<0x10000>(PVOID Mem)
{
    Mem64K->push(Mem);
}

template <>
FORCEINLINE PVOID
allocateContiguous<0x1000>()
{
    return Contiguous4K->pop();
}

template <>
FORCEINLINE void
deallocateContiguous<0x1000>(PVOID Mem)
{
    Contiguous4K->push(Mem);
}

template <>
FORCEINLINE PVOID
allocateContiguous<0x2000>()
{
    return Contiguous8K->pop();
}

template <>
FORCEINLINE void
deallocateContiguous<0x2000>(PVOID Mem)
{
    Contiguous8K->push(Mem);
}

template <>
FORCEINLINE PVOID
allocateContiguous<0x4000>()
{
    return Contiguous16K->pop();
}

template <>
FORCEINLINE void
deallocateContiguous<0x4000>(PVOID Mem)
{
    Contiguous16K->push(Mem);
}

template <>
FORCEINLINE PVOID
allocateContiguous<0x8000>()
{
    return Contiguous32K->pop();
}

template <>
FORCEINLINE void
deallocateContiguous<0x8000>(PVOID Mem)
{
    Contiguous32K->push(Mem);
}

template <size_t T>
void initialize(size_t PhysicalSize);

template <size_t T>
int vmxon(PVOID);

template <size_t T>
int vmxoff(PVOID);

#endif // !__3a1c6fd0f7b982d2d5718381b6ebc2dc__
