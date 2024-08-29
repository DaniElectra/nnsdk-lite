#include "nn/boss/detail/Privileged.h"
#include "nn/Result.h"
#include "nn/os/ipc.h"
#include "nn/svc/svc.h"

namespace nn {

namespace boss {

namespace detail {

nn::Result Privileged::GetNsDataIdList(u32 filter, u32 *list, u32 maxEntries, u16 *outEntries, u16 startIndex, u32 startNsDataId, u16 *lastIndex) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x10, 4, 2, 0);  // 0x100102
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

nn::Result Privileged::DeleteNsData(u32 nsDataId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x26, 1, 0, 0);  // 0x260040
    cmdbuf[1] = nsDataId;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::GetNsDataHeaderInfo(u32 nsDataId, HeaderInfoType type, u8 *buffer, u32 size) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x27, 3, 2, 0);  // 0x2700C2
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

nn::Result Privileged::ReadNsData(u32 nsDataId, s64 offset, u8 *buffer, u32 size, u32 *sizeRead, u32 *unknownOut) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x28, 4, 2, 0);  // 0x280102
    cmdbuf[1] = nsDataId;
    cmdbuf[2] = offset;
    cmdbuf[3] = offset >> 32;
    cmdbuf[4] = size;
    nn::os::ipc::WriteMappedBufferWrite(cmdbuf, 5, buffer, size);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *sizeRead = cmdbuf[2];
        *unknownOut = cmdbuf[3];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::SetNsDataNewFlag(u32 nsDataId, bool flag) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x2B, 2, 0, 0);  // 0x2B0080
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
    nn::os::ipc::WriteHeader(cmdbuf, 0x2C, 1, 0, 0);  // 0x2C0040
    cmdbuf[1] = nsDataId;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        *flag = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::DeleteNsDataPrivileged(u64 titleId, u32 nsDataId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x415, 3, 0, 0);  // 0x41500C0
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
    nn::os::ipc::WriteHeader(cmdbuf, 0x416, 5, 2, 0);  // 0x4160142
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

nn::Result Privileged::ReadNsDataPrivileged(u64 titleId, u32 nsDataId, s64 offset, u8 *buffer, u32 size, u32 *sizeRead, u32 *unknownOut) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x417, 6, 2, 0);  // 0x4170182
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
        *unknownOut = cmdbuf[3];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Privileged::SetNsDataNewFlagPrivileged(u64 titleId, u32 nsDataId, bool flag) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x41A, 4, 0, 0);  // 0x41B0100
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
    nn::os::ipc::WriteHeader(cmdbuf, 0x41B, 3, 0, 0);  // 0x41B00C0
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

}  // namespace detail

}  // namespace boss

}  // namespace nn
