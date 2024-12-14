#include "nn/boss/ResultCode.h"
#include "nn/Result.h"

// TODO - Why is clang-format failing here?
// clang-format off
#define MAKE_BOSS_RESULT(level, summary, desc) {level, summary, nn::Result::ModuleType_BOSS, static_cast<int>(desc)}
// clang-format on

namespace nn {

namespace boss {

namespace detail {

nn::Result ChangeBossRetCodeToResult(ResultCode code) {
    switch (code) {
        case ResultCode::Success:
            return RESULT_SUCCESS;
        case ResultCode::InvalidPolicy:
            // 0xD8E0F801
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidPolicy);
        case ResultCode::InvalidAction:
            // 0xD8E0F802
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidAction);
        case ResultCode::InvalidOption:
            // 0xD8E0F803
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidOption);
        case ResultCode::InvalidAppIdList:
            // 0xD8E0F804
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidAppIdList);
        case ResultCode::InvalidPolicy2:
            // 0xD8E0F805
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidPolicy2);
        case ResultCode::InvalidStepIdList:
            // 0xD8E0F806
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidStepIdList);
        case ResultCode::InvalidNsDataIdList:
            // 0xD8E0F807
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNsDataIdList);
        case ResultCode::InvalidTaskStatus:
            // 0xC8A0F808
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::InvalidTaskStatus);
        case ResultCode::InvalidPropertyValue:
            // 0xD8E0F809
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidPropertyValue);
        case ResultCode::InvalidNewArrivalEvent:
            // 0xD8E0F80A
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNewArrivalEvent);
        case ResultCode::InvalidNewArrivalFlag:
            // 0xD8E0F80B
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNewArrivalFlag);
        case ResultCode::InvalidOptoutFlag:
            // 0xD8E0F80C
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidOptoutFlag);
        case ResultCode::InvalidTaskError:
            // 0xC8A0F80D
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::InvalidTaskError);
        case ResultCode::InvalidNsDataValue:
            // 0xD8E0F80E
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNsDataValue);
        case ResultCode::InvalidNsDataInfo:
            // 0xD8E0F80F
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNsDataInfo);
        case ResultCode::InvalidNsDataReadFlag:
            // 0xD8E0F810
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNsDataReadFlag);
        case ResultCode::InvalidNsDataTime:
            // 0xD8E0F811
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNsDataTime);
        case ResultCode::InvalidNextExecuteTime:
            // 0xD8E0F812
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNextExecuteTime);
        case ResultCode::HttpRequestHeaderPointerNull:
            // 0xD8E0F813
            return MAKE_BOSS_RESULT(
                nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::HttpRequestHeaderPointerNull);
        case ResultCode::Unknown0x14:
            // 0xD8E0F814
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x14);
        case ResultCode::InvalidTestModeAvailability:
            // 0xD8E0F815
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidTestModeAvailability);
        case ResultCode::InvalidTaskId:
            // 0xD8E0F81A
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidTaskId);
        case ResultCode::InvalidTaskStep:
            // 0xD8E0F81B
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidTaskStep);
        case ResultCode::InvalidPropertyType:
            // 0xD8E0F81C
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidPropertyType);
        case ResultCode::InvalidUrl:
            // 0xD8E0F81D
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidUrl);
        case ResultCode::InvalidPolicy3:
            // 0xD8E0F81E
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidPolicy3);
        case ResultCode::InvalidTaskPriority:
            // 0xD8E0F81F
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidTaskPriority);
        case ResultCode::InvalidTaskTargetDuration:
            // 0xD8E0F820
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidTaskTargetDuration);
        case ResultCode::ActionCodeOutOfRange:
            // 0xD8E0F821
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::ActionCodeOutOfRange);
        case ResultCode::InvalidNsDataSeekPosition:
            // 0xD8E0F822
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidNsDataSeekPosition);
        case ResultCode::InvalidMaxHttpRequestHeader:
            // 0xD860F823
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::InvalidMaxHttpRequestHeader);
        case ResultCode::InvalidMaxClientCert:
            // 0xD860F824
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::InvalidMaxClientCert);
        case ResultCode::InvalidPolicy4:
            // 0xD860F825
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::InvalidPolicy4);
        case ResultCode::SchedulingPolicyOutOfRange:
            // 0xD8E0F826
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::SchedulingPolicyOutOfRange);
        case ResultCode::ApInfoTypeOutOfRange:
            // 0xD8E0F827
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::ApInfoTypeOutOfRange);
        case ResultCode::TaskPermissionOutOfRange:
            // 0xD8E0F828
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::TaskPermissionOutOfRange);
        case ResultCode::WaitFinishTimeout:
            // 0xD840F829
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, ResultCode::WaitFinishTimeout);
        case ResultCode::WaitFinishTaskNotDone:
            // 0xD840F82A
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, ResultCode::WaitFinishTaskNotDone);
        case ResultCode::IpcNotSessionInitialized:
            // 0xC8A0F82B
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::IpcNotSessionInitialized);
        case ResultCode::IpcPropertySizeError:
            // 0xD860F82C
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::IpcPropertySizeError);
        case ResultCode::IpcTooManyRequests:
            // 0xD860F82D
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::IpcTooManyRequests);
        case ResultCode::AlreadyInitialized:
            // 0xC8A0F82E
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::AlreadyInitialized);
        case ResultCode::OutOfMemory:
            // 0xD860F82F
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::OutOfMemory);
        case ResultCode::InvalidNumberOfNsd:
            // 0xD860F830
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::InvalidNumberOfNsd);
        case ResultCode::NsDataInvalidFormat:
            // 0xD860F831
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::NsDataInvalidFormat);
        case ResultCode::AppNotExist:
            // 0xC8A0F832
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::AppNotExist);
        case ResultCode::TaskNotExist:
            // 0xC8A0F833
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::TaskNotExist);
        case ResultCode::TaskStepNotExist:
            // 0xC8A0F834
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::TaskStepNotExist);
        case ResultCode::ApliIdNotExist:
            // 0xC8A0F835
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::ApliIdNotExist);
        case ResultCode::TaskIdAlreadyExist:
            // 0xC8A0F836
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::TaskIdAlreadyExist);
        case ResultCode::TaskStepAlreadyExist:
            // 0xC8A0F837
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::TaskStepAlreadyExist);
        case ResultCode::InvalidSequence:
            // 0xC8A0F838
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::InvalidSequence);
        case ResultCode::DatabaseFull:
            // 0xC8A0F839
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::DatabaseFull);
        case ResultCode::CantUnregisterTask:
            // 0xC8A0F83A
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::CantUnregisterTask);
        case ResultCode::TaskNotRegistered:
            // 0xC8A0F83B
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::TaskNotRegistered);
        case ResultCode::InvalidFileHandle:
            // 0xC8A0F83C
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::InvalidFileHandle);
        case ResultCode::InvalidTaskSchedulingPolicy:
            // 0xC8A0F83D
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::InvalidTaskSchedulingPolicy);
        case ResultCode::InvalidHttpRequestHeader:
            // 0xC8A0F83E
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::InvalidHttpRequestHeader);
        case ResultCode::InvalidHeadType:
            // 0xC8A0F83F
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::InvalidHeadType);
        case ResultCode::StorageAccessPermission:
            // 0xC8A0F840
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::StorageAccessPermission);
        case ResultCode::StorageInsufficiency:
            // 0xC8A0F841
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::StorageInsufficiency);
        case ResultCode::StorageNotFound:
            // 0xC8A0F842
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::StorageNotFound);
        case ResultCode::NsDataNotFound:
            // 0xC8A0F843
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::NsDataNotFound);
        case ResultCode::InvalidNsDataGetHeadSize:
            // 0xC960F844
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::InvalidNsDataGetHeadSize);
        case ResultCode::NsDataListSizeShortage:
            // 0xD840F845
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, ResultCode::NsDataListSizeShortage);
        case ResultCode::InvalidPolicy5:
            // 0xD840F846
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, ResultCode::InvalidPolicy5);
        case ResultCode::NotConnectApWithLocation:
            // 0xC8A0F847
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::NotConnectApWithLocation);
        case ResultCode::NotConnectNetwork:
            // 0xC8A0F848
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::NotConnectNetwork);
        case ResultCode::InvalidFriendcode:
            // 0xC8A0F849
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::InvalidFriendcode);
        case ResultCode::FileAccess:
            // 0xC960F84A
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::FileAccess);
        case ResultCode::TaskAlreadyPaused:
            // 0xC960F84B
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::TaskAlreadyPaused);
        case ResultCode::TaskAlreadyResumed:
            // 0xC960F84C
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::TaskAlreadyResumed);
        case ResultCode::InvalidConfigParentalControl:
        case ResultCode::InvalidConfigEulaAgreement:
        case ResultCode::InvalidPolicyListEnvId:
        case ResultCode::InvalidPolicyListUrl:
        case ResultCode::Unexpect:
        default:
            // 0xC960F84D
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::Unexpect);
        case ResultCode::InvalidStorageParameter:
            // 0xD8E0F8C0
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidStorageParameter);
        case ResultCode::CfgInfoTypeOutOfRange:
            // 0xD8E0F8C1
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::CfgInfoTypeOutOfRange);
        case ResultCode::InvalidMaxHttpQuery:
            // 0xD860F8C2
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::InvalidMaxHttpQuery);
        case ResultCode::InvalidMaxDataStoreDst:
            // 0xD860F8C3
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::InvalidMaxDataStoreDst);
        case ResultCode::NSAListInvalidFormat:
            // 0xD860F8C4
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::NSAListInvalidFormat);
        case ResultCode::NSAListDownloadTaskError:
            // 0xC8A0F8C5
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::NSAListDownloadTaskError);
        case ResultCode::InvalidPointer:
            // 0xD8E0FBF6
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidPointer);
        case ResultCode::NotFound:
            // 0xC8A0FBFA
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::NotFound);
        case ResultCode::AlreadyExists:
            // 0xC8A0FBFC
            return MAKE_BOSS_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::AlreadyExists);
        case ResultCode::OutOfRange:
            // 0xD8E0FBFD
            return MAKE_BOSS_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::OutOfRange);
    }
}

} // namespace detail

} // namespace boss

} // namespace nn
