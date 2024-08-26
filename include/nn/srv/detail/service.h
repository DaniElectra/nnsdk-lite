#pragma once

#include "nn/Result.h"
#include "nn/os/ipc.h"

namespace nn {

namespace srv {

namespace detail {

// TODO - Is this really a class or just a namespace?
class Service {
public:
    static nn::os::ipc::Session s_Session;

    static nn::Result RegisterClient();
    static nn::Result GetServiceHandle(Handle* out, const char* service, s32 serviceLen, u32 flags);
};

}  // namespace detail

}  // namespace srv

}  // namespace nn
