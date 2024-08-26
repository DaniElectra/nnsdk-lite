#pragma once

#include "helpers.h"
#include "nn/Handle.h"

namespace nn {

namespace os {

class WaitableCounter {
public:
    static Handle s_Handle;

    /// Initializes the WaitableCounter
    void Initialize();
};

class SimpleLock {
    s32 lock;

public:
    /// Initializes the SimpleLock
    void Initialize();

    /// Locks the SimpleLock
    void Lock();

    /// Unlocks the SimpleLock
    void Unlock();
};
CHECK_SIZE(SimpleLock, 0x4);

class CriticalSection {
    SimpleLock lock;
    u32 threadTag;
    u32 counter;

public:
    // UNOFFICIAL: Guess from static initializers
    CriticalSection() { Initialize(); }

    /// Initializes the CriticalSection
    void Initialize();

    /// Enters into the CriticalSection
    void Enter();

    /// Leaves the CriticalSection
    void Leave();
};
CHECK_SIZE(CriticalSection, 0xC);

}  // namespace os

}  // namespace nn
