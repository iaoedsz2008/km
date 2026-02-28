
/**
 * 用户为本，科技向善
 **/

#if !defined(__3a1c6fd0f7b982d2d5718381b6ebc2dc__)
#define __3a1c6fd0f7b982d2d5718381b6ebc2dc__

#include <ntifs.h>

#include <ntddk.h>

#include "Support.h"

template <size_t>
PVOID allocate();

template <size_t>
void deallocate(PVOID Mem);

template <size_t T>
int initialize(PVOID);

template <size_t T>
int cleanup(PVOID);

#endif // !__3a1c6fd0f7b982d2d5718381b6ebc2dc__
