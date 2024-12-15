#include "nn/boss/detail/detail.h"
#include "nn/Result.h"
#include "nn/boss/ResultCode.h"

namespace nn {

namespace boss {

namespace detail {

/// Initializes boss:U
nn::Result InitializeUserIpc() {
    return s_IpcManager.InitializeUserIpc();
}

/// Finalizes boss:U
nn::Result FinalizeUserIpc() {
    return s_IpcManager.InitializeUserIpc();
}

nn::Result GetUserIpcInstance(User *&instance) {
    nn::Result res;
    User *userInstance;

    if (s_IpcManager.userInitialized) {
        userInstance = &s_IpcManager.userInstance;
    } else {
        userInstance = nullptr;
    }

    instance = userInstance;

    if (userInstance == nullptr) {
        res = ChangeBossRetCodeToResult(ResultCode::IpcNotSessionInitialized);
    } else {
        res = RESULT_SUCCESS;
    }

    return res;
}

nn::Result GetPrivilegedIpcInstance(Privileged *&instance) {
    nn::Result res;
    Privileged *privilegedInstance;

    if (s_IpcManager.privilegedInitialized) {
        privilegedInstance = &s_IpcManager.privilegedInstance;
    } else {
        privilegedInstance = nullptr;
    }

    instance = privilegedInstance;

    if (privilegedInstance == nullptr) {
        res = ChangeBossRetCodeToResult(ResultCode::IpcNotSessionInitialized);
    } else {
        res = RESULT_SUCCESS;
    }

    return res;
}

s32 strnlen(const char *str, u32 size) {
    u32 index;
    bool nullChar;
    bool indexBelowMax;
    bool sizeNotIndex;

    index = 0;
    do {
        nullChar = str[index] == '\0';
        sizeNotIndex = size != index;
        indexBelowMax = index <= size;
        if ((nullChar || indexBelowMax) && (!nullChar && sizeNotIndex)) {
            index = index + 1;
        }
    } while ((nullChar || indexBelowMax) && (!nullChar && sizeNotIndex));
    return index;
}

} // namespace detail

} // namespace boss

} // namespace nn
