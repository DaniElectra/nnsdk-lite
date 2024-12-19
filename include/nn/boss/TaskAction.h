#pragma once

#include <cstring>

#include "helpers.h"
#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/types.h"

namespace nn {

namespace boss {

constexpr int ACTION_DATA_SIZE = 0x200;
constexpr int URL_SIZE = 0x200;
constexpr int HTTP_HEADER_SIZE = 0x20;
constexpr int HTTP_HEADER_VALUE_SIZE = 0x100;
constexpr int MAX_HEADERS = 3;
constexpr int MAX_ROOT_CAS = 3;
constexpr int MAX_CLIENT_CERTS = 1;

// UNOFFICIAL: The official name of these enums are unknown

/// Represents an action that a task will perform
enum ActionCode : u8 {
    /// Action code used for listing files on the BOSS server. May be a generic raw download?
    ActionCodeFileList = 0x1,
    /// Action code for downloading data from the given URL, principally an @link NsData @endlink
    ActionCodeNsaDownload,
    /// Action code for uploading data to the given URL
    ActionCodeUpload,
    /// Unknown action code
    ActionCodeUnknown0x4,
    /// Unknown action code
    ActionCodeUnknown0x5,
    /// Action code used by task ID "pl" from the Home Menu
    ActionCodePl,
    /// Action code used by task ID "phu" from the Home Menu
    ActionCodePhu,
    /// Action code used by task ID "tiu" from the Home Menu
    ActionCodeTiu,
    /// Action code used by task ID "splu" from the Home Menu
    ActionCodeSplu,
    /// Action code used for downloading data from DataStore through an Hpp server. Stores notification data?
    ActionCodeDataStoreDownload,
    /// Action code related to DataStore?
    ActionCodeDataStore2,
    /// Action code used for StreetPass Relay
    ActionCodeSPRelay,
    /// Action code used for downloading the title version list (versionList.dat)
    ActionCodeVersionList
};

/// Flags which add additional information related to the console's access point to the data sent to the server
enum ApInfoType : u8 {
    /// Adds the "apgroup" parameter to the query
    ApInfoTypeApGroup = 1 << 0,
    /// Adds the "aparea" parameter to the query
    ApInfoTypeApArea = 1 << 1,
    /// Adds the "ap" parameter to the query
    ApInfoTypeAp = 1 << 2,
};

/// Flags which add additional information related to the console's configuration to the data sent to the server
enum CfgInfoType : u8 {
    /// Adds the "c" parameter to the query
    CfgInfoTypeCountry = 1 << 0,
    /// Adds the "l" parameter to the query
    CfgInfoTypeLanguage = 1 << 1,
    /// Adds the "tm" parameter to the query
    CfgInfoTypeTargetModel = 1 << 2,
};

// UNOFFICIAL: The official name of this struct is unknown
struct HeaderField {
    char header[HTTP_HEADER_SIZE];
    char value[HTTP_HEADER_VALUE_SIZE];
};
CHECK_SIZE(HeaderField, 0x120);
CHECK_OFFSET(HeaderField, 0x0, header);
CHECK_OFFSET(HeaderField, 0x20, value);

/// Contains the configuration for a task action
struct TaskActionConfig {
    /// Code for the action to perform
    ActionCode code;
    /// If non-zero, enables the task root CA to be read from the filesystem. May be a bool?
    u8 fsRootCA;
    /// If non-zero, enables the task client certificate to be read from the filesystem. May be a bool?
    u8 fsClientCert;
    /// See @link ApInfoType @endlink. Must be between 0 and 7 inclusively
    u8 apInfoType;
    /// This parameter is unknown. Must be between 0 and 6 inclusively. Controls what data is relevant? Matches with @link PropertyType @endlink 0x9
    u8 property0x9;
    /// See @link CfgInfoType @endlink. Must be between 0 and 7 inclusively
    u8 cfgInfoType;
    INSERT_PADDING_BYTES(2);
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x16
    u32 property0x16;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x8
    u32 property0x8;
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x3B
    u32 property0x3B;
    /// Contains a file handle with the data to send
    nn::Handle fileHandle{};
    /// Additional data for the action. The contents depend on the @link ActionCode @endlink used
    u8 actionData[ACTION_DATA_SIZE];
    /// Target URL where the contents are sent. Unused for DataStore actions
    char url[URL_SIZE];
    /// Additional headers to include in the request sent to the server
    HeaderField headerFields[MAX_HEADERS];
    /// Array of Root CA IDs to be used when connecting to the server
    u32 rootCAs[MAX_ROOT_CAS];
    /// Array of client certificate IDs to be used when connecting to the server
    u32 clientCerts[MAX_CLIENT_CERTS];
    /// Amount of Root CAs stored in the previous array
    u32 rootCaCount;
    /// Amount of client certificates stored in the previous array
    u32 clientCertCount;
    INSERT_UNKNOWN_BYTES(4);
    /// This parameter is unknown. Matches with @link PropertyType @endlink 0x15
    u8 property0x15[0x40];
};
CHECK_SIZE(TaskActionConfig, 0x7D4);
CHECK_OFFSET(TaskActionConfig, 0x0, code);
CHECK_OFFSET(TaskActionConfig, 0x1, fsRootCA);
CHECK_OFFSET(TaskActionConfig, 0x2, fsClientCert);
CHECK_OFFSET(TaskActionConfig, 0x3, apInfoType);
CHECK_OFFSET(TaskActionConfig, 0x4, property0x9);
CHECK_OFFSET(TaskActionConfig, 0x5, cfgInfoType);
CHECK_OFFSET(TaskActionConfig, 0x8, property0x16);
CHECK_OFFSET(TaskActionConfig, 0xC, property0x8);
CHECK_OFFSET(TaskActionConfig, 0x10, property0x3B);
CHECK_OFFSET(TaskActionConfig, 0x14, fileHandle);
CHECK_OFFSET(TaskActionConfig, 0x18, actionData);
CHECK_OFFSET(TaskActionConfig, 0x218, url);
CHECK_OFFSET(TaskActionConfig, 0x418, headerFields);
CHECK_OFFSET(TaskActionConfig, 0x778, rootCAs);
CHECK_OFFSET(TaskActionConfig, 0x784, clientCerts);
CHECK_OFFSET(TaskActionConfig, 0x788, rootCaCount);
CHECK_OFFSET(TaskActionConfig, 0x78C, clientCertCount);
CHECK_OFFSET(TaskActionConfig, 0x794, property0x15);

/// The details of this type are unknown
using FileDescriptor = u8;

/// Base class for task actions. Must not be inherited directly, @link TaskAction @endlink must be used instead
class TaskActionBase {
public:
    TaskActionConfig config;

