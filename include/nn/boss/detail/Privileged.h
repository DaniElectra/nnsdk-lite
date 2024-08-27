#pragma once

#include "helpers.h"
#include "nn/Handle.h"

namespace nn {

namespace boss {

namespace detail {

/// Manages a privileged session with BOSS
class Privileged {
public:
    nn::Handle session;
};
CHECK_SIZE(Privileged, 0x4);
CHECK_OFFSET(Privileged, 0x0, session);

}  // namespace detail

}  // namespace boss

}  // namespace nn
