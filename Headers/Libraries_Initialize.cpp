#include "QwerkE_Defines.h"
#include "QwerkE_Platform.h"

// TODO: Hide loading behind load/splash screen?

//////////////////////////////
// Setup any libraries that have program wide states
// that need to be initialized before used
//////////////////////////////

#include "Libraries_Include.h"
#include "../QwerkE_Common/Libraries/imgui/imgui_impl_glfw.h"

namespace QwerkE {

    // TODO: Use _QFailure and other error messages?
    bool Libs_Setup()
    {
        ConfigData config = ConfigHelper::GetConfigData(); // TODO: Add #include
        bool errorFree = true; // Return value. If error occurs set to false

        Log::Safe("Libs_Setup(): Initializing libraries...\n");

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
// spdlog
        Log::Initialize();

// font loading/rendering
// freetype2
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            Log::Safe("Error loading freetype2!");
            errorFree = false;
        }
        else
        {
            Log::Safe("Freetype Loaded,\n");
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
            Log::Safe("\nError loading GLFW step 1!\n");
            errorFree = false;
        }
        else
        {
            Log::Safe("GLFW Loaded,\n");

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
                Log::Safe("\nError loading GLFW step 2!\n");
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
                    Log::Safe("\nError loading GLEW!\n");
                    errorFree = false;
                }
                else
                    Log::Safe("GLEW Loaded,\n");

                glfwDestroyWindow(window); // Clean up
            }
        }
        //////////////////////////////

        //////////////////////////////
        // GUIs //
        //////////////////////////////
        // immediate mode //
        // imgui
        ImGuiContext* context = ImGui::CreateContext();
        if (context == nullptr)
        {
            Log::Safe("\nError loading imgui!\n");
            errorFree = false;
        }
        else
        {
            ImGui::SetCurrentContext(context);

            Log::Safe("imgui Loaded,\n");
            ImGuiIO& io = ImGui::GetIO();

            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

            //ImGui::CaptureMouseFromApp(true);
            //ImGui::CaptureKeyboardFromApp(true);

            ImGui::StyleColorsDark();

            ImGuiStyle& style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            ImGui_ImplOpenGL3_Init("#version 410");
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
            Log::Safe("Libs_Setup(): Libraries Initialized successfully\n\n");
        else
            Log::Safe("Libs_Setup(): Error loading libraries\n\n");

        return errorFree;
    }

    void Libs_TearDown()
    {
        ImGui_ImplGlfw_Shutdown(); // shutdown imgui
        ImGui::DestroyContext(); // destroy imgui
        // TODO: OpenAL, Bullet, freetype2, GLEW?, RakNet

        // Last to keep error logging functionality
        glfwTerminate();
        Log::Shutdown();
    }

}
