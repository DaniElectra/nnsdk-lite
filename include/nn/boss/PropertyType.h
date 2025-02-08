#pragma once

#include "nn/types.h"

namespace nn {

namespace boss {

/// Properties of a session. Most of these properties are task-specific and would be used when configuring or receiving the status of one
enum class PropertyType : u16 {
    Priority = 0,
    SchedulingPolicy,
    TaskTargetDuration,
    Interval,
    Count,
    TaskPermission,
    ActionCode,
    Url,
    Unknown0x08,
    Unknown0x09,
    Unknown0x0A,
    Unknown0x0B,
    Handle,
    HeaderFields,
    ClientCerts,
    RootCAs,
    FSClientCert,
    FSRootCA,
    ApInfoType,
    RootCaCount,
    ClientCertCount,
    Unknown0x15,
    Unknown0x16,
    Unknown0x17,
    Unknown0x18,
    Unknown0x19,
    Unknown0x1A,
    Unknown0x1B,
    Unknown0x1C,
    StateCode,
    Unknown0x1E,
    Unknown0x1F,
    TaskResultCode,
    ServiceStatus,
    Unknown0x22,
    CommErrorCode,
    Unknown0x24,
    Unknown0x25,
    Unknown0x26,
    Unknown0x27,
    LastSuccessfulTimestamp,
    Unknown0x29,
    Unknown0x2A,
    Unknown0x2B,
    Unknown0x2C,
    Unknown0x2D,
    Unknown0x2E,
    LastModifiedHeader,
    Unknown0x30,
    Unknown0x31,
    Unknown0x32,
    TotalApps,
    AppIdList,
    TotalTasks,
    TaskIdList,
    TotalSteps,
    StepIdList,
    Unknown0x39,
    Unknown0x3A,
    Unknown0x3B,
    Unknown0x3C,
    Unknown0x3D,
    DataStoreDownloadActionData,
    CfgInfoType
};

} // namespace boss

} // namespace nn
