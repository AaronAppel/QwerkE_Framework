#ifndef _Timer_H_
#define _Timer_H_

// Simplified time management.
// Pretty basic implementation so far but is intended
// to be expanded upon in the future.

// Possible feature/functionality addition: CallBacks
// Use a CallBack* to notify listeners of timer expiry,
// or trigger a function.

#include <float.h>

class Timer
{
public:
    Timer();
    virtual ~Timer();

    void Reset(double a_TimeLength) // start
    {
        m_ElapsedTime = 0.0f;
        m_TimeLength = a_TimeLength;
        m_HasCompleted = false;
    }

    bool Tick(double a_Deltatime) // update
    {
        if (m_HasCompleted == false)
        {
            m_ElapsedTime += a_Deltatime;
            CheckIfCompleted();
        }
        return m_HasCompleted;
    }

    bool HasCompleted() { return m_HasCompleted; };
    // void SetCallBack(CallBack* callback) { m_CallBack = callback;};
    // void CallBack(...); // build a universal function callback pointer if possible
private:
    void CheckIfCompleted()
    {
        if (m_ElapsedTime >= m_TimeLength)
        {
            m_HasCompleted = true;
            // m_CallBack->Trigger();
        }
        else
            m_HasCompleted = false;
    }
    bool m_HasCompleted = false;
    float m_ElapsedTime = 0.0f;
    float m_TimeLength = FLT_MAX;

    // CallBack* m_CallBack = nullptr;
};

#endif //!_Timer_H_
