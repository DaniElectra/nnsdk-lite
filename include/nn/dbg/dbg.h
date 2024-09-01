#pragma once

#include "nn/dbg/BreakReason.h"

namespace nn {

namespace dbg {

/**
 * @brief Breaks execution of the program
 * @param reason Reason for breaking execution
 */
void Break(BreakReason reason);

/// Triggers a panic
void Panic();

} // namespace dbg

} // namespace nn
