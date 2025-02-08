#include "nn/boss/storage.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/detail/Privileged.h"
#include "nn/boss/detail/User.h"
#include "nn/boss/detail/detail.h"
#include "nn/fs/MediaType.h"

namespace nn {

namespace boss {

nn::Result GetStorageInfo(u32 *size) {
    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetStorageInfo(size);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetStorageInfo(size);
        }
    }

    return res;
}

nn::Result RegisterStorage(u32 lowExtDataId, u32 size, u16 entryId, StorageType storageType) {
    if (entryId > 0x2000) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidStorageParameter);
    }

    u64 extDataId;
    nn::fs::MediaType mediaType;
    if (storageType != StorageType::SD) {
        extDataId = (static_cast<u64>(0x48000) << 32) | lowExtDataId;
        mediaType = nn::fs::MediaType::NAND;
    } else {
        extDataId = lowExtDataId;
        mediaType = nn::fs::MediaType::SD;
    }

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->RegisterStorageEntry(extDataId, size, entryId, mediaType);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->RegisterStorageEntry(extDataId, size, entryId, mediaType);
        }
    }

    return res;
}

nn::Result UnregisterStorage() {
    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->UnregisterStorage();
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->UnregisterStorage();
        }
    }

    return res;
}

} // namespace boss

} // namespace nn
