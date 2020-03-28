#include "CallbackFunctions.h"
#include "../../Debug/Log/Log.h"
#include "../../FileSystem/FileIO/FileUtilities.h"
#include "../../FileSystem/FileSystem.h"
#include "../Resources/Resources.h"
#include "../Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../Graphics/DataTypes/Texture.h"

#include "../../Libraries/glew/GL/glew.h"
#include "../../Libraries/glfw/GLFW/glfw3.h"

namespace QwerkE {

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
            // debug_GetGameCore()->GetScenes()->GetCurrentScene()->SetIsPaused(false); // regained focus
        }
        else
        {
            // debug_GetGameCore()->GetScenes()->GetCurrentScene()->SetIsPaused(true); // lost focus
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
        // TODO: Framebuffer resized
    }

    void error_callback(int error, const char* description)
    {
        LOG_ERROR(description);
    }

    void file_drop_callback(GLFWwindow* window, int count, const char** paths)
    {
        // Path of file drag and dropped onto this window
        // TODO: Handle file drop correctly. This is hacked in for testing purposes at the moment.

        std::string dropFileExtensionStr = GetFileExtension(*paths).c_str(); // TODO: Avoid extra variable due to heap deallocation
        const char* dropFileExtension = dropFileExtensionStr.c_str();

        for (int i = 0; i < count; i++)
        {
            if (strcmp(dropFileExtension, "png") == 0 || strcmp(GetFileExtension(*paths).c_str(), "jpg") == 0)
            {
                // TODO: Ask Resources or another file to load the asset
                GLuint result = Load2DTexture(*paths, 0);
                if (result != 0)
                {
                    Texture* texture = new Texture();
                    texture->s_Handle = result;
                    texture->s_Name = GetFileNameWithExt(*paths);
                    Resources::AddTexture(GetFileNameNoExt(*paths).c_str(), texture);
                }
            }
            else if (strcmp(dropFileExtension, "fbx") == 0 || strcmp(GetFileExtension(*paths).c_str(), "obj") == 0)
            {
                FileSystem::LoadModelFileToMeshes(*paths);
            }
            else if (strcmp(dropFileExtension, "msch") == 0)
            {
                // TODO:
            }
            else if (strcmp(dropFileExtension, "ssch") == 0)
            {
                // TODO:
            }
            else if (strcmp(dropFileExtension, "osch") == 0)
            {
                // TODO:
            }
            else
            {
                LOG_WARN("Drag file type unsupported: {0}", dropFileExtension);
            }
        }
    }

}
