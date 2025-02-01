#include "nn/boss/Task.h"
#include <cstring>
#include "nn/Result.h"
#include "nn/ac/CTR/ac.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/TaskOption.h"
#include "nn/boss/TaskResultCode.h"
#include "nn/boss/TaskServiceStatus.h"
#include "nn/boss/boss.h"
#include "nn/boss/common.h"
#include "nn/boss/detail/detail.h"
#include "nn/boss/detail/property.h"
#include "nn/boss/detail/task.h"
#include "nn/fnd/TimeSpan.h"

namespace nn {

namespace boss {

nn::Result Task::Initialize(const char *taskId) {
    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    u32 len = detail::strnlen(taskId, 8);
    if (len >= 8) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    if (detail::IsFgOnlyTaskId(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    std::strcpy(this->taskId, taskId);
    return RESULT_SUCCESS;
}

nn::Result Task::UpdateCount(u32 count) {
    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    u32 taskIdLen = std::strlen(taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->UpdateTaskCount(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, count);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->UpdateTaskCount(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, count);
        }
    }

    return res;
}

u32 Task::GetCount() {
    if (!detail::CheckTaskIdOk(taskId)) {
        return -1;
    }

    u32 taskIdLen = std::strlen(taskId);
    u32 count;

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetTaskCount(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, &count);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetTaskCount(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, &count);
        }
    }

    return count;
}

TaskServiceStatus Task::GetServiceStatus() {
    if (!detail::CheckTaskIdOk(taskId)) {
        return TaskServiceStatus::Unknown0x03;
    }

    u32 taskIdLen = std::strlen(taskId);
    TaskServiceStatus status;

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetTaskServiceStatus(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, &status);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetTaskServiceStatus(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, &status);
        }
    }

    if (res.Failed()) {
        return TaskServiceStatus::Unknown0x03;
    }

    return status;
}

nn::Result Task::Start() {
    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    u32 taskIdLen = std::strlen(taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->StartTask(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->StartTask(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1);
        }
    }

    return res;
}

nn::Result Task::StartImmediate() {
    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    if (!nn::ac::CTR::IsConnected()) {
        // 0xC8A0F848
        return {
            nn::Result::Level_Status, nn::Result::Summary_InvalidState, nn::Result::ModuleType_BOSS, static_cast<int>(ResultCode::NotConnectNetwork)};
    }

    u32 taskIdLen = std::strlen(taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->StartImmediateTask(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->StartImmediateTask(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1);
        }
    }

    return res;
}

nn::Result Task::Cancel() {
    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    u32 taskIdLen = std::strlen(taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->CancelTask(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->CancelTask(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1);
        }
    }

    return res;
}

nn::Result Task::WaitFinish(nn::fnd::TimeSpan &timeout) {
    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    nn::Result res;
    u8 property0x1D;
    TaskStatus status = {};

    do {
        res = GetStateDetail(&status, false, nullptr, STEP_ID_CURRENT);
        if (res.Failed()) {
            return res;
        }

        status.GetProperty(PropertyType::Unknown0x1D, &property0x1D, sizeof(u8));
        if (property0x1D == 6 || property0x1D == 7) {
            return RESULT_SUCCESS;
        }

        if (property0x1D == 5 || property0x1D == 0) {
            return detail::ChangeBossRetCodeToResult(ResultCode::WaitFinishTaskNotDone);
        }

        res = WaitFinishWaitEvent(timeout);
    } while (res.Succeeded());

    return res;
}

TaskStateCode Task::GetState(bool unk, u32 *count, u8 *currentStepId) {
    if (!detail::CheckTaskIdOk(taskId)) {
        return TaskStateCode::Unknown0x09;
    }

    u32 taskIdLen = std::strlen(taskId);
    u32 taskCount;
    u8 taskCurrentStepId;
    TaskStateCode stateCode;

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetTaskState(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, &stateCode, unk, &taskCount, &taskCurrentStepId);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetTaskState(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, &stateCode, unk, &taskCount, &taskCurrentStepId);
        }
    }

    if (res.Failed()) {
        return TaskStateCode::Unknown0x09;
    }

    if (count != nullptr) {
        *count = taskCount;
    }

    if (currentStepId != nullptr) {
        *currentStepId = taskCurrentStepId;
    }

    return stateCode;
}

