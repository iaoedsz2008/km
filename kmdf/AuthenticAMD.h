
/**
 * 用户为本，科技向善
 **/

#if !defined(__72014abad6d4f5486f4748c282f475d7__)
#define __72014abad6d4f5486f4748c282f475d7__

#include "kmdf.h"

template <>
int initialize<Hash("AuthenticAMD")>(PVOID vcpu);

template <>
int cleanup<Hash("AuthenticAMD")>(PVOID vcpu);

#endif // !__72014abad6d4f5486f4748c282f475d7__
