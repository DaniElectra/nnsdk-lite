#pragma once

#include "nn/Result.h"
#include "nn/fnd/TimeSpan.h"
#include "nn/types.h"

namespace nn {

namespace os {

// UNOFFICIAL: The official name for this is unknown, and may not belong in this namespace

/**
 * @brief Gets the Thread Local Storage
 * @return Pointer to the Thread Local Storage
 */
void *getThreadLocalStorage();

class Thread {
public:
    /**
     * @brief Sleeps the current thread for a given timespan
     * @param timespan Timespan for which the thread will sleep
     */
    static nn::Result SleepImpl(nn::fnd::TimeSpan timespan);
};

} // namespace os

} // namespace nn