TaskResultCode Task::GetResult(u32 *count, u8 *currentStepId) {
    if (!detail::CheckTaskIdOk(taskId)) {
        return TaskResultCode::Unknown0x03;
    }

    u32 taskIdLen = std::strlen(taskId);
    u32 taskCount;
    u8 taskCurrentStepId;
    TaskResultCode resultCode;

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetTaskResult(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, &resultCode, &taskCount, &taskCurrentStepId);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetTaskResult(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, &resultCode, &taskCount, &taskCurrentStepId);
        }
    }

    if (res.Failed()) {
        return TaskResultCode::Unknown0x02;
    }

    if (count != nullptr) {
        *count = taskCount;
    }

    if (currentStepId != nullptr) {
        *currentStepId = taskCurrentStepId;
    }

    return resultCode;
}

nn::Result Task::GetStateDetail(TaskStatus *status, bool unk, u8 *currentStepId, u8 stepId) {
    if (status == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskStatus);
    }

    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    u32 taskIdLen = std::strlen(taskId);
    u8 taskCurrentStepId = 0;

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetTaskStatus(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, unk, &taskCurrentStepId, stepId);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetTaskStatus(reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, unk, &taskCurrentStepId, stepId);
        }
    }

    if (res) {
        res = detail::ReceiveUserTaskStatus(&status->statusInfo);
    }

    if (currentStepId != nullptr) {
        *currentStepId = taskCurrentStepId;
    }

    return res;
}

nn::Result Task::SetQuery(TaskQuery *query) {
    if (!detail::CheckTaskIdOk(taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    if (query == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPointer);
    }

    u32 taskIdLen = std::strlen(taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->SetTaskQuery(
            reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, reinterpret_cast<const u8 *>(&query->config), sizeof(TaskQueryConfig));
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->SetTaskQuery(
                reinterpret_cast<const u8 *>(taskId), taskIdLen + 1, reinterpret_cast<const u8 *>(&query->config), sizeof(TaskQueryConfig));
        }
    }

    return res;
}

nn::Result RegisterTask(Task *task, TaskPolicy *policy, TaskAction *action, TaskOption *option, u8 stepId) {
    if (task == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    if (policy == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPolicy);
    }

    if (action == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidAction);
    }

    // Foreground-only tasks are not allowed
    if (!detail::CheckTaskIdOk(task->taskId) || detail::IsFgOnlyTaskId(task->taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    // STEP_ID_CURRENT is a magic value for the current step of a task, it doesn't make sense to use in this context
    if (stepId == STEP_ID_CURRENT) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskStep);
    }

    nn::Result res = detail::VerifyTaskPolicyConfig(policy);
    if (res.Failed()) {
        return res;
    }

    res = detail::VerifyTaskActionConfig(&action->config);
    if (res.Failed()) {
        return res;
    }

    if (option != nullptr) {
        res = detail::VerifyTaskOptionConfig(option);
        if (res.Failed()) {
            return res;
        }
    }

    TaskOptionConfig *optionConfig = nullptr;
    u8 taskOptionsConfigured = option != nullptr;
    if (taskOptionsConfigured) {
        optionConfig = &option->config;
    }

    res = detail::SendUserTaskPolicy(&policy->config);
    if (res.Failed()) {
        return res;
    }

    res = detail::SendUserTaskAction(&action->config);
    if (res.Failed()) {
        return res;
    }

    if (option != nullptr) {
        res = detail::SendUserTaskOption(optionConfig);
        if (res.Failed()) {
            return res;
        }
    }

    u32 taskIdLen = std::strlen(task->taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->RegisterTask(reinterpret_cast<const u8 *>(task->taskId), taskIdLen + 1, taskOptionsConfigured, stepId);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->RegisterTask(reinterpret_cast<const u8 *>(task->taskId), taskIdLen + 1, taskOptionsConfigured, stepId);
        }
    }

    return res;
}

