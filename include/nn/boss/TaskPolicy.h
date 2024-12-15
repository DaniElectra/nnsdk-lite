#pragma once

#include "helpers.h"
#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/types.h"

namespace nn {

namespace boss {

// UNOFFICIAL: The official name for this enum is unknoen

/// Represents the priority of a task
enum PriorityLevel : u8 {
    PriorityLevelExpedite1 = 0x15,
    PriorityLevelExpedite2,
    PriorityLevelExpedite3,
    PriorityLevelExpedite4,
    PriorityLevelExpedite5,
    PriorityLevelExpedite6,
    PriorityLevelExpedite7,
    PriorityLevelExpedite8,

    PriorityLevelExpedite = 0x23,

    PriorityLevelHigh = 0x50,

    PriorityLevelMedium = 0x7D,

    PriorityLevelLow = 0xAA,

    PriorityLevelLowest = 0xD7,

    PriorityLevelLowest1 = 0xDD,
    PriorityLevelLowest2,
    PriorityLevelLowest3,
    PriorityLevelLowest4,
    PriorityLevelLowest5,
    PriorityLevelLowest6,
    PriorityLevelLowest7,
    PriorityLevelLowest8,

    PriorityLevelStopped = 0xFF
};

/// Contains the configuration for a task policy
struct TaskPolicyConfig {
    /// Priority of the task
    PriorityLevel priority{};
    /// This parameter is unknown. Must be 1
    u8 schedulingPolicy{};
    /// This parameter is unknown. Must be below 4 (not inclusive)
    u8 taskPermission{};
    /// This parameter is unknown. Seems unused?
    u8 unk_0x3{};
    /// This parameter is unknown. Must be below 0x10000
    u32 taskTargetDuration{};
    /// Interval in seconds of the task
    u32 interval{};
    /// Number of times that the task will be run. If zero, the task is persistent
    u32 count{};
};
CHECK_SIZE(TaskPolicyConfig, 0x10);
CHECK_OFFSET(TaskPolicyConfig, 0x0, priority);
CHECK_OFFSET(TaskPolicyConfig, 0x1, schedulingPolicy);
CHECK_OFFSET(TaskPolicyConfig, 0x2, taskPermission);
CHECK_OFFSET(TaskPolicyConfig, 0x3, unk_0x3);
CHECK_OFFSET(TaskPolicyConfig, 0x4, taskTargetDuration);
CHECK_OFFSET(TaskPolicyConfig, 0x8, interval);
CHECK_OFFSET(TaskPolicyConfig, 0xC, count);

/// Determines the policies for a task
class TaskPolicy {
    u32 *vtable; // The vtable is empty
public:
    TaskPolicyConfig config{};

    /**
     * @brief Initializes the task policy
     * @param intrerval Interval in seconds of the task
     * @param count Number of times that the task will be run. If zero, the task is persistent
     */
    nn::Result InitializeWithSecInterval(u32 interval, u32 count);

    /**
     * @brief Sets a property of the task policy
     * @param type Property type
     * @param buf Pointer to the property data
     * @param size Size of the property data
     */
    nn::Result SetProperty(PropertyType type, const void *buf, u32 size);
};
CHECK_SIZE(TaskPolicy, 0x14);
CHECK_OFFSET(TaskPolicy, 0x4, config);

} // namespace boss

} // namespace nn
