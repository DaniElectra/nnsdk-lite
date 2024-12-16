#include "nn/boss/TaskStatus.h"
#include <cstring>
#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/ResultCode.h"

namespace nn {

namespace boss {

nn::Result TaskStatus::GetProperty(PropertyType type, void *buf, u32 size) {
    if (buf == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPropertyValue);
    }

    switch (type) {
        case PropertyType::Unknown0x1D:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.property0x1D, size);
            break;
        case PropertyType::Unknown0x20:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.property0x20, size);
            break;
        case PropertyType::Unknown0x21:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.property0x21, size);
            break;
        case PropertyType::Unknown0x22:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.property0x22, size);
            break;
        case PropertyType::Unknown0x23:
            if (size > 4) {
                size = 4;
            }

            std::memcpy(buf, &statusInfo.property0x23, size);
            break;
        case PropertyType::Unknown0x24:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.property0x24, size);
            break;
        case PropertyType::Unknown0x25:
            if (size > 4) {
                size = 4;
            }

            std::memcpy(buf, &statusInfo.property0x25, size);
            break;
        case PropertyType::Unknown0x26:
            if (size > 4) {
                size = 4;
            }

            std::memcpy(buf, &statusInfo.property0x26, size);
            break;
        case PropertyType::Unknown0x27:
            if (size > 4) {
                size = 4;
            }

            std::memcpy(buf, &statusInfo.property0x27, size);
            break;
        case PropertyType::Unknown0x28:
            if (size > 8) {
                size = 8;
            }

            std::memcpy(buf, &statusInfo.property0x28, size);
            break;
        case PropertyType::Unknown0x29:
            if (size > 8) {
                size = 8;
            }

            std::memcpy(buf, &statusInfo.property0x29, size);
            break;
        case PropertyType::Unknown0x2A:
            if (size > 4) {
                size = 4;
            }

            std::memcpy(buf, &statusInfo.property0x2A, size);
            break;
        case PropertyType::Unknown0x2B:
            if (size > 4) {
                size = 4;
            }

            std::memcpy(buf, &statusInfo.property0x2B, size);
            break;
        case PropertyType::Unknown0x2C:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.property0x2C, size);
            break;
        case PropertyType::Unknown0x2F:
            if (size > 0x40) {
                size = 0x40;
            }

            std::memcpy(buf, statusInfo.property0x2F, size);
            break;
        default:
            return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPropertyType);
    }

    return RESULT_SUCCESS;
}

} // namespace boss

} // namespace nn
