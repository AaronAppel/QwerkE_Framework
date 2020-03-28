#include "Mouse.h"
#include "Keyboard.h"
#include "../Libraries/glfw/GLFW/glfw3.h"

namespace QwerkE {

    eKeys Input::GLFWToQwerkEKey(int key)
    {
        return (eKeys)m_KeyCodex[key];
    }

    // Windows 32 bit
    void Input::AssignGLFWKeys(InputDevice* device)
    {
        eInputDeviceTypes deviceType = device->GetType();

        if (deviceType > eInputDeviceTypes::Keyboard_Min&&
            deviceType < eInputDeviceTypes::Keyboard_Max)
        {
            // Keyboard
            Keyboard* keyboard = (Keyboard*)device;

            // Modifiers
            // Either
            // m_KeyCodex[?] = eKeys_CTRL; // TODO: Handle either left Or right
            // m_KeyCodex[?] = eKeys_SHIFT; // TODO: Handle either left Or right
            // m_KeyCodex[?] = eKeys_ALT; // TODO: Handle either left Or right
            // Left
            keyboard->s_KeyCodex[GLFW_KEY_LEFT_CONTROL] = eKeys_LCTRL; // GLFWK_KEY_RIGHT_CONTROL
            keyboard->s_KeyCodex[GLFW_KEY_LEFT_SHIFT] = eKeys_LSHIFT; // LGW_KEY_RIGHT_SHIFT
            keyboard->s_KeyCodex[GLFW_KEY_LEFT_ALT] = eKeys_LALT; // GLFW_KEY_RIGHT_ALT
            // Right
            keyboard->s_KeyCodex[GLFW_KEY_RIGHT_CONTROL] = eKeys_RCTRL; // GLFWK_KEY_RIGHT_CONTROL
            keyboard->s_KeyCodex[GLFW_KEY_RIGHT_SHIFT] = eKeys_RSHIFT; // LGW_KEY_RIGHT_SHIFT
            keyboard->s_KeyCodex[GLFW_KEY_RIGHT_ALT] = eKeys_RALT; // GLFW_KEY_RIGHT_ALT

            // Alternate Keys
            keyboard->s_KeyCodex[GLFW_KEY_ENTER] = eKeys_Return;
            keyboard->s_KeyCodex[GLFW_KEY_INSERT] = eKeys_Insert;
            keyboard->s_KeyCodex[GLFW_KEY_DELETE] = eKeys_Delete;
            keyboard->s_KeyCodex[GLFW_KEY_PAGE_UP] = eKeys_PageUp;
            keyboard->s_KeyCodex[GLFW_KEY_PAGE_DOWN] = eKeys_PageDown;
            keyboard->s_KeyCodex[GLFW_KEY_HOME] = eKeys_Home;
            keyboard->s_KeyCodex[GLFW_KEY_END] = eKeys_End;
            keyboard->s_KeyCodex[GLFW_KEY_TAB] = eKeys_Tab;
            keyboard->s_KeyCodex[GLFW_KEY_ESCAPE] = eKeys_Escape;
            keyboard->s_KeyCodex[GLFW_KEY_BACKSPACE] = eKeys_Backspace;
            keyboard->s_KeyCodex[GLFW_KEY_PRINT_SCREEN] = eKeys_PrintScreen;
            keyboard->s_KeyCodex[GLFW_KEY_PAUSE] = eKeys_Pause;
            keyboard->s_KeyCodex[GLFW_KEY_MENU] = eKeys_Menu;
            // m_KeyCodex[?] = eKeys_FN; // TODO: Find fn key

            // Locks
            keyboard->s_KeyCodex[GLFW_KEY_CAPS_LOCK] = eKeys_CapsLock,
            keyboard->s_KeyCodex[GLFW_KEY_NUM_LOCK] = eKeys_NumLock;
            keyboard->s_KeyCodex[GLFW_KEY_SCROLL_LOCK] = eKeys_ScrollLock;

            // Key Pad
            keyboard->s_KeyCodex[GLFW_KEY_KP_DECIMAL] = eKeys_Pad_Decimal;
            keyboard->s_KeyCodex[GLFW_KEY_ENTER] = eKeys_Pad_Return;
            keyboard->s_KeyCodex[GLFW_KEY_KP_ADD] = eKeys_Pad_Plus;
            keyboard->s_KeyCodex[GLFW_KEY_KP_SUBTRACT] = eKeys_Pad_Minus;
            keyboard->s_KeyCodex[GLFW_KEY_KP_DIVIDE] = eKeys_Pad_Division;
            keyboard->s_KeyCodex[GLFW_KEY_KP_MULTIPLY] = eKeys_Pad_Multiplication;

            keyboard->s_KeyCodex[GLFW_KEY_KP_0] = eKeys_Pad_0;
            keyboard->s_KeyCodex[GLFW_KEY_KP_1] = eKeys_Pad_1;
            keyboard->s_KeyCodex[GLFW_KEY_KP_2] = eKeys_Pad_2;
            keyboard->s_KeyCodex[GLFW_KEY_KP_3] = eKeys_Pad_3;
            keyboard->s_KeyCodex[GLFW_KEY_KP_4] = eKeys_Pad_4;
            keyboard->s_KeyCodex[GLFW_KEY_KP_5] = eKeys_Pad_5;
            keyboard->s_KeyCodex[GLFW_KEY_KP_6] = eKeys_Pad_6;
            keyboard->s_KeyCodex[GLFW_KEY_KP_7] = eKeys_Pad_7;
            keyboard->s_KeyCodex[GLFW_KEY_KP_8] = eKeys_Pad_8;
            keyboard->s_KeyCodex[GLFW_KEY_KP_9] = eKeys_Pad_9;

            // Alphabet
            keyboard->s_KeyCodex[GLFW_KEY_A] = eKeys_A;
            keyboard->s_KeyCodex[GLFW_KEY_B] = eKeys_B;
            keyboard->s_KeyCodex[GLFW_KEY_C] = eKeys_C;
            keyboard->s_KeyCodex[GLFW_KEY_D] = eKeys_D;
            keyboard->s_KeyCodex[GLFW_KEY_E] = eKeys_E;
            keyboard->s_KeyCodex[GLFW_KEY_F] = eKeys_F;
            keyboard->s_KeyCodex[GLFW_KEY_G] = eKeys_G;
            keyboard->s_KeyCodex[GLFW_KEY_H] = eKeys_H;
            keyboard->s_KeyCodex[GLFW_KEY_I] = eKeys_I;
            keyboard->s_KeyCodex[GLFW_KEY_J] = eKeys_J;
            keyboard->s_KeyCodex[GLFW_KEY_K] = eKeys_K;
            keyboard->s_KeyCodex[GLFW_KEY_L] = eKeys_L;
            keyboard->s_KeyCodex[GLFW_KEY_M] = eKeys_M;
            keyboard->s_KeyCodex[GLFW_KEY_N] = eKeys_N;
            keyboard->s_KeyCodex[GLFW_KEY_O] = eKeys_O;
            keyboard->s_KeyCodex[GLFW_KEY_P] = eKeys_P;
            keyboard->s_KeyCodex[GLFW_KEY_Q] = eKeys_Q;
            keyboard->s_KeyCodex[GLFW_KEY_R] = eKeys_R;
            keyboard->s_KeyCodex[GLFW_KEY_S] = eKeys_S;
            keyboard->s_KeyCodex[GLFW_KEY_T] = eKeys_T;
            keyboard->s_KeyCodex[GLFW_KEY_U] = eKeys_U;
            keyboard->s_KeyCodex[GLFW_KEY_V] = eKeys_V;
            keyboard->s_KeyCodex[GLFW_KEY_W] = eKeys_W;
            keyboard->s_KeyCodex[GLFW_KEY_X] = eKeys_X;
            keyboard->s_KeyCodex[GLFW_KEY_Y] = eKeys_Y;
            keyboard->s_KeyCodex[GLFW_KEY_Z] = eKeys_Z;

            // Numbers
            keyboard->s_KeyCodex[GLFW_KEY_0] = eKeys_0;
            keyboard->s_KeyCodex[GLFW_KEY_1] = eKeys_1;
            keyboard->s_KeyCodex[GLFW_KEY_2] = eKeys_2;
            keyboard->s_KeyCodex[GLFW_KEY_3] = eKeys_3;
            keyboard->s_KeyCodex[GLFW_KEY_4] = eKeys_4;
            keyboard->s_KeyCodex[GLFW_KEY_5] = eKeys_5;
            keyboard->s_KeyCodex[GLFW_KEY_6] = eKeys_6;
            keyboard->s_KeyCodex[GLFW_KEY_7] = eKeys_7;
            keyboard->s_KeyCodex[GLFW_KEY_8] = eKeys_8;
            keyboard->s_KeyCodex[GLFW_KEY_9] = eKeys_9;

            // Punctuation
            keyboard->s_KeyCodex[GLFW_KEY_SPACE] = eKeys_Space;
            keyboard->s_KeyCodex[GLFW_KEY_APOSTROPHE] = eKeys_Apostrophe;
            keyboard->s_KeyCodex[GLFW_KEY_COMMA] = eKeys_Comma;
            keyboard->s_KeyCodex[GLFW_KEY_PERIOD] = eKeys_Period;
            keyboard->s_KeyCodex[GLFW_KEY_SLASH] = eKeys_ForwardSlash;
            keyboard->s_KeyCodex[GLFW_KEY_BACKSLASH] = eKeys_BackSlash;
            keyboard->s_KeyCodex[GLFW_KEY_SEMICOLON] = eKeys_SemiColon;
            keyboard->s_KeyCodex[GLFW_KEY_LEFT_BRACKET] = eKeys_LeftBracket;
            keyboard->s_KeyCodex[GLFW_KEY_RIGHT_BRACKET] = eKeys_RightBracket;
            keyboard->s_KeyCodex[GLFW_KEY_GRAVE_ACCENT] = eKeys_Tilde;
            keyboard->s_KeyCodex[GLFW_KEY_MINUS] = eKeys_Minus;
            keyboard->s_KeyCodex[GLFW_KEY_EQUAL] = eKeys_Equal;

            // Arrow keys
            keyboard->s_KeyCodex[GLFW_KEY_UP] = eKeys_Up;
            keyboard->s_KeyCodex[GLFW_KEY_DOWN] = eKeys_Down;
            keyboard->s_KeyCodex[GLFW_KEY_LEFT] = eKeys_Left;
            keyboard->s_KeyCodex[GLFW_KEY_RIGHT] = eKeys_Right;

            // Function Keys
            keyboard->s_KeyCodex[GLFW_KEY_F1] = eKeys_F1;
            keyboard->s_KeyCodex[GLFW_KEY_F2] = eKeys_F2;
            keyboard->s_KeyCodex[GLFW_KEY_F3] = eKeys_F3;
            keyboard->s_KeyCodex[GLFW_KEY_F4] = eKeys_F4;
            keyboard->s_KeyCodex[GLFW_KEY_F5] = eKeys_F5;
            keyboard->s_KeyCodex[GLFW_KEY_F6] = eKeys_F6;
            keyboard->s_KeyCodex[GLFW_KEY_F7] = eKeys_F7;
            keyboard->s_KeyCodex[GLFW_KEY_F8] = eKeys_F8;
            keyboard->s_KeyCodex[GLFW_KEY_F9] = eKeys_F9;
            keyboard->s_KeyCodex[GLFW_KEY_F10] = eKeys_F10;

            keyboard->s_KeyCodex[GLFW_KEY_F11] = eKeys_F11;
            keyboard->s_KeyCodex[GLFW_KEY_F12] = eKeys_F12;
            keyboard->s_KeyCodex[GLFW_KEY_F13] = eKeys_F13;
            keyboard->s_KeyCodex[GLFW_KEY_F14] = eKeys_F14;
            keyboard->s_KeyCodex[GLFW_KEY_F15] = eKeys_F15;
            keyboard->s_KeyCodex[GLFW_KEY_F16] = eKeys_F16;
            keyboard->s_KeyCodex[GLFW_KEY_F17] = eKeys_F17;
            keyboard->s_KeyCodex[GLFW_KEY_F18] = eKeys_F18;
            keyboard->s_KeyCodex[GLFW_KEY_F19] = eKeys_F19;
            keyboard->s_KeyCodex[GLFW_KEY_F20] = eKeys_F20;

            keyboard->s_KeyCodex[GLFW_KEY_F21] = eKeys_F21;
            keyboard->s_KeyCodex[GLFW_KEY_F22] = eKeys_F22;
            keyboard->s_KeyCodex[GLFW_KEY_F23] = eKeys_F23;
            keyboard->s_KeyCodex[GLFW_KEY_F24] = eKeys_F24;
            keyboard->s_KeyCodex[GLFW_KEY_F25] = eKeys_F25;

            // System Keys
            // keyboard->s_KeyCodex[eKeys_System] = -1; // Set to Max
        }
        else if (deviceType > eInputDeviceTypes::Mouse_Min &&
                deviceType < eInputDeviceTypes::Mouse_Max)
        {
            // Mouse
            Mouse* mouse = (Mouse*)device;

            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_LEFT] = eKeys_LeftClick;
            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_RIGHT] = eKeys_RightClick;
            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_MIDDLE] = eKeys_MiddleClick;

            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_2] = eKeys_MouseButton2;
            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_3] = eKeys_MouseButton3;
            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_4] = eKeys_MouseButton4;
            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_5] = eKeys_MouseButton5;
            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_6] = eKeys_MouseButton6;
            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_7] = eKeys_MouseButton7;
            mouse->s_KeyCodex[GLFW_MOUSE_BUTTON_8] = eKeys_MouseButton8;
        }
        else if (deviceType > eInputDeviceTypes::GamePad_Min&&
            deviceType < eInputDeviceTypes::GamePad_Max)
        {
            // GamePad
            // GamePad* gamePad = (GamePad*)device;
            // TODO:
        }
    }

    void Input::SetupGLFWKeyCodex()
    {
        /* Generic */
        // Mouse
        m_KeyCodex[GLFW_MOUSE_BUTTON_LEFT] = eKeys_LeftClick;
        m_KeyCodex[GLFW_MOUSE_BUTTON_RIGHT] = eKeys_RightClick;
        m_KeyCodex[GLFW_MOUSE_BUTTON_MIDDLE] = eKeys_MiddleClick;

        m_KeyCodex[GLFW_MOUSE_BUTTON_2] = eKeys_MouseButton2;
        m_KeyCodex[GLFW_MOUSE_BUTTON_3] = eKeys_MouseButton3;
        m_KeyCodex[GLFW_MOUSE_BUTTON_4] = eKeys_MouseButton4;
        m_KeyCodex[GLFW_MOUSE_BUTTON_5] = eKeys_MouseButton5;
        m_KeyCodex[GLFW_MOUSE_BUTTON_6] = eKeys_MouseButton6;
        m_KeyCodex[GLFW_MOUSE_BUTTON_7] = eKeys_MouseButton7;
        m_KeyCodex[GLFW_MOUSE_BUTTON_8] = eKeys_MouseButton8;

        // Modifiers
        // Either
        // m_KeyCodex[?] = eKeys_CTRL; // TODO: Handle either left Or right
        // m_KeyCodex[?] = eKeys_SHIFT; // TODO: Handle either left Or right
        // m_KeyCodex[?] = eKeys_ALT; // TODO: Handle either left Or right
        // Left
        m_KeyCodex[GLFW_KEY_LEFT_CONTROL] = eKeys_LCTRL; // GLFWK_KEY_RIGHT_CONTROL
        m_KeyCodex[GLFW_KEY_LEFT_SHIFT] = eKeys_LSHIFT; // LGW_KEY_RIGHT_SHIFT
        m_KeyCodex[GLFW_KEY_LEFT_ALT] = eKeys_LALT; // GLFW_KEY_RIGHT_ALT
        // Right
        m_KeyCodex[GLFW_KEY_RIGHT_CONTROL] = eKeys_RCTRL; // GLFWK_KEY_RIGHT_CONTROL
        m_KeyCodex[GLFW_KEY_RIGHT_SHIFT] = eKeys_RSHIFT; // LGW_KEY_RIGHT_SHIFT
        m_KeyCodex[GLFW_KEY_RIGHT_ALT] = eKeys_RALT; // GLFW_KEY_RIGHT_ALT

        // Alternate Keys
        m_KeyCodex[GLFW_KEY_ENTER] = eKeys_Return;
        m_KeyCodex[GLFW_KEY_INSERT] = eKeys_Insert;
        m_KeyCodex[GLFW_KEY_DELETE] = eKeys_Delete;
        m_KeyCodex[GLFW_KEY_PAGE_UP] = eKeys_PageUp;
        m_KeyCodex[GLFW_KEY_PAGE_DOWN] = eKeys_PageDown;
        m_KeyCodex[GLFW_KEY_HOME] = eKeys_Home;
        m_KeyCodex[GLFW_KEY_END] = eKeys_End;
        m_KeyCodex[GLFW_KEY_TAB] = eKeys_Tab;
        m_KeyCodex[GLFW_KEY_ESCAPE] = eKeys_Escape;
        m_KeyCodex[GLFW_KEY_BACKSPACE] = eKeys_Backspace;
        m_KeyCodex[GLFW_KEY_PRINT_SCREEN] = eKeys_PrintScreen;
        m_KeyCodex[GLFW_KEY_PAUSE] = eKeys_Pause;
        m_KeyCodex[GLFW_KEY_MENU] = eKeys_Menu;
        // m_KeyCodex[?] = eKeys_FN; // TODO: Find fn key

        // Locks
        m_KeyCodex[GLFW_KEY_CAPS_LOCK] = eKeys_CapsLock,
            m_KeyCodex[GLFW_KEY_NUM_LOCK] = eKeys_NumLock;
        m_KeyCodex[GLFW_KEY_SCROLL_LOCK] = eKeys_ScrollLock;

        // Key Pad
        m_KeyCodex[GLFW_KEY_KP_DECIMAL] = eKeys_Pad_Decimal;
        m_KeyCodex[GLFW_KEY_ENTER] = eKeys_Pad_Return;
        m_KeyCodex[GLFW_KEY_KP_ADD] = eKeys_Pad_Plus;
        m_KeyCodex[GLFW_KEY_KP_SUBTRACT] = eKeys_Pad_Minus;
        m_KeyCodex[GLFW_KEY_KP_DIVIDE] = eKeys_Pad_Division;
        m_KeyCodex[GLFW_KEY_KP_MULTIPLY] = eKeys_Pad_Multiplication;

        m_KeyCodex[GLFW_KEY_KP_0] = eKeys_Pad_0;
        m_KeyCodex[GLFW_KEY_KP_1] = eKeys_Pad_1;
        m_KeyCodex[GLFW_KEY_KP_2] = eKeys_Pad_2;
        m_KeyCodex[GLFW_KEY_KP_3] = eKeys_Pad_3;
        m_KeyCodex[GLFW_KEY_KP_4] = eKeys_Pad_4;
        m_KeyCodex[GLFW_KEY_KP_5] = eKeys_Pad_5;
        m_KeyCodex[GLFW_KEY_KP_6] = eKeys_Pad_6;
        m_KeyCodex[GLFW_KEY_KP_7] = eKeys_Pad_7;
        m_KeyCodex[GLFW_KEY_KP_8] = eKeys_Pad_8;
        m_KeyCodex[GLFW_KEY_KP_9] = eKeys_Pad_9;

        // Alphabet
        m_KeyCodex[GLFW_KEY_A] = eKeys_A;
        m_KeyCodex[GLFW_KEY_B] = eKeys_B;
        m_KeyCodex[GLFW_KEY_C] = eKeys_C;
        m_KeyCodex[GLFW_KEY_D] = eKeys_D;
        m_KeyCodex[GLFW_KEY_E] = eKeys_E;
        m_KeyCodex[GLFW_KEY_F] = eKeys_F;
        m_KeyCodex[GLFW_KEY_G] = eKeys_G;
        m_KeyCodex[GLFW_KEY_H] = eKeys_H;
        m_KeyCodex[GLFW_KEY_I] = eKeys_I;
        m_KeyCodex[GLFW_KEY_J] = eKeys_J;
        m_KeyCodex[GLFW_KEY_K] = eKeys_K;
        m_KeyCodex[GLFW_KEY_L] = eKeys_L;
        m_KeyCodex[GLFW_KEY_M] = eKeys_M;
        m_KeyCodex[GLFW_KEY_N] = eKeys_N;
        m_KeyCodex[GLFW_KEY_O] = eKeys_O;
        m_KeyCodex[GLFW_KEY_P] = eKeys_P;
        m_KeyCodex[GLFW_KEY_Q] = eKeys_Q;
        m_KeyCodex[GLFW_KEY_R] = eKeys_R;
        m_KeyCodex[GLFW_KEY_S] = eKeys_S;
        m_KeyCodex[GLFW_KEY_T] = eKeys_T;
        m_KeyCodex[GLFW_KEY_U] = eKeys_U;
        m_KeyCodex[GLFW_KEY_V] = eKeys_V;
        m_KeyCodex[GLFW_KEY_W] = eKeys_W;
        m_KeyCodex[GLFW_KEY_X] = eKeys_X;
        m_KeyCodex[GLFW_KEY_Y] = eKeys_Y;
        m_KeyCodex[GLFW_KEY_Z] = eKeys_Z;

        // Numbers
        m_KeyCodex[GLFW_KEY_0] = eKeys_0;
        m_KeyCodex[GLFW_KEY_1] = eKeys_1;
        m_KeyCodex[GLFW_KEY_2] = eKeys_2;
        m_KeyCodex[GLFW_KEY_3] = eKeys_3;
        m_KeyCodex[GLFW_KEY_4] = eKeys_4;
        m_KeyCodex[GLFW_KEY_5] = eKeys_5;
        m_KeyCodex[GLFW_KEY_6] = eKeys_6;
        m_KeyCodex[GLFW_KEY_7] = eKeys_7;
        m_KeyCodex[GLFW_KEY_8] = eKeys_8;
        m_KeyCodex[GLFW_KEY_9] = eKeys_9;

        // Punctuation
        m_KeyCodex[GLFW_KEY_SPACE] = eKeys_Space;
        m_KeyCodex[GLFW_KEY_APOSTROPHE] = eKeys_Apostrophe;
        m_KeyCodex[GLFW_KEY_COMMA] = eKeys_Comma;
        m_KeyCodex[GLFW_KEY_PERIOD] = eKeys_Period;
        m_KeyCodex[GLFW_KEY_SLASH] = eKeys_ForwardSlash;
        m_KeyCodex[GLFW_KEY_BACKSLASH] = eKeys_BackSlash;
        m_KeyCodex[GLFW_KEY_SEMICOLON] = eKeys_SemiColon;
        m_KeyCodex[GLFW_KEY_LEFT_BRACKET] = eKeys_LeftBracket;
        m_KeyCodex[GLFW_KEY_RIGHT_BRACKET] = eKeys_RightBracket;
        m_KeyCodex[GLFW_KEY_GRAVE_ACCENT] = eKeys_Tilde;
        m_KeyCodex[GLFW_KEY_MINUS] = eKeys_Minus;
        m_KeyCodex[GLFW_KEY_EQUAL] = eKeys_Equal;

        // Arrow keys
        m_KeyCodex[GLFW_KEY_UP] = eKeys_Up;
        m_KeyCodex[GLFW_KEY_DOWN] = eKeys_Down;
        m_KeyCodex[GLFW_KEY_LEFT] = eKeys_Left;
        m_KeyCodex[GLFW_KEY_RIGHT] = eKeys_Right;

        // Function Keys
        m_KeyCodex[GLFW_KEY_F1] = eKeys_F1;
        m_KeyCodex[GLFW_KEY_F2] = eKeys_F2;
        m_KeyCodex[GLFW_KEY_F3] = eKeys_F3;
        m_KeyCodex[GLFW_KEY_F4] = eKeys_F4;
        m_KeyCodex[GLFW_KEY_F5] = eKeys_F5;
        m_KeyCodex[GLFW_KEY_F6] = eKeys_F6;
        m_KeyCodex[GLFW_KEY_F7] = eKeys_F7;
        m_KeyCodex[GLFW_KEY_F8] = eKeys_F8;
        m_KeyCodex[GLFW_KEY_F9] = eKeys_F9;
        m_KeyCodex[GLFW_KEY_F10] = eKeys_F10;

        m_KeyCodex[GLFW_KEY_F11] = eKeys_F11;
        m_KeyCodex[GLFW_KEY_F12] = eKeys_F12;
        m_KeyCodex[GLFW_KEY_F13] = eKeys_F13;
        m_KeyCodex[GLFW_KEY_F14] = eKeys_F14;
        m_KeyCodex[GLFW_KEY_F15] = eKeys_F15;
        m_KeyCodex[GLFW_KEY_F16] = eKeys_F16;
        m_KeyCodex[GLFW_KEY_F17] = eKeys_F17;
        m_KeyCodex[GLFW_KEY_F18] = eKeys_F18;
        m_KeyCodex[GLFW_KEY_F19] = eKeys_F19;
        m_KeyCodex[GLFW_KEY_F20] = eKeys_F20;

        m_KeyCodex[GLFW_KEY_F21] = eKeys_F21;
        m_KeyCodex[GLFW_KEY_F22] = eKeys_F22;
        m_KeyCodex[GLFW_KEY_F23] = eKeys_F23;
        m_KeyCodex[GLFW_KEY_F24] = eKeys_F24;
        m_KeyCodex[GLFW_KEY_F25] = eKeys_F25;

        // System Keys
        // m_KeyCodex[eKeys_System] = -1; // Set to Max
    }

}
