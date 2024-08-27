#pragma once

#include "helpers.h"
#include "nn/Handle.h"
#include "nn/Result.h"

namespace nn {

namespace boss {

namespace detail {

/// Manages a user session with BOSS
class User {
public:
    nn::Handle session;

    /**
     * @brief Initializes the user session
     * @param titleId Title ID to use for the session, or zero for the current program
     */
    nn::Result InitializeSession(u64 titleId);
};
CHECK_SIZE(User, 0x4);
CHECK_OFFSET(User, session, 0x0);

}  // namespace detail

}  // namespace boss

}  // namespace nn
