#pragma once

#include "nn/Result.h"
#include "nn/boss/TaskAction.h"
#include "nn/boss/TaskOption.h"
#include "nn/boss/TaskPolicy.h"

namespace nn {

namespace boss {

namespace detail {

/**
 * @brief Checks that the configuration of the task action is valid
 * @param action Task action config
 */
nn::Result VerifyTaskActionConfig(TaskActionConfig *action);

/**
 * @brief Checks that the configuration of the task policy is valid
 * @param policy Task policy
 */
nn::Result VerifyTaskPolicyConfig(TaskPolicy *policy);

/**
 * @brief Checks that the configuration of the task policy is valid
 * @param option Task option
 */
nn::Result VerifyTaskOptionConfig(TaskOption *option);

} // namespace detail

} // namespace boss

} // namespace nn
