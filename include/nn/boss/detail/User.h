#pragma once

#include "helpers.h"
#include "nn/Handle.h"
#include "nn/Result.h"
#include "nn/boss/NsDataHeaderInfo.h"
#include "nn/boss/PropertyType.h"
#include "nn/boss/TaskResultCode.h"
#include "nn/boss/TaskServiceStatus.h"
#include "nn/boss/TaskStateCode.h"
#include "nn/fs/MediaType.h"

namespace nn {

namespace boss {

namespace detail {

/// Manages a user session with BOSS
class User {
public:
    nn::Handle session;

    /**
     * @brief Initializes the user session
     * @param titleId Title ID to use for the session, or zero for the current program
     */
    nn::Result InitializeSession(u64 titleId);

    /**
     * @brief Gets information about the current storage
     * @param unkOut Unknown output parameter
     */
    nn::Result GetStorageInfo(u32 *unkOut);

    /**
     * @brief Registers a given task
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param taskOptionsConfigured Whether the @link TaskOption @endlink properties were sent
     * @param stepId Task step ID
     */
    nn::Result RegisterTask(const u8 *taskId, u32 taskIdSize, u8 taskOptionsConfigured, u8 stepId);

    /**
     * @brief Unregisters a given task
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param stepId Task step ID
     */
    nn::Result UnregisterTask(const u8 *taskId, u32 taskIdSize, u8 stepId);

    /**
     * @brief Reconfigures a given task
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param stepId Task step ID
     */
    nn::Result ReconfigureTask(const u8 *taskId, u32 taskIdSize, u8 stepId);

    /// Internally retrieves the list of task IDs from the application so that it can be accessed through @link ReceiveProperty @endlink
    nn::Result GetTaskIdList();

    /**
     * @brief Internally retrieves the list of steps from a given task so that it can be accessed through @link ReceiveProperty @endlink
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     */
    nn::Result GetStepIdList(const u8 *taskId, u32 taskIdSize);

    /**
     * @brief Gets a list of NS Data IDs
     * @param filter Filter by content datatypes, see https://www.3dbrew.org/wiki/BOSSU:GetNsDataIdList#Filter
     * @param list Output array of NS Data IDs
     * @param maxEntries Number of entries that the list can hold
     * @param outEntries Output number of entries written to the list
     * @param startIndex Start index for NS Data IDs
     * @param startNsDataId Start NS Data ID to look up
     * @param lastIndex Output last index written to the list
     */
    nn::Result GetNsDataIdList(u32 filter, u32 *list, u32 maxEntries, u16 *outEntries, u16 startIndex, u32 startNsDataId, u16 *lastIndex);

    /**
     * @brief Sends a property to the currently loaded session
     * @param type Property type
     * @param buffer Input buffer
     * @param size Buffer size
     */
    nn::Result SendProperty(PropertyType type, const u8 *buffer, u32 size);

    /**
     * @brief Sends a property handle to the currently loaded session
     * @param type Property type
     * @param handle Input handle
     */
    nn::Result SendPropertyHandle(PropertyType type, nn::Handle handle);

    /**
     * @brief Receives a property from the currently loaded session
     * @param type Property type
     * @param buffer Output buffer
     * @param size Buffer size
     * @param sizeRead Size written to the buffer
     */
    nn::Result ReceiveProperty(PropertyType type, u8 *buffer, u32 size, u32 *sizeRead);

    /**
     * @brief Updates the the task count @link PropertyType @endlink
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param count New count
     */
    nn::Result UpdateTaskCount(const u8 *taskId, u32 taskIdSize, u32 count);

    /**
     * @brief Gets the the task count @link PropertyType @endlink
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param count Output task count
     */
    nn::Result GetTaskCount(const u8 *taskId, u32 taskIdSize, u32 *count);

    /**
     * @brief Gets the the task service status
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param status Output task service status
     */
    nn::Result GetTaskServiceStatus(const u8 *taskId, u32 taskIdSize, TaskServiceStatus *status);

    /**
     * @brief Starts a given task
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     */
    nn::Result StartTask(const u8 *taskId, u32 taskIdSize);

    /**
     * @brief Starts a given immediate task
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     */
    nn::Result StartImmediateTask(const u8 *taskId, u32 taskIdSize);

