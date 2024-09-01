#pragma once

#include "nn/Result.h"

namespace nn {

namespace ndm {

/// Initializes NDM (Daemon Manager)
nn::Result Initialize();

/// Finalizes NDM (Daemon Manager)
nn::Result Finalize();

/// Leaves the esclusive state
nn::Result LeaveExclusiveState();

} // namespace ndm

} // namespace nn
