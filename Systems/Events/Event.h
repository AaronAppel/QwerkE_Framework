#ifndef _Event_H_
#define _Event_H_

#include <cstdint>
enum class eEventTypes : std::uint8_t
{
	eEvent_Invalid = 0,
	eEvent_InputEvent,
	eEvent_AssetLoaded,
	eEvent_JobQueued,
	eEvent_System_Message,
	eEvent_Max
};

// TODO: Design Event system

class Event // abstract
{
public:
	Event();
	~Event();

	void SetID(int id);
	int GetID();

	void SetValue(int value);
	int GetValue();

	eEventTypes GetType();

	virtual void Process() {}

protected:
	signed int m_EventID = -1;
	eEventTypes m_EventType = eEventTypes::eEvent_Invalid;
	int m_Value = -1;
};

#endif // !_Event_H_
