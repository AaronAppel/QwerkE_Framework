#include "QwerkE_Defines.h"
#include "QwerkE_Platform.h"

// TODO: Hide loading behind load/splash screen?

//////////////////////////////
// Setup any libraries that have program wide states
// that need to be initialized before used
//////////////////////////////

#include "Libraries_Include.h"
#include "../QwerkE_Common/Utilities/PrintFunctions.h"

// TODO: Use _QFailure and other error messages?
bool Libs_Setup()
{
    ConfigData config = ConfigHelper::GetConfigData(); // TODO: Add #include
    bool errorFree = true; // Return value. If error occurs set to false

	ConsolePrint("Libs_Setup(): Initializing libraries...\n");
    // Setup/Load libraries based on platform, architecture, configuration
    // TODO: Clean up #ifs
#ifdef _Q32Bit // architecture
// platform
#ifdef _QWindows
// TODO: setup libraries

#elif _Android
#elif _Mac
#elif _Linux
#else
#pragma warning "Define Platform!"
#endif

#elif _Q64Bit // architecture
// platform
#ifdef _QWindows
#elif _Android
#elif _Mac
#elif _Linux
#else
#pragma warning "Define Platform!"
#endif

#endif // !platform

//////////////////////////////
// FILES //
//////////////////////////////
// font loading/rendering
// freetype2
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        ConsolePrint("\nError loading freetype2!\n");
        errorFree = false;
    }
	else
	{
		ConsolePrint("Freetype Loaded,\n");
		FT_Done_FreeType(ft);
	}
    //////////////////////////////

    //////////////////////////////
    // Graphics //
    //////////////////////////////
    // window creation //
    // GLFW
    if (!glfwInit())
    {
        ConsolePrint("\nError loading GLFW step 1!\n");
        errorFree = false;
    }
    else
    {
		ConsolePrint("GLFW Loaded,\n");

        // TODO: Setup proper window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //using OpenGL 4.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 8);

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 8);
        glfwWindowHint(GLFW_DEPTH_BITS, 0);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);

        GLFWwindow* window;
        window = glfwCreateWindow(100, 100, "Test", NULL, NULL);
        if (!window)
        {
            ConsolePrint("\nError loading GLFW step 2!\n");
            errorFree = false;

            /*int code = glfwGetError(NULL);

            switch (code)
            {
            case GLFW_NOT_INITIALIZED:
                ConsolePrint("\nGLFW error GLFW_NOT_INITIALIZED!\n");
                break;
            case GLFW_NO_CURRENT_CONTEXT:
                ConsolePrint("\nGLFW error GLFW_NO_CURRENT_CONTEXT!\n");
                break;
            case GLFW_INVALID_ENUM:
                ConsolePrint("\nGLFW error GLFW_INVALID_ENUM!\n");
                break;
            case GLFW_INVALID_VALUE:
                ConsolePrint("\nGLFW error GLFW_INVALID_VALUE!\n");
                break;
            case GLFW_OUT_OF_MEMORY:
                ConsolePrint("\nGLFW error GLFW_OUT_OF_MEMORY!\n");
                break;
            case GLFW_API_UNAVAILABLE:
                ConsolePrint("\nGLFW error GLFW_API_UNAVAILABLE!\n");
                break;
            case GLFW_VERSION_UNAVAILABLE:
                ConsolePrint("\nGLFW error GLFW_VERSION_UNAVAILABLE!\n");
                break;
            case GLFW_PLATFORM_ERROR:
                ConsolePrint("\nGLFW error GLFW_PLATFORM_ERROR!\n");
                break;
            case GLFW_FORMAT_UNAVAILABLE:
                ConsolePrint("\nGLFW error GLFW_FORMAT_UNAVAILABLE!\n");
                break;
            case GLFW_NO_WINDOW_CONTEXT:
                ConsolePrint("\nGLFW error GLFW_NO_WINDOW_CONTEXT!\n");
                break;
            case GLFW_NO_ERROR:
                ConsolePrint("\nNo error was detected, but GLFW was not able to create a window object!\n");
                break;
            }*/
        }
        else
        {
            // openGL extensions wrangler //
            // GLEW
            glfwMakeContextCurrent(window);
            if (glewInit() != GLEW_OK)
            {
                ConsolePrint("\nError loading GLEW!\n");
                errorFree = false;
            }
			else
				ConsolePrint("GLEW Loaded,\n");

            glfwDestroyWindow(window); // Clean up
        }
    }
    //////////////////////////////

    //////////////////////////////
    // GUIs //
    //////////////////////////////
    // immediate mode //
    // imgui
    ImGuiContext* context = nullptr;
    context = ImGui::CreateContext();
    if (context == nullptr)
    {
        ConsolePrint("\nError loading imgui!\n");
        errorFree = false;
    }
    else
    {
		ConsolePrint("imgui Loaded,\n");
        ImGuiIO& io = ImGui::GetIO();
		(void)io;
		//ImGui::CaptureMouseFromApp(true);
		//ImGui::CaptureKeyboardFromApp(true);
    }
    //////////////////////////////

    //////////////////////////////
    // threading //
    //////////////////////////////
    // pthreads
    // Load anything?
    //////////////////////////////

    //////////////////////////////
    // networking
    //////////////////////////////
    // RakNet
    // Load anything?
    //////////////////////////////

    //////////////////////////////
    // Audio
    //////////////////////////////
    // OpenAL
	// TODO: Test startup and shutdown of system
	// TODO: Init alut?
	// ConsolePrint("\nError loading OpenAL!\n");

    //////////////////////////////

    if (errorFree)
        ConsolePrint("Libs_Setup(): Libraries Initialized successfully\n\n");
    else
        ConsolePrint("Libs_Setup(): Error loading libraries\n\n");

    return errorFree;
}

void Libs_TearDown()
{
    ImGui_ImplGlfwGL3_Shutdown(); // shutdown imgui
    ImGui::DestroyContext(); // destroy imgui
    glfwTerminate(); // shutdown glfw
	// TODO: OpenAL, Bullet, freetype2, GLEW?, RakNet
}
