#pragma once

#include "nn/Result.h"
#include "nn/types.h"

namespace nn {

namespace boss {

enum class StorageType : u8 {
    SD = 0,
    NAND
};

/**
 * @brief Gets information about the current storage
 * @param size Output storage space reserved
 */
nn::Result GetStorageInfo(u32 *size);

/**
 * @brief Registers storage to be used for BOSS
 * @param lowExtDataId Lower part of the Extra Data ID of the title
 * @param size Storage space to reserve
 * @param entryId Entry ID? Can be up to 0x2000
 * @param storageType Storage type to store the data
 */
nn::Result RegisterStorage(u32 lowExtDataId, u32 size, u16 entryId, StorageType storageType);

/// Unregisters the current storage being used
nn::Result UnregisterStorage();

} // namespace boss

} // namespace nn
