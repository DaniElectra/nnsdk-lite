#pragma once

#include "helpers.h"
#include "nn/Result.h"
#include "nn/boss/NsDataHeaderInfo.h"
#include "nn/types.h"

namespace nn {

namespace boss {

// TODO - Are all of the fields really public? Not sure how they would be set otherwise

/// Represents a container that holds data
class NNSDK_PACKED NsData {
    u32 *vtable;  // The vtable is empty
public:
    INSERT_UNKNOWN_BYTES(4);
    bool privilegedAccess;
    INSERT_UNKNOWN_BYTES(3);
    u32 nsDataId;
    u32 payloadSize;
    u32 unknownOut;
    u64 titleId;
    s64 offset;

    NsData() {
        privilegedAccess = false;
        nsDataId = 0;
        payloadSize = 0;
        unknownOut = 0;
        titleId = 0xA010;  // TODO - What is this?
        offset = 0;
    }

    /**
     * @brief Initializes \link NsData \endlink with the given NS Data ID
     * @param nsDataId NS Data ID
     */
    nn::Result Initialize(u32 nsDataId);

    /// Deletes the \link NsData \endlink
    nn::Result Delete();

    /**
     * @brief Gets header information about the \link NsData \endlink
     * @param type Header info type
     * @param buffer Output buffer
     * @param size Buffer size
     */
    nn::Result GetHeaderInfo(HeaderInfoType type, void *buffer, u32 size);

    /**
     * @brief Reads the content from the \link NsData \endlink
     * @param buffer Output buffer
     * @param size Buffer size
     * @return Size read from the content, or negative value for errors
     */
    s32 ReadData(u8 *buffer, u32 size);

    /**
     * @brief Sets whether the content has been read
     * @param flag Output flag
     */
    nn::Result SetReadFlag(bool flag);

    /**
     * @brief Gets whether the content has been read
     * @param flag Output flag
     */
    nn::Result GetReadFlag(bool *flag);

private:
    /**
     * @brief Gets the payload size of the \link NsData \endlink
     * @remark UNOFFICIAL: This is inlined so the name may be incorrect
     * @param size Output payload size
     */
    nn::Result GetPayloadSize(u32 *size);
};
CHECK_SIZE(NsData, 0x28);
CHECK_OFFSET(NsData, 0x08, privilegedAccess);
CHECK_OFFSET(NsData, 0x0C, nsDataId);
CHECK_OFFSET(NsData, 0x10, payloadSize);
CHECK_OFFSET(NsData, 0x14, unknownOut);
CHECK_OFFSET(NsData, 0x18, titleId);
CHECK_OFFSET(NsData, 0x20, offset);

}  // namespace boss

}  // namespace nn
