#pragma once

#include "nn/types.h"
#include "nn/Result.h"
#include "nn/fnd/TimeSpan.h"

namespace nn {

namespace os {

// UNOFFICIAL: The official name for this is unknown, and may not belong in this namespace
void *getThreadLocalStorage();

class Thread {
public:
    static nn::Result SleepImpl(nn::fnd::TimeSpan timespan);
};

}  // namespace os

}  // namespace nn
