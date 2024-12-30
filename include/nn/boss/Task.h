#pragma once

#include "helpers.h"
#include "nn/Result.h"
#include "nn/boss/TaskAction.h"
#include "nn/boss/TaskOption.h"
#include "nn/boss/TaskPolicy.h"
#include "nn/boss/TaskResultCode.h"
#include "nn/boss/TaskServiceStatus.h"
#include "nn/boss/TaskStateCode.h"
#include "nn/boss/TaskStatus.h"
#include "nn/fnd/TimeSpan.h"
#include "nn/types.h"

namespace nn {

namespace boss {

class Task {
    u32 *vtable; // The vtable is empty
public:
    INSERT_UNKNOWN_BYTES(8);
    char taskId[8];

    /**
     * @brief Initializes a task
     * @param taskId Task ID
     */
    nn::Result Initialize(const char *taskId);

    /**
     * @brief Updates the task count @link PropertyType @endlink
     * @param count New count
     */
    nn::Result UpdateCount(u32 count);

    /**
     * @brief Gets the task count
     * @return Task count or -1 for errors
     */
    u32 GetCount();

    /**
     * @brief Gets the task service status
     * @return Task service status
     */
    TaskServiceStatus GetServiceStatus();

    /// Starts the task
    nn::Result Start();

    /// Starts the immediate task
    nn::Result StartImmediate();

    /// Cancels the task
    nn::Result Cancel();

    /**
     * @brief Waits for the task to finish
     * @param timeout Timeout in nanoseconds
     */
    nn::Result WaitFinish(nn::fnd::TimeSpan &timeout);

    /**
     * @brief Gets the state of a task
     * @param unk Unknown parameter
     * @param count Optional. Output task count
     * @param currentStepId Optional. Output of the current step ID being run?
     * @return Task state code
     */
    TaskStateCode GetState(bool unk, u32 *count, u8 *currentStepId);

    /**
     * @brief Gets the result of a task
     * @param count Optional. Output task count?
     * @param currentStepId Optional. Output of the current step ID being run?
     * @return Task result code
     */
    TaskResultCode GetResult(u32 *count, u8 *currentStepId);

    /**
     * @brief Gets all details from the state of a task
     * @param status Output task status
     * @param unk Unknown parameter
     * @param currentStepId Optional. Output of the current step ID being inspected?
     * @param stepId Task step ID to get the details from?
     */
    nn::Result GetStateDetail(TaskStatus *status, bool unk, u8 *currentStepId, u8 stepId);
};
CHECK_SIZE(Task, 0x14);
CHECK_OFFSET(Task, 0xC, taskId);

/**
 * @brief Registers a given task
 * @param task Task to register
 * @param policy Task policy
 * @param action Task action
 * @param option Optional. Task option
 * @param stepId Task step ID
 */
nn::Result RegisterTask(Task *task, TaskPolicy *policy, TaskAction *action, TaskOption *option, u8 stepId);

/**
 * @brief Unregisters a given task
 * @param task Task to unregister
 * @param stepId Task step ID
 */
nn::Result UnregisterTask(Task *task, u8 stepId);

/**
 * @brief Registers a given immediate task
 * @param task Task to register
 * @param action Task action
 * @param policy Optional. Task policy
 * @param option Optional. Task option
 * @param stepId Task step ID
 */
nn::Result RegisterImmediateTask(Task *task, TaskAction *action, TaskPolicy *policy, TaskOption *option, u8 stepId);

} // namespace boss

} // namespace nn
