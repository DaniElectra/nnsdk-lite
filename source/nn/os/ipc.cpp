#include "nn/os/ipc.h"

namespace nn {

namespace os {

namespace ipc {

constexpr u32 MakeHeader(u32 commandID, u32 normalParams, u32 translateParams, u32 unused) {
    return (commandID << 16) | (unused << 28 >> 10) | (normalParams << 26 >> 20) | (translateParams & 0x3F);
}

void WriteHeader(u32 *cmdbuf, u32 commandID, u32 normalParams, u32 translateParams, u32 unused) {
    cmdbuf[0] = MakeHeader(commandID, normalParams, translateParams, unused);
}

void WriteMappedBufferRead(u32 *cmdbuf, u32 offset, const void *buffer, u32 size) {
    cmdbuf[offset] = (size << 4) | 0xA;
    cmdbuf[offset + 1] = reinterpret_cast<u32>(buffer);
}

void WriteMappedBufferWrite(u32 *cmdbuf, u32 offset, void *buffer, u32 size) {
    cmdbuf[offset] = (size << 4) | 0xC;
    cmdbuf[offset + 1] = reinterpret_cast<u32>(buffer);
}

void WriteStaticBufferTranslate(u32 *cmdbuf, u32 offset, u32 staticBufferId, u32 size) {
    cmdbuf[offset] = (size << 14) | (staticBufferId << 28 >> 18) | 2;
}

void *ReadBuffer(u32 *cmdbuf, u32 offset) {
    return reinterpret_cast<void *>(cmdbuf[offset]);
}

void WriteProcessIDTranslate(u32 *cmdbuf, u32 offset) {
    cmdbuf[offset] = 0x20;
}

void WriteHandleTranslate(u32 *cmdbuf, u32 offset, u32 numHandles) {
    cmdbuf[offset] = (numHandles - 1) << 26;
}

}  // namespace ipc

}  // namespace os

}  // namespace nn
