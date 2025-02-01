#include "nn/boss/AppIdList.h"
#include "nn/boss/ResultCode.h"
#include "nn/boss/detail/detail.h"
#include "nn/boss/detail/property.h"

namespace nn {

namespace boss {

nn::Result GetAppIdList(AppIdList *list) {
    if (list == nullptr) {
        return detail::ChangeBossRetCodeToResult(ResultCode::InvalidAppIdList);
    }

    detail::Privileged *privilegedInstance;

    // Try with the privileged instance
    nn::Result res = detail::GetPrivilegedIpcInstance(privilegedInstance);
    if (res) {
        res = privilegedInstance->GetAppIdList();
    }

    if (res) {
        res = detail::ReceivePrivilegedAppIdList(&list->infoList);
    }

    return res;
}

} // namespace boss

} // namespace nn
