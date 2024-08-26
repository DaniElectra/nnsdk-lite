#include "nn/ac/CTR/detail/ac.h"
#include "nn/os/ipc.h"
#include "nn/svc/svc.h"

namespace nn {

namespace ac {

namespace CTR {

namespace detail {

nn::Result Ac::IsConnected(u32 unk, bool *connected) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x3E, 1, 2, 0); // 0x3E0042
    cmdbuf[1] = unk;
    nn::os::ipc::WriteProcessIDTranslate(cmdbuf, 2);

    nn::Result res = nn::svc::SendSyncRequest(s_Session.session);
    if (res) {
        *connected = cmdbuf[2];
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

nn::Result Ac::SetClientVersion(u32 version) {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 0x40, 1, 2, 0); // 0x400042
    cmdbuf[1] = version;
    nn::os::ipc::WriteProcessIDTranslate(cmdbuf, 2);

    nn::Result res = nn::svc::SendSyncRequest(s_Session.session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

}  // namespace detail

}  // namespace CTR

}  // namespace ac

}  // namespace nn
