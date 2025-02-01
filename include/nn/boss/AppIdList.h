#pragma once

#include "helpers.h"
#include "nn/Result.h"
#include "nn/boss/common.h"
#include "nn/types.h"

namespace nn {

namespace boss {

/// List of application IDs registered in BOSS
struct AppIdInfoList {
    u16 appIdCount;
    u64 apps[APP_ID_LIST_SIZE];
};
CHECK_SIZE(AppIdInfoList, 0x408);
CHECK_OFFSET(AppIdInfoList, 0x0, appIdCount);
CHECK_OFFSET(AppIdInfoList, 0x8, apps);

/// Contains the list of applications that are registered in BOSS. Requires privileged access
class AppIdList {
    u32 *vtable; // TODO - Are there any entries on the vtable?
public:
    AppIdInfoList infoList;
};
CHECK_SIZE(AppIdList, 0x410);
CHECK_OFFSET(AppIdList, 0x8, infoList);

/**
 * @brief Retrieves the list of applications that are registered in BOSS
 * @param taskId Task ID
 * @param list Output list of step IDs
 */
nn::Result GetAppIdList(AppIdList *list);

} // namespace boss

} // namespace nn
