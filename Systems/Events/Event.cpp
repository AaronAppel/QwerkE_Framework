#include "Event.h"

Event::Event()
{
}

Event::~Event()
{
}

void Event::SetID(int id)
{
	m_EventID = id;
}

int Event::GetID()
{
	return m_EventID;
}

eEventTypes Event::GetType()
{
	return m_EventType;
}

void Event::SetValue(int value)
{
	m_Value = value;
}

int Event::GetValue()
{
	return m_Value;
}