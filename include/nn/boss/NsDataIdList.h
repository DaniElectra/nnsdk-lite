#pragma once

#include "helpers.h"
#include "nn/Result.h"
#include "nn/types.h"

namespace nn {

namespace boss {

/// Contains a list of NS Data IDs
class NsDataIdList {
    u32 *vtable; // The vtable is empty
public:
    u16 outEntries;
    u16 lastIndex;
    u32 startNsDataId;
    u32 *list;
    u32 count;

    /**
     * @brief Constructs \link NsDataIdList \endlink with the given parameters
     * @param listBuffer Array of \c u32 for holding the NS Data IDs
     * @param listSize Number of elements that the list can hold
     */
    NsDataIdList(u32 *listBuffer, u16 listSize) {
        lastIndex = 0;
        startNsDataId = 0;
        list = listBuffer;
        count = listSize;
        if (listBuffer == nullptr) {
            count = 0;
        }
    }

    /// Initializes the \link NsDataIdList \endlink
    void Initialize();

    /**
     * @brief Retrieves an NS Data ID from the given index
     * @param index Index to lookup
     * @return NS Data ID from the index or -1 for errors
     */
    u32 GetNsDataId(u16 index);
};
CHECK_SIZE(NsDataIdList, 0x14);
CHECK_OFFSET(NsDataIdList, 0x04, outEntries);
CHECK_OFFSET(NsDataIdList, 0x06, lastIndex);
CHECK_OFFSET(NsDataIdList, 0x08, startNsDataId);
CHECK_OFFSET(NsDataIdList, 0x0C, list);
CHECK_OFFSET(NsDataIdList, 0x10, count);

/**
 * @brief Fills the given \link NsDataIdList \endlink with NS Data IDs
 * @param filter Filter for content datatypes, see https://www.3dbrew.org/wiki/BOSSU:GetNsDataIdList#Filter
 * @param list Output list
 */
nn::Result GetNsDataIdList(u32 filter, NsDataIdList *list);

} // namespace boss

} // namespace nn
