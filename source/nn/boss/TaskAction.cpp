#include "nn/boss/TaskAction.h"
#include "nn/Result.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/common.h"
#include "nn/boss/detail/detail.h"

namespace nn {

namespace boss {

nn::Result TaskActionBase::SetProperty(PropertyType type, const void *buf, u32 size) {
    void *dst;
    u32 diff;

    if (buf == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPropertyValue);
    }

    switch (type) {
        case PropertyType::Url:
            // Prevent overflow
            if (size > URL_SIZE) {
                size = URL_SIZE;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(config.url) + size, URL_SIZE - size);
            std::memset(reinterpret_cast<u8 *>(config.url) + size, 0, URL_SIZE - size);

            dst = config.url;
            break;
        case PropertyType::HeaderFields:
            // Prevent overflow
            if (size > 0x360) {
                size = 0x360;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.headerFields) + size, 0x360 - size);
            std::memset(reinterpret_cast<u8 *>(&config.headerFields) + size, 0, 0x360 - size);

            dst = config.headerFields;
            break;
        case PropertyType::ClientCerts:
            // Prevent overflow
            if (size > 4) {
                size = 4;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(config.clientCerts) + size, 4 - size);
            std::memset(reinterpret_cast<u8 *>(config.clientCerts) + size, 0, 4 - size);

            dst = config.clientCerts;
            break;
        case PropertyType::RootCAs:
            // Prevent overflow
            if (size > 0xC) {
                size = 0xC;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(config.rootCAs) + size, 0xC - size);
            std::memset(reinterpret_cast<u8 *>(config.rootCAs) + size, 0, 0xC - size);

            dst = config.rootCAs;
            break;
        case PropertyType::FSClientCert:
            // Prevent overflow
            if (size > 1) {
                size = 1;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.fsClientCert) + size, size == 0 ? 1 : 0);
            std::memset(reinterpret_cast<u8 *>(&config.fsClientCert) + size, 0, size == 0 ? 1 : 0);

            dst = &config.fsClientCert;
            break;
        case PropertyType::FSRootCA:
            // Prevent overflow
            if (size > 1) {
                size = 1;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.fsRootCA) + size, size == 0 ? 1 : 0);
            std::memset(reinterpret_cast<u8 *>(&config.fsRootCA) + size, 0, size == 0 ? 1 : 0);

            dst = &config.fsRootCA;
            break;
        case PropertyType::ApInfoType:
            // Prevent overflow
            if (size > 1) {
                size = 1;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.apInfoType) + size, size == 0 ? 1 : 0);
            std::memset(reinterpret_cast<u8 *>(&config.apInfoType) + size, 0, size == 0 ? 1 : 0);

            dst = &config.apInfoType;
            break;
        case PropertyType::RootCaCount:
            // Prevent overflow
            if (size > 4) {
                size = 4;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.rootCaCount) + size, 4 - size);
            std::memset(reinterpret_cast<u8 *>(&config.rootCaCount) + size, 0, 4 - size);

            dst = &config.rootCaCount;
            break;
        case PropertyType::ClientCertCount:
            // Prevent overflow
            if (size > 4) {
                size = 4;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.clientCertCount) + size, 4 - size);
            std::memset(reinterpret_cast<u8 *>(&config.clientCertCount) + size, 0, 4 - size);

            dst = &config.rootCaCount;
            break;
        case PropertyType::Unknown0x15:
            // Prevent overflow
            if (size > 0x40) {
                size = 0x40;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(config.property0x15) + size, 0x40 - size);
            std::memset(reinterpret_cast<u8 *>(config.property0x15) + size, 0, 0x40 - size);

            dst = config.property0x15;
            break;
        case PropertyType::Unknown0x16:
            // Prevent overflow
            if (size > 4) {
                size = 4;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.property0x16) + size, 4 - size);
            std::memset(reinterpret_cast<u8 *>(&config.property0x16) + size, 0, 4 - size);

            dst = &config.property0x16;
            break;
        case PropertyType::CfgInfoType:
            // Prevent overflow
            if (size > 1) {
                size = 1;
            }

            // Clear the bytes that won't be set

            // memclr(reinterpret_cast<u8 *>(&config.cfgInfoType) + size, size == 0 ? 1 : 0);
            std::memset(reinterpret_cast<u8 *>(&config.cfgInfoType) + size, 0, size == 0 ? 1 : 0);

            dst = &config.cfgInfoType;
            break;
        default:
            return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPropertyType);
    }

    std::memcpy(dst, buf, size);
    return RESULT_SUCCESS;
}

nn::Result TaskActionBase::SetApInfoType(u8 infoType) {
    config.apInfoType = infoType;
    return RESULT_SUCCESS;
}

nn::Result TaskActionBase::SetCfgInfoType(u8 infoType) {
    config.cfgInfoType = infoType;
    return RESULT_SUCCESS;
}

