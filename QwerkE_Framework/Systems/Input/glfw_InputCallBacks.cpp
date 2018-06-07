#include "InputManager.h"
#include "Keyboard.h"
#include "Mouse.h"

#ifdef dearimgui
#include "../../QwerkE_Common/Libraries/imgui/imgui.h"
#endif // dearimgui

#ifdef GLFW3
InputManager* l_InputManager = nullptr;

InputManager::InputManager(GLFWwindow* window)
{
	// Create input devices
	Keyboard* keyboard = new Keyboard(eInputDeviceTypes::Keyboard_Device0);
	Mouse* mouse = new Mouse(eInputDeviceTypes::Mouse_Device0);

	AddDevice(keyboard);
	AddDevice(mouse);

	AssignSystemKeys(keyboard);
	AssignSystemKeys(mouse);

	SetupControllers(); // TODO: Remove?

	m_KeyCodex = new unsigned short[GLFW_KEY_LAST];
	memset(m_KeyCodex, 0, GLFW_KEY_LAST); // set values to 0
	SetupGLFWKeyCodex(); // TODO: Remove

	SetupCallbacks(window);
	NewFrame(); // init buffers
}

void InputManager::SetupCallbacks(GLFWwindow* window)
{
	l_InputManager = this;
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCharCallback(window, char_callback);
	glfwSetCharModsCallback(window, char_mods_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetJoystickCallback(joystick_callback);
}
void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		l_InputManager->ProcessKeyEvent(l_InputManager->GLFWToQwerkEKey(key),
			eKeyState::eKeyState_Press);
	}
	else if (action == GLFW_RELEASE)
	{
		l_InputManager->ProcessKeyEvent(l_InputManager->GLFWToQwerkEKey(key),
			eKeyState::eKeyState_Release);
	}

#ifdef dearimgui
	ImGuiIO& io = ImGui::GetIO();
	if (action == GLFW_PRESS)
		io.KeysDown[key] = true;
	if (action == GLFW_RELEASE)
		io.KeysDown[key] = false;

	//(void)mods; // Modifiers are not reliable across systems
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif // dearimgui
}
void InputManager::char_callback(GLFWwindow* window, unsigned int codePoint)
{
	// l_InputManager->ProcessKeyEvent(l_InputManager->GLFWToQwerkEKey(key), eKeyState::eKeyState_Down);
	int bp = 1;

#ifdef dearimgui
	ImGuiIO& io = ImGui::GetIO();
	if (codePoint > 0 && codePoint < 0x10000)
		io.AddInputCharacter((unsigned short)codePoint);
#endif // dearimgui
}
void InputManager::char_mods_callback(GLFWwindow* window, unsigned int codepoint, int mods)
{
	// TODO:
}
void InputManager::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	l_InputManager->ProcessMouseMove(xpos, -ypos);

	ypos = (double)g_WindowHeight - ypos; // invert y
}
void InputManager::cursor_enter_callback(GLFWwindow* window, int entered)
{
	// ProcessMouse();
	if (entered == GLFW_TRUE)
	{
		// mouse entered window rectangle
	}
	else
	{
		// mouse left window rectangle
	}
}
void InputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		//ProcessMouseClick(GLFWToQwerkEKey(button), eKeyState::eKeyState_Press);
	}
	else if (action == GLFW_RELEASE)
	{
		//ProcessMouseClick(GLFWToQwerkEKey(button), eKeyState::eKeyState_Release);
	}

	// imgui
	// io.MouseDown[i] = ;
}
void InputManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// ProcessMouse();

#ifdef dearimgui
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += (float)xoffset;
	io.MouseWheel += (float)yoffset;
#endif // dearimgui
}
void InputManager::joystick_callback(int joy, int event)
{
	// ProcessGamePad/Joystick();
	// joystick button pressed
	// http://www.glfw.org/docs/latest/input_guide.html#joystick
	int bp = 1;
}
#endif // GLFW3