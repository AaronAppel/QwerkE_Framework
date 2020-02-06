#ifndef _QwerkE_eKeys_H_
#define _QwerkE_eKeys_H_

namespace QwerkE {

    enum eKeyState
    {
        eKeyState_Release = 0,
        eKeyState_Press,
        // eKeyState_Held, ? affects GetIsKeyDown()

        eKeyState_Max
    };

    enum eKeys
    {
        eKeys_NULL_KEY = 0,

        // Mouse
        eKeys_LeftClick,
        eKeys_RightClick,
        eKeys_MiddleClick,

        eKeys_MouseButton1,
        eKeys_MouseButton2,
        eKeys_MouseButton3,
        eKeys_MouseButton4,
        eKeys_MouseButton5,
        eKeys_MouseButton6,
        eKeys_MouseButton7,
        eKeys_MouseButton8,

        // Joystick

    //#define 	GLFW_JOYSTICK_1   0
    //
    //#define 	GLFW_JOYSTICK_2   1
    //
    //#define 	GLFW_JOYSTICK_3   2
    //
    //#define 	GLFW_JOYSTICK_4   3
    //
    //#define 	GLFW_JOYSTICK_5   4
    //
    //#define 	GLFW_JOYSTICK_6   5
    //
    //#define 	GLFW_JOYSTICK_7   6
    //
    //#define 	GLFW_JOYSTICK_8   7
    //
    //#define 	GLFW_JOYSTICK_9   8
    //
    //#define 	GLFW_JOYSTICK_10   9
    //
    //#define 	GLFW_JOYSTICK_11   10
    //
    //#define 	GLFW_JOYSTICK_12   11
    //
    //#define 	GLFW_JOYSTICK_13   12
    //
    //#define 	GLFW_JOYSTICK_14   13
    //
    //#define 	GLFW_JOYSTICK_15   14
    //
    //#define 	GLFW_JOYSTICK_16   15

    // #define 	GLFW_MOD_SHIFT   0x0001

        // Modifiers
        // Either
        eKeys_CTRL,
        eKeys_SHIFT,
        eKeys_ALT,
        // Left
        eKeys_LCTRL,
        eKeys_LSHIFT,
        eKeys_LALT,
        // Right
        eKeys_RCTRL,
        eKeys_RSHIFT,
        eKeys_RALT,

        // Alternate Keys
        eKeys_Return,
        eKeys_Insert,
        eKeys_Delete,
        eKeys_PageUp,
        eKeys_PageDown,
        eKeys_Home,
        eKeys_End,
        eKeys_Tab,
        eKeys_Escape,
        eKeys_Backspace,
        eKeys_PrintScreen,
        eKeys_Pause,
        eKeys_Menu,
        eKeys_FN, // Alternate function key (Sleep, volume, etc)

        // Locks
        eKeys_CapsLock,
        eKeys_NumLock,
        eKeys_ScrollLock,

        // Key Pad
        eKeys_Pad_Decimal,
        eKeys_Pad_Return,
        eKeys_Pad_Plus,
        eKeys_Pad_Minus,
        eKeys_Pad_Division,
        eKeys_Pad_Multiplication,

        eKeys_Pad_0,
        eKeys_Pad_1,
        eKeys_Pad_2,
        eKeys_Pad_3,
        eKeys_Pad_4,
        eKeys_Pad_5,
        eKeys_Pad_6,
        eKeys_Pad_7,
        eKeys_Pad_8,
        eKeys_Pad_9,

        // Alphabet
        eKeys_A,
        eKeys_B,
        eKeys_C,
        eKeys_D,
        eKeys_E,
        eKeys_F,
        eKeys_G,
        eKeys_H,
        eKeys_I,
        eKeys_J,
        eKeys_K,
        eKeys_L,
        eKeys_M,
        eKeys_N,
        eKeys_O,
        eKeys_P,
        eKeys_Q,
        eKeys_R,
        eKeys_S,
        eKeys_T,
        eKeys_U,
        eKeys_V,
        eKeys_W,
        eKeys_X,
        eKeys_Y,
        eKeys_Z,

        // Numbers
        eKeys_0,
        eKeys_1,
        eKeys_2,
        eKeys_3,
        eKeys_4,
        eKeys_5,
        eKeys_6,
        eKeys_7,
        eKeys_8,
        eKeys_9,

        // Punctuation
        eKeys_Space,
        eKeys_Apostrophe,
        eKeys_Comma,
        eKeys_Period,
        eKeys_ForwardSlash,
        eKeys_BackSlash,
        eKeys_SemiColon,
        eKeys_LeftBracket,
        eKeys_RightBracket,
        eKeys_Tilde,
        eKeys_Minus,
        eKeys_Equal,

        // Arrow keys
        eKeys_Up,
        eKeys_Down,
        eKeys_Left,
        eKeys_Right,

        // Function Keys
        eKeys_F1,
        eKeys_F2,
        eKeys_F3,
        eKeys_F4,
        eKeys_F5,
        eKeys_F6,
        eKeys_F7,
        eKeys_F8,
        eKeys_F9,
        eKeys_F10,
        eKeys_F11,
        eKeys_F12,
        eKeys_F13,
        eKeys_F14,
        eKeys_F15,
        eKeys_F16,
        eKeys_F17,
        eKeys_F18,
        eKeys_F19,
        eKeys_F20,
        eKeys_F21,
        eKeys_F22,
        eKeys_F23,
        eKeys_F24,
        eKeys_F25,

        // System Keys
        eKeys_System, // Super, Window key, Command Key, etc

        // Media Keys?
        // Macro Keys?

        eKeys_MAX
    };

}
#endif //!_QwerkE_eKeys_H_
