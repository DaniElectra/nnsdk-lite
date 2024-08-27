#pragma once

#include "nn/Result.h"

namespace nn {

namespace boss {

/// Initializes BOSS
nn::Result Initialize();

/// Finalizes BOSS
nn::Result Finalize();

}  // namespace boss

}  // namespace nn
