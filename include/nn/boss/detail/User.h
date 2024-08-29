#pragma once

#include "helpers.h"
#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/boss/NsDataHeaderInfo.h"

namespace nn {

namespace boss {

namespace detail {

/// Manages a user session with BOSS
class User {
public:
    nn::Handle session;

    /**
     * @brief Initializes the user session
     * @param titleId Title ID to use for the session, or zero for the current program
     */
    nn::Result InitializeSession(u64 titleId);

    /**
     * @brief Deletes the content for the specified NS Data ID
     * @param nsDataId NS Data ID
     */
    nn::Result DeleteNsData(u32 nsDataId);

    /**
     * @brief Gets header information about the specified NS Data ID
     * @param nsDataId NS Data ID
     * @param type Header info type
     * @param buffer Output buffer
     * @param size Buffer size
     */
    nn::Result GetNsDataHeaderInfo(u32 nsDataId, HeaderInfoType type, u8 *buffer, u32 size);

    /**
     * @brief Reads the content from the specified NS Data ID
     * @param nsDataId NS Data ID
     * @param offset Offset to read from
     * @param buffer Output buffer
     * @param size Buffer size
     * @param sizeRead Size written to the buffer
     * @param unknownOut Unknown output
     */
    nn::Result ReadNsData(u32 nsDataId, s64 offset, u8 *buffer, u32 size, u32 *sizeRead, u32 *unknownOut);

    /**
     * @brief Sets whether the content for the specified NS Data ID has been read
     * @param nsDataId NS Data ID
     * @param flag Read flag
     */
    nn::Result SetNsDataNewFlag(u32 nsDataId, bool flag);

    /**
     * @brief Gets whether the content for the specified NS Data ID has been read
     * @param nsDataId NS Data ID
     * @param flag Output flag
     */
    nn::Result GetNsDataNewFlag(u32 nsDataId, bool *flag);
};
CHECK_SIZE(User, 0x4);
CHECK_OFFSET(User, 0x0, session);

}  // namespace detail

}  // namespace boss

}  // namespace nn
