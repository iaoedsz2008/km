
/**
 * 用户为本，科技向善
 **/

#if !defined(__30e198a17ac6cb6863df7abc4772b825__)
#define __30e198a17ac6cb6863df7abc4772b825__

#if defined(_WIN32)

#if defined(_KERNEL_MODE)

class lfqueue {
  public:
    explicit lfqueue(size_t capacity) :
        sequence_(nullptr),
        data_(nullptr),
        mask_(capacity - 1),
        enqueue_pos_(0),
        dequeue_pos_(0)
    {
        if (capacity == 0 || (capacity & (capacity - 1)) != 0) {
            return;
        }
        sequence_ = static_cast<volatile LONG64*>(ExAllocatePool(NonPagedPool, sizeof(LONG64) * capacity));
        data_ = static_cast<PVOID*>(ExAllocatePool(NonPagedPool, sizeof(PVOID*) * capacity));
        if (!sequence_ || !data_) {
            if (sequence_) {
                ExFreePool(const_cast<LONG64*>(sequence_));
                sequence_ = nullptr;
            }
            if (data_) {
                ExFreePool(data_);
                data_ = nullptr;
            }
            return;
        }
        for (size_t i = 0; i < capacity; ++i) {
            sequence_[i] = static_cast<LONG64>(i);
            data_[i] = nullptr;
        }
    }

    ~lfqueue()
    {
        if (sequence_) {
            ExFreePool(const_cast<LONG64*>(sequence_));
            sequence_ = nullptr;
        }
        if (data_) {
            ExFreePool(data_);
            data_ = nullptr;
        }
    }

    lfqueue(const lfqueue&) = delete;

    lfqueue& operator=(const lfqueue&) = delete;

    bool
    push(PVOID e)
    {
        LONG64 pos = ReadNoFence64(&enqueue_pos_);
        for (;;) {
            size_t index = static_cast<size_t>(pos) & mask_;
            const LONG64 seq = InterlockedCompareExchange64(&sequence_[index], 0, 0);
            LONG64 dif = seq - pos;
            if (dif == 0) {
                LONG64 old = InterlockedCompareExchange64(&enqueue_pos_, pos + 1, pos);
                if (old == pos) {
                    data_[index] = e;
                    InterlockedExchange64(const_cast<LONG64*>(&sequence_[index]), pos + 1);
                    return true;
                }
                pos = old;
            } else if (dif < 0) {
                return false;
            } else {
                pos = ReadNoFence64(&enqueue_pos_);
            }
        }
    }

    PVOID
    pop()
    {
        LONG64 pos = ReadNoFence64(&dequeue_pos_);
        for (;;) {
            size_t index = static_cast<size_t>(pos) & mask_;
            const LONG64 seq = InterlockedCompareExchange64(&sequence_[index], 0, 0);
            LONG64 dif = seq - (pos + 1);
            if (dif == 0) {
                LONG64 old = InterlockedCompareExchange64(&dequeue_pos_, pos + 1, pos);
                if (old == pos) {
                    PVOID e = data_[index];
                    InterlockedExchange64(const_cast<LONG64*>(&sequence_[index]), pos + mask_ + 1);
                    return e;
                }
                pos = old;
            } else if (dif < 0) {
                return nullptr;
            } else {
                pos = ReadNoFence64(&dequeue_pos_);
            }
        }
    }

  private:
    volatile LONG64* sequence_;
    PVOID* data_;

    size_t mask_;

    __declspec(align(64)) volatile LONG64 enqueue_pos_;
    __declspec(align(64)) volatile LONG64 dequeue_pos_;
};

#else

class lfqueue {
  public:
    explicit lfqueue(size_t capacity) :
        sequence_(new std::atomic<size_t>[capacity]),
        data_(new PVOID*[capacity]),
        mask_(capacity - 1),
        enqueue_pos_(0),
        dequeue_pos_(0)
    {
        for (size_t i = 0; i < capacity; ++i) {
            sequence_[i].store(i, std::memory_order_relaxed);
            data_[i] = nullptr;
        }
    }

    lfqueue(const lfqueue&) = delete;

    lfqueue& operator=(const lfqueue&) = delete;

    bool
    push(PVOID* e)
    {
        size_t pos = enqueue_pos_.load(std::memory_order_relaxed);
        for (;;) {
            size_t index = pos & mask_;
            size_t seq = sequence_[index].load(std::memory_order_acquire);
            intptr_t dif = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos);
            if (dif == 0) {
                if (enqueue_pos_.compare_exchange_weak(pos, pos + 1, std::memory_order_relaxed)) {
                    data_[index] = e;
                    sequence_[index].store(pos + 1, std::memory_order_release);
                    return true;
                }
            } else if (dif < 0) {
                return false;
            } else {
                pos = enqueue_pos_.load(std::memory_order_relaxed);
            }
        }
    }

    PVOID*
    pop()
    {
        size_t pos = dequeue_pos_.load(std::memory_order_relaxed);
        for (;;) {
            size_t index = pos & mask_;
            size_t seq = sequence_[index].load(std::memory_order_acquire);
            intptr_t dif = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos + 1);
            if (dif == 0) {
                if (dequeue_pos_.compare_exchange_weak(pos, pos + 1, std::memory_order_relaxed)) {
                    PVOID* e = data_[index];
                    sequence_[index].store(pos + mask_ + 1, std::memory_order_release);
                    return e;
                }
            } else if (dif < 0) {
                return nullptr;
            } else {
                pos = dequeue_pos_.load(std::memory_order_relaxed);
            }
        }
    }

  private:
    std::unique_ptr<std::atomic<size_t>[]> sequence_;
    std::unique_ptr<PVOID*[]> data_;

    size_t mask_;

    alignas(64) std::atomic<size_t> enqueue_pos_;
    alignas(64) std::atomic<size_t> dequeue_pos_;
};

#endif

#endif

#endif // !__30e198a17ac6cb6863df7abc4772b825__
