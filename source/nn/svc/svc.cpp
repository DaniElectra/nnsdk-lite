#include "nn/svc/svc.h"

namespace nn {

namespace svc {

__attribute__((naked)) nn::Result SleepThread(s64 nanoseconds) asm(
    "svc 0xA"
    "bx lr");

__attribute__((naked)) nn::Result CreateAddressArbiter(Handle* arbiter) asm(
    "str r0, [sp, #-0x4]!"
    "svc 0x21"
    "ldr r2, [sp, #0x0]"
    "str r1, [r2, #0x0]"
    "add sp, sp, #0x4"
    "bx lr");

__attribute__((naked)) nn::Result ArbitrateAddress(Handle arbiter, u32 addr, nn::os::ArbitrationType arbitrationType, s32 value, s64 nanoseconds) asm(
    "stmdb sp!, {r4, r5}"
    "ldr r4, [sp, #0x8]"
    "ldr r5, [sp, #0xC]"
    "svc 0x22"
    "ldmia sp!, {r4, r5}"
    "bx lr");

__attribute__((naked)) nn::Result CloseHandle(Handle handle) asm(
    "svc 0x23"
    "bx lr");

__attribute__((naked)) nn::Result ConnectToPort(Handle* out, char* portName) asm(
    "str r0, [sp, #-0x4]!"
    "svc 0x2D"
    "ldr r2, [sp, #0x0]"
    "str r1, [r2, #0x0]"
    "add sp, sp, #0x4"
    "bx lr");

__attribute__((naked)) nn::Result SendSyncRequest(Handle handle) asm(
    "svc 0x32"
    "bx lr");

}  // namespace svc

}  // namespace nn
