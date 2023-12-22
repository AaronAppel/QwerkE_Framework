#pragma once

#include "Event.h"

namespace QwerkE {

    class InputEvent : public Event
    {
    public:
        InputEvent(int value);
        ~InputEvent();

    private:

    };

}
