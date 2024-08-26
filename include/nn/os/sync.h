#pragma once

#include "helpers.h"
#include "nn/Handle.h"

namespace nn {

namespace os {

class WaitableCounter {
public:
    static Handle s_Handle;

    void Initialize();
};

class SimpleLock {
    s32 lock;

public:
    void Initialize();
    void Lock();
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

    void Initialize();
    void Enter();
    void Leave();
};
CHECK_SIZE(CriticalSection, 0xC);

}  // namespace os

}  // namespace nn
