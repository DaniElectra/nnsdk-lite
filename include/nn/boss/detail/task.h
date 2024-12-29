#pragma once

#include "nn/Result.h"
#include "nn/boss/TaskAction.h"
#include "nn/boss/TaskOption.h"
#include "nn/boss/TaskPolicy.h"

namespace nn {

namespace boss {

namespace detail {

/**
 * @brief Checks that the given task ID is valid
 * @param taskId Task ID
 * @return Whether the task ID is valid
 */
bool CheckTaskIdOk(const char *taskId);

/**
 * @brief Checks if the given task ID will only run in foreground
 * @param taskId Task ID
 * @return Whether the task ID will only run in foreground
 */
bool IsFgOnlyTaskId(const char *taskId);

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
