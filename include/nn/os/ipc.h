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
CHECK_OFFSET(Session, 0x0, session);

// UNOFFICIAL: Replicating from libctru

/**
 * @brief Gets the thread command buffer
 * @return Pointer to the thread command buffer
 */
static inline u32 *getThreadCommandBuffer() {
    return reinterpret_cast<u32 *>(reinterpret_cast<u8 *>(getThreadLocalStorage()) + 0x80);
}

/**
 * @brief Gets the thread static buffers
 * @return Pointer to the thread static buffers
 */
static inline u32 *getThreadStaticBuffers() {
    return reinterpret_cast<u32 *>(reinterpret_cast<u8 *>(getThreadLocalStorage()) + 0x180);
}

/**
 * @brief Makes an IPC header with the given paramaters
 * @param commandID Command ID of the header
 * @param normalParams Amount of normal parameters that will be used
 * @param translateParams Size that the translate parameters will use
 * @param unused Represents the unused part of an IPC header, see https://www.3dbrew.org/wiki/IPC#Message_Structure
 */
constexpr u32 MakeHeader(u32 commandID, u32 normalParams, u32 translateParams, u32 unused);

/**
 * @brief Makes an IPC header with the given paramaters and writes it into the command buffer
 * @param cmdbuf Buffer where the IPC header will be written into
 * @param commandID Command ID of the header
 * @param normalParams Amount of normal parameters that will be used
 * @param translateParams Size that the translate parameters will use
 * @param unused Represents the unused part of an IPC header, see https://www.3dbrew.org/wiki/IPC#Message_Structure
 */
void WriteHeader(u32 *cmdbuf, u32 commandID, u32 normalParams, u32 translateParams, u32 unused);

/**
 * @brief Writes the translate parameters for a read-only mapped buffer
 * @param cmdbuf Buffer where the translate parameters will be written into
 * @param offset Offset word in which the translate parameters will be written
 * @param buffer Buffer pointer to write
 * @param size Size of the buffer
 */
void WriteMappedBufferRead(u32 *cmdbuf, u32 offset, const void *buffer, u32 size);

/**
 * @brief Writes the translate parameters for a write-only mapped buffer
 * @param cmdbuf Buffer where the translate parameters will be written into
 * @param offset Offset word in which the translate parameters will be written
 * @param buffer Buffer pointer to write
 * @param size Size of the buffer
 */
void WriteMappedBufferWrite(u32 *cmdbuf, u32 offset, void *buffer, u32 size);

/**
 * @brief Writes the translate parameter for a static buffer. This will not write the buffer pointer
 * @param cmdbuf Buffer where the translate parameter will be written into
 * @param offset Offset word in which the translate parameter will be written
 * @param staticBufferId ID of the static buffer
 * @param size Size of the buffer
 */
void WriteStaticBufferTranslate(u32 *cmdbuf, u32 offset, u32 staticBufferId, u32 size);

/**
 * @brief Reads the pointer of a buffer from the command buffer
 * @param cmdbuf Command buffer
 * @param offset Offset word from which the pointer will be read
 * @return The buffer pointer
 */
void *ReadBuffer(u32 *cmdbuf, u32 offset);

/**
 * @brief Writes the translate parameter for a process ID
 * @param cmdbuf Buffer where the translate parameter will be written into
 * @param offset Offset word where the translate parameter will be written into
 */
void WriteProcessIDTranslate(u32 *cmdbuf, u32 offset);

/**
 * @brief Writes the translate parameter for one or multiple handles
 * @param cmdbuf Buffer where the translate parameter will be written into
 * @param offset Offset word where the translate parameter will be written into
 * @param numHandles Number of handles that will be used
 */
void WriteHandleTranslate(u32 *cmdbuf, u32 offset, u32 numHandles);

}  // namespace ipc

}  // namespace os

}  // namespace nn
