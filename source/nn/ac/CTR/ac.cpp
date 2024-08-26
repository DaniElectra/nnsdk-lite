#include "nn/ac/CTR/ac.h"
#include "nn/ac/CTR/detail/ac.h"
#include "nn/os/sync.h"
#include "nn/srv/srv.h"
#include "nn/svc/svc.h"

#include <cstring>

namespace nn {

namespace ac {

namespace CTR {

// UNOFFICIAL: Guess from nn::ndm
namespace {

static u32 s_InitializedCount;
static nn::os::CriticalSection s_cs = nn::os::CriticalSection();
static constexpr auto PORT_NAME_USER = "ac:u";

}  // namespace

bool IsInitializedInternal() {
    return detail::Ac::s_SessionInternal.session.m_Handle != 0;
}

nn::Result Initialize() {
    s_cs.Enter();

    if (IsInitializedInternal()) {
        s_cs.Leave();
        // 0xD8A09FF9
        return {nn::Result::Level_Permanent, nn::Result::Summary_InvalidState, nn::Result::ModuleType_AC, nn::Result::Description_AlreadyInitialized};
    }

    s_cs.Enter();
    bool alreadyInitialized = s_InitializedCount != 0;
    s_cs.Leave();
    if (alreadyInitialized) {
        s_InitializedCount++;
        s_cs.Leave();
        // 0x209FF9
        return {nn::Result::Level_Success, nn::Result::Summary_Nop, nn::Result::ModuleType_AC, nn::Result::Description_AlreadyInitialized};
    }

    nn::Result res = nn::srv::Initialize();
    if (res.Failed()) {
        s_cs.Leave();
        return res;
    }

    res = nn::srv::GetServiceHandle(&detail::Ac::s_Session.session, PORT_NAME_USER, std::strlen(PORT_NAME_USER), 0);
    if (res.Failed()) {
        s_cs.Leave();
        return res;
    }

    s_InitializedCount++;
    detail::Ac::SetClientVersion(0xB0301C8);  // 11.3.1-200
    s_cs.Leave();
    return RESULT_SUCCESS;
}

nn::Result Finalize() {
    s_cs.Enter();

    s_cs.Enter();
    bool notInitialized = s_InitializedCount == 0;
    s_cs.Leave();

    if (notInitialized) {
        s_cs.Leave();
        // 0x209FF8
        return {nn::Result::Level_Success, nn::Result::Summary_Nop, nn::Result::ModuleType_AC, nn::Result::Description_NotInitialized};
    }

    // TODO - Implement this
    // anonymous_namespace::NdmLeaveExclusive();

    s_InitializedCount--;
    if (s_InitializedCount == 0) {
        nn::Result res = nn::svc::CloseHandle(detail::Ac::s_Session.session);
        if (res.Failed()) {
            s_cs.Leave();
            return res;
        }
    }

    s_cs.Leave();
    return RESULT_SUCCESS;
}

bool IsConnected() {
    s_cs.Enter();
    const bool initialized = s_InitializedCount != 0;
    s_cs.Leave();

    // If neither ac:u and ac:i are initialized, assume we are not connected
    if (!initialized && !IsInitializedInternal()) {
        return false;
    }

    bool connected = false;
    detail::Ac::IsConnected(0, &connected);
    return connected;
}

}  // namespace CTR

}  // namespace ac

}  // namespace nn
