#pragma once

#include "helpers.h"
#include "nn/Handle.h"

namespace nn {

namespace boss {

namespace detail {

// UNOFFICIAL: The real class name is unknown

/// Manages a BOSS session used by NDM
class bossM {
public:
    nn::Handle session;
};
CHECK_SIZE(bossM, 0x4);
CHECK_OFFSET(bossM, 0x0, session);

} // namespace detail

} // namespace boss

} // namespace nn
