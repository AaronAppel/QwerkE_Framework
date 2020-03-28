#ifndef _Keyboard_H_
#define _Keyboard_H_

#include "InputDevice.h"

namespace QwerkE {

    // TODO: Should be class?
    // TODO: Useful?
    struct Keyboard : public InputDevice
    {
        Keyboard(eInputDeviceTypes type) : InputDevice(type) {}
        ~Keyboard() {}
    };

}
#endif // !_Keyboard_H_
