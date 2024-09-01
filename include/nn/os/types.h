#pragma once

namespace nn {

namespace os {

enum class ArbitrationType {
    Signal = 0,
    WaitIfLessThan,
    DecrementAndWaitIfLessThan,
    WaitIfLessThanTimeout,
    DecrementAndWaitIfLessThanTimeout
};

} // namespace os

} // namespace nn
