#ifndef _InputEvent_H_
#define _InputEvent_H_

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
#endif // !_InputEvent_H_
