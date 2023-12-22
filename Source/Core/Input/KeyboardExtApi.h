#pragma once

#include "../Input/Input.h"

namespace QwerkE {

    struct Keyboard;

    class KeyboardExtAPI
    {
    public:
        KeyboardExtAPI(Keyboard* keyboard) { m_Keyboard = keyboard; }
        ~KeyboardExtAPI() {}

        bool GetIsKeyDown(eKeys key) const;

        bool FrameAction(eKeys key, eKeyState state) const; // #TODO Rename

    private:
        Keyboard* m_Keyboard = nullptr;
    };

}
