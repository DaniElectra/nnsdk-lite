#include "nn/boss/detail/User.h"
#include "nn/Result.h"
#include "nn/os/ipc.h"
#include "nn/svc/svc.h"

namespace nn {

namespace boss {

namespace detail {

nn::Result User::InitializeSession(u64 titleId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 1, 2, 2, 0);  // 0x10082
    cmdbuf[1] = titleId;
    cmdbuf[2] = titleId >> 32;
    nn::os::ipc::WriteProcessIDTranslate(cmdbuf, 3);

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result User::GetNsDataIdList(u32 filter, u32 *list, u32 maxEntries, u16 *outEntries, u16 startIndex, u32 startNsDataId, u16 *lastIndex) {
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

nn::Result User::DeleteNsData(u32 nsDataId) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x26, 1, 0, 0);  // 0x260040
    cmdbuf[1] = nsDataId;

    nn::Result res = nn::svc::SendSyncRequest(session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result User::GetNsDataHeaderInfo(u32 nsDataId, HeaderInfoType type, u8 *buffer, u32 size) {
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

nn::Result User::ReadNsData(u32 nsDataId, s64 offset, u8 *buffer, u32 size, u32 *sizeRead, u32 *unknownOut) {
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

nn::Result User::SetNsDataNewFlag(u32 nsDataId, bool flag) {
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

nn::Result User::GetNsDataNewFlag(u32 nsDataId, bool *flag) {
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

}  // namespace detail

}  // namespace boss

}  // namespace nn
