#include "nn/boss/detail/task.h"
#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/TaskAction.h"
#include "nn/boss/TaskPolicy.h"

namespace nn {

namespace boss {

namespace detail {

nn::Result VerifyTaskActionConfig(TaskActionConfig *action) {
    ActionCode code = action->code;
    if (code == 0 || code > ActionCodeVersionList) {
        return ChangeBossRetCodeToResult(ResultCode::ActionCodeOutOfRange);
    }

    if (code != ActionCodeFileList && code != ActionCodeNsaDownload && code != ActionCodeUpload && code != ActionCodePl && code != ActionCodePhu &&
        code != ActionCodeTiu && code != ActionCodeSplu) {
        return RESULT_SUCCESS;
    }

    if (action->url[0] == '\0') {
        return ChangeBossRetCodeToResult(ResultCode::InvalidUrl);
    }

    if (action->apInfoType >= 8) {
        return ChangeBossRetCodeToResult(ResultCode::ApInfoTypeOutOfRange);
    }

    if (action->cfgInfoType >= 8) {
        return ChangeBossRetCodeToResult(ResultCode::CfgInfoTypeOutOfRange);
    }

    if (code != ActionCodeFileList && code != ActionCodeUpload) {
        return RESULT_SUCCESS;
    }

    u8 property0x9 = action->property0x9;
    if (property0x9 == 0) {
        if (action->actionData[0] != '\0') {
            return RESULT_SUCCESS;
        }
    } else if (property0x9 == 1) {
        if (*reinterpret_cast<u16 *>(action->actionData) != '\0') {
            return RESULT_SUCCESS;
        }
    } else if (property0x9 == 2) {
        return RESULT_SUCCESS;
    } else if (code == ActionCodeUpload && (property0x9 == 3 || property0x9 == 4)) {
        return RESULT_SUCCESS;
    }

    return ChangeBossRetCodeToResult(ResultCode::InvalidPolicy3);
}

nn::Result VerifyTaskPolicyConfig(TaskPolicy *policy) {
    PriorityLevel priority = policy->config.priority;
    if (priority < PriorityLevelExpedite1) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskPriority);
    }

    if (priority > PriorityLevelExpedite8 && priority < PriorityLevelExpedite) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskPriority);
    }

    if (priority > PriorityLevelExpedite && priority < PriorityLevelHigh) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskPriority);
    }

    if (priority > PriorityLevelHigh && priority < PriorityLevelMedium) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskPriority);
    }

    if (priority > PriorityLevelMedium && priority < PriorityLevelLow) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskPriority);
    }

    if (priority > PriorityLevelLow && priority < PriorityLevelLowest) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskPriority);
    }

    if (priority > PriorityLevelLowest && priority < PriorityLevelLowest1) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskPriority);
    }

    if (priority > PriorityLevelLowest8 && priority < PriorityLevelStopped) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskPriority);
    }

    if (policy->config.taskPermission >= 4) {
        return ChangeBossRetCodeToResult(ResultCode::TaskPermissionOutOfRange);
    }

    if (policy->config.schedulingPolicy == 0 || policy->config.schedulingPolicy > 1) {
        return ChangeBossRetCodeToResult(ResultCode::SchedulingPolicyOutOfRange);
    }

    if (policy->config.taskTargetDuration >= 0x10000) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidTaskTargetDuration);
    }

    return RESULT_SUCCESS;
}

nn::Result VerifyTaskOptionConfig(TaskOption *option) {
    if (option->config.property0x18 == 0 || option->config.property0x18 > 1) {
        return ChangeBossRetCodeToResult(ResultCode::InvalidOption);
    }

    return RESULT_SUCCESS;
}

} // namespace detail

} // namespace boss

} // namespace nn
