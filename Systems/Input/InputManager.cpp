#include "InputManager.h"
#include "../../Headers/QwerkE_Enums.h"
#include "../../QwerkE_Common/Utilities/PrintFunctions.h"

InputManager::InputManager()
{
	// Create input devices
	Keyboard* keyboard = new InputManager::Keyboard(eInputDeviceTypes::Keyboard_Device0);
	Mouse* mouse = new InputManager::Mouse(eInputDeviceTypes::Mouse_Device0);
	AddDevice(keyboard);
	AddDevice(mouse);

	AssignSystemKeys(keyboard);
	AssignSystemKeys(mouse);

	m_KeyCodex = new unsigned short[GLFW_KEY_LAST];
	memset(m_KeyCodex, 0, GLFW_KEY_LAST); // set values to 0
	SetupGLFWKeyCodex(); // TODO: Change

	m_KeyboardAPI = new KeyboardExtAPI(keyboard);

	NewFrame(); // init buffers
}

InputManager::~InputManager()
{
	m_Devices; // TODO: Loop and delete
	m_KeyboardAPI;
}

void InputManager::NewFrame()
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

void InputManager::ProcessMouseMove(vec2 position)
{
	Mouse* mouse = (Mouse*)m_Devices.find(m_DefaultMouse)->second;
	mouse->s_MouseDelta = mouse->s_MousePos - position;
	mouse->s_MousePos = position;
}

void InputManager::ProcessMouseMove(float x, float y)
{
	Mouse* mouse = (Mouse*)m_Devices.find(m_DefaultMouse)->second;
	mouse->s_MouseDelta = mouse->s_MousePos - vec2(x, y);
	mouse->s_MousePos = vec2(x, y);
}

void InputManager::ProcessMouseClick(eKeys key, eKeyState state) // handle mouse clicks
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

void InputManager::ProcessKeyEvent(eKeys key, eKeyState state)
{
	Keyboard* keyboard = (Keyboard*)m_Devices.find(m_DefaultKeyboard)->second;
	keyboard->s_OneFrameBuffersAreDirty = true;

	RaiseInputEvent(key, state);
	keyboard->RaiseInputEvent(key, state);
	keyboard->s_KeyStates[key] = state;
}

vec2 InputManager::GetMouseDragDelta() const
{
	Mouse* mouse = (Mouse*)m_Devices.find(m_DefaultMouse)->second;
	if (mouse->s_KeyStates[eKeys::eKeys_LeftClick])
	{
		return mouse->s_MousePos - mouse->s_MouseDragStart;
	}
	return vec2(0.0f, 0.0f);
}

bool InputManager::GetIsKeyDown(eKeys key) const
{
	return m_Devices.find(m_DefaultKeyboard)->second->s_KeyStates[key];
}

bool InputManager::FrameKeyAction(eKeys key, eKeyState state) const
{
	if(m_InputEventKeys[0] != eKeys::eKeys_NULL_KEY) // was a key even pressed?
	for (int i = 0; i < QWERKE_ONE_FRAME_MAX_INPUT; i++)
	{
		if (m_InputEventKeys[i] == key)
			return m_InputEventValues[i] == state;
	}
	return 0;
}
// private functions
void InputManager::RaiseInputEvent(eKeys key, eKeyState state)
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
bool InputManager::AddDevice(InputDevice* device)
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
