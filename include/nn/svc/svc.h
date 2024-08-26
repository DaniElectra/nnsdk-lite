#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/os/types.h"
#include "nn/types.h"

namespace nn {

namespace svc {

nn::Result SleepThread(s64 nanoseconds);
nn::Result CreateAddressArbiter(Handle *arbiter);
nn::Result ArbitrateAddress(Handle arbiter, u32 addr, nn::os::ArbitrationType arbitrationType, s32 value, s64 nanoseconds);
nn::Result CloseHandle(Handle handle);
nn::Result ConnectToPort(Handle *out, const char *portName);
nn::Result SendSyncRequest(Handle handle);

}  // namespace svc

}  // namespace nn
