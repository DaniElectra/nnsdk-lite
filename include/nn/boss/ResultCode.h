#pragma once

#include "nn/Result.h"
#include "nn/types.h"

namespace nn {

namespace boss {

enum class ResultCode : u32 {
    Success = 0,
    InvalidPolicy,
    InvalidAction,
    InvalidOption,
    InvalidAppIdList,
    InvalidPolicy2, ///< Internally has the same name as InvalidPolicy?
    InvalidStepIdList,
    InvalidNsDataIdList,
    InvalidTaskStatus,
    InvalidPropertyValue,
    InvalidNewArrivalEvent,
    InvalidNewArrivalFlag,
    InvalidOptoutFlag,
    InvalidTaskError,
    InvalidNsDataValue,
    InvalidNsDataInfo,
    InvalidNsDataReadFlag,
    InvalidNsDataTime,
    InvalidNextExecuteTime,
    HttpRequestHeaderPointerNull,
    Unknown0x14,
    InvalidTestModeAvailability,
    InvalidConfigParentalControl,
    InvalidConfigEulaAgreement,
    InvalidPolicyListEnvId,
    InvalidPolicyListUrl,
    InvalidTaskId,
    InvalidTaskStep,
    InvalidPropertyType,
    InvalidUrl,
    InvalidPolicy3, ///< Internally has the same name as InvalidPolicy?
    InvalidTaskPriority,
    InvalidTaskTargetDuration,
    ActionCodeOutOfRange,
    InvalidNsDataSeekPosition,
    InvalidMaxHttpRequestHeader,
    InvalidMaxClientCert,
    InvalidPolicy4, ///< Internally has the same name as InvalidPolicy?
    SchedulingPolicyOutOfRange,
    ApInfoTypeOutOfRange,
    TaskPermissionOutOfRange,
    WaitFinishTimeout,
    WaitFinishTaskNotDone,
    IpcNotSessionInitialized,
    IpcPropertySizeError,
    IpcTooManyRequests,
    AlreadyInitialized,
    OutOfMemory,
    InvalidNumberOfNsd,
    NsDataInvalidFormat,
    AppNotExist,
    TaskNotExist,
    TaskStepNotExist,
    ApliIdNotExist,
    TaskIdAlreadyExist,
    TaskStepAlreadyExist,
    InvalidSequence,
    DatabaseFull,
    CantUnregisterTask,
    TaskNotRegistered,
    InvalidFileHandle,
    InvalidTaskSchedulingPolicy,
    InvalidHttpRequestHeader,
    InvalidHeadType,
    StorageAccessPermission,
    StorageInsufficiency,
    StorageNotFound,
    NsDataNotFound,
    InvalidNsDataGetHeadSize,
    NsDataListSizeShortage,
    InvalidPolicy5, ///< Internally has the same name as InvalidPolicy?
    NotConnectApWithLocation,
    NotConnectNetwork,
    InvalidFriendcode,
    FileAccess,
    TaskAlreadyPaused,
    TaskAlreadyResumed,
    Unexpect,

    InvalidStorageParameter = 0xC0,
    CfgInfoTypeOutOfRange,
    InvalidMaxHttpQuery,
    InvalidMaxDataStoreDst,
    NSAListInvalidFormat,
    NSAListDownloadTaskError,

    InvalidPointer = 1014,
    NotFound = 1018,
    AlreadyExists = 1020,
    OutOfRange = 1021
};

namespace detail {

/// Returns the \link nn::Result \endlink that matches with the given \link ResultCode \endlink
nn::Result ChangeBossRetCodeToResult(ResultCode code);

} // namespace detail

} // namespace boss

} // namespace nn
