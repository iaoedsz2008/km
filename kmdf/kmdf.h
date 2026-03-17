
/**
 * 用户为本，科技向善
 **/

#if !defined(__3a1c6fd0f7b982d2d5718381b6ebc2dc__)
#define __3a1c6fd0f7b982d2d5718381b6ebc2dc__

#include <ntifs.h>

#include <ntddk.h>

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

template <size_t>
static inline size_t CalculatePTEs(size_t PhysicalSize);
template <size_t>
static inline size_t CalculatePDEs(size_t PhysicalSize);
template <size_t>
static inline size_t CalculatePDPTEs(size_t PhysicalSize);
template <size_t>
static inline size_t CalculatePML4Es(size_t PhysicalSize);
template <size_t>
static inline size_t CalculatePML5Es(size_t PhysicalSize);

template <>
inline size_t
CalculatePTEs<0x1000>(size_t PhysicalSize)
{
    return (PhysicalSize + 0xFFF) >> 12;
}

template <>
inline size_t
CalculatePDEs<0x1000>(size_t PhysicalSize)
{
    return (CalculatePTEs<0x1000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
inline size_t
CalculatePDPTEs<0x1000>(size_t PhysicalSize)
{
    return (CalculatePDEs<0x1000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
inline size_t
CalculatePML4Es<0x1000>(size_t PhysicalSize)
{
    return (CalculatePDPTEs<0x1000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
inline size_t
CalculatePDEs<0x200000>(size_t PhysicalSize)
{
    return (PhysicalSize + 0x1FFFFF) >> 21;
}

template <>
inline size_t
CalculatePDPTEs<0x200000>(size_t PhysicalSize)
{
    return (CalculatePDEs<0x200000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
inline size_t
CalculatePML4Es<0x200000>(size_t PhysicalSize)
{
    return (CalculatePDPTEs<0x200000>(PhysicalSize) + 0x1FF) >> 9;
}

template <>
inline size_t
CalculatePDPTEs<0x40000000>(size_t PhysicalSize)
{
    return (PhysicalSize + 0x3FFFFFFF) >> 30;
}

template <>
inline size_t
CalculatePML4Es<0x40000000>(size_t PhysicalSize)
{
    return (CalculatePDPTEs<0x40000000>(PhysicalSize) + 0x1FF) >> 9;
}

template <size_t>
PVOID allocate();

template <size_t>
void deallocate(PVOID);

template <size_t>
PVOID allocateContiguous();

template <size_t>
void deallocateContiguous(PVOID);

template <size_t T>
void initialize();

template <size_t T>
int vmxon(PVOID);

template <size_t T>
int vmxoff(PVOID);

#endif // !__3a1c6fd0f7b982d2d5718381b6ebc2dc__
