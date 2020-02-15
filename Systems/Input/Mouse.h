#ifndef _Mouse_H_
#define _Mouse_H_

#include "InputDevice.h"

#include "../Modules/Math/Vector.h"

namespace QwerkE {

    // TODO: Should be class?
    struct Mouse : public InputDevice
    {
        vec2 s_MousePos = vec2(0, 0);
        vec2 s_MouseDelta = vec2(0, 0); // position change from last frame
        vec2 s_MouseDragStart = vec2(0, 0);
        bool s_DragReset = false;

        void NewFrame();

        Mouse(eInputDeviceTypes type) : InputDevice(type) {}
        ~Mouse() {}
    };

}
#endif // !_Mouse_H_
