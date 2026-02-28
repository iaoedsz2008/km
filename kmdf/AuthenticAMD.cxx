
/**
 * 用户为本，科技向善
 **/

#include "AuthenticAMD.h"

template <>
int
initialize<Hash("AuthenticAMD")>(PVOID vcpu)
{
    return 0;
}

template <>
int
cleanup<Hash("AuthenticAMD")>(PVOID vcpu)
{
    return 0;
}
