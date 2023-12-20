#ifndef _Keyboard_Ext_Api_H_
#define _Keyboard_Ext_Api_H_

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
#endif // !_Keyboard_Ext_Api_H_
