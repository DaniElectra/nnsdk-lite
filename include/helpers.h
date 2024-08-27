#pragma once

#ifdef NNSDK_CHECKS

#include <cstddef>

// Helper macros for checking sizes and offsets
#define CHECK_SIZE(type, size) static_assert(sizeof(type) == size)
#define CHECK_OFFSET(type, offset, member) static_assert(offsetof(type, member) == offset)

#else

#define CHECK_SIZE(type, size)
#define CHECK_OFFSET(type, offset, member)

#endif

// Helper macros for inserting unknown/padding bytes to a struct. Adapted from https://github.com/devkitPro/wut/blob/master/include/wut_structsize.h

// Workaround weird macro concat ## behaviour
#define PP_CAT(a, b) PP_CAT_I(a, b)
#define PP_CAT_I(a, b) PP_CAT_II(~, a##b)
#define PP_CAT_II(p, res) res

// Allow us to easily add UNKNOWN / PADDING bytes into our structs,
// generates unique variable names using __COUNTER__
#define INSERT_UNKNOWN_BYTES(size) char PP_CAT(__unk, __COUNTER__)[size]
#define INSERT_PADDING_BYTES(size) char PP_CAT(__pad, __COUNTER__)[size]
