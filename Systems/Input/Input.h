#ifndef _Input_H_
#define _Input_H_

// Reference: https://www.gamedev.net/blogs/entry/2250186-designing-a-robust-input-handling-system-for-games/

#include "../../Headers/QwerkE_Enums.h"
#include "QwerKE_eKeys.h"
#include "../../Headers/QwerkE_Defines.h"
#include "../../Headers/QwerkE_Platform.h"
#include "../../Headers/Libraries_Include.h"
#include "../../QwerkE_Common/DataTypes/Vector.h"

#ifdef GLFW3
#include "../../QwerkE_Common/Libraries/glew/GL/glew.h" // TODO: Need?
#include "../../QwerkE_Common/Libraries/glfw/GLFW/glfw3.h"
#endif // GLFW3

// #include <string>
// #include <map>

namespace QwerkE {

    class KeyboardExtAPI;

    static int g_NumPlayers = 1;
    const char QWERKE_ONE_FRAME_MAX_INPUT = 12; // no more than QWERKE_ONE_FRAME_MAX_INPUT key events per frame. Is that enough?

    // TODO: Provide cross platform callback API for convenience
    // TODO: Add input functions for non-GLFW projects
    // TODO: Add input query functions such as WNDPROC for getting input and CheckInput() game loop function.
    // TODO: Think of abstracting class for different libraries and platforms
    // TODO: Key event callback registration. Should that be handled by the event system? probably...
    // TODO: Support more than 1 keyboard or multiple mice... for fun.
    // TODO: Fix GLFW callbacks to avoid "static" everywhere

    class InputDevice;

    class Input
    {
    public:
        Input();
        ~Input();

#ifdef GLFW3
        Input(GLFWwindow* window);
        void Initialize(GLFWwindow* window);
#else
        void Initialize();
#endif // GLFW3

        void NewFrame(); // Call before other libraries! Resets frame input buffer

        vec2 GetMouseDragDelta() const; // get distance from mouse down
        bool GetIsKeyDown(eKeys key) const; // check if keyIsDown

        const KeyboardExtAPI* GetDeviceAPI() const { return m_KeyboardAPI; }

        bool FrameKeyAction(eKeys key, eKeyState state) const; // check if key was pressed or released this frame

    private:

#ifdef GLFW3
        void SetupCallbacks(GLFWwindow* window);

        // TODO: Clean up assign keys methods
        void AssignGLFWKeys(InputDevice* device);
        void SetupGLFWKeyCodex(); // TODO: Remove
        eKeys GLFWToQwerkEKey(int key) const;
        void Initialize();
#else
        // TODO:
        // void AssignWin32Keys() {}
        // void AssignMacKeys() {}
        // void AssignLinuxKeys() {}
#endif // GLFW3

        // Handle input
        // TODO: ProcessMouseScroll
        void ProcessMouseMove(vec2 position);
        void ProcessMouseMove(float x, float y);
        void ProcessMouseClick(eKeys key, eKeyState state);
        void ProcessKeyEvent(eKeys key, eKeyState state);

        // Input events
        bool m_KeyEventsAreDirty = true; // wipe at init
        unsigned short m_InputEventKeys[QWERKE_ONE_FRAME_MAX_INPUT];
        bool m_InputEventValues[QWERKE_ONE_FRAME_MAX_INPUT] = { false };
        void RaiseInputEvent(eKeys key, eKeyState state);

        // Input devices
        std::map<eInputDeviceTypes, InputDevice*> m_Devices;
        void SetupDeviceCustomKeys() {}
        bool AddDevice(InputDevice* device);

        eInputDeviceTypes m_DefaultMouse = eInputDeviceTypes::Mouse_Device0;
        eInputDeviceTypes m_DefaultKeyboard = eInputDeviceTypes::Keyboard_Device0;
        KeyboardExtAPI* m_KeyboardAPI = nullptr; // TEST:

        // Setup system key maps (rename platform?)
        void AssignSystemKeys(InputDevice* device); // TODO: Change to a max keys buffer that only needs to track 10ish keys at a time

        // TODO: Fix GLFW callbacks to avoid static functions
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void char_callback(GLFWwindow* window, unsigned int codePoint);
        static void char_mods_callback(GLFWwindow* window, unsigned int codepoint, int mods);
        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        static void cursor_enter_callback(GLFWwindow* window, int entered);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        static void joystick_callback(int joy, int event);

        // TEMP: Conversion function for GLFW to QwerkE
        unsigned short* m_KeyCodex;
    };
}
#endif // !_Input_H_
