#pragma once

#include "nn/Result.h"
#include "nn/types.h"

namespace nn {

namespace boss {

enum class ResultCode : u32 {
    Success = 0,
    Unknown0x01,
    Unknown0x02,
    Unknown0x03,
    Unknown0x04,
    Unknown0x05,
    Unknown0x06,
    Unknown0x07,
    Unknown0x08,
    Unknown0x09,
    Unknown0x0A,
    Unknown0x0B,
    Unknown0x0C,
    Unknown0x0D,
    Unknown0x0E,
    Unknown0x0F,
    Unknown0x10,
    Unknown0x11,
    Unknown0x12,
    Unknown0x13,
    Unknown0x14,
    Unknown0x15,
    Unknown0x16,
    Unknown0x17,
    Unknown0x18,
    Unknown0x19,
    Unknown0x1A,
    Unknown0x1B,
    Unknown0x1C,
    Unknown0x1D,
    Unknown0x1E,
    Unknown0x1F,
    Unknown0x20,
    Unknown0x21,
    Unknown0x22,
    Unknown0x23,
    Unknown0x24,
    Unknown0x25,
    Unknown0x26,
    Unknown0x27,
    Unknown0x28,
    Unknown0x29,
    Unknown0x2A,
    Unknown0x2B,
    Unknown0x2C,
    Unknown0x2D,
    Unknown0x2E,
    Unknown0x2F,
    Unknown0x30,
    Unknown0x31,
    Unknown0x32,
    Unknown0x33,
    Unknown0x34,
    Unknown0x35,
    Unknown0x36,
    Unknown0x37,
    Unknown0x38,
    Unknown0x39,
    Unknown0x3A,
    Unknown0x3B,
    Unknown0x3C,
    Unknown0x3D,
    Unknown0x3E,
    Unknown0x3F,
    Unknown0x40,
    Unknown0x41,
    Unknown0x42,
    Unknown0x43,
    Unknown0x44,
    Unknown0x45,
    Unknown0x46,
    Unknown0x47,
    Unknown0x48,
    Unknown0x49,
    Unknown0x4A,
    Unknown0x4B,
    Unknown0x4C,
    Unknown0x4D,

    Unknown0xC0 = 0xC0,
    Unknown0xC1,
    Unknown0xC2,
    Unknown0xC3,
    Unknown0xC4,
    Unknown0xC5,

    InvalidPointer = 1014,
    NotFound = 1018,
    AlreadyExists = 1020,
    OutOfRange = 1021
};

namespace detail {

/// Returns the \link nn::Result \endlink that matches with the given \link ResultCode \endlink
nn::Result ChangeBossRetCodeToResult(ResultCode code);

} // namespace detail

} // namespace boss

} // namespace nn
