#include "nn/svc/svc.h"
#include "nn/dbg/BreakReason.h"

namespace nn {

namespace svc {

NNSDK_NAKED nn::Result SleepThread(s64 nanoseconds) {
    asm("svc 0xA \n"
        "bx lr");
}

NNSDK_NAKED nn::Result CreateAddressArbiter(Handle *arbiter) {
    asm("str r0, [sp, #-0x4]! \n"
        "svc 0x21 \n"
        "ldr r2, [sp, #0x0] \n"
        "str r1, [r2, #0x0] \n"
        "add sp, sp, #0x4 \n"
        "bx lr");
}

NNSDK_NAKED nn::Result ArbitrateAddress(Handle arbiter, u32 addr, nn::os::ArbitrationType arbitrationType, s32 value, s64 nanoseconds) {
    asm("stmdb sp!, {r4, r5} \n"
        "ldr r4, [sp, #0x8] \n"
        "ldr r5, [sp, #0xC] \n"
        "svc 0x22 \n"
        "ldmia sp!, {r4, r5} \n"
        "bx lr");
}

NNSDK_NAKED nn::Result CloseHandle(Handle handle) {
    asm("svc 0x23 \n"
        "bx lr");
}

NNSDK_NAKED nn::Result WaitSynchronization1(Handle handle, s64 nanoseconds) {
    asm("svc 0x24 \n"
        "bx lr");
}

NNSDK_NAKED nn::Result ConnectToPort(Handle *out, char *portName) {
    asm("str r0, [sp, #-0x4]! \n"
        "svc 0x2D \n"
        "ldr r2, [sp, #0x0] \n"
        "str r1, [r2, #0x0] \n"
        "add sp, sp, #0x4 \n"
        "bx lr");
}

NNSDK_NAKED nn::Result SendSyncRequest(Handle handle) {
    asm("svc 0x32 \n"
        "bx lr");
}

NNSDK_NAKED void Break(nn::dbg::BreakReason reason) {
    asm("svc 0x3C \n"
        "bx lr");
}

} // namespace svc

} // namespace nn
