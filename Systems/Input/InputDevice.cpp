#include "InputDevice.h"

namespace QwerkE {

    void InputDevice::RaiseInputEvent(eKeys key, eKeyState state)
    {
        s_OneFrameBuffersAreDirty = true;

        for (int i = 0; i < 12; i++)
        {
            if (s_OneFrameKeyBuffer[i] == eKeys_NULL_KEY)
            {
                s_OneFrameKeyBuffer[i] = key;
                s_OneFrameValueBuffer[i] = state;
                return;
            }
        }
    }

    void InputDevice::NewFrame()
    {
        if (s_OneFrameBuffersAreDirty)
        {
            // m_MouseDragStart = 0.0f;
            memset(s_OneFrameKeyBuffer, eKeys_NULL_KEY, 12 * sizeof(short));
            memset(s_OneFrameValueBuffer, 0, 12); // TODO: Do I want a 3rd key state?
            s_OneFrameBuffersAreDirty = false;
        }
    }

}
