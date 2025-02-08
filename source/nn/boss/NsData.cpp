#include "nn/boss/NsData.h"
#include "nn/Result.h"
#include "nn/boss/NsDataHeaderInfo.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/detail/detail.h"

namespace nn {

namespace boss {

nn::Result NsData::Initialize(u32 nsDataId) {
    this->nsDataId = nsDataId;
    payloadSize = 0;
    offset = 0;
    privilegedAccess = false;

    return RESULT_SUCCESS;
}

nn::Result NsData::Delete() {
    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with privileged access first
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (privilegedAccess) {
        if (res) {
            return privilegedInstance->DeleteNsDataPrivileged(titleId, nsDataId);
        }

        return res;
    }

    // If privileged access is disabled, try the privileged instance without privileged access
    if (res) {
        return privilegedInstance->DeleteNsData(nsDataId);
    }

    // Finally, try with the user instance
    res = detail::GetUserIpcInstance(userInstance);
    if (res) {
        return userInstance->DeleteNsData(nsDataId);
    }

    return res;
}

nn::Result NsData::GetHeaderInfo(HeaderInfoType type, void *buffer, u32 size) {
    if (buffer == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidNsDataValue);
    }

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with privileged access first
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (privilegedAccess) {
        if (res) {
            return privilegedInstance->GetNsDataHeaderInfoPrivileged(titleId, nsDataId, type, reinterpret_cast<u8 *>(buffer), size);
        }

        return res;
    }

    // If privileged access is disabled, try the privileged instance without privileged access
    if (res) {
        return privilegedInstance->GetNsDataHeaderInfo(nsDataId, type, reinterpret_cast<u8 *>(buffer), size);
    }

    // Finally, try with the user instance
    res = detail::GetUserIpcInstance(userInstance);
    if (res) {
        return userInstance->GetNsDataHeaderInfo(nsDataId, type, reinterpret_cast<u8 *>(buffer), size);
    }

    return res;
}

s32 NsData::ReadData(u8 *buffer, u32 size) {
    if (buffer == nullptr || size == 0) {
        return 0;
    }

    // If no payload size is provided from the class, get it ourselves
    if (payloadSize == 0) {
        u32 payloadOutput = payloadSize;

        // NOTE - This should technically use a direct pointer to payloadSize but the compiler complains about using an unaligned pointer
        nn::Result res = GetPayloadSize(&payloadOutput);
        if (res.Failed()) {
            return -1;
        }

        payloadSize = payloadOutput;
    }

    // Adjust the buffer size in case it overflows the payload size
    if (payloadSize < (size + offset)) {
        size = payloadSize - offset;
    }

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with privileged access first
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (privilegedAccess) {
        u32 sizeRead = 0;
        if (res.Failed()) {
            return -3;
        }

        u32 outputVersion;
        res = privilegedInstance->ReadNsDataPrivileged(titleId, nsDataId, offset, buffer, size, &sizeRead, &outputVersion);
        if (res.Failed()) {
            return -2;
        }

        if (version == 0) {
            version = outputVersion;
        }

        if (version == outputVersion) {
            offset += sizeRead;
            return sizeRead;
        }

        return -4;
    }

    u32 sizeRead = 0;

    // If privileged access is disabled, try the privileged instance without privileged access
    if (res) {
        u32 outputVersion;
        res = privilegedInstance->ReadNsData(nsDataId, offset, buffer, size, &sizeRead, &outputVersion);
        if (res.Failed()) {
            return -2;
        }

        if (version == 0) {
            version = outputVersion;
        }

        if (version == outputVersion) {
            offset += sizeRead;
            return sizeRead;
        }

        return -4;
    }

    // Finally, try with the user instance
    res = detail::GetUserIpcInstance(userInstance);
    if (res) {
        u32 outputVersion;
        res = userInstance->ReadNsData(nsDataId, offset, buffer, size, &sizeRead, &outputVersion);
        if (res.Failed()) {
            return -2;
        }

        if (version == 0) {
            version = outputVersion;
        }

        if (version == outputVersion) {
            offset += sizeRead;
            return sizeRead;
        }

        return -4;
    }

    return -3;
}

nn::Result NsData::SetReadFlag(bool flag) {
    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with privileged access first
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (privilegedAccess) {
        if (res) {
            return privilegedInstance->SetNsDataNewFlagPrivileged(titleId, nsDataId, flag);
        }

        return res;
    }

    // If privileged access is disabled, try the privileged instance without privileged access
    if (res) {
        return privilegedInstance->SetNsDataNewFlag(nsDataId, flag);
    }

    // Finally, try with the user instance
    res = detail::GetUserIpcInstance(userInstance);
    if (res) {
        return userInstance->SetNsDataNewFlag(nsDataId, flag);
    }

    return res;
}

nn::Result NsData::GetReadFlag(bool *flag) {
    if (flag == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidNsDataReadFlag);
    }

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with privileged access first
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (privilegedAccess) {
        if (res) {
            return privilegedInstance->GetNsDataNewFlagPrivileged(titleId, nsDataId, flag);
        }

        return res;
    }

    // If privileged access is disabled, try the privileged instance without privileged access
    if (res) {
        return privilegedInstance->GetNsDataNewFlag(nsDataId, flag);
    }

    // Finally, try with the user instance
    res = detail::GetUserIpcInstance(userInstance);
    if (res) {
        return userInstance->GetNsDataNewFlag(nsDataId, flag);
    }

    return res;
}

nn::Result NsData::GetPayloadSize(u32 *size) {
    if (size == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidNsDataValue);
    }

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with privileged access first
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (privilegedAccess) {
        if (res) {
            return privilegedInstance->GetNsDataHeaderInfoPrivileged(
                titleId, nsDataId, HeaderInfoType::PayloadSize, reinterpret_cast<u8 *>(size), sizeof(u32));
        }

        return res;
    }

    // If privileged access is disabled, try the privileged instance without privileged access
    if (res) {
        return privilegedInstance->GetNsDataHeaderInfo(nsDataId, HeaderInfoType::PayloadSize, reinterpret_cast<u8 *>(size), sizeof(u32));
    }

    // Finally, try with the user instance
    res = detail::GetUserIpcInstance(userInstance);
    if (res) {
        return userInstance->GetNsDataHeaderInfo(nsDataId, HeaderInfoType::PayloadSize, reinterpret_cast<u8 *>(size), sizeof(u32));
    }

    return res;
}

} // namespace boss

} // namespace nn
