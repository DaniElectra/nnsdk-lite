#include "nn/srv/srv.h"
#include "nn/fnd/TimeSpan.h"
#include "nn/srv/detail/service.h"
#include "nn/Result.h"
#include "nn/os/sync.h"
#include "nn/os/thread.h"
#include "nn/svc/svc.h"

namespace nn {

namespace srv {

namespace {
    // UNOFFICIAL: The real name for this is unknown
    static bool InitializedLock;

    static nn::os::CriticalSection s_InitializeLock;
    static u32 s_InitializeCount;
    static constexpr auto PORT_NAME = "srv:";
}

nn::Result Initialize() {
    nn::Result res;

    // NOTE - Different versions of the SDK don't use this and initialize the lock statically
    if (!InitializedLock) {
        s_InitializeLock.Initialize();
        InitializedLock = true;
    }

    s_InitializeLock.Enter(); // TODO - This uses a nn::os::CriticalSection::ScopedLock for managing the lock

    if (s_InitializeCount > 0) {
        s_InitializeCount++;
        s_InitializeLock.Leave();
        return {nn::Result::Level_Info, nn::Result::Summary_Nop, nn::Result::ModuleType_SRV, nn::Result::Description_AlreadyInitialized}; // 0x82067F9
    }

    while (true) {
        res = nn::svc::ConnectToPort(&detail::Service::s_Session.session, PORT_NAME);

        if (res.GetLevel() != nn::Result::Level_Permanent ||
            res.GetSummary() != nn::Result::Summary_NotFound ||
            res.GetDescription() != nn::Result::Description_NotFound)
            break;

        // While the SRV service isn't initialized, sleep for 500'000 (0,5 milliseconds) nanoseconds and try again
        nn::os::Thread::SleepImpl(nn::fnd::TimeSpan(500'000));
    }

    if (res) {
        res = detail::Service::RegisterClient();
        s_InitializeCount++;
    }

    s_InitializeLock.Leave();
    return res;
}

}  // namespace srv

}  // namespace nn
