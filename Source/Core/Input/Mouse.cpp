#include "Mouse.h"

#include "../Input/Input.h"

namespace QwerkE {

    void Mouse::NewFrame()
    {
        if (s_DragReset)
        {
            s_MouseDragStart = 0.0f;
            s_DragReset = false;
        }

        // reset 1 frame buffers
        if (s_OneFrameBuffersAreDirty)
        {
            memset(s_OneFrameKeyBuffer, eKeys_NULL_KEY, QWERKE_ONE_FRAME_MAX_INPUT * sizeof(short));
            memset(s_OneFrameValueBuffer, 0, QWERKE_ONE_FRAME_MAX_INPUT); // TODO: Do I want a 3rd key state?
            s_OneFrameBuffersAreDirty = false;
        }
    }

}
