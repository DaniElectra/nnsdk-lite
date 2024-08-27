#include "nn/boss/detail/User.h"
#include "nn/Result.h"
#include "nn/os/ipc.h"
#include "nn/svc/svc.h"

namespace nn {

namespace boss {

namespace detail {

nn::Result User::InitializeSession(u64 titleId) {
    u32* cmdbuf = nn::os::ipc::getThreadCommandBuffer();
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

}  // namespace detail

}  // namespace boss

}  // namespace nn
