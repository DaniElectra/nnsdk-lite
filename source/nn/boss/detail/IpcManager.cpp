#include "nn/boss/detail/IpcManager.h"
#include "nn/Result.h"
#include "nn/boss/ResultCode.h"
#include "nn/dbg/dbg.h"
#include "nn/srv/srv.h"
#include "nn/svc/svc.h"

namespace nn {

namespace boss {

namespace detail {

// UNOFFICIAL: Guess from other services
namespace {

constexpr auto PORT_NAME_USER = "boss:U";

}

nn::Result IpcManager::InitializeUserIpc() {
    if (userInitialized) {
        return ChangeBossRetCodeToResult(ResultCode::Unknown0x2E);
    }

    nn::Result res = nn::srv::Initialize();
    if (res.Failed()) {
        nn::dbg::Panic();
    }

    res = nn::srv::GetServiceHandle(&userSession, PORT_NAME_USER);
    if (res.Failed()) {
        return res;
    }

    // Pass the session handle to the user instance
    userInstance.session = userSession.session;

    res = userInstance.InitializeSession(titleId);
    if (res.Failed()) {
        // If we couldn't initialize the session, close the handle and clear it up
        if (userSession.session.m_Handle != 0) {
            nn::svc::CloseHandle(userSession.session);
            userSession.session.m_Handle = 0;
        }

        return res;
    }

    userInitialized = true;
    return res;
}

nn::Result IpcManager::FinalizeUserIpc() {
    if (!userInitialized) {
        return ChangeBossRetCodeToResult(ResultCode::Unknown0x2B);
    }

    if (userSession.session.m_Handle != 0) {
        nn::svc::CloseHandle(userSession.session);
        userSession.session.m_Handle = 0;
    }

    userInitialized = false;
    return RESULT_SUCCESS;
}

}  // namespace detail

}  // namespace boss

}  // namespace nn
