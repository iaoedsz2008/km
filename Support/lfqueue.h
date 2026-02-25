
/**
 * 用户为本，科技向善
 **/

#if !defined(__30e198a17ac6cb6863df7abc4772b825__)
#define __30e198a17ac6cb6863df7abc4772b825__

#if defined(_KERNEL_MODE)

#include <ntddk.h>

class lfqueue {
  public:
    lfqueue() :
        Head{},
        Tail{}
    {
    }

    ~lfqueue()
    {
    }

    inline void
    push(PVOID* Current)
    {
        PVOID* Old = NULL;

        *Current = NULL;

        do {
            Old = static_cast<PVOID*>(InterlockedCompareExchangePointer((PVOID*)&Tail, NULL, NULL));
            if (Old)
                *Old = Current; // Old->Flink = Current;
        } while (InterlockedCompareExchangePointer((PVOID*)&Tail, Current, Old) != Old);

        InterlockedCompareExchangePointer((PVOID*)&Head, Current, NULL);
    }

    inline PVOID*
    pop()
    {
        PVOID* Old = NULL;

        do {
            Old = static_cast<PVOID*>(InterlockedCompareExchangePointer((PVOID*)&Head, NULL, NULL));
            if (Old == NULL)
                return NULL;
        } while (InterlockedCompareExchangePointer((PVOID*)&Head, *Old, Old) != Old);

#if defined(_DEBUG)
        *Old = NULL;
#endif

        InterlockedCompareExchangePointer((PVOID*)&Tail, NULL, Old);

        return Old;
    }

  private:
    PVOID* Head;
    PVOID* Tail;
};

#endif

#endif // !__30e198a17ac6cb6863df7abc4772b825__
