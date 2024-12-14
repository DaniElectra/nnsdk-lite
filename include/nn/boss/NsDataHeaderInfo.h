#pragma once

#include "helpers.h"
#include "nn/types.h"

namespace nn {

namespace boss {

// UNOFFICIAL: The struct name may not be correct

/// Contains all information about a @link NsData @endlink
struct NsDataHeaderInfo {
    u64 titleId;
    u32 unknown;
    u32 dataType;
    u32 payloadSize;
    u32 nsDataId;
    u32 version;
    INSERT_UNKNOWN_BYTES(4);
};
CHECK_SIZE(NsDataHeaderInfo, 0x20);
CHECK_OFFSET(NsDataHeaderInfo, 0x00, titleId);
CHECK_OFFSET(NsDataHeaderInfo, 0x08, unknown);
CHECK_OFFSET(NsDataHeaderInfo, 0x0C, dataType);
CHECK_OFFSET(NsDataHeaderInfo, 0x10, payloadSize);
CHECK_OFFSET(NsDataHeaderInfo, 0x14, nsDataId);
CHECK_OFFSET(NsDataHeaderInfo, 0x18, version);

enum class HeaderInfoType : u8 {
    TitleId = 0,
    Unknown,
    DataType,
    PayloadSize,
    NsDataId,
    Version,
    Everything
};

} // namespace boss

} // namespace nn
