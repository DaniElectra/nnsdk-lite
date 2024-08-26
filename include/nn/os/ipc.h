#pragma once

#include "helpers.h"
#include "nn/Handle.h"
#include "nn/os/thread.h"

namespace nn {

namespace os {

namespace ipc {

class Session {
public:
    Handle session;
};
CHECK_SIZE(Session, 4);
CHECK_OFFSET(Session, session, 0x0);

// UNOFFICIAL: Replicating from libctru
static inline u32 *getThreadCommandBuffer() {
    return reinterpret_cast<u32 *>(reinterpret_cast<u8 *>(getThreadLocalStorage()) + 0x80);
}

static inline u32 *getThreadStaticBuffers() {
    return reinterpret_cast<u32 *>(reinterpret_cast<u8 *>(getThreadLocalStorage()) + 0x180);
}

constexpr u32 MakeHeader(u32 commandID, u32 normalParams, u32 translateParams, u32 unused);
void WriteHeader(u32 *cmdbuf, u32 commandID, u32 normalParams, u32 translateParams, u32 unused);

void WriteMappedBufferRead(u32 *cmdbuf, u32 offset, const void *buffer, u32 size);
void WriteMappedBufferWrite(u32 *cmdbuf, u32 offset, void *buffer, u32 size);

void WriteStaticBufferTranslate(u32 *cmdbuf, u32 offset, u32 staticBufferId, u32 size);

void *ReadBuffer(u32 *cmdbuf, u32 offset);

void WriteProcessIDTranslate(u32 *cmdbuf, u32 offset);
void WriteHandleTranslate(u32 *cmdbuf, u32 offset, u32 numHandles);

}  // namespace ipc

}  // namespace os

}  // namespace nn
