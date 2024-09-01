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
public:
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

    // vtable +0x0
    virtual ~IpcManager();

    /// Initializes boss:U
    nn::Result InitializeUserIpc();

    /// Finalizes boss:U
    nn::Result FinalizeUserIpc();
};
CHECK_SIZE(IpcManager, 0x28);
CHECK_OFFSET(IpcManager, 0x04, userInitialized);
CHECK_OFFSET(IpcManager, 0x05, privilegedInitialized);
CHECK_OFFSET(IpcManager, 0x06, bossMInitialized);
CHECK_OFFSET(IpcManager, 0x08, userSession);
CHECK_OFFSET(IpcManager, 0x0C, privilegedSession);
CHECK_OFFSET(IpcManager, 0x10, bossMSession);
CHECK_OFFSET(IpcManager, 0x14, userInstance);
CHECK_OFFSET(IpcManager, 0x18, privilegedInstance);
CHECK_OFFSET(IpcManager, 0x1C, bossMInstance);
CHECK_OFFSET(IpcManager, 0x20, titleId);

} // namespace detail

} // namespace boss

} // namespace nn
