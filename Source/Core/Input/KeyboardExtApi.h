#ifndef _Keyboard_Ext_Api_H_
#define _Keyboard_Ext_Api_H_

namespace QwerkE {

    struct Keyboard;

    class KeyboardExtAPI
    {
    public:
        KeyboardExtAPI(Keyboard* keyboard) { m_Keyboard = keyboard; }
        ~KeyboardExtAPI() {}

        bool GetIsKeyDown(eKeys key) const;

        bool FrameAction(eKeys key, eKeyState state) const;

    private:
        Keyboard* m_Keyboard = nullptr;
    };

}
#endif // !_Keyboard_Ext_Api_H_
