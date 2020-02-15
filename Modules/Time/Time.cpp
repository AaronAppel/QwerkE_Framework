#include "Time.h"

namespace QwerkE {

    double Time::m_Delta;
    double Time::m_LastFrame = DBL_MAX;

    Time::Time()
    {
    }

    Time::~Time()
    {
    }

    void Time::NewFrame()
    {
        m_LastFrame = m_Delta;
        m_Delta = Now() - m_LastFrame;
    }

    double Time::Delta()
    {
        return m_Delta;
    }

    double Time::Now()
    {
        unsigned __int64 freq;
        unsigned __int64 time;
        QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
        QueryPerformanceCounter((LARGE_INTEGER*)&time);
        return (double)time / freq;
    }

}
