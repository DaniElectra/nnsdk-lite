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
        case PropertyType::StateCode:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.stateCode, size);
            break;
        case PropertyType::TaskResultCode:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.result, size);
            break;
        case PropertyType::ServiceStatus:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.serviceStatus, size);
            break;
        case PropertyType::Unknown0x22:
            if (size > 1) {
                size = 1;
            }

            std::memcpy(buf, &statusInfo.property0x22, size);
            break;
        case PropertyType::CommErrorCode:
            if (size > 4) {
                size = 4;
            }

            std::memcpy(buf, &statusInfo.commErrorCode, size);
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
        case PropertyType::LastSuccessfulTimestamp:
            if (size > 8) {
                size = 8;
            }

            std::memcpy(buf, &statusInfo.lastSuccessfulTimestamp, size);
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
        case PropertyType::LastModifiedHeader:
            if (size > 0x40) {
                size = 0x40;
            }

            std::memcpy(buf, statusInfo.lastModifiedHeader, size);
            break;
        default:
            return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPropertyType);
    }

    return RESULT_SUCCESS;
}

} // namespace boss

} // namespace nn
