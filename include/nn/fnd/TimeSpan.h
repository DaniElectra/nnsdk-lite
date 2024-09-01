#pragma once

#include "helpers.h"
#include "nn/types.h"

namespace nn {

namespace fnd {

// UNOFFICIAL: The constructors and operators may not be accurate
class TimeSpan {
    s64 value;

public:
    TimeSpan() {}
    TimeSpan(s64 val) : value(val) {}

    operator s64() { return value; }
};
CHECK_SIZE(TimeSpan, 8);

} // namespace fnd

} // namespace nn