nn::Result UnregisterTask(Task *task, u8 stepId) {
    if (task == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    if (!detail::CheckTaskIdOk(task->taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    u32 taskIdLen = std::strlen(task->taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->UnregisterTask(reinterpret_cast<const u8 *>(task->taskId), taskIdLen + 1, stepId);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->UnregisterTask(reinterpret_cast<const u8 *>(task->taskId), taskIdLen + 1, stepId);
        }
    }

    return res;
}

nn::Result ReconfigureTask(Task *task, TaskPolicy *policy, u8 stepId) {
    if (task == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    if (policy == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPolicy);
    }

    if (!detail::CheckTaskIdOk(task->taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    nn::Result res = detail::VerifyTaskPolicyConfig(policy);
    if (res.Failed()) {
        return res;
    }

    res = detail::SendUserTaskPolicy(&policy->config);
    if (res.Failed()) {
        return res;
    }

    u32 taskIdLen = std::strlen(task->taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->ReconfigureTask(reinterpret_cast<const u8 *>(task->taskId), taskIdLen + 1, stepId);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->ReconfigureTask(reinterpret_cast<const u8 *>(task->taskId), taskIdLen + 1, stepId);
        }
    }

    return res;
}

nn::Result RegisterImmediateTask(Task *task, TaskAction *action, TaskPolicy *policy, TaskOption *option, u8 stepId) {
    if (task == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    if (action == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidAction);
    }

    // Foreground-only tasks are not allowed
    if (!detail::CheckTaskIdOk(task->taskId) || detail::IsFgOnlyTaskId(task->taskId)) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskId);
    }

    // STEP_ID_CURRENT is a magic value for the current step of a task, it doesn't make sense to use in this context
    if (stepId == STEP_ID_CURRENT) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidTaskStep);
    }

    nn::Result res = detail::VerifyTaskActionConfig(&action->config);
    if (res.Failed()) {
        return res;
    }

    if (option != nullptr) {
        res = detail::VerifyTaskOptionConfig(option);
        if (res.Failed()) {
            return res;
        }
    }

    TaskPolicy taskPolicy = {};
    if (policy == nullptr) {
        taskPolicy.InitializeWithSecInterval(1, 1);
        policy = &taskPolicy;
    }

    // NOTE - These properties are originally stored in a shared static variable
    u32 count = 1;
    u32 interval = 1;
    policy->SetProperty(PropertyType::Count, &count, sizeof(u32));
    policy->SetProperty(PropertyType::Interval, &interval, sizeof(u32));

    TaskOptionConfig *optionConfig = nullptr;
    u8 taskOptionsConfigured = option != nullptr;
    if (taskOptionsConfigured) {
        optionConfig = &option->config;
    }

    res = detail::SendUserTaskPolicy(&policy->config);
    if (res.Failed()) {
        return res;
    }

    res = detail::SendUserTaskAction(&action->config);
    if (res.Failed()) {
        return res;
    }

    if (option != nullptr) {
        res = detail::SendUserTaskOption(optionConfig);
        if (res.Failed()) {
            return res;
        }
    }

    u32 taskIdLen = std::strlen(task->taskId);

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->RegisterImmediateTask(reinterpret_cast<const u8 *>(task->taskId), taskIdLen + 1, taskOptionsConfigured, stepId);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->RegisterImmediateTask(reinterpret_cast<const u8 *>(task->taskId), taskIdLen + 1, taskOptionsConfigured, stepId);
        }
    }

    return res;
}

} // namespace boss

} // namespace nn
