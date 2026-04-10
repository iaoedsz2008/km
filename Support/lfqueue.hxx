
/**
 * 用户为本，科技向善
 **/

#if !defined(__30e198a17ac6cb6863df7abc4772b825__)
#define __30e198a17ac6cb6863df7abc4772b825__

class lfqueue2 {
  public:
    lfqueue2() :
        Head{},
        Tail{}
    {
    }

    ~lfqueue2()
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

class lfqueue {
  public:
    lfqueue()
    {
        Head = NULL;
        Tail = NULL;
    }

    ~lfqueue()
    {
    }

    inline void
    push(PVOID Block)
    {
        LIST_ENTRY* Old = NULL;

        do {
            Old = static_cast<LIST_ENTRY*>(InterlockedCompareExchangePointer((PVOID*)&Head, NULL, NULL));
            static_cast<LIST_ENTRY*>(Block)->Flink = Old;
            static_cast<LIST_ENTRY*>(Block)->Blink = NULL;
        } while (InterlockedCompareExchangePointer((PVOID*)&Head, Block, Old) != Old);

        if (Old)
            Old->Blink = static_cast<LIST_ENTRY*>(Block);

        InterlockedCompareExchangePointer((PVOID*)&Tail, Block, NULL);
    }

    inline PVOID
    pop()
    {
        LIST_ENTRY* Old = NULL;

        do {
            Old = static_cast<LIST_ENTRY*>(InterlockedCompareExchangePointer((PVOID*)&Tail, NULL, NULL));
            if (Old == NULL)
                break;
        } while (InterlockedCompareExchangePointer((PVOID*)&Tail, Old->Blink, Old) != Old);

#if defined(_DEBUG) // 不存在从Tail往后遍历的情况,所以不清零也是可以的.
        if (Old && Old->Blink)
            Old->Blink->Flink = NULL;
#endif

        InterlockedCompareExchangePointer((PVOID*)&Head, NULL, Old);

        return Old;
    }

  private:
    LIST_ENTRY* Head;
    LIST_ENTRY* Tail;
};

#endif // !__30e198a17ac6cb6863df7abc4772b825__