    /**
     * @brief Cancels a given task
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     */
    nn::Result CancelTask(const u8 *taskId, u32 taskIdSize);

    /**
     * @brief Gets the finish event handle of the currently loaded task
     * @param handle Output finish handle
     */
    nn::Result GetTaskFinishHandle(Handle *handle);

    /**
     * @brief Gets the the task state
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param stateCode Output task state code
     * @param unk Unknown parameter
     * @param count Output task count @link PropertyType @endlink
     * @param currentStepId Output of the current step ID being run?
     */
    nn::Result GetTaskState(const u8 *taskId, u32 taskIdSize, TaskStateCode *stateCode, bool unk, u32 *count, u8 *currentStepId);

    /**
     * @brief Gets the the task result
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param resultCode Output task result code
     * @param count Output task count @link PropertyType @endlink ?
     * @param currentStepId Output of the current step ID being run?
     */
    nn::Result GetTaskResult(const u8 *taskId, u32 taskIdSize, TaskResultCode *resultCode, u32 *count, u8 *currentStepId);

    /**
     * @brief Internally retrieves all properties in relation to the status of the task, so that they can be stored on the @link TaskStatus @endlink
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param unk Unknown parameter
     * @param currentStepId Output of the current step ID being inspected?
     * @param stepId Task step ID to get the status from?
     */
    nn::Result GetTaskStatus(const u8 *taskId, u32 taskIdSize, bool unk, u8 *currentStepId, u8 stepId);

    /**
     * @brief Deletes the content for the specified NS Data ID
     * @param nsDataId NS Data ID
     */
    nn::Result DeleteNsData(u32 nsDataId);

    /**
     * @brief Gets header information about the specified NS Data ID
     * @param nsDataId NS Data ID
     * @param type Header info type
     * @param buffer Output buffer
     * @param size Buffer size
     */
    nn::Result GetNsDataHeaderInfo(u32 nsDataId, HeaderInfoType type, u8 *buffer, u32 size);

    /**
     * @brief Reads the content from the specified NS Data ID
     * @param nsDataId NS Data ID
     * @param offset Offset to read from
     * @param buffer Output buffer
     * @param size Buffer size
     * @param sizeRead Size written to the buffer
     * @param unknownOut Unknown output
     */
    nn::Result ReadNsData(u32 nsDataId, s64 offset, u8 *buffer, u32 size, u32 *sizeRead, u32 *unknownOut);

    /**
     * @brief Sets whether the content for the specified NS Data ID has been read
     * @param nsDataId NS Data ID
     * @param flag Read flag
     */
    nn::Result SetNsDataNewFlag(u32 nsDataId, bool flag);

    /**
     * @brief Gets whether the content for the specified NS Data ID has been read
     * @param nsDataId NS Data ID
     * @param flag Output flag
     */
    nn::Result GetNsDataNewFlag(u32 nsDataId, bool *flag);

    /**
     * @brief Gets the error code for the given @link TaskResultCode @endlink
     * @param errorCode Output error code
     * @param result Task result code
     */
    nn::Result GetErrorCode(u32 *errorCode, TaskResultCode result);

    /**
     * @brief Registers a storage entry to be used for BOSS
     * @param extDataId Extra Data ID to be used
     * @param unk1 Unknown parameter
     * @param unk2 Unknown parameter
     * @param mediaType Media type to store the data
     */
    nn::Result RegisterStorageEntry(u64 extDataId, u32 unk1, u16 unk2, nn::fs::MediaType mediaType);

    /// Unregisters the current storage being used
    nn::Result UnregisterStorage();

    /**
     * @brief Registers a given immediate task
     * @param taskId Task ID
     * @param taskIdSize Size of task ID, including @c NULL terminator
     * @param taskOptionsConfigured Whether the @link TaskOption @endlink properties were sent
     * @param stepId Task step ID
     */
    nn::Result RegisterImmediateTask(const u8 *taskId, u32 taskIdSize, u8 taskOptionsConfigured, u8 stepId);
};
CHECK_SIZE(User, 0x4);
CHECK_OFFSET(User, 0x0, session);

} // namespace detail

} // namespace boss

} // namespace nn
