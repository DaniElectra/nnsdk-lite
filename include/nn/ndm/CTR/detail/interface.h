#pragma once

#include "nn/Result.h"
#include "nn/os/ipc.h"

namespace nn {

namespace ndm {

namespace CTR {

namespace detail {

// TODO - Is this really a class or just a namespace?
class Interface {
public:
    static nn::os::ipc::Session s_Session;

    /// Leaves the exclusive state
    static nn::Result LeaveExclusiveState();
};

} // namespace detail

} // namespace CTR

} // namespace ndm

} // namespace nn
