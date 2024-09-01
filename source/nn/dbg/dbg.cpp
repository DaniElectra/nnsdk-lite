#include "nn/dbg/dbg.h"
#include "nn/svc/svc.h"

namespace nn {

namespace dbg {

void Break(BreakReason reason) {
    // NOTE - Some versions of the SDK seem to have a callback here

    return nn::svc::Break(reason);
}

void Panic() {
    // NOTE - Some versions of the SDK seem to have a callback here

    return nn::svc::Break(BreakReason::Panic);
}

} // namespace dbg

} // namespace nn
