#include "nn/boss/StepIdList.h"
#include "nn/Result.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/detail/Privileged.h"
#include "nn/boss/detail/User.h"
#include "nn/boss/detail/detail.h"
#include "nn/boss/detail/property.h"
#include "nn/boss/detail/task.h"

namespace nn {

namespace boss {

nn::Result GetStepIdList(const char *taskId, StepIdList *list) {
    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    if (list == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidStepIdList);
    }

    // NOTE - After this the task ID is also copied into the stack with strncpy
    u32 taskIdLen = detail::strnlen(taskId, 8);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetStepIdList(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetStepIdList(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1);
        }
    }

    if (res) {
        res = detail::ReceiveUserStepIdList(&list->infoList);
    }

    return res;
}

} // namespace boss

} // namespace nn
