#pragma once

#include "Instrumentor.h"

#define QPROFILING 0

#if QPROFILING
#define PROFILE_SCOPE(scopeName) InstrumentationTimer timer##__LINE__(scopeName)
// NOTE: Could use __FUNCSIG__ to show args for overloaded function, but it is more info than needed currently
#define PROFILE_FUNC() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(scopeName)
#define PROFILE_FUNC(scopeName)
#endif

namespace QwerkE {

    class Profiler
    {
    public:
    private:
    };

}