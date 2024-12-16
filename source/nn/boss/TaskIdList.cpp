#include "nn/boss/TaskIdList.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/detail/detail.h"
#include "nn/boss/detail/property.h"

namespace nn {

namespace boss {

const char *TaskIdList::GetTaskId(u16 index) {
    if (index >= infoList.taskCount) {
        return nullptr;
    }

    return infoList.tasks[index];
}

nn::Result GetTaskIdList(TaskIdList *list) {
    if (list == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPolicy2);
    }

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetTaskIdList();
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetTaskIdList();
        }
    }

    if (res) {
        res = detail::ReceiveUserTaskIdList(&list->infoList);
    }

    return res;
}

} // namespace boss

} // namespace nn
