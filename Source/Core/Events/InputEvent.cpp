#include "InputEvent.h"

namespace QwerkE {

    InputEvent::InputEvent(int value)
    {
        // TODO: Init list
        m_Value = value;
        m_EventType = eEventTypes::eEvent_InputEvent;
    }

    InputEvent::~InputEvent()
    {
    }

}
