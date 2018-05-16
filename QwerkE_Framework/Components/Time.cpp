#include "Time.h"

namespace QwerkE
{
    const double* Time::m_DeltaTime = nullptr;
	const float* Time::m_FPS = nullptr;

    Time::Time()
    {
    }

    Time::~Time()
    {
    }

    void Time::SetDeltatime(double* deltaTime)
    {
        m_DeltaTime = deltaTime;
    }

    double Time::GetDeltaTime()
    {
        return *m_DeltaTime;
    }

	void Time::SetFrameRate(float* framesPerSecond)
	{
		m_FPS = framesPerSecond;
	}

	float Time::GetFrameRate()
	{
		return *m_FPS;
	}
}