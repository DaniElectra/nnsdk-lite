#pragma once

#include "nn/types.h"

namespace nn {

namespace boss {

/// Properties of a task
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
    Unknown0x1D,
    Unknown0x1E,
    Unknown0x1F,
    Unknown0x20,
    Unknown0x21,
    Unknown0x22,
    Unknown0x23,
    Unknown0x24,
    Unknown0x25,
    Unknown0x26,
    Unknown0x27,
    Unknown0x28,
    Unknown0x29,
    Unknown0x2A,
    Unknown0x2B,
    Unknown0x2C,
    Unknown0x2D,
    Unknown0x2E,
    Unknown0x2F,
    Unknown0x30,
    Unknown0x31,
    Unknown0x32,
    Unknown0x33,
    Unknown0x34,
    TotalTasks,
    TaskIdList,
    Unknown0x37,
    Unknown0x38,
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
