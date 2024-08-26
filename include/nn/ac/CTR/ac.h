#pragma once

#include "nn/Result.h"

namespace nn {

namespace ac {

namespace CTR {

nn::Result Initialize();
nn::Result Finalize();

bool IsConnected();

}  // namespace CTR

}  // namespace ac

}  // namespace nn