nn::Result TaskActionBase::AddHeaderField(const char *header, const char *value) {
    u32 length;
    u32 diff;
    u32 index;

    if (header == nullptr || value == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::HttpRequestHeaderPointerNull);
    }

    index = 0;

    do {
        if (config.headerFields[index].header[0] == '\0') {
            // Clear the part of the header string that will be empty
            length = detail::strnlen(header, HTTP_HEADER_SIZE - 1);
            if (length < HTTP_HEADER_SIZE) {
                diff = HTTP_HEADER_SIZE - length;
            } else {
                diff = 0;
            }

            // memclr(config.headerFields[index].header + length, diff);
            std::memset(config.headerFields[index].header + length, 0, diff);

            // And now, copy the string
            if (HTTP_HEADER_SIZE - 1 < length) {
                length = HTTP_HEADER_SIZE;
            }
            std::memcpy(&config.headerFields[index].header, header, length);

            // Clear the part of the value string that will be empty
            length = detail::strnlen(value, HTTP_HEADER_VALUE_SIZE - 1);
            if (length < HTTP_HEADER_VALUE_SIZE) {
                diff = HTTP_HEADER_VALUE_SIZE - length;
            } else {
                diff = 0;
            }

            // memclr(config.headerFields[index].value + length, diff);
            std::memset(config.headerFields[index].value + length, 0, diff);

            // And now, copy the string
            if (HTTP_HEADER_VALUE_SIZE - 1 < length) {
                length = HTTP_HEADER_VALUE_SIZE;
            }
            std::memcpy(config.headerFields[index].value, value, length);
            break;
        }

        index = index + 1 & 0xFF;
    } while (index < MAX_HEADERS);

    if (index != MAX_HEADERS) {
        return RESULT_SUCCESS;
    }

    return detail::ChangeBossRetCodeToResult(ResultCode::InvalidMaxHttpRequestHeader);
}

nn::Result TaskActionBase::SetRootCa(u32 certId) {
    u32 nextIndex = config.rootCaCount;

    // Check if the cert ID was already set
    if (config.rootCaCount != 0) {
        for (u32 i = 0; i < MAX_ROOT_CAS; i++) {
            if (config.rootCAs[i] == certId) {
                return RESULT_SUCCESS;
            }
        }
    }

    if (nextIndex < MAX_ROOT_CAS) {
        config.rootCAs[nextIndex] = certId;
        config.rootCaCount++;
        return RESULT_SUCCESS;
    }

    return detail::ChangeBossRetCodeToResult(ResultCode::InvalidPolicy4);
}

nn::Result TaskActionBase::SetClientCert(u32 certId) {
    u32 nextIndex = config.clientCertCount;

    // Check if the cert ID was already set
    if (config.clientCertCount != 0) {
        for (u32 i = 0; i < MAX_CLIENT_CERTS; i++) {
            if (config.clientCerts[i] == certId) {
                return RESULT_SUCCESS;
            }
        }
    }

    if (nextIndex < MAX_CLIENT_CERTS) {
        config.clientCerts[nextIndex] = certId;
        config.clientCertCount++;
        return RESULT_SUCCESS;
    }

    return detail::ChangeBossRetCodeToResult(ResultCode::InvalidMaxClientCert);
}

nn::Result FileListAction::Initialize(const char *url, nn::Handle handle) {
    if (url == nullptr || url[0] == '\0') {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidUrl);
    }

    u32 size = detail::strnlen(url, URL_SIZE);
    if (size > URL_SIZE) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidUrl);
    }

    // memclr(&config, sizeof(config));
    std::memset(&config, 0, sizeof(config));

    config.code = ActionCodeFileList;
    std::strncpy(config.url, url, URL_SIZE);

    config.fileHandle = handle;
    config.property0x9 = 2;

    return RESULT_SUCCESS;
}

nn::Result NsaDownloadAction::Initialize(const char *url) {
    Result res;

    if (url == nullptr || url[0] == '\0') {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidUrl);
    }

    u32 size = detail::strnlen(url, URL_SIZE);
    if (size > URL_SIZE - 1) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidUrl);
    }

    // memclr(&config, sizeof(config));
    std::memset(&config, 0, sizeof(config));

    config.code = ActionCodeNsaDownload;
    std::strncpy(config.url, url, URL_SIZE);

    res = SetRootCa(7);
    if (res.Failed()) {
        return res;
    }

    res = SetRootCa(3);
    if (res.Failed()) {
        return res;
    }
    res = SetRootCa(6);
    if (res.Failed()) {
        return res;
    }

    return RESULT_SUCCESS;
}

nn::Result UploadAction::Initialize(const char *url, nn::Handle handle, FileDescriptor fd) {
    if (url == nullptr || url[0] == '\0') {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidUrl);
    }

    u32 size = detail::strnlen(url, URL_SIZE);
    if (size > URL_SIZE - 1) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidUrl);
    }

    // memclr(&config, sizeof(config));
    std::memset(&config, 0, sizeof(config));

    config.code = ActionCodeUpload;
    std::strncpy(config.url, url, URL_SIZE - 1);

    config.fileHandle = handle;
    config.property0x9 = fd;

    return RESULT_SUCCESS;
}

nn::Result DataStoreDownloadAction::Initialize(u32 gameServerId, const char16_t *accessKey) {
    if (accessKey == nullptr) {
        // 0xD8E0FBF6
        return {
            nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, nn::Result::ModuleType_BOSS, nn::Result::Description_InvalidPointer};
    }

    u32 size = detail::wcsnlen(accessKey, URL_SIZE);
    if (size == 0 || size > 8) {
        // 0xD8E0FBEC
        return {nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, nn::Result::ModuleType_BOSS, nn::Result::Description_InvalidSize};
    }

    // memclr(&config, sizeof(config));
    std::memset(&config, 0, sizeof(config));
    config.code = ActionCodeDataStoreDownload;
    config.property0x9 = 5;
    *reinterpret_cast<u32 *>(config.actionData) = gameServerId;
    std::memcpy(config.actionData + 4, accessKey, size * 2);

    return RESULT_SUCCESS;
}

} // namespace boss

} // namespace nn
