#include "CallbackFunctions.h"
#include "../ServiceLocator.h"
#include "../ResourceManager/ResourceManager.h"
#include "../FileSystem/FileSystem.h"
#include "../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../Graphics/Texture.h"

#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../QwerkE_Common/Libraries/glfw/GLFW/glfw3.h"

// TODO: No Globals!
extern int g_WindowWidth, g_WindowHeight;
InputManager* l_InputManager;

void SetupCallbacks(GLFWwindow* window)
{
	l_InputManager = (InputManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Input_Manager);
	// input
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCharCallback(window, char_callback);
	glfwSetCharModsCallback(window, char_mods_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// TODO: glfwSetJoystickCallback()

	// window
	glfwSetWindowPosCallback(window, window_position_callback);
	glfwSetWindowSizeCallback(window, window_resize_callback);
	glfwSetWindowCloseCallback(window, window_close_callback);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	// error
	glfwSetErrorCallback(error_callback);

	// other
	glfwSetDropCallback(window, file_drop_callback);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		// TODO: Just pass int and interperate key inside InputManager
		l_InputManager->ProcessKeyEvent(l_InputManager->GetKeyCode(key),
			eKeyState::eKeyState_Press);
	}
	else if (action == GLFW_RELEASE)
	{
		l_InputManager->ProcessKeyEvent(l_InputManager->GetKeyCode(key),
			eKeyState::eKeyState_Release);
	}
	// imgui
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
}
void char_callback(GLFWwindow* window, unsigned int codePoint)
{
	// TODO: Tell InputManager that a key state changed
	// l_InputManager->ProcessKeyEvent(l_InputManager->GetKeyCode(key), eKeyState::eKeyState_Down);
	int bp = 1;

	// imgui
	ImGuiIO& io = ImGui::GetIO();
	if (codePoint > 0 && codePoint < 0x10000)
		io.AddInputCharacter((unsigned short)codePoint);
}
void char_mods_callback(GLFWwindow* window, unsigned int codepoint, int mods)
{
	// TODO: Tell InputManager that a key state changed
	// l_InputManager->ProcessKeyEvent(l_InputManager->GetKeyCode(key), eKeyState::eKeyState_Down);
	// spacebar
	// ~ to =
	int bp = 1;
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	l_InputManager->ProcessMouseMove(xpos, -ypos);

	ypos = (double)g_WindowHeight - ypos; // invert y
}
void cursor_enter_callback(GLFWwindow* window, int entered)
{
	// TODO: Tell InputManager that the mouse moved
	// l_InputManager->ProcessMouse();
	if (entered == GLFW_TRUE)
	{
		// mouse entered window rectangle
	}
	else
	{
		// mouse left window rectangle
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		l_InputManager->ProcessMouseClick(l_InputManager->GetKeyCode(button), eKeyState::eKeyState_Press);
	}
	else if (action == GLFW_RELEASE)
	{
		l_InputManager->ProcessMouseClick(l_InputManager->GetKeyCode(button), eKeyState::eKeyState_Release);
	}

	// imgui
	// io.MouseDown[i] = ;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// TODO: Tell InputManager that the mouse moved
	// l_InputManager->ProcessMouse();

	// imgui
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += (float)xoffset;
	io.MouseWheel += (float)yoffset;
	// ImGui::SetScrollY(yoffset);
}
void joystick_callback(int joy, int event)
{
	// TODO: Tell InputManager that a joystick changed
	// l_InputManager->ProcessGamePad/Joystick();
	// joystick button pressed
	int bp = 1;
}
// window callbacks
void window_position_callback(GLFWwindow* window, int x, int y)
{
	// window moved
	int bp = 1;
}
void window_resize_callback(GLFWwindow* window, int width, int height)
{
	// window resized
	int bp = 1;
}
void window_close_callback(GLFWwindow* window)
{
	// window closed
	int bp = 1;
}
void window_refresh_callback(GLFWwindow* window)
{
	// window refreshed
	int bp = 1;
}
void window_focus_callback(GLFWwindow* window, int isFocused)
{
	if (isFocused == GLFW_TRUE)
	{
		// debug_GetGameCore()->GetSceneManager()->GetCurrentScene()->SetIsPaused(false); // regained focus
	}
	else
	{
		// debug_GetGameCore()->GetSceneManager()->GetCurrentScene()->SetIsPaused(true); // lost focus
	}
}
void window_iconify_callback(GLFWwindow* window, int isIconified)
{
	if (isIconified == GLFW_TRUE)
	{
		// iconified
		int bp = 1;
	}
	else
	{
		int bp = 1;
	}
}
void framebuffer_resize_callback(GLFWwindow* window, int x, int y)
{
	// framebuffer resized
}
void error_callback(int error, const char* description)
{
	// fprintf(stderr, "Error %d: %s\n", error, description);
}
// file
void file_drop_callback(GLFWwindow* window, int count, const char** paths)
{
	// path of file drag and dropped onto this window
	// TODO: Handle file drop correctly. This is hacked in for testing purposes at the moment.
	for (int i = 0; i < count; i++)
	{
		FileSystem* fileSystem = (FileSystem*)QwerkE::ServiceLocator::GetService(eEngineServices::FileSystem);
		if (strcmp(GetFileExtension(*paths).c_str(), "png") == 0 || strcmp(GetFileExtension(*paths).c_str(), "jpg") == 0)
		{
			GLuint result = Load2DTexture(*paths, 0);
			if (result != 0)
			{
				Texture* texture = new Texture();
				texture->s_Handle = result;
				texture->s_Name = GetFileNameWithExt(*paths);
				((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->AddTexture(
					GetFileNameNoExt(*paths).c_str(), texture);
			}
		}
		else if (strcmp(GetFileExtension(*paths).c_str(), "fbx") == 0 || strcmp(GetFileExtension(*paths).c_str(), "obj") == 0)
		{
			fileSystem->LoadModelFileToMeshes(*paths);
		}
		else if (strcmp(GetFileExtension(*paths).c_str(), "msch") == 0)
		{
			// TODO:
		}
		else if (strcmp(GetFileExtension(*paths).c_str(), "ssch") == 0)
		{
			// TODO:
		}
		else if (strcmp(GetFileExtension(*paths).c_str(), "osch") == 0)
		{
			// TODO:
		}
	}
}