    // vtable +0x0
    virtual ~TaskActionBase() = 0;

    /**
     * @brief Sets a client certificate ID to be used by the task
     * @param certId Client certificate ID to include
     */
    nn::Result SetClientCert(u32 certId);

    /**
     * @brief Adds an additional header field to the task
     * @param header Header field
     * @param value Value of the header field
     */
    nn::Result AddHeaderField(const char *header, const char *value);

    /**
     * @brief Sets a Root CA ID to be used by the task
     * @param certId Root CA ID to include
     */
    nn::Result SetRootCa(u32 certId);
};
CHECK_SIZE(TaskActionBase, 0x7D8);
CHECK_OFFSET(TaskActionBase, 0x4, config);

/// Generic class for task actions. All task actions inherit from this class
class TaskAction : public TaskActionBase {
public:
    TaskAction() {
        // memclr(&config, sizeof(config))
        std::memset(&config, 0, sizeof(config));
    }

    // vtable +0x0
    ~TaskAction();
};
CHECK_SIZE(TaskAction, 0x7D8);

// UNOFFICIAL: The official name for FileListAction is unknown

/// Task action used for retrieving the list of files on the BOSS server for a given task. May be a generic raw download?
class FileListAction : public TaskAction {
public:
    /**
     * @brief Initializes the task action
     * @param url Target URL where the data will be downloaded from
     * @param handle File handle where data will be stored
     */
    nn::Result Initialize(const char *url, nn::Handle handle);
};
CHECK_SIZE(FileListAction, 0x7D8);

/// Task action used for downloading data from a given URL, principally an @link NsData @endlink
class NsaDownloadAction : public TaskAction {
public:
    /**
     * @brief Initializes the task action
     * @param url Target URL to download the data from
     */
    nn::Result Initialize(const char *url);
};
CHECK_SIZE(NsaDownloadAction, 0x7D8);

/// Task action used for uploading data to a given URL
class UploadAction : public TaskAction {
public:
    /**
     * @brief Initializes the task action
     * @param url Target URL where the data will be uploaded
     * @param handle File handle where data will be read from
     * @param fd Unknown parameter
     */
    nn::Result Initialize(const char *url, nn::Handle handle, FileDescriptor fd);
};
CHECK_SIZE(UploadAction, 0x7D8);

/// Task action used for downloading data from DataStore through an Hpp server. Stores notification data?
class DataStoreDownloadAction : public TaskAction {
public:
    /**
     * @brief Initializes the task action
     * @param gameServerId Game server ID to download data from
     * @param accessKey Access key for accessing the server
     */
    nn::Result Initialize(u32 gameServerId, const char16_t *accessKey);
};
CHECK_SIZE(DataStoreDownloadAction, 0x7D8);

} // namespace boss

} // namespace nn
