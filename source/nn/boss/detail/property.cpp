#include "nn/boss/detail/property.h"
#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/TaskAction.h"
#include "nn/boss/TaskPolicy.h"
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
 * @brief Sends a property to the currently loaded session
 * @param type Property type
 * @param buf Input buffer
 * @param size Buffer size
 */
nn::Result SendPropertyUserInternal(PropertyType type, const u8 *buf, u32 size) {
    nn::Result res;
    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance. NOTE: This function is inlined
    res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->SendProperty(type, buf, size);
    } else {
        // If it isn't available, try with the user instance. NOTE: This function is inlined
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->SendProperty(type, buf, size);
        }
    }

    s_PropertyResult = res;
    return res;
}

/**
 * @brief Sends a property to the currently loaded session
 * @param type Property type
 * @param handle Input handle
 */
nn::Result SendPropertyUserInternal(PropertyType type, nn::Handle handle) {
    nn::Result res;
    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance. NOTE: This function is inlined
    res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->SendPropertyHandle(type, handle);
    } else {
        // If it isn't available, try with the user instance. NOTE: This function is inlined
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->SendPropertyHandle(type, handle);
        }
    }

    s_PropertyResult = res;
    return res;
}

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

nn::Result SendUserTaskAction(TaskActionConfig *action) {
    s_PropertyResult = RESULT_SUCCESS;
    SendPropertyUserInternal(PropertyType::ActionCode, reinterpret_cast<u8 *>(&action->code), 1);
    SendPropertyUserInternal(PropertyType::Url, reinterpret_cast<u8 *>(action->url), URL_SIZE);
    SendPropertyUserInternal(PropertyType::Unknown0x09, reinterpret_cast<u8 *>(&action->property0x9), 1);
    switch (action->property0x9) {
        case 0:
            SendPropertyUserInternal(PropertyType::Unknown0x0A, action->actionData, 0x100);
            break;
        case 1:
            SendPropertyUserInternal(PropertyType::Unknown0x0B, action->actionData, 0x200);
            break;
        case 2:
        case 3:
        case 4:
            SendPropertyUserInternal(PropertyType::Handle, action->fileHandle);
            break;
        case 6:
            SendPropertyUserInternal(PropertyType::Handle, action->fileHandle);
        case 5:
            SendPropertyUserInternal(PropertyType::DataStoreDownloadActionData, action->actionData, 0x200);
            break;
        default:
            return {nn::Result::Level_Status, nn::Result::Summary_Internal, nn::Result::ModuleType_BOSS, static_cast<int>(ResultCode::Unexpect)};
    }
    SendPropertyUserInternal(PropertyType::HeaderFields, reinterpret_cast<u8 *>(action->headerFields), 0x360);
    SendPropertyUserInternal(PropertyType::Unknown0x16, reinterpret_cast<u8 *>(&action->property0x16), 4);
    SendPropertyUserInternal(PropertyType::Unknown0x08, reinterpret_cast<u8 *>(&action->property0x8), 4);
    SendPropertyUserInternal(PropertyType::ClientCerts, reinterpret_cast<u8 *>(action->clientCerts), 4);
    SendPropertyUserInternal(PropertyType::RootCAs, reinterpret_cast<u8 *>(action->rootCAs), 0xC);
    SendPropertyUserInternal(PropertyType::Unknown0x3B, reinterpret_cast<u8 *>(&action->property0x3B), 4);
    SendPropertyUserInternal(PropertyType::ApInfoType, reinterpret_cast<u8 *>(&action->apInfoType), 1);
    SendPropertyUserInternal(PropertyType::CfgInfoType, reinterpret_cast<u8 *>(&action->cfgInfoType), 1);
    SendPropertyUserInternal(PropertyType::FSClientCert, reinterpret_cast<u8 *>(&action->fsClientCert), 1);
    SendPropertyUserInternal(PropertyType::FSRootCA, reinterpret_cast<u8 *>(&action->fsRootCA), 1);
    SendPropertyUserInternal(PropertyType::RootCaCount, reinterpret_cast<u8 *>(&action->rootCaCount), 4);
    SendPropertyUserInternal(PropertyType::ClientCertCount, reinterpret_cast<u8 *>(&action->clientCertCount), 4);
    SendPropertyUserInternal(PropertyType::Unknown0x15, reinterpret_cast<u8 *>(action->property0x15), 0x40);
    return s_PropertyResult;
}

nn::Result SendUserTaskPolicy(TaskPolicyConfig *policy) {
    s_PropertyResult = RESULT_SUCCESS;
    SendPropertyUserInternal(PropertyType::Priority, reinterpret_cast<u8 *>(&policy->priority), 1);
    SendPropertyUserInternal(PropertyType::SchedulingPolicy, reinterpret_cast<u8 *>(&policy->schedulingPolicy), 1);
    SendPropertyUserInternal(PropertyType::TaskTargetDuration, reinterpret_cast<u8 *>(&policy->taskTargetDuration), 4);
    SendPropertyUserInternal(PropertyType::Interval, reinterpret_cast<u8 *>(&policy->interval), 4);
    SendPropertyUserInternal(PropertyType::Count, reinterpret_cast<u8 *>(&policy->count), 4);
    SendPropertyUserInternal(PropertyType::TaskPermission, reinterpret_cast<u8 *>(&policy->taskPermission), 1);
    return s_PropertyResult;
}

nn::Result SendUserTaskOption(TaskOptionConfig *option) {
    s_PropertyResult = RESULT_SUCCESS;
    SendPropertyUserInternal(PropertyType::Unknown0x18, reinterpret_cast<u8 *>(&option->property0x18), 1);
    SendPropertyUserInternal(PropertyType::Unknown0x19, reinterpret_cast<u8 *>(&option->property0x19), 1);
    SendPropertyUserInternal(PropertyType::Unknown0x1A, reinterpret_cast<u8 *>(&option->property0x1A), 1);
    SendPropertyUserInternal(PropertyType::Unknown0x1B, reinterpret_cast<u8 *>(&option->property0x1B), 4);
    SendPropertyUserInternal(PropertyType::Unknown0x1C, reinterpret_cast<u8 *>(&option->property0x1C), 4);
    return s_PropertyResult;
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
