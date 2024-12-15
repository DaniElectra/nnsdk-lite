#include "nn/srv/detail/service.h"
#include "nn/os/ipc.h"
#include "nn/svc/svc.h"

#include <cstring>

namespace nn {

namespace srv {

namespace detail {

nn::Result Service::RegisterClient() {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 1, 0, 2, 0); // 0x10002
    nn::os::ipc::WriteProcessIDTranslate(cmdbuf, 1);

    nn::Result res = nn::svc::SendSyncRequest(s_Session.session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Service::GetServiceHandle(Handle *out, const char *service, s32 serviceLen, u32 flags) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 5, 4, 0, 0); // 0x50100
    std::memcpy(&cmdbuf[1], service, 8);
    cmdbuf[3] = serviceLen;
    cmdbuf[4] = flags;

    nn::Result res = nn::svc::SendSyncRequest(s_Session.session);
    if (res) {
        *out = RAW_HANDLE(cmdbuf[2]);
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

} // namespace detail

} // namespace srv

} // namespace nn
