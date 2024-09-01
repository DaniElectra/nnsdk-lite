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
 * @param unkOut Unknown output parameter
 */
nn::Result GetStorageInfo(u32 *unkOut);

/**
 * @brief Registers storage to be used for BOSS
 * @param lowExtDataId Lower part of the Extra Data ID of the title
 * @param unk1 Unknown parameter
 * @param unk2 Unknown parameter
 * @param storageType Storage type to store the data
 */
nn::Result RegisterStorage(u32 lowExtDataId, u32 unk1, u16 unk2, StorageType storageType);

/// Unregisters the current storage being used
nn::Result UnregisterStorage();

} // namespace boss

} // namespace nn
