#pragma once

#include <cstdint>

namespace QwerkE {

#define INVALID_EVENT_ID -1
#define INVALID_EVENT_VALUE -1

    enum class eEventTypes : std::uint8_t
    {
        eEvent_Invalid = 0,
        eEvent_InputEvent,
        eEvent_AssetLoaded,
        eEvent_JobQueued,
        eEvent_System_Message,
        eEvent_Max
    };

    class Event
    {
    public:
        virtual ~Event() = default;

        void SetID(int id) { m_EventID = id; }
        signed int GetID() { return m_EventID; }

        void SetValue(int value) { m_Value = value; }
        signed int GetValue() { return m_Value; }

        eEventTypes GetType() { return m_EventType; }

        virtual void Process() = 0;

    protected:
        signed int m_EventID = INVALID_EVENT_ID;
        eEventTypes m_EventType = eEventTypes::eEvent_Invalid;
        int m_Value = INVALID_EVENT_VALUE;
    };

}
