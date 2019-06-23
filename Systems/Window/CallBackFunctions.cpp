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

void SetupCallbacks(GLFWwindow* window)
{
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
		// no longer iconified
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