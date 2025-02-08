#pragma once

#include "nn/types.h"

namespace nn {

namespace boss {

// TODO - Add more state codes
enum class TaskStateCode : u8 {
    Unknown0x00 = 0,
    Unknown0x05 = 5,
    Unknown0x06,
    Unknown0x07,
    Unknown0x09 = 9
};

} // namespace boss

} // namespace nn
