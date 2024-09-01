#include "nn/os/thread.h"
#include "nn/svc/svc.h"

namespace nn {

namespace os {

void *getThreadLocalStorage() {
    void *ret;
    asm("mrc p15, 0, %[data], c13, c0, 3" : [data] "=r"(ret));
    return ret;
}

nn::Result Thread::SleepImpl(nn::fnd::TimeSpan timespan) {
    return nn::svc::SleepThread(timespan);
}

} // namespace os

} // namespace nn
