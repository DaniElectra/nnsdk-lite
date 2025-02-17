#include "nn/boss/detail/Privileged.h"
#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/TaskServiceStatus.h"
#include "nn/os/ipc.h"
#include "nn/svc/svc.h"

namespace nn {

namespace boss {

namespace detail {

nn::Result Privileged::GetStorageInfo(u32 *size) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 4, 0, 0, 0); // 0x40000

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *size = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::RegisterTask(const u8 *taskId, u32 taskIdSize, u8 taskOptionsConfigured, u8 stepId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0xB, 3, 2, 0); // 0xB00C2
    cmdbuf[1] = taskIdSize;
    cmdbuf[2] = taskOptionsConfigured;
    cmdbuf[3] = stepId;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 4, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::UnregisterTask(const u8 *taskId, u32 taskIdSize, u8 stepId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0xC, 2, 2, 0); // 0xC0082
    cmdbuf[1] = taskIdSize;
    cmdbuf[2] = stepId;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 3, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::ReconfigureTask(const u8 *taskId, u32 taskIdSize, u8 stepId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0xD, 2, 2, 0); // 0xD0082
    cmdbuf[1] = taskIdSize;
    cmdbuf[2] = stepId;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 3, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetTaskIdList() {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0xE, 0, 0, 0); // 0xE0000

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetStepIdList(const u8 *taskId, u32 taskIdSize) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0xF, 1, 2, 0); // 0xF0042
    cmdbuf[1] = taskIdSize;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 2, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetNsDataIdList(u32 filter, u32 *list, u32 maxEntries, u16 *outEntries, u16 startIndex, u32 startNsDataId, u16 *lastIndex) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x10, 4, 2, 0); // 0x100102
    cmdbuf[1] = filter;
    cmdbuf[2] = maxEntries;
    cmdbuf[3] = startIndex;
    cmdbuf[4] = startNsDataId;
    nn::os::ipc::WriteMappedBufferWrite(cmdbuf, 5, list, maxEntries * sizeof(u32));

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *outEntries = cmdbuf[2];
        *lastIndex = cmdbuf[3];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::SendProperty(PropertyType type, const u8 *buffer, u32 size) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x14, 2, 2, 0); // 0x140082
    cmdbuf[1] = static_cast<u16>(type);
    cmdbuf[2] = size;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 3, buffer, size);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::SendPropertyHandle(PropertyType type, nn::Handle handle) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x15, 1, 2, 0); // 0x150042
    cmdbuf[1] = static_cast<u16>(type);
    nn::os::ipc::WriteHandleCopyTranslate(cmdbuf, 2, 1);
    cmdbuf[3] = handle.m_Handle;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::ReceiveProperty(PropertyType type, u8 *buffer, u32 size, u32 *sizeRead) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x16, 2, 2, 0); // 0x160082
    cmdbuf[1] = static_cast<u16>(type);
    cmdbuf[2] = size;
    nn::os::ipc::WriteMappedBufferWrite(cmdbuf, 3, buffer, size);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *sizeRead = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::UpdateTaskCount(const u8 *taskId, u32 taskIdSize, u32 count) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x18, 2, 2, 0); // 0x180082
    cmdbuf[1] = taskIdSize;
    cmdbuf[2] = count;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 2, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetTaskCount(const u8 *taskId, u32 taskIdSize, u32 *count) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x1A, 1, 2, 0); // 0x1A0042
    cmdbuf[1] = taskIdSize;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 2, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *count = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetTaskServiceStatus(const u8 *taskId, u32 taskIdSize, TaskServiceStatus *status) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x1B, 1, 2, 0); // 0x1B0042
    cmdbuf[1] = taskIdSize;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 2, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *status = static_cast<TaskServiceStatus>(cmdbuf[2]);
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::StartTask(const u8 *taskId, u32 taskIdSize) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x1C, 1, 2, 0); // 0x1C0042
    cmdbuf[1] = taskIdSize;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 2, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::StartImmediateTask(const u8 *taskId, u32 taskIdSize) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x1D, 1, 2, 0); // 0x1D0042
    cmdbuf[1] = taskIdSize;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 2, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::CancelTask(const u8 *taskId, u32 taskIdSize) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x1E, 1, 2, 0); // 0x1E0042
    cmdbuf[1] = taskIdSize;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 2, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetTaskFinishHandle(Handle *handle) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x1F, 0, 0, 0); // 0x1F0000

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        handle->m_Handle = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetTaskState(const u8 *taskId, u32 taskIdSize, TaskStateCode *stateCode, bool unk, u32 *count, u8 *currentStepId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x20, 2, 2, 0); // 0x200082
    cmdbuf[1] = taskIdSize;
    cmdbuf[2] = unk;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 3, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *stateCode = static_cast<TaskStateCode>(cmdbuf[2]);
        *count = cmdbuf[3];
        *currentStepId = cmdbuf[4];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetTaskResult(const u8 *taskId, u32 taskIdSize, TaskResultCode *resultCode, u32 *count, u8 *currentStepId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x21, 1, 2, 0); // 0x210042
    cmdbuf[1] = taskIdSize;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 2, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *resultCode = static_cast<TaskResultCode>(cmdbuf[2]);
        *count = cmdbuf[3];
        *currentStepId = cmdbuf[4];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetTaskStatus(const u8 *taskId, u32 taskIdSize, bool unk, u8 *currentStepId, u8 stepId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x23, 3, 2, 0); // 0x2300C2
    cmdbuf[1] = taskIdSize;
    cmdbuf[2] = unk;
    cmdbuf[3] = stepId;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 4, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *currentStepId = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::DeleteNsData(u32 nsDataId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x26, 1, 0, 0); // 0x260040
    cmdbuf[1] = nsDataId;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetNsDataHeaderInfo(u32 nsDataId, HeaderInfoType type, u8 *buffer, u32 size) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x27, 3, 2, 0); // 0x2700C2
    cmdbuf[1] = nsDataId;
    cmdbuf[2] = static_cast<u32>(type);
    cmdbuf[3] = size;
    nn::os::ipc::WriteMappedBufferWrite(cmdbuf, 4, buffer, size);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::ReadNsData(u32 nsDataId, s64 offset, u8 *buffer, u32 size, u32 *sizeRead, u32 *version) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x28, 4, 2, 0); // 0x280102
    cmdbuf[1] = nsDataId;
    cmdbuf[2] = offset;
    cmdbuf[3] = offset >> 32;
    cmdbuf[4] = size;
    nn::os::ipc::WriteMappedBufferWrite(cmdbuf, 5, buffer, size);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *sizeRead = cmdbuf[2];
        *version = cmdbuf[3];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::SetNsDataNewFlag(u32 nsDataId, bool flag) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x2B, 2, 0, 0); // 0x2B0080
    cmdbuf[1] = nsDataId;
    cmdbuf[2] = flag;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetNsDataNewFlag(u32 nsDataId, bool *flag) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x2C, 1, 0, 0); // 0x2C0040
    cmdbuf[1] = nsDataId;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *flag = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetErrorCode(u32 *errorCode, TaskResultCode result) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x2E, 1, 0, 0); // 0x2E0040
    cmdbuf[1] = static_cast<u32>(result);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *errorCode = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::RegisterStorageEntry(u64 extDataId, u32 size, u16 entryId, nn::fs::MediaType mediaType) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x2F, 5, 0, 0); // 0x2F0140
    cmdbuf[1] = extDataId;
    cmdbuf[2] = extDataId >> 32;
    cmdbuf[3] = size;
    cmdbuf[4] = entryId;
    cmdbuf[5] = static_cast<u32>(mediaType);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::UnregisterStorage() {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x30, 0, 0, 0); // 0x300000

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::RegisterImmediateTask(const u8 *taskId, u32 taskIdSize, u8 taskOptionsConfigured, u8 stepId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x35, 3, 2, 0); // 0x3500C2
    cmdbuf[1] = taskIdSize;
    cmdbuf[2] = taskOptionsConfigured;
    cmdbuf[3] = stepId;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 4, taskId, taskIdSize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::SetTaskQuery(const u8 *taskId, u32 taskIdSize, const u8 *query, u32 querySize) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x36, 2, 4, 0); // 0x360084
    cmdbuf[1] = taskIdSize;
    cmdbuf[2] = querySize;
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 3, taskId, taskIdSize);
    nn::os::ipc::WriteMappedBufferRead(cmdbuf, 5, query, querySize);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetAppIdList() {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x40A, 0, 0, 0); // 0x40A0000

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::DeleteNsDataPrivileged(u64 titleId, u32 nsDataId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x415, 3, 0, 0); // 0x41500C0
    cmdbuf[1] = titleId;
    cmdbuf[2] = titleId >> 32;
    cmdbuf[3] = nsDataId;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetNsDataHeaderInfoPrivileged(u64 titleId, u32 nsDataId, HeaderInfoType type, u8 *buffer, u32 size) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x416, 5, 2, 0); // 0x4160142
    cmdbuf[1] = titleId;
    cmdbuf[2] = titleId >> 32;
    cmdbuf[3] = nsDataId;
    cmdbuf[4] = static_cast<u32>(type);
    cmdbuf[5] = size;
    nn::os::ipc::WriteMappedBufferWrite(cmdbuf, 6, buffer, size);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::ReadNsDataPrivileged(u64 titleId, u32 nsDataId, s64 offset, u8 *buffer, u32 size, u32 *sizeRead, u32 *version) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x417, 6, 2, 0); // 0x4170182
    cmdbuf[1] = titleId;
    cmdbuf[2] = titleId >> 32;
    cmdbuf[3] = nsDataId;
    cmdbuf[4] = offset;
    cmdbuf[5] = offset >> 32;
    cmdbuf[6] = size;
    nn::os::ipc::WriteMappedBufferWrite(cmdbuf, 7, buffer, size);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *sizeRead = cmdbuf[2];
        *version = cmdbuf[3];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::SetNsDataNewFlagPrivileged(u64 titleId, u32 nsDataId, bool flag) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x41A, 4, 0, 0); // 0x41B0100
    cmdbuf[1] = titleId;
    cmdbuf[2] = titleId >> 32;
    cmdbuf[3] = nsDataId;
    cmdbuf[4] = flag;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetNsDataNewFlagPrivileged(u64 titleId, u32 nsDataId, bool *flag) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x41B, 3, 0, 0); // 0x41B00C0
    cmdbuf[1] = titleId;
    cmdbuf[2] = titleId >> 32;
    cmdbuf[3] = nsDataId;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *flag = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

} // namespace detail

} // namespace boss

} // namespace nn
