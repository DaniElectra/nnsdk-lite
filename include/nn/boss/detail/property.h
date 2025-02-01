#pragma once

#include "nn/Result.h"
#include "nn/boss/AppIdList.h"
#include "nn/boss/StepIdList.h"
#include "nn/boss/TaskAction.h"
#include "nn/boss/TaskIdList.h"
#include "nn/boss/TaskOption.h"
#include "nn/boss/TaskPolicy.h"
#include "nn/boss/TaskStatus.h"

namespace nn {

namespace boss {

namespace detail {

/**
 * @brief Sends the task action configuration data to the BOSS session
 * @param action Task action config
 */
nn::Result SendUserTaskAction(TaskActionConfig *action);

/**
 * @brief Sends the task policy configuration data to the BOSS session
 * @param policy Task policy config
 */
nn::Result SendUserTaskPolicy(TaskPolicyConfig *policy);

/**
 * @brief Sends the task option configuration data to the BOSS session
 * @param option Task option config
 */
nn::Result SendUserTaskOption(TaskOptionConfig *option);

/**
 * @brief Receives the list of task IDs from the application
 * @param list Output list of task IDs
 */
nn::Result ReceiveUserTaskIdList(TaskIdInfoList *list);

/**
 * @brief Receives the list of steps from the previously specified task
 * @param list Output list of step IDs
 */
nn::Result ReceiveUserStepIdList(StepIdInfoList *list);

/**
 * @brief Receives the status of the currently loaded task
 * @param status Output task status
 */
nn::Result ReceiveUserTaskStatus(TaskStatusInfo *status);

/**
 * @brief Receives the list of applications that are registered in BOSS
 * @param list Output list of app IDs
 */
nn::Result ReceivePrivilegedAppIdList(AppIdInfoList *list);

} // namespace detail

} // namespace boss

} // namespace nn
