#pragma once

#include "nn/Result.h"
#include "nn/os/ipc.h"

namespace nn {

namespace ac {

namespace CTR {

namespace detail {

// TODO - Is this really a class or just a namespace?
class Ac {
public:
    // UNOFFICIAL: Guess from nn::ndm
    static nn::os::ipc::Session s_Session;

    // UNOFFICIAL: Guess from context
    static nn::os::ipc::Session s_SessionInternal;

    /**
     * @brief Gets if the console is connected to a network
     * @param unk Unknown parameter
     * @param connected Pointer where the connection status will be written
     */
    static nn::Result IsConnected(u32 unk, bool *connected);

    /**
     * @brief Sets the client SDK version
     * @param version SDK version
     */
    static nn::Result SetClientVersion(u32 version);
};

}  // namespace detail

}  // namespace CTR

}  // namespace ac

}  // namespace nn
