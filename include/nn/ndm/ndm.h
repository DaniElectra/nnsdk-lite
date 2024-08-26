#pragma once

#include "nn/Result.h"

namespace nn {

namespace ndm {

nn::Result Initialize();
nn::Result Finalize();

nn::Result LeaveExclusiveState();

}  // namespace ndm

}  // namespace nn
