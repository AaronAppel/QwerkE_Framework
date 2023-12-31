#include "Time.h"

#ifdef _WIN32
#include <profileapi.h>
#include <winnt.h>
#else
#error "Support non windows platform!"
#endif

namespace QwerkE {

    float Time::m_Delta = 0.0;
    float Time::m_CurrentFrame = 0.0;
    float Time::m_LastFrame = 0.0;

    void Time::NewFrame()
    {
        m_LastFrame = m_CurrentFrame; // #TODO Fix faulty logic for first frame when all values are 0
        m_CurrentFrame = Now();
        m_Delta = m_CurrentFrame - m_LastFrame;
    }

    float Time::Now()
    {
        unsigned __int64 freq;
        unsigned __int64 time;
        QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
        QueryPerformanceCounter((LARGE_INTEGER*)&time);
        return (float)time / freq;
    }

}
