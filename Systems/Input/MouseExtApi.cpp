#include "MouseExtApi.h"
#include "Mouse.h"

namespace QwerkE {    

    bool MouseExtAPI::GetIsKeyDown(eKeys key) const
    {
        return m_Mouse->s_KeyStates[key];
    }

    bool MouseExtAPI::FrameAction(eKeys key, eKeyState state) const
    {
        if (m_Mouse->s_OneFrameKeyBuffer[0] != eKeys::eKeys_NULL_KEY) // was a key even pressed?
            for (int i = 0; i < QWERKE_ONE_FRAME_MAX_INPUT; i++)
            {
                if (m_Mouse->s_OneFrameKeyBuffer[i] == key)
                    return m_Mouse->s_OneFrameValueBuffer[i] == (bool)state;
            }
        return 0;
    }

}
