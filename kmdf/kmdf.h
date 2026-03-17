
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
