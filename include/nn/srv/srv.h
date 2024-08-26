#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/os/ipc.h"

namespace nn {

namespace srv {

nn::Result Initialize();
nn::Result GetServiceHandle(nn::Handle *out, const char *service, s32 serviceLen, u32 flags);
nn::Result GetServiceHandle(nn::os::ipc::Session *outSession, const char *service);

}  // namespace srv

}  // namespace nn
