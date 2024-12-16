#pragma once

#include <cstring>
#include "helpers.h"
#include "nn/Result.h"
#include "nn/types.h"
namespace nn {

namespace boss {

constexpr int TASK_ID_SIZE = 8;
constexpr int TASK_ID_LIST_SIZE = 128;

/// List of task IDs registered by the application
struct TaskIdInfoList {
    /// Number of task IDs on the list
    u16 taskCount;
    INSERT_PADDING_BYTES(6);
    /// List of task IDs
    char tasks[TASK_ID_SIZE][TASK_ID_LIST_SIZE];
};
CHECK_SIZE(TaskIdInfoList, 0x408);
CHECK_OFFSET(TaskIdInfoList, 0x0, taskCount);
CHECK_OFFSET(TaskIdInfoList, 0x8, tasks);

/// Contains the list of task IDs registered by the application
class TaskIdList {
public:
    TaskIdInfoList infoList;

    // TODO - vtable +0x0 is empty, what could it be?

    // vtable +0x4
    virtual ~TaskIdList();

    TaskIdList() {
        // memclr(&infoList, sizeof(infoList))
        std::memset(&infoList, 0, sizeof(infoList));
    }

    /**
     * @brief Gets a task ID from the list
     * @param index Index to look up
     * @return Task ID or nullptr if the index is out of range
     */
    const char *GetTaskId(u16 index);
};
CHECK_SIZE(TaskIdList, 0x40C);
CHECK_OFFSET(TaskIdList, 0x4, infoList);

/**
 * @brief Retrieves the list of task ID from the application
 * @param list Output list of task IDs
 */
nn::Result GetTaskIdList(TaskIdList *list);

} // namespace boss

} // namespace nn
