#include "InputEvent.h"

InputEvent::InputEvent(int value)
{
    m_EventType = eEventTypes::eEvent_InputEvent;
    m_Value = value; // key that was pressed
}

InputEvent::~InputEvent()
{
}