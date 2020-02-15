#include "Input.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "MouseExtApi.h"
#include "KeyboardExtApi.h"
#include "../../Headers/QwerkE_Enums.h"

namespace QwerkE {

    std::map<eInputDeviceTypes, InputDevice*> Input::m_Devices;

    eInputDeviceTypes Input::m_DefaultMouse = eInputDeviceTypes::Mouse_Device0;
    eInputDeviceTypes Input::m_DefaultKeyboard = eInputDeviceTypes::Keyboard_Device0;
    KeyboardExtAPI* Input::m_KeyboardAPI = nullptr; // TEST:

    bool Input::m_KeyEventsAreDirty = true; // TODO: Wipe at init?
    unsigned short Input::m_InputEventKeys[QWERKE_ONE_FRAME_MAX_INPUT];
    bool Input::m_InputEventValues[QWERKE_ONE_FRAME_MAX_INPUT] = { false };

    // TEMP: Conversion function for GLFW to QwerkE
    unsigned short* Input::m_KeyCodex = nullptr;

#ifdef GLFW3
    void Input::Initialize(GLFWwindow* window)
    {
        Initialize();
        SetupGLFWKeyCodex(); // TODO: Change
        SetupCallbacks(window);
    }
#endif // GLFW3

    void Input::Initialize()
    {
        // Create input devices
        Keyboard* keyboard = new Keyboard(eInputDeviceTypes::Keyboard_Device0);
        Mouse* mouse = new Mouse(eInputDeviceTypes::Mouse_Device0);
        AddDevice(keyboard);
        AddDevice(mouse);

        AssignSystemKeys(keyboard);
        AssignSystemKeys(mouse);

        m_KeyCodex = new unsigned short[GLFW_KEY_LAST];
        memset(m_KeyCodex, 0, GLFW_KEY_LAST); // set values to 0

        NewFrame(); // Init buffers
        m_KeyboardAPI = new KeyboardExtAPI(keyboard);
    }

    void Input::NewFrame()
    {
        // reset state of each input device
        // TODO: Loop through array to reset all devices
        Mouse* mouse = (Mouse*)m_Devices.find(m_DefaultMouse)->second;
        mouse->NewFrame();

        Keyboard* keyboard = (Keyboard*)m_Devices.find(m_DefaultKeyboard)->second;
        keyboard->NewFrame();

        if (m_KeyEventsAreDirty)
        {
            memset(m_InputEventKeys, eKeys_NULL_KEY, QWERKE_ONE_FRAME_MAX_INPUT * sizeof(short));
            memset(m_InputEventValues, eKeyState::eKeyState_Release, QWERKE_ONE_FRAME_MAX_INPUT * sizeof(bool));
            m_KeyEventsAreDirty = false;
        }
    }

    void Input::ProcessMouseMove(vec2 position)
    {
        Mouse* mouse = (Mouse*)m_Devices.find(m_DefaultMouse)->second;
        mouse->s_MouseDelta = mouse->s_MousePos - position;
        mouse->s_MousePos = position;
    }

    void Input::ProcessMouseMove(float x, float y)
    {
        Mouse* mouse = (Mouse*)m_Devices.find(m_DefaultMouse)->second;
        mouse->s_MouseDelta = mouse->s_MousePos - vec2(x, y);
        mouse->s_MousePos = vec2(x, y);
    }

    void Input::ProcessMouseClick(eKeys key, eKeyState state) // handle mouse clicks
    {
        Mouse* mouse = (Mouse*)m_Devices.find(m_DefaultMouse)->second;
        // TODO:: Handle mouse drag for eKeys_RightClick and eKeys_MiddleClick
        if (key == eKeys_LeftClick && state == eKeyState::eKeyState_Press)
        {
            mouse->s_MouseDragStart = mouse->s_MousePos; // start drag
        }
        else if (key == eKeys_LeftClick && state == eKeyState::eKeyState_Release)
        {
            mouse->s_DragReset = true; // drag ended, reset value next frame so it can be used this frame
        }
        mouse->s_KeyStates[key] = state; // TODO: Is setting bool to key state an issue?

        RaiseInputEvent(key, state);
    }

    void Input::ProcessKeyEvent(eKeys key, eKeyState state)
    {
        Keyboard* keyboard = (Keyboard*)m_Devices.find(m_DefaultKeyboard)->second;
        keyboard->s_OneFrameBuffersAreDirty = true;

        RaiseInputEvent(key, state);
        keyboard->RaiseInputEvent(key, state);
        // TODO: Convert key into eKeys range
        keyboard->s_KeyStates[key] = state;
    }

    vec2 Input::GetMouseDragDelta()
    {
        Mouse* mouse = (Mouse*)m_Devices.find(m_DefaultMouse)->second;
        if (mouse->s_KeyStates[eKeys::eKeys_LeftClick])
        {
            return mouse->s_MousePos - mouse->s_MouseDragStart;
        }
        return vec2(0.0f, 0.0f);
    }

    bool Input::GetIsKeyDown(eKeys key)
    {
        return m_Devices.find(m_DefaultKeyboard)->second->s_KeyStates[key];
    }

    bool Input::FrameKeyAction(eKeys key, eKeyState state)
    {
        if (m_InputEventKeys[0] != eKeys::eKeys_NULL_KEY) // was a key even pressed?
            for (int i = 0; i < QWERKE_ONE_FRAME_MAX_INPUT; i++)
            {
                if (m_InputEventKeys[i] == key)
                    return m_InputEventValues[i] == (bool)state;
            }
        return 0;
    }

    // Private functions
    void Input::RaiseInputEvent(eKeys key, eKeyState state)
    {
        m_KeyEventsAreDirty = true;

        for (int i = 0; i < QWERKE_ONE_FRAME_MAX_INPUT; i++)
        {
            if (m_InputEventKeys[i] == eKeys_NULL_KEY)
            {
                m_InputEventKeys[i] = key;
                m_InputEventValues[i] = state;
                return;
            }
        }
    }

    bool Input::AddDevice(InputDevice* device)
    {
        if (device)
        {
            if (m_Devices.find(device->GetType()) == m_Devices.end())
            {
                // setup key data
                AssignSystemKeys(device);
                m_Devices[device->GetType()] = device;
                return true;
            }
        }
        return false;
    }

    void Input::AssignSystemKeys(InputDevice* device)
    {
#ifdef GLFW3
        //void AssignGLFWKeys(InputDevice * device);
        //void SetupGLFWKeyCodex(); // TODO: Remove
        //eKeys GLFWToQwerkEKey(int key) const
        //{
        //    return (eKeys)m_KeyCodex[key];
        //}
#endif

#ifdef GLFW3
        // TODO: Reduce the size of array
        device->s_KeyCodex = new unsigned short[GLFW_KEY_LAST]; // number of recognized glfw keys
        memset(device->s_KeyCodex, 0, GLFW_KEY_LAST); // set values to 0
        AssignGLFWKeys(device);

#elif _QWin32
        AssignWin32Keys();

#elif _QMac32 // 64
        AssignMacKeys();

#elif _QLinux32 // 64
        AssignLinuxKeys();

#else
        // Other Platforms or default layout
        // TODO: Map ascii default layout
        // https://www.asciitable.com/index/asciifull.gif
#pragma error "Input(): No platform defined! Cannot assign keys!"
#endif
    }

}
