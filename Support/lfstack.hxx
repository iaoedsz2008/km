
/**
 * 用户为本，科技向善
 **/

#if !defined(__cd467977d7bbaeb1a12c8bd31d82e84f__)
#define __cd467977d7bbaeb1a12c8bd31d82e84f__

#if defined(_WIN32)

#if defined(_KERNEL_MODE)

#endif

class lfstack {
  public:
    lfstack()
    {
        InitializeSListHead(&Head);
    }

    inline void
    push(PVOID Block)
    {
        InterlockedPushEntrySList(&Head, static_cast<PSLIST_ENTRY>(Block));
    }

    inline PVOID
    pop()
    {
        return InterlockedPopEntrySList(&Head);
    }

  private:
    SLIST_HEADER Head;
};

#endif

#endif // !__cd467977d7bbaeb1a12c8bd31d82e84f__
