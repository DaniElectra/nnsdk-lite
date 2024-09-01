#pragma once

#include "nn/Result.h"
#include "nn/boss/TaskResultCode.h"

namespace nn {

namespace boss {

/// Initializes BOSS
nn::Result Initialize();

/// Finalizes BOSS
nn::Result Finalize();

/**
 * @brief Gets the error code for the given \link TaskResultCode \endlink
 * @param errorCode Output error code
 * @param result Task result code
 */
nn::Result GetErrorCode(u32 *errorCode, TaskResultCode result);

} // namespace boss

} // namespace nn
