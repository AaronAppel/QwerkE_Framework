#pragma once

#include "InputDevice.h"

namespace QwerkE {

    struct Keyboard : public InputDevice
    {
        Keyboard(eInputDeviceTypes type) : InputDevice(type) {}
        ~Keyboard() {}
    };

}
