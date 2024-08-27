#pragma once

#include "helpers.h"
#include "nn/boss/detail/Privileged.h"
#include "nn/boss/detail/User.h"
#include "nn/boss/detail/bossM.h"
#include "nn/os/ipc.h"

namespace nn {

namespace boss {

namespace detail {

// TODO - What does the M in boss:M stand for?

// UNOFFICIAL: The real member names are unknown

/// Manages all IPC sessions for BOSS
class IpcManager {
    // u32 *vtable; // The vtable is implicit
    bool userInitialized{};
    bool privilegedInitialized{};
    bool bossMInitialized{};
    INSERT_PADDING_BYTES(1);
    nn::os::ipc::Session userSession{};
    nn::os::ipc::Session privilegedSession{};
    nn::os::ipc::Session bossMSession{};
    User userInstance{};
    Privileged privilegedInstance{};
    bossM bossMInstance{};
    u64 titleId{};

public:
    virtual ~IpcManager();

    /// Initializes boss:U
    nn::Result InitializeUserIpc();

    /// Finalizes boss:U
    nn::Result FinalizeUserIpc();
};
CHECK_SIZE(IpcManager, 0x28);

// UNOFFICIAL: Guess from context
namespace {
static IpcManager s_IpcManager;
}

}  // namespace detail

}  // namespace boss

}  // namespace nn
