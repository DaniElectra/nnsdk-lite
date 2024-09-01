#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/os/ipc.h"

namespace nn {

namespace srv {

/**
 * @brief Initializes the Service Manager
 */
nn::Result Initialize();

/**
 * @brief Gets a handle for a service with the given flags
 * @param out Output handle of the service
 * @param service Name of the service
 * @param serviceLen Length of the service name
 * @param flags Flags, see https://www.3dbrew.org/wiki/SRV:GetServiceHandle
 */
nn::Result GetServiceHandle(nn::Handle *out, const char *service, s32 serviceLen, u32 flags);

/**
 * @brief Gets a handle for a service
 * @param outSession Output session of the service
 * @param service Name of the service
 */
nn::Result GetServiceHandle(nn::os::ipc::Session *outSession, const char *service);

} // namespace srv

} // namespace nn
