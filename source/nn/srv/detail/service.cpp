#include "nn/srv/detail/service.h"
#include "nn/os/ipc.h"
#include "nn/svc/svc.h"

namespace nn {

namespace srv {

namespace detail {

nn::Result Service::RegisterClient(void) {
    u32* cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 1, 0, 2, 0);
    nn::os::ipc::WriteProcessIDTranslate(cmdbuf, 1);

    nn::Result res = nn::svc::SendSyncRequest(s_Session.session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

}  // namespace detail

}  // namespace srv

}  // namespace nn
