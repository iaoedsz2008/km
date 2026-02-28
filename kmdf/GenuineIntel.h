
/**
 * 用户为本，科技向善
 **/

#if !defined(__398ab4fa7c7ae78c3d6413bc104aff31__)
#define __398ab4fa7c7ae78c3d6413bc104aff31__

#include "kmdf.h"

template <>
int initialize<Hash("GenuineIntel")>(PVOID vcpu);

template <>
int cleanup<Hash("GenuineIntel")>(PVOID vcpu);

#endif // !__398ab4fa7c7ae78c3d6413bc104aff31__
