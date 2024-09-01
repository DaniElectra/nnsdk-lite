#include "nn/boss/boss.h"
#include "nn/Result.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/TaskResultCode.h"
#include "nn/boss/detail/detail.h"
#include "nn/ndm/ndm.h"

namespace nn {

namespace boss {

// UNOFFICIAL: Guess from other services
namespace {

static bool s_IsInitialized;

}

nn::Result Initialize() {
    if (s_IsInitialized) {
        return RESULT_SUCCESS;
    }

    s_IsInitialized = true;

    nn::Result res = nn::ndm::Initialize();
    if (res.Failed()) {
        return res;
    }

    return detail::InitializeUserIpc();
}

nn::Result Finalize() {
    if (!s_IsInitialized) {
        return RESULT_SUCCESS;
    }

    s_IsInitialized = false;

    nn::ndm::Finalize();
    return detail::FinalizeUserIpc();
}

nn::Result GetErrorCode(u32 *errorCode, TaskResultCode result) {
    if (errorCode == nullptr) {
        return {nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, nn::Result::ModuleType_BOSS, static_cast<int>(ResultCode::Unknown0x4D)};
    }

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetErrorCode(errorCode, result);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetErrorCode(errorCode, result);
        }
    }

    return res;
}

} // namespace boss

} // namespace nn
