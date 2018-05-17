#ifndef __Tween_H__
#define __Tween_H__

#include "TweenFuncs.h"

class Tween
{
public:
    Tween() {}

    Tween(float min, float range, float timeSpan) :
        m_StartingValue(min),
        m_Range(range),
        m_EndTime(timeSpan) {}

    ~Tween() {}

    void SetTween(TweenFunc function) { m_pTweenFunction = function; }

    float Tick(double a_Deltatime)
    {
        m_ElapsedTime += (float)a_Deltatime;
        return m_pTweenFunction(m_StartingValue, m_Range, m_ElapsedTime, m_EndTime);
    }

    void Reset()
    {
        Reset(m_StartingValue, m_Range, m_EndTime);
    }

    void Reset(float min, float range, float time)
    {
        m_ElapsedTime = 0.0f; // reset timer
        m_StartingValue = min;
        m_Range = range;
        m_EndTime = time;
    }

	float Progress() { return m_pTweenFunction(m_StartingValue, m_Range, m_ElapsedTime, m_EndTime); };

    // TODO: Callbacks

private:
	TweenFunc m_pTweenFunction = nullptr;
	float m_StartingValue = 0.0f;
	float m_Range = 0.0f;
	float m_ElapsedTime = 0.0f;
	float m_EndTime = 0.0f;
};

#endif //!__Tween_H__
