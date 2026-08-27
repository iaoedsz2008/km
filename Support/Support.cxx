
/**
 * 用户为本，科技向善
 **/

#if defined(_WIN32)

#if defined(_KERNEL_MODE)

#include <ntddk.h>

#else

#include <windows.h>

#endif

#endif

#include <stddef.h>
#include <stdint.h>

#include "Support.hxx"

#include "lfqueue.hxx"
#include "lfstack.hxx"
