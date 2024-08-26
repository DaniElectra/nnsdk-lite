#include "nn/ndm/ndm.h"
#include "nn/ndm/CTR/detail/interface.h"
#include "nn/Result.h"
#include "nn/os/sync.h"
#include "nn/srv/srv.h"
#include "nn/svc/svc.h"

#include <cstring>

namespace {
    static nn::os::CriticalSection s_cs;
}

namespace nn {

namespace ndm {

// UNOFFICIAL: Guessing from nn::srv
namespace {
    static u32 s_InitializedCount;
    static constexpr auto PORT_NAME_USER = "ndm:u";
}  // namespace

nn::Result Initialize() {
    s_cs.Enter();

    // We only need to initialize the first time
    if (s_InitializedCount == 0) {
        nn::srv::Initialize();
        nn::Result res = nn::srv::GetServiceHandle(&CTR::detail::Interface::s_Session.session, PORT_NAME_USER, std::strlen(PORT_NAME_USER), 0);
        if (res.Failed()) {
            s_cs.Leave();
            return res;
        }
    }

    s_InitializedCount++;
    s_cs.Leave();
    return RESULT_SUCCESS;
}

nn::Result Finalize() {
    s_cs.Enter();

    if (s_InitializedCount == 0) {
        s_cs.Leave();
        // 0xC8A06BF8
        return {nn::Result::Level_Status, nn::Result::Summary_InvalidState, nn::Result::ModuleType_NDM, nn::Result::Description_NotInitialized};
    }

    // If there is only one reference remaining, close the handle
    if (s_InitializedCount == 1) {
        nn::Result res = nn::svc::CloseHandle(CTR::detail::Interface::s_Session.session);
        if (res.Failed()) {
            s_cs.Leave();
            return res;
        }

        CTR::detail::Interface::s_Session.session = {}; // Clear handle
    }

    s_InitializedCount--;
    s_cs.Leave();
    return RESULT_SUCCESS;
}

nn::Result LeaveExclusiveState() {
    return CTR::detail::Interface::LeaveExclusiveState();
}

}  // namespace ndm

}  // namespace nn
