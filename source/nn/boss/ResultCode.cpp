#include "nn/boss/ResultCode.h"
#include "nn/Result.h"

// TODO - Why is clang-format failing here?
// clang-format off
#define MAKE_RESULT(level, summary, desc) {level, summary, nn::Result::ModuleType_BOSS, static_cast<int>(desc)}
// clang-format on

namespace nn {

namespace boss {

namespace detail {

nn::Result ChangeBossRetCodeToResult(ResultCode code) {
    switch (code) {
        case ResultCode::Success:
            return RESULT_SUCCESS;
        case ResultCode::Unknown0x01:
            // 0xD8E0F801
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x01);
        case ResultCode::Unknown0x02:
            // 0xD8E0F802
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x02);
        case ResultCode::Unknown0x03:
            // 0xD8E0F803
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x03);
        case ResultCode::Unknown0x04:
            // 0xD8E0F804
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x04);
        case ResultCode::Unknown0x05:
            // 0xD8E0F805
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x05);
        case ResultCode::Unknown0x06:
            // 0xD8E0F806
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x06);
        case ResultCode::Unknown0x07:
            // 0xD8E0F807
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x07);
        case ResultCode::Unknown0x08:
            // 0xC8A0F808
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x08);
        case ResultCode::Unknown0x09:
            // 0xD8E0F809
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x09);
        case ResultCode::Unknown0x0A:
            // 0xD8E0F80A
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x0A);
        case ResultCode::Unknown0x0B:
            // 0xD8E0F80B
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x0B);
        case ResultCode::Unknown0x0C:
            // 0xD8E0F80C
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x0C);
        case ResultCode::Unknown0x0D:
            // 0xC8A0F80D
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x0D);
        case ResultCode::Unknown0x0E:
            // 0xD8E0F80E
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x0E);
        case ResultCode::Unknown0x0F:
            // 0xD8E0F80F
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x0F);
        case ResultCode::Unknown0x10:
            // 0xD8E0F810
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x10);
        case ResultCode::Unknown0x11:
            // 0xD8E0F811
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x11);
        case ResultCode::Unknown0x12:
            // 0xD8E0F812
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x12);
        case ResultCode::Unknown0x13:
            // 0xD8E0F813
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x13);
        case ResultCode::Unknown0x14:
            // 0xD8E0F814
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x14);
        case ResultCode::Unknown0x15:
            // 0xD8E0F815
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x15);
        case ResultCode::Unknown0x1A:
            // 0xD8E0F81A
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x1A);
        case ResultCode::Unknown0x1B:
            // 0xD8E0F81B
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x1B);
        case ResultCode::Unknown0x1C:
            // 0xD8E0F81C
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x1C);
        case ResultCode::Unknown0x1D:
            // 0xD8E0F81D
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x1D);
        case ResultCode::Unknown0x1E:
            // 0xD8E0F81E
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x1E);
        case ResultCode::Unknown0x1F:
            // 0xD8E0F81F
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x1F);
        case ResultCode::Unknown0x20:
            // 0xD8E0F820
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x20);
        case ResultCode::Unknown0x21:
            // 0xD8E0F821
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x21);
        case ResultCode::Unknown0x22:
            // 0xD8E0F822
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x22);
        case ResultCode::Unknown0x23:
            // 0xD860F823
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0x23);
        case ResultCode::Unknown0x24:
            // 0xD860F824
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0x24);
        case ResultCode::Unknown0x25:
            // 0xD860F825
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0x25);
        case ResultCode::Unknown0x26:
            // 0xD8E0F826
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x26);
        case ResultCode::Unknown0x27:
            // 0xD8E0F827
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x27);
        case ResultCode::Unknown0x28:
            // 0xD8E0F828
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0x28);
        case ResultCode::Unknown0x29:
            // 0xD840F829
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, ResultCode::Unknown0x29);
        case ResultCode::Unknown0x2A:
            // 0xD840F82A
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, ResultCode::Unknown0x2A);
        case ResultCode::Unknown0x2B:
            // 0xC8A0F82B
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x2B);
        case ResultCode::Unknown0x2C:
            // 0xD860F82C
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0x2C);
        case ResultCode::Unknown0x2D:
            // 0xD860F82D
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0x2D);
        case ResultCode::Unknown0x2E:
            // 0xC8A0F82E
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x2E);
        case ResultCode::Unknown0x2F:
            // 0xD860F82F
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0x2F);
        case ResultCode::Unknown0x30:
            // 0xD860F830
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0x30);
        case ResultCode::Unknown0x31:
            // 0xD860F831
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0x31);
        case ResultCode::Unknown0x32:
            // 0xC8A0F832
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x32);
        case ResultCode::Unknown0x33:
            // 0xC8A0F833
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x33);
        case ResultCode::Unknown0x34:
            // 0xC8A0F834
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x34);
        case ResultCode::Unknown0x35:
            // 0xC8A0F835
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x35);
        case ResultCode::Unknown0x36:
            // 0xC8A0F836
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x36);
        case ResultCode::Unknown0x37:
            // 0xC8A0F837
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x37);
        case ResultCode::Unknown0x38:
            // 0xC8A0F838
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x38);
        case ResultCode::Unknown0x39:
            // 0xC8A0F839
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x39);
        case ResultCode::Unknown0x3A:
            // 0xC8A0F83A
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x3A);
        case ResultCode::Unknown0x3B:
            // 0xC8A0F83B
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x3B);
        case ResultCode::Unknown0x3C:
            // 0xC8A0F83C
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x3C);
        case ResultCode::Unknown0x3D:
            // 0xC8A0F83D
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x3D);
        case ResultCode::Unknown0x3E:
            // 0xC8A0F83E
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x3E);
        case ResultCode::Unknown0x3F:
            // 0xC8A0F83F
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x3F);
        case ResultCode::Unknown0x40:
            // 0xC8A0F840
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x40);
        case ResultCode::Unknown0x41:
            // 0xC8A0F841
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x41);
        case ResultCode::Unknown0x42:
            // 0xC8A0F842
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x42);
        case ResultCode::Unknown0x43:
            // 0xC8A0F843
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x43);
        case ResultCode::Unknown0x44:
            // 0xC960F844
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::Unknown0x44);
        case ResultCode::Unknown0x45:
            // 0xD840F845
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, ResultCode::Unknown0x45);
        case ResultCode::Unknown0x46:
            // 0xD840F846
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_WouldBlock, ResultCode::Unknown0x46);
        case ResultCode::Unknown0x47:
            // 0xC8A0F847
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x47);
        case ResultCode::Unknown0x48:
            // 0xC8A0F848
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x48);
        case ResultCode::Unknown0x49:
            // 0xC8A0F849
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0x49);
        case ResultCode::Unknown0x4A:
            // 0xC960F84A
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::Unknown0x4A);
        case ResultCode::Unknown0x4B:
            // 0xC960F84B
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::Unknown0x4B);
        case ResultCode::Unknown0x4C:
            // 0xC960F84C
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::Unknown0x4C);
        case ResultCode::Unknown0x16:
        case ResultCode::Unknown0x17:
        case ResultCode::Unknown0x18:
        case ResultCode::Unknown0x19:
        case ResultCode::Unknown0x4D:
        default:
            // 0xC960F84D
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_Internal, ResultCode::Unknown0x4D);
        case ResultCode::Unknown0xC0:
            // 0xD8E0F8C0
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0xC0);
        case ResultCode::Unknown0xC1:
            // 0xD8E0F8C1
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::Unknown0xC1);
        case ResultCode::Unknown0xC2:
            // 0xD860F8C2
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0xC2);
        case ResultCode::Unknown0xC3:
            // 0xD860F8C3
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0xC3);
        case ResultCode::Unknown0xC4:
            // 0xD860F8C4
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_OutOfResources, ResultCode::Unknown0xC4);
        case ResultCode::Unknown0xC5:
            // 0xC8A0F8C5
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::Unknown0xC5);
        case ResultCode::InvalidPointer:
            // 0xD8E0FBF6
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::InvalidPointer);
        case ResultCode::NotFound:
            // 0xC8A0FBFA
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::NotFound);
        case ResultCode::AlreadyExists:
            // 0xC8A0FBFC
            return MAKE_RESULT(nn::Result::Level_Status, nn::Result::Summary_InvalidState, ResultCode::AlreadyExists);
        case ResultCode::OutOfRange:
            // 0xD8E0FBFD
            return MAKE_RESULT(nn::Result::Level_Permanent, nn::Result::Summary_InvalidArgument, ResultCode::OutOfRange);
    }
}

} // namespace detail

} // namespace boss

} // namespace nn
