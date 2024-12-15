#include "nn/boss/TaskPolicy.h"

#include <cstring>

#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/ResultCode.h"

namespace nn {

namespace boss {

nn::Result TaskPolicy::InitializeWithSecInterval(u32 interval, u32 count) {
    config.priority = PriorityLevelMedium;
    config.schedulingPolicy = 1;
    config.taskTargetDuration = 0;
    config.taskPermission = 2;
    config.interval = interval;
    config.count = count;

    return RESULT_SUCCESS;
}

nn::Result TaskPolicy::SetProperty(PropertyType type, const void *buf, u32 size) {
    void *dst;
    u32 diff;

    if (buf == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPropertyValue);
    }

    // Calculate difference with 4 as a preset for clearing unset bytes on a property
    diff = 4 - size;
    switch (type) {
        case PropertyType::Priority:
            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.priority) + size, size == 0 ? 1 : 0);
            std::memset(reinterpret_cast<u8 *>(&config.priority) + size, 0, size == 0 ? 1 : 0);

            // Prevent size overflow
            if (size > 1) {
                size = 1;
            }
            dst = &config.priority;
            break;
        case PropertyType::SchedulingPolicy:
            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.schedulingPolicy) + size, size == 0 ? 1 : 0);
            std::memset(reinterpret_cast<u8 *>(&config.schedulingPolicy) + size, 0, size == 0 ? 1 : 0);

            if (size > 1) {
                size = 1;
            }
            dst = &config.schedulingPolicy;
            break;
        case PropertyType::TaskTargetDuration:
            // Clear the bytes that won't be set
            if (size >= 4) {
                diff = 0;
            }

            // memclr(reinterpret_cast<u8 *>(&config.taskTargetDuration) + size, diff);
            std::memset(reinterpret_cast<u8 *>(&config.taskTargetDuration) + size, 0, diff);

            // Prevent size overflow
            if (size > 4) {
                size = 4;
            }
            dst = &config.taskTargetDuration;
            break;
        case PropertyType::Interval:
            // Clear the bytes that won't be set
            if (size >= 4) {
                diff = 0;
            }

            // memclr(reinterpret_cast<u8 *>(&config.interval) + size, diff);
            std::memset(reinterpret_cast<u8 *>(&config.interval) + size, 0, diff);

            // Prevent size overflow
            if (size > 4) {
                size = 4;
            }
            dst = &config.interval;
            break;
        case PropertyType::Count:
            // Clear the bytes that won't be set
            if (size >= 4) {
                diff = 0;
            }

            // memclr(reinterpret_cast<u8 *>(&config.count) + size, diff);
            std::memset(reinterpret_cast<u8 *>(&config.count) + size, 0, diff);

            // Prevent size overflow
            if (size > 4) {
                size = 4;
            }
            dst = &config.count;
            break;
        case PropertyType::TaskPermission:
            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.taskPermission) + size, size == 0 ? 1 : 0);
            std::memset(reinterpret_cast<u8 *>(&config.taskPermission) + size, 0, size == 0 ? 1 : 0);

            // Prevent size overflow
            if (size > 1) {
                size = 1;
            }
            dst = &config.taskPermission;
            break;
        default:
            return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPropertyType);
    }

    std::memcpy(dst, buf, size);
    return RESULT_SUCCESS;
}

} // namespace boss

} // namespace nn
