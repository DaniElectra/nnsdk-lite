#pragma once

namespace nn {

namespace dbg {

enum class BreakReason {
    Panic = 0,
    Assert,
    User,
    LoadRO,
    UnloadRO
};

} // namespace dbg

} // namespace nn
