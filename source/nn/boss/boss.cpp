#include "nn/boss/boss.h"
#include "nn/Result.h"
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

}  // namespace boss

}  // namespace nn
