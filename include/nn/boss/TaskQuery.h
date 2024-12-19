#pragma once

#include <cstring>
#include "helpers.h"
#include "nn/Result.h"
namespace nn {

namespace boss {

constexpr int QUERY_NAME_SIZE = 0xF;
constexpr int QUERY_VALUE_SIZE = 0x10;
constexpr int MAX_QUERY_FIELDS = 3;

// UNOFFICIAL: The official name of all structs and classes in this header are unknown

/// Represents a field of a query
struct QueryField {
    bool used;
    char name[QUERY_NAME_SIZE];
    char value[QUERY_VALUE_SIZE];
};
CHECK_SIZE(QueryField, 0x20);
CHECK_OFFSET(QueryField, 0x0, used);
CHECK_OFFSET(QueryField, 0x1, name);
CHECK_OFFSET(QueryField, 0x10, value);

/// Configuration of a task query
struct TaskQueryConfig {
    QueryField fields[MAX_QUERY_FIELDS];
};
CHECK_SIZE(TaskQueryConfig, 0x60);
CHECK_OFFSET(TaskQueryConfig, 0x0, fields);

/// Contains the query of a task
class TaskQuery {
public:
    TaskQueryConfig config;

    // vtable +0x0
    virtual ~TaskQuery();

    TaskQuery() {
        // memclr(&config, sizeof(config));
        std::memset(&config, 0, sizeof(config));
    }

    // UNOFFICIAL: The official name of this function is unknown

    /**
     * @brief Adds a parameter to the query
     * @remark The name must be smaller than 15 characters and the value must be smaller than 16 characters. A maximum of 3 parameters is allowed
     * @param name Parameter name
     * @param value Parameter value
     */
    nn::Result AddQuery(const char *name, const char *value);
};
CHECK_SIZE(TaskQuery, 0x64);
CHECK_OFFSET(TaskQuery, 0x4, config);

} // namespace boss

} // namespace nn
