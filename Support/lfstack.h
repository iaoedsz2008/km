
/**
 * 用户为本，科技向善
 **/

#if !defined(__cd467977d7bbaeb1a12c8bd31d82e84f__)
#define __cd467977d7bbaeb1a12c8bd31d82e84f__

#if defined(_KERNEL_MODE)

#include <ntddk.h>

class lfstack {
  public:
    lfstack() :
        Head{},
        Tail{}
    {
    }

    ~lfstack()
    {
    }

    inline void
    push(PVOID* Current)
    {
        PVOID* Old = NULL;

        do {
            Old = static_cast<PVOID*>(InterlockedCompareExchangePointer((PVOID*)&Tail, NULL, NULL));
            *Current = Old; // Current->Blink = Old;
        } while (InterlockedCompareExchangePointer((PVOID*)&Tail, Current, Old) != Old);

        InterlockedCompareExchangePointer((PVOID*)&Head, Current, NULL);
    }

    inline PVOID*
    pop()
    {
        PVOID* Old = NULL;

        do {
            Old = static_cast<PVOID*>(InterlockedCompareExchangePointer((PVOID*)&Tail, NULL, NULL));
            if (Old == NULL)
                return NULL;
        } while (InterlockedCompareExchangePointer((PVOID*)&Tail, *Old, Old) != Old);

#if defined(_DEBUG)
        *Old = NULL;
#endif

        InterlockedCompareExchangePointer((PVOID*)&Head, NULL, Old);

        return Old;
    }

  private:
    PVOID* Head;
    PVOID* Tail;
};

#endif

#endif // !__cd467977d7bbaeb1a12c8bd31d82e84f__
