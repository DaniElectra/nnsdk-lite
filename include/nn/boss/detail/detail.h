#pragma once

#include "nn/boss/detail/IpcManager.h"

namespace nn {

namespace boss {

namespace detail {

// UNOFFICIAL: Guess from context
namespace {

static IpcManager s_IpcManager;

}

/// Initializes boss:U
nn::Result InitializeUserIpc();

/// Finalizes boss:U
nn::Result FinalizeUserIpc();

/**
 * @brief Gets a \link User \endlink instance for BOSS
 * @param instance Reference where a pointer to the instance will be returned
 */
nn::Result GetUserIpcInstance(User *&instance);

/**
 * @brief Gets a \link Privileged \endlink instance for BOSS
 * @param instance Reference where a pointer to the instance will be returned
 */
nn::Result GetPrivilegedIpcInstance(Privileged *&instance);

} // namespace detail

} // namespace boss

} // namespace nn
