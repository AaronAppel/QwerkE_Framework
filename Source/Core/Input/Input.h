#ifndef _Input_H_
#define _Input_H_

// Reference: https://www.gamedev.net/blogs/entry/2250186-designing-a-robust-input-handling-system-for-games/

#include "../../Headers/QwerkE_Enums.h"
#include "QwerKE_eKeys.h"
#include "../../Headers/QwerkE_Defines.h"
#include "../../Headers/QwerkE_Platform.h"
#include "../../Headers/Libraries_Include.h"
#include "../Math/Vector.h"

#ifdef GLFW3
#include "../../Libraries/glew/GL/glew.h" // TODO: Need?
#include "../../Libraries/glfw/GLFW/glfw3.h"
#endif // GLFW3

#include <map>

namespace QwerkE {

    class KeyboardExtAPI;

    static int g_NumPlayers = 1;
    const char QWERKE_ONE_FRAME_MAX_INPUT = 12; // No more than QWERKE_ONE_FRAME_MAX_INPUT key events per frame. Is that enough?

    // TODO: Provide cross platform callback API for convenience
    // TODO: Add input functions for non-GLFW projects
    // TODO: Add input query functions such as WNDPROC for getting input and CheckInput() game loop function.
    // TODO: Think of abstracting class for different libraries and platforms
    // TODO: Key event callback registration. Should that be handled by the event system? probably...
    // TODO: Support more than 1 keyboard or multiple mice... for fun.
    // TODO: Fix GLFW callbacks to avoid "static" everywhere

    struct InputDevice;

    class Input
    {
    public:

#ifdef GLFW3
        static void Initialize(GLFWwindow* window);
#else
        static void Initialize();
#endif // GLFW3

        static void NewFrame(); // Call before other libraries! Resets frame input buffer

        static vec2 GetMouseDragDelta(); // get distance from mouse down
        static bool GetIsKeyDown(eKeys key); // check if keyIsDown

        static const KeyboardExtAPI* GetDeviceAPI() { return m_KeyboardAPI; }

        static bool FrameKeyAction(eKeys key, eKeyState state); // check if key was pressed or released this frame

    private:
        Input() {}
        ~Input() {}

#ifdef GLFW3
        static void SetupCallbacks(GLFWwindow* window);

        // TODO: Clean up assign keys methods
        static void AssignGLFWKeys(InputDevice* device);
        static void SetupGLFWKeyCodex(); // TODO: Remove
        static eKeys GLFWToQwerkEKey(int key);
        static void Initialize();
#else
        // TODO:
        // void AssignWin32Keys() {}
        // void AssignMacKeys() {}
        // void AssignLinuxKeys() {}
#endif // GLFW3

        // Handle input
        // TODO: ProcessMouseScroll
        static void ProcessMouseMove(vec2 position);
        static void ProcessMouseMove(float x, float y);
        static void ProcessMouseClick(eKeys key, eKeyState state);
        static void ProcessKeyEvent(eKeys key, eKeyState state);

        // Input devices
        static std::map<eInputDeviceTypes, InputDevice*> m_Devices;
        static void SetupDeviceCustomKeys() {}
        static bool AddDevice(InputDevice* device);

        static eInputDeviceTypes m_DefaultMouse;
        static eInputDeviceTypes m_DefaultKeyboard;
        static KeyboardExtAPI* m_KeyboardAPI; // TEST:

        // Setup system key maps (rename platform?)
        static void AssignSystemKeys(InputDevice* device); // TODO: Change to a max keys buffer that only needs to track 10ish keys at a time

        // TODO: Fix GLFW callbacks to avoid static functions
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void char_callback(GLFWwindow* window, unsigned int codePoint);
        static void char_mods_callback(GLFWwindow* window, unsigned int codepoint, int mods);
        static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        static void cursor_enter_callback(GLFWwindow* window, int entered);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        static void joystick_callback(int joy, int event);

        // Input events
        static void RaiseInputEvent(eKeys key, eKeyState state);

        static bool m_KeyEventsAreDirty;
        static unsigned short m_InputEventKeys[];
        static bool m_InputEventValues[];

        // TEMP: Conversion function for GLFW to QwerkE
        static unsigned short* m_KeyCodex;
    };
}
#endif // !_Input_H_
