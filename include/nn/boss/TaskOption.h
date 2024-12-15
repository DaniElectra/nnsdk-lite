#pragma once

#include "helpers.h"
#include "nn/types.h"

namespace nn {

namespace boss {

/// Configuration of task options
struct TaskOptionConfig {
    /// This parameter is unknown. Must be 1. Matches with @link PropertyType @endlink 0x18
    u8 property0x18;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x19
    u8 property0x19;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x1A
    u8 property0x1A;
    INSERT_PADDING_BYTES(1);
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x1B
    u32 property0x1B;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x1C
    u32 property0x1C;
};
CHECK_SIZE(TaskOptionConfig, 0xC);
CHECK_OFFSET(TaskOptionConfig, 0x0, property0x18);
CHECK_OFFSET(TaskOptionConfig, 0x1, property0x19);
CHECK_OFFSET(TaskOptionConfig, 0x2, property0x1A);
CHECK_OFFSET(TaskOptionConfig, 0x4, property0x1B);
CHECK_OFFSET(TaskOptionConfig, 0x8, property0x1C);

/// Contains options of a task
class TaskOption {
    u32 *vtable; // TODO - Are there any entries on the vtable?
public:
    TaskOptionConfig config;
};
CHECK_SIZE(TaskOption, 0x10);
CHECK_OFFSET(TaskOption, 0x4, config);

} // namespace boss

} // namespace nn
