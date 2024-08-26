#include "nn/os/sync.h"
#include "nn/os/thread.h"
#include "nn/os/types.h"
#include "nn/svc/svc.h"
#include "nn/types.h"

namespace nn {

namespace os {

// Imported from https://github.com/devkitPro/libctru/blob/master/libctru/source/synchronization.c

/// Performs a Data Synchronization Barrier operation.
static inline void __dsb() {
    __asm__ __volatile__("mcr p15, 0, %[val], c7, c10, 4" ::[val] "r"(0) : "memory");
}

/// Performs a Data Memory Barrier operation.
static inline void __dmb() {
    __asm__ __volatile__("mcr p15, 0, %[val], c7, c10, 5" ::[val] "r"(0) : "memory");
}

/// Performs an Instruction Synchronization Barrier (officially "flush prefetch buffer") operation.
static inline void __isb() {
    __asm__ __volatile__("mcr p15, 0, %[val], c7, c5, 4" ::[val] "r"(0) : "memory");
}

/// Performs a clrex operation.
static inline void __clrex() {
    __asm__ __volatile__("clrex" ::: "memory");
}

/**
 * @brief Performs a ldrex operation.
 * @param addr Address to perform the operation on.
 * @return The resulting value.
 */
static inline s32 __ldrex(s32* addr) {
    s32 val;
    __asm__ __volatile__("ldrex %[val], %[addr]" : [val] "=r"(val) : [addr] "Q"(*addr));
    return val;
}

/**
 * @brief Performs a strex operation.
 * @param addr Address to perform the operation on.
 * @param val Value to store.
 * @return Whether the operation was successful.
 */
static inline bool __strex(s32* addr, s32 val) {
    bool res;
    __asm__ __volatile__("strex %[res], %[val], %[addr]" : [res] "=&r"(res) : [val] "r"(val), [addr] "Q"(*addr));
    return res;
}

void WaitableCounter::Initialize() {
    Handle arbiter;
    if (nn::svc::CreateAddressArbiter(&arbiter)) {
        s_Handle = arbiter;
    }
}

void SimpleLock::Initialize() {
    do
        __ldrex(&lock);
    while (__strex(&lock, 1));
}

void SimpleLock::Lock() {
    s32 val;
    bool bAlreadyLocked;

    // Try to lock, or if that's not possible, increment the number of waiting threads
    do {
        // Read the current lock state
        val = __ldrex(&lock);
        if (val == 0)
            val = 1;  // 0 is an invalid state - treat it as 1 (unlocked)
        bAlreadyLocked = val < 0;

        // Calculate the desired next state of the lock
        if (!bAlreadyLocked)
            val = -val;  // transition into locked state
        else
            --val;  // increment the number of waiting threads (which has the sign reversed during locked state)
    } while (__strex(&lock, val));

    // While the lock is held by a different thread:
    while (bAlreadyLocked) {
        // Wait for the lock holder thread to wake us up
        nn::svc::ArbitrateAddress(WaitableCounter::s_Handle, reinterpret_cast<u32>(&lock), ArbitrationType::WaitIfLessThan, 0, 0);

        // Try to lock again
        do {
            // Read the current lock state
            val = __ldrex(&lock);
            bAlreadyLocked = val < 0;

            // Calculate the desired next state of the lock
            if (!bAlreadyLocked)
                val = -(val - 1);  // decrement the number of waiting threads *and* transition into locked state
            else {
                // Since the lock is still held, we need to cancel the atomic update and wait again
                __clrex();
                break;
            }
        } while (__strex(&lock, val));
    }

    __dmb();
}

void SimpleLock::Unlock() {
    __dmb();

    s32 val;
    do
        val = -__ldrex(&lock);
    while (__strex(&lock, val));

    if (val > 1)
        // Wake up exactly one thread
        nn::svc::ArbitrateAddress(WaitableCounter::s_Handle, reinterpret_cast<u32>(&lock), ArbitrationType::Signal, 1, 0);
}

void CriticalSection::Initialize() {
    lock.Initialize();
    threadTag = 0;
    counter = 0;
}

void CriticalSection::Enter() {
    u32 tag = reinterpret_cast<u32>(getThreadLocalStorage());
    if (threadTag != tag) {
        lock.Lock();
        threadTag = tag;
    }

    counter++;
}

void CriticalSection::Leave() {
    if (!--counter) {
        threadTag = 0;
        lock.Unlock();
    }
}

}  // namespace os

}  // namespace nn
