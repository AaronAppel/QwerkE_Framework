#include "Input.h"
#include <Windows.h>

namespace QwerkE {

#ifndef GLFW3

    // Windows 32 bit
    void Input::AssignWin32Keys()
    {
        // TODO: Invert key codes ie. m_KeyCodex[VK_LBUTTON] = eKeys_LeftClick;

        // Mouse
        m_KeyCodex[eKeys_LeftClick] = VK_LBUTTON;
        m_KeyCodex[eKeys_RightClick] = VK_RBUTTON;
        m_KeyCodex[eKeys_MiddleClick] = VK_MBUTTON;

        m_KeyCodex[eKeys_MouseButton1] = VK_XBUTTON1;
        m_KeyCodex[eKeys_MouseButton2] = VK_XBUTTON2;

        //// Modifiers
        // Either
        m_KeyCodex[eKeys_CTRL] = VK_CONTROL;
        m_KeyCodex[eKeys_SHIFT] = VK_SHIFT;
        m_KeyCodex[eKeys_ALT] = VK_MENU;
        // Left
        m_KeyCodex[eKeys_LCTRL] = VK_LCONTROL;
        m_KeyCodex[eKeys_LSHIFT] = VK_LSHIFT;
        m_KeyCodex[eKeys_LALT] = VK_MENU; // TODO: Is there L/R Alt buttons?
        // Right
        m_KeyCodex[eKeys_RCTRL] = VK_RCONTROL;
        m_KeyCodex[eKeys_RSHIFT] = VK_RSHIFT;
        m_KeyCodex[eKeys_RALT] = VK_MENU;

        // Alternate Keys
        m_KeyCodex[eKeys_Return] = VK_RETURN;
        m_KeyCodex[eKeys_Insert] = VK_INSERT;
        m_KeyCodex[eKeys_Delete] = VK_DELETE;
        m_KeyCodex[eKeys_PageUp] = VK_PRIOR;
        m_KeyCodex[eKeys_PageDown] = VK_NEXT;
        m_KeyCodex[eKeys_Home] = VK_HOME;
        m_KeyCodex[eKeys_End] = VK_END;
        m_KeyCodex[eKeys_Tab] = VK_TAB;
        m_KeyCodex[eKeys_Escape] = VK_ESCAPE;

        m_KeyCodex[eKeys_Backspace] = VK_BACK;
        m_KeyCodex[eKeys_PrintScreen] = VK_PRINT;
        m_KeyCodex[eKeys_Pause] = VK_PAUSE;
        m_KeyCodex[eKeys_Menu] = VK_MENU;
        // m_KeyCodex[eKeys_FN] = 0; // May not be exposed by laptop os'

        // Alphabet
        m_KeyCodex[eKeys_A] = 0x41; // ASCII "A" == 65 == 0x41
        m_KeyCodex[eKeys_B] = 0x42;
        m_KeyCodex[eKeys_C] = 0x43;
        m_KeyCodex[eKeys_D] = 0x44;
        m_KeyCodex[eKeys_E] = 0x45;
        m_KeyCodex[eKeys_F] = 0x46;
        m_KeyCodex[eKeys_G] = 0x47;
        m_KeyCodex[eKeys_H] = 0x48;
        m_KeyCodex[eKeys_I] = 0x49;
        m_KeyCodex[eKeys_J] = 0x4A;
        m_KeyCodex[eKeys_K] = 0x4B;
        m_KeyCodex[eKeys_L] = 0x4C;
        m_KeyCodex[eKeys_M] = 0x4D;
        m_KeyCodex[eKeys_N] = 0x4E;
        m_KeyCodex[eKeys_O] = 0x4F;
        m_KeyCodex[eKeys_P] = 0x50;
        m_KeyCodex[eKeys_Q] = 0x51;
        m_KeyCodex[eKeys_R] = 0x52;
        m_KeyCodex[eKeys_S] = 0x53;
        m_KeyCodex[eKeys_T] = 0x54;
        m_KeyCodex[eKeys_U] = 0x55;
        m_KeyCodex[eKeys_V] = 0x56;
        m_KeyCodex[eKeys_W] = 0x57;
        m_KeyCodex[eKeys_X] = 0x58;
        m_KeyCodex[eKeys_Y] = 0x59;
        m_KeyCodex[eKeys_Z] = 0x5A;

        // Numbers
        m_KeyCodex[eKeys_0] = 0x30;
        m_KeyCodex[eKeys_1] = 0x31;
        m_KeyCodex[eKeys_2] = 0x32;
        m_KeyCodex[eKeys_3] = 0x33;
        m_KeyCodex[eKeys_4] = 0x34;
        m_KeyCodex[eKeys_5] = 0x35;
        m_KeyCodex[eKeys_6] = 0x36;
        m_KeyCodex[eKeys_7] = 0x37;
        m_KeyCodex[eKeys_8] = 0x38;
        m_KeyCodex[eKeys_9] = 0x39;

        // Arrow keys
        m_KeyCodex[eKeys_Up] = VK_UP;
        m_KeyCodex[eKeys_Down] = VK_DOWN;
        m_KeyCodex[eKeys_Left] = VK_LEFT;
        m_KeyCodex[eKeys_Right] = VK_RIGHT;

        // Function Keys
        m_KeyCodex[eKeys_F1] = VK_F1;
        m_KeyCodex[eKeys_F2] = VK_F2;
        m_KeyCodex[eKeys_F3] = VK_F3;
        m_KeyCodex[eKeys_F4] = VK_F4;
        m_KeyCodex[eKeys_F5] = VK_F5;
        m_KeyCodex[eKeys_F6] = VK_F6;
        m_KeyCodex[eKeys_F7] = VK_F7;
        m_KeyCodex[eKeys_F8] = VK_F8;
        m_KeyCodex[eKeys_F9] = VK_F9;
        m_KeyCodex[eKeys_F10] = VK_F10;
        m_KeyCodex[eKeys_F11] = VK_F11;
        m_KeyCodex[eKeys_F12] = VK_F12;
        m_KeyCodex[eKeys_F13] = VK_F13;
        m_KeyCodex[eKeys_F14] = VK_F14;
        m_KeyCodex[eKeys_F15] = VK_F15;
        m_KeyCodex[eKeys_F16] = VK_F16;
        m_KeyCodex[eKeys_F17] = VK_F17;
        m_KeyCodex[eKeys_F18] = VK_F18;
        m_KeyCodex[eKeys_F19] = VK_F19;
        m_KeyCodex[eKeys_F20] = VK_F20;
        m_KeyCodex[eKeys_F21] = VK_F21;
        m_KeyCodex[eKeys_F22] = VK_F22;
        m_KeyCodex[eKeys_F23] = VK_F23;
        m_KeyCodex[eKeys_F24] = VK_F24;
        m_KeyCodex[eKeys_F25]; // Only 24 function keys on windows

        // System Keys
        m_KeyCodex[eKeys_System] = VK_LWIN; // TODO: Also handle VK_RWIN

        // TODO: Game Pad
        // m_KeyCodex[eKeys_System] = VK_GAMEPAD_A;
    }
#endif // GLFW3
}
