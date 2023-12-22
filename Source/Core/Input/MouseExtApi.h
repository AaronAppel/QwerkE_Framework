#pragma once

#include "QwerKE_eKeys.h"

namespace QwerkE {

    struct Mouse;

    class MouseExtAPI
    {
    public:
        MouseExtAPI(Mouse* mouse) { m_Mouse = mouse; }
        ~MouseExtAPI() {}

        bool GetIsKeyDown(eKeys key) const;

        bool FrameAction(eKeys key, eKeyState state) const;

    private:
        Mouse* m_Mouse = nullptr;
    };

}
