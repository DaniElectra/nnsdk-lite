#pragma once

#include <cstring>
#include "helpers.h"
#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/types.h"

namespace nn {

namespace boss {

/// Information about the status of a task
struct TaskStatusInfo {
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x28
    u64 property0x28;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x29
    u64 property0x29;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x1D
    u8 property0x1D;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x1E
    u8 property0x1E;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x1F
    u8 property0x1F;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x21
    u8 property0x21;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x22
    u8 property0x22;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x20
    u8 property0x20;
    INSERT_PADDING_BYTES(2);
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x23
    u32 property0x23;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x25
    u32 property0x25;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x26
    u32 property0x26;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x27
    u32 property0x27;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x2A
    u32 property0x2A;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x2B
    u32 property0x2B;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x2D
    u16 property0x2D;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x2E
    u16 property0x2E;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x2C
    u8 property0x2C;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x24
    u8 property0x24;
    INSERT_PADDING_BYTES(2);
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x2F
    u8 property0x2F[0x40];
};
CHECK_SIZE(TaskStatusInfo, 0x78);
CHECK_OFFSET(TaskStatusInfo, 0x0, property0x28);
CHECK_OFFSET(TaskStatusInfo, 0x8, property0x29);
CHECK_OFFSET(TaskStatusInfo, 0x10, property0x1D);
CHECK_OFFSET(TaskStatusInfo, 0x11, property0x1E);
CHECK_OFFSET(TaskStatusInfo, 0x12, property0x1F);
CHECK_OFFSET(TaskStatusInfo, 0x13, property0x21);
CHECK_OFFSET(TaskStatusInfo, 0x14, property0x22);
CHECK_OFFSET(TaskStatusInfo, 0x15, property0x20);
CHECK_OFFSET(TaskStatusInfo, 0x18, property0x23);
CHECK_OFFSET(TaskStatusInfo, 0x1C, property0x25);
CHECK_OFFSET(TaskStatusInfo, 0x20, property0x26);
CHECK_OFFSET(TaskStatusInfo, 0x24, property0x27);
CHECK_OFFSET(TaskStatusInfo, 0x28, property0x2A);
CHECK_OFFSET(TaskStatusInfo, 0x2C, property0x2B);
CHECK_OFFSET(TaskStatusInfo, 0x30, property0x2D);
CHECK_OFFSET(TaskStatusInfo, 0x32, property0x2E);
CHECK_OFFSET(TaskStatusInfo, 0x34, property0x2C);
CHECK_OFFSET(TaskStatusInfo, 0x35, property0x24);
CHECK_OFFSET(TaskStatusInfo, 0x38, property0x2F);

class TaskStatus {
    u32 *vtable; // The vtable is empty
public:
    INSERT_PADDING_BYTES(4);
    TaskStatusInfo statusInfo;

    TaskStatus() {
        // memclr(&statusInfo, sizeof(statusInfo))
        std::memset(&statusInfo, 0, sizeof(statusInfo));
    }

    /**
     * @brief Gets a property of the task status
     * @param type Property type
     * @param buf Output buffer
     * @param size Buffer size
     */
    nn::Result GetProperty(PropertyType type, void *buf, u32 size);
};
CHECK_SIZE(TaskStatus, 0x80);
CHECK_OFFSET(TaskStatus, 0x8, statusInfo);

} // namespace boss

} // namespace nn
