#include "nn/boss/TaskQuery.h"
#include "nn/Result.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/detail/detail.h"

namespace nn {

namespace boss {

nn::Result TaskQuery::AddQuery(const char *name, const char *value) {
    if (name == nullptr) {
        // 0xD8E0FBF6
        return {nn::Result::Level_Permanent,
                nn::Result::Summary_InvalidArgument,
                nn::Result::ModuleType_BOSS,
                static_cast<int>(ResultCode::InvalidPointer)};
    }

    u32 nameLen = detail::strnlen(name, QUERY_NAME_SIZE);
    if (nameLen >= QUERY_NAME_SIZE) {
        // 0xD8E0FBF6
        return {nn::Result::Level_Permanent,
                nn::Result::Summary_InvalidArgument,
                nn::Result::ModuleType_BOSS,
                static_cast<int>(ResultCode::InvalidPointer)};
    }

    if (value == nullptr) {
        // 0xD8E0FBF6
        return {nn::Result::Level_Permanent,
                nn::Result::Summary_InvalidArgument,
                nn::Result::ModuleType_BOSS,
                static_cast<int>(ResultCode::InvalidPointer)};
    }

    u32 valueLen = detail::strnlen(value, QUERY_VALUE_SIZE);
    if (valueLen >= QUERY_VALUE_SIZE) {
        // 0xD8E0FBF6
        return {nn::Result::Level_Permanent,
                nn::Result::Summary_InvalidArgument,
                nn::Result::ModuleType_BOSS,
                static_cast<int>(ResultCode::InvalidPointer)};
    }

    for (u8 i = 0; i < MAX_QUERY_FIELDS; i++) {
        if (!config.fields[i].used) {
            config.fields[i].used = true;
            std::strncpy(config.fields[i].name, name, QUERY_NAME_SIZE);
            std::strncpy(config.fields[i].value, value, QUERY_VALUE_SIZE);
            return RESULT_SUCCESS;
        }
    }

    // 0xD860F8C2
    return {nn::Result::Level_Permanent,
            nn::Result::Summary_OutOfResources,
            nn::Result::ModuleType_BOSS,
            static_cast<int>(ResultCode::InvalidMaxHttpQuery)};
}

} // namespace boss

} // namespace nn
