#include "nn/boss/detail/property.h"
#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/detail/detail.h"

namespace nn {

namespace boss {

namespace detail {

// UNOFFICIAL: Guess from context
namespace {

/// Internal shared result for functions related to task properties
static nn::Result s_PropertyResult;

} // namespace

/**
 * @brief Receives a property from the currently loaded session
 * @remark If the buffer size doesn't match with the property size, this function will return "ResultCode::IpcPropertySizeError"
 * @param type Property type
 * @param buf Output buffer
 * @param size Buffer size
 */
nn::Result ReceivePropertyUserInternal(PropertyType type, u8 *buf, u32 size) {
    nn::Result res;
    detail::User *userInstance;
    detail::Privileged *privilegedInstance;
    u32 sizeRead;

    // Try with the privileged instance. NOTE: This function is inlined
    res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->ReceiveProperty(type, buf, size, &sizeRead);
    } else {
        // If it isn't available, try with the user instance. NOTE: This function is inlined
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->ReceiveProperty(type, buf, size, &sizeRead);
        }
    }

    if (res && size != sizeRead) {
        res = detail::ChangeBossRetCodeToResult(ResultCode::IpcPropertySizeError);
    }

    s_PropertyResult = res;
    return res;
}

nn::Result ReceiveUserTaskIdList(TaskIdInfoList *list) {
    s_PropertyResult = RESULT_SUCCESS;
    ReceivePropertyUserInternal(PropertyType::TotalTasks, reinterpret_cast<u8 *>(&list->taskCount), sizeof(list->taskCount));
    ReceivePropertyUserInternal(PropertyType::TaskIdList, reinterpret_cast<u8 *>(list->tasks), sizeof(list->tasks));
    return s_PropertyResult;
}

nn::Result ReceiveUserTaskStatus(TaskStatusInfo *status) {
    s_PropertyResult = RESULT_SUCCESS;
    ReceivePropertyUserInternal(PropertyType::Unknown0x1D, reinterpret_cast<u8 *>(&status->property0x1D), sizeof(status->property0x1D));
    ReceivePropertyUserInternal(PropertyType::Unknown0x1E, reinterpret_cast<u8 *>(&status->property0x1E), sizeof(status->property0x1E));
    ReceivePropertyUserInternal(PropertyType::Unknown0x1F, reinterpret_cast<u8 *>(&status->property0x1F), sizeof(status->property0x1F));
    ReceivePropertyUserInternal(PropertyType::Unknown0x20, reinterpret_cast<u8 *>(&status->property0x20), sizeof(status->property0x20));
    ReceivePropertyUserInternal(PropertyType::Unknown0x21, reinterpret_cast<u8 *>(&status->property0x21), sizeof(status->property0x21));
    ReceivePropertyUserInternal(PropertyType::Unknown0x23, reinterpret_cast<u8 *>(&status->property0x23), sizeof(status->property0x23));
    ReceivePropertyUserInternal(PropertyType::Unknown0x25, reinterpret_cast<u8 *>(&status->property0x25), sizeof(status->property0x25));
    ReceivePropertyUserInternal(PropertyType::Unknown0x26, reinterpret_cast<u8 *>(&status->property0x26), sizeof(status->property0x26));
    ReceivePropertyUserInternal(PropertyType::Unknown0x27, reinterpret_cast<u8 *>(&status->property0x27), sizeof(status->property0x27));
    ReceivePropertyUserInternal(PropertyType::Unknown0x28, reinterpret_cast<u8 *>(&status->property0x28), sizeof(status->property0x28));
    ReceivePropertyUserInternal(PropertyType::Unknown0x29, reinterpret_cast<u8 *>(&status->property0x29), sizeof(status->property0x29));
    ReceivePropertyUserInternal(PropertyType::Unknown0x2A, reinterpret_cast<u8 *>(&status->property0x2A), sizeof(status->property0x2A));
    ReceivePropertyUserInternal(PropertyType::Unknown0x2B, reinterpret_cast<u8 *>(&status->property0x2B), sizeof(status->property0x2B));
    ReceivePropertyUserInternal(PropertyType::Unknown0x2C, reinterpret_cast<u8 *>(&status->property0x2C), sizeof(status->property0x2C));
    ReceivePropertyUserInternal(PropertyType::Unknown0x2D, reinterpret_cast<u8 *>(&status->property0x2D), sizeof(status->property0x2D));
    ReceivePropertyUserInternal(PropertyType::Unknown0x2E, reinterpret_cast<u8 *>(&status->property0x2E), sizeof(status->property0x2E));
    ReceivePropertyUserInternal(PropertyType::Unknown0x22, reinterpret_cast<u8 *>(&status->property0x22), sizeof(status->property0x22));
    ReceivePropertyUserInternal(PropertyType::Unknown0x24, reinterpret_cast<u8 *>(&status->property0x24), sizeof(status->property0x24));
    ReceivePropertyUserInternal(PropertyType::Unknown0x2F, reinterpret_cast<u8 *>(status->property0x2F), sizeof(status->property0x2F));
    return s_PropertyResult;
}

} // namespace detail

} // namespace boss

} // namespace nn
