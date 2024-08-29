#include "nn/boss/NsDataIdList.h"
#include "nn/Result.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/detail/detail.h"

namespace nn {

namespace boss {

void NsDataIdList::Initialize() {
    lastIndex = 0;
    startNsDataId = 0;
}

u32 NsDataIdList::GetNsDataId(u16 index) {
    if (list == nullptr || count == 0 || index >= outEntries) {
        return -1;
    }

    return list[index];
}

nn::Result GetNsDataIdList(u32 filter, NsDataIdList *list) {
    if (list == nullptr || list->count == 0 || list->count > 0x1000) {
        return detail::ChangeBossRetCodeToResult(ResultCode::Unknown0x07);
    }

    detail::User *userInstance;
    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetNsDataIdList(
            filter, list->list, list->count, &list->outEntries, list->lastIndex, list->startNsDataId, &list->lastIndex);
    } else {
        // If it isn't available, try with the user instance
        res = detail::GetUserIpcInstance(userInstance);
        if (res) {
            res = userInstance->GetNsDataIdList(
                filter, list->list, list->count, &list->outEntries, list->lastIndex, list->startNsDataId, &list->lastIndex);
        }
    }

    // This is inlined with the raw result code: 0xD840F845
    nn::Result resultUnk45 = {
        nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, nn::Result::ModuleType_BOSS, static_cast<int>(ResultCode::Unknown0x45)};
    if (res == resultUnk45) {
        list->startNsDataId = list->GetNsDataId(list->outEntries - 1);
    }

    return res;
}

} // namespace boss

} // namespace nn
