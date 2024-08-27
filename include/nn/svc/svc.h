#pragma once

#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/dbg/BreakReason.h"
#include "nn/os/types.h"
#include "nn/types.h"

namespace nn {

namespace svc {

/**
 * @brief Sleeps the current thread for a given amount of time
 * @param nanoseconds The amount of nanoseconds for which the thread will sleep
 */
nn::Result SleepThread(s64 nanoseconds);

/**
 * @brief Creates an address arbiter
 * @param arbiter Output handle for the arbiter
 */
nn::Result CreateAddressArbiter(Handle* arbiter);

/**
 * @brief Arbitrates an address
 * @param arbiter Handle of the arbiter
 * @param addr Address to arbitrate
 * @param arbitrationType Type of arbitration to perform
 * @param value Value for the arbitration
 * @param nanoseconds Time in which the arbitration will timeout
 */
nn::Result ArbitrateAddress(Handle arbiter, u32 addr, nn::os::ArbitrationType arbitrationType, s32 value, s64 nanoseconds);

/**
 * @brief Closes a handle
 * @param handle Handle to close
 */
nn::Result CloseHandle(Handle handle);

/**
 * @brief Connects to the specified port
 * @param handle Output handle for connecting to the port
 * @param portName Name of the port to connect
 */
nn::Result ConnectToPort(Handle* out, const char* portName);

/**
 * @brief Sends a syncronization request to a specified session
 * @param handle Handle of the session
 */
nn::Result SendSyncRequest(Handle handle);

/**
 * @brief Breaks execution of the program
 * @param reason Reason for breaking execution
 */
void Break(nn::dbg::BreakReason reason);

}  // namespace svc

}  // namespace nn
