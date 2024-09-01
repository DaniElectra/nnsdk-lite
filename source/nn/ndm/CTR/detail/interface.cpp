#include "nn/ndm/CTR/detail/interface.h"
#include "nn/svc/svc.h"

namespace nn {

namespace ndm {

namespace CTR {

namespace detail {

nn::Result Interface::LeaveExclusiveState() {
    u32 *cmdbuf = nn::os::ipc::getThreadCommandBuffer();
    nn::os::ipc::WriteHeader(cmdbuf, 2, 0, 2, 0); // 0x20002
    nn::os::ipc::WriteProcessIDTranslate(cmdbuf, 1);

    nn::Result res = nn::svc::SendSyncRequest(s_Session.session);
    if (res) {
        res = RAW_RESULT(cmdbuf[1]);
    }

    return res;
}

} // namespace detail

} // namespace CTR

} // namespace ndm

} // namespace nn
