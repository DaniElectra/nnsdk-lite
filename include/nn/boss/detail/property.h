#pragma once

#include "helpers.h"
#include "nn/Result.h"
#include "nn/boss/TaskIdList.h"
#include "nn/boss/TaskStatus.h"

namespace nn {

namespace boss {

namespace detail {

/**
 * @brief Receives the list of task IDs from the application
 * @param list Output list of task IDs
 */
nn::Result ReceiveUserTaskIdList(TaskIdInfoList *list);

/**
 * @brief Receives the status of the currently loaded task
 * @param status Output task status
 */
nn::Result ReceiveUserTaskStatus(TaskStatusInfo *status);

} // namespace detail

} // namespace boss

} // namespace nn
