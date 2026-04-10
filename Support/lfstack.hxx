
/**
 * 用户为本，科技向善
 **/

#if !defined(__cd467977d7bbaeb1a12c8bd31d82e84f__)
#define __cd467977d7bbaeb1a12c8bd31d82e84f__

class lfstack2 {
  public:
    lfstack2() :
        Head{},
        Tail{}
    {
    }

    ~lfstack2()
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

class lfstack {
  public:
    lfstack()
    {
        Head = NULL;
    }

    ~lfstack()
    {
    }

    inline void
    push(PVOID Block)
    {
        LIST_ENTRY* Old = NULL;

        do {
            Old = static_cast<LIST_ENTRY*>(InterlockedCompareExchangePointer((PVOID*)&Head, NULL, NULL));
            static_cast<LIST_ENTRY*>(Block)->Flink = Old;
        } while (InterlockedCompareExchangePointer((PVOID*)&Head, Block, Old) != Old);
    }

    inline PVOID
    pop()
    {
        LIST_ENTRY* Old = NULL;

        do {
            Old = static_cast<LIST_ENTRY*>(InterlockedCompareExchangePointer((PVOID*)&Head, NULL, NULL));

            if (Old == NULL)
                break;
        } while (InterlockedCompareExchangePointer((PVOID*)&Head, Old->Flink, Old) != Old);

        return Old;
    }

  private:
    LIST_ENTRY* Head;
};

#endif // !__cd467977d7bbaeb1a12c8bd31d82e84f__
