#pragma once

#include "nn/Result.h"

namespace nn {

namespace ac {

namespace CTR {

/// Initializes AC
nn::Result Initialize();

/// Finalizes AC
nn::Result Finalize();

/**
 * @brief Gets if the console is connected to a network
 * @return Whether the console is connected to a network
 */
bool IsConnected();

}  // namespace CTR

}  // namespace ac

}  // namespace nn
