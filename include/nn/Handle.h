#pragma once

#include "helpers.h"
#include "nn/types.h"

// Imported from https://github.com/3dsdecomp/nnsdk/blob/main/Include/nn/Handle.h

namespace nn {

struct Handle {
    u32 m_Handle;

    Handle() : m_Handle(0) {}
};
CHECK_SIZE(Handle, 4);

// Helper macro for transforming a raw value into an nn::Handle
#define RAW_HANDLE(res) (*reinterpret_cast<nn::Handle *>(&res))

} // namespace nn
