#pragma once

#include "helpers.h"
#include "nn/Result.h"
#include "nn/types.h"

namespace nn {

namespace boss {

// UNOFFICIAL: All names are guesses from TaskIdList

/// List of steps that a task has registered
struct StepIdInfoList {
    /// Number of step IDs on the list
    u16 stepCount;
    INSERT_PADDING_BYTES(2);
    /// List of step IDs. TODO - Is this actually a u8?
    u8 steps[0x80];
};
CHECK_SIZE(StepIdInfoList, 0x84);
CHECK_OFFSET(StepIdInfoList, 0x0, stepCount);
CHECK_OFFSET(StepIdInfoList, 0x4, steps);

/// Contains the list of steps that a task has registered
class StepIdList {
    u32 *vtable; // TODO - Are there any entries on the vtable?
public:
    StepIdInfoList infoList;
};
CHECK_SIZE(StepIdList, 0x88);
CHECK_OFFSET(StepIdList, 0x4, infoList);

/**
 * @brief Retrieves the list of steps from a given task
 * @param taskId Task ID
 * @param list Output list of step IDs
 */
nn::Result GetStepIdList(const char *taskId, StepIdList *list);

} // namespace boss

} // namespace nn
