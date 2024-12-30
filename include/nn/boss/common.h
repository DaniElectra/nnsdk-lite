#pragma once

#include "nn/types.h"

namespace nn {

namespace boss {

constexpr int ACTION_DATA_SIZE = 0x200;
constexpr int URL_SIZE = 0x200;
constexpr int HTTP_HEADER_SIZE = 0x20;
constexpr int HTTP_HEADER_VALUE_SIZE = 0x100;
constexpr int MAX_HEADERS = 3;
constexpr int MAX_ROOT_CAS = 3;
constexpr int MAX_CLIENT_CERTS = 1;

constexpr int TASK_ID_SIZE = 8;
constexpr int TASK_ID_LIST_SIZE = 128;

constexpr int QUERY_NAME_SIZE = 0xF;
constexpr int QUERY_VALUE_SIZE = 0x10;
constexpr int MAX_QUERY_FIELDS = 3;

constexpr u8 STEP_ID_CURRENT = 0x80;
constexpr int STEP_ID_LIST_SIZE = 0x80;

} // namespace boss

} // namespace nn
