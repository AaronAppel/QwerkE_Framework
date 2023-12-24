#include "Framework.h"

#include "Source/Headers/QwerkE_Defines.h"

#ifdef GLFW3 // #TODO Move library dependent logic into appropriate class, like Window
#include "Libraries/glew/GL/glew.h"
#include "Libraries/glfw/GLFW/glfw3.h"
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw.h"
#include "Libraries/imgui/imgui_impl_opengl3.h"
#endif

#include "Headers/QwerkE_Enums.h"
#include "Headers/Libraries_Initialize.h"

#include "Core/Audio/Audio.h"
#include "Core/DataManager/ConfigHelper.h"
#include "Core/DataManager/DataManager.h"
#include "Core/Events/EventManager.h"
#include "Core/Factory/Factory.h"
#include "Core/Graphics/Mesh/MeshFactory.h"
#include "Core/Graphics/Graphics_Header.h"
#include "Core/Graphics/Renderer.h"
#include "Core/Graphics/ShaderFactory/ShaderFactory.h"
#include "Core/Input/Input.h"
#include "Core/Jobs/Jobs.h"
#include "Core/Network/Network.h"
#include "Core/Physics/Physics.h"
#include "Core/Resources/Resources.h"
#include "Core/Scenes/Scene.h"
#include "Core/Scenes/Scenes.h"
#include "Core/Time/Time.h"
#include "Core/Window/Window.h"
#include "Core/Window/Windows.h"
#include "Core/Window/glfw_Window.h"
#include "Core/Window/CallbackFunctions.h"
#include "Debug/Debugger/Debugger.h"
#include "Debug/Log/Log.h"
#include "FileSystem/FileSystem.h"
#include "Utilities/Helpers.h"

namespace QwerkE {

    extern const char* g_WindowTitle = "QwerkEngine";

    static Window* m_Window = nullptr;
    static bool m_IsRunning = false;

	namespace Framework
	{
		eEngineMessage Framework::Startup()
		{
			return Startup(ConfigsFolderPath("preferences.qpref"), 0); // Default flag settings
		}

		eEngineMessage Framework::Startup(std::string configFilePath, std::uint_fast8_t flags)
		{
            Log::Initialize();

			cJSON* root = OpencJSONStream(configFilePath.c_str()); // #TODO Remove engine behaviour
			cJSON* systems = nullptr;
			if (root)
			{
				systems = GetItemFromRootByKey(root, "Systems"); // #TODO Use flags to see if systems are enabled/disabled
			}

            ConfigHelper::LoadConfigData(configFilePath); // Init config data
            const ConfigData config = ConfigHelper::GetConfigData();

            // #TODO Load libraries dynamically. Need functions to load .dlls
			// #TODO Avoid loading unused libraries. React to system flags

			if (Libs_Setup() == false) // setup libraries
			{
				Log::Safe("\nStartup(): Error loading libraries!\n");
				return eEngineMessage::_QFailure; // failure
            }

            // #TODO Cleanup switch or if/else if statements below. Find a nice way to detect which library objects to load

			// #TODO Try to reduce or avoid order dependency in system creation

			// Load and register systems
			// Audio, Networking, Graphics (Renderer, GUI), Utilities (Conversion, FileIO, Printing),
            // Physics, Event, Debug, Memory, Window, Application, Input, Resources

			// ShaderFactory // #Dependency Resources

			// #TODO Could change to data and iterate over systems in a loop.
			//	Each system has a name string (JSON parent object name) and enabled boolean.
			//	If false, skip, true loads and on error/success print system name string.

			if (config.libraries.Window == "GLFW3") // #TODO Improve platform handling
			{
#ifdef GLFW3
				m_Window = new glfw_Window(Renderer::g_WindowWidth, Renderer::g_WindowHeight, g_WindowTitle);
#endif
			}
            else
            {
				LOG_ERROR("No window library detected! Check config libraries value.");
                assert(false);
            }

            Windows::AddWindow(m_Window);

            Input::Initialize((GLFWwindow*)Windows::GetWindow(0)->GetContext());

            cJSON* audioEnabled = GetItemFromArrayByKey(systems, "AudioEnabled");
            bool enabled = audioEnabled != nullptr ? (bool)audioEnabled->valuedouble : false; // #TODO Improve value handling

            if (config.systems.AudioEnabled && Audio::Initialize())
            {
                Log::Safe("Audio system initialized with OpenAL."); // #TODO Swap with LOG_TRACE()
            }
            else
            {
				Log::Safe("No audio system loaded."); // #TODO Swap with LOG_WARNING()
            }

            Resources::Initialize(); // #Dependency Audio, OpenGL, Window?

			Renderer::Initialize();
			Renderer::DrawFont("Loading...");
			m_Window->SwapBuffers();

			EventManager::Initialize();

			cJSON* JobManagerMultiThreadedEnabled = GetItemFromArrayByKey(systems, "JobManagerMultiThreadedEnabled");

			if (JobManagerMultiThreadedEnabled != nullptr && JobManagerMultiThreadedEnabled->valueint == 1) // #TODO Replace with if (config.systems.JobManagerEnabled)
			{
				// Jobs::MaxThreads(10); // #TODO Setup thread max value and place it in data somewhere
				Log::Safe("Jobs are using {0} threads"); // #TODO Swap with LOG_TRACE() and include number of threads in formatting
			}
			else
			{
				// Jobs::MaxThreads(1); // #TODO Setup thread max value and place it in data somewhere
				Log::Safe("Jobs are running single threaded."); // #TODO Swap with LOG_WARNING()
			}

			if (config.systems.NetworkingEnabled)
			{
				Network::Initialize();
				Log::Safe("Networking system initialized"); // #TODO Swap with LOG_TRACE()
			}
			else
			{
				Log::Safe("No network system loaded."); // #TODO Swap with LOG_WARNING()
			}

			// #TODO load scene later, like in Run() as it's more than just initializing
			Scenes::Initialize(); // #TODO Investigate other system dependencies as there are likely several

			// No dependencies //
			Physics::Initialize();

			return eEngineMessage::_QSuccess;
		}

		eEngineMessage Framework::TearDown()
        {
			// #TODO ShutdownSystems();
            EventManager::Shutdown();

			Libs_TearDown(); // unload libraries

			// #TODO Safety checks?
			return eEngineMessage::_QSuccess;
		}

		void Framework::Run()
        {
            assert(m_Window != nullptr); // Don't forget to call Framework::Startup() to initiailize the framework

			// #TODO check if(initialized) in case user defined simple API.
			// Might want to create another function for the game loop and
			// leave Run() smaller and abstracted from the functionality.
			m_IsRunning = true;

			/* Application Loop */
			int FPS_MAX = 120; // Maximum number of frames that can be made per second
			float FPS_MAX_DELTA = 1.0f / FPS_MAX;

			while (m_Window->IsClosing() == false)
			{
                /* Game Loop */
                Time::NewFrame();

				double deltaTime = Time::Delta();

				// if (deltaTime >= FPS_MAX_DELTA)
				{
					/* New Frame */
					Framework::NewFrame();

					/* Input */
					Framework::PollInput();

					/* Logic */
					Framework::Update(deltaTime);

					/* Render */
					Framework::Draw();

					// FPS
					//framesSincePrint++; // Framerate tracking
					//timeSinceLastFrame = 0.0; // FPS_Max
				}
				// #TODO Fix delta time issues
				// else
				// {
				// 	Yield();
				// }
			}
		}

		void Framework::Stop()
		{
			m_IsRunning = false;
			m_Window->SetClosing(true);
		}

		void Framework::NewFrame()
		{
			Input::NewFrame();
			EventManager::ProcessEvents();
			Renderer::NewFrame();

			// NOTE: ImGUI::NewFrame() is in PollInput()!
		}

		void Framework::PollInput()
		{
			// #TODO Abstract libraries
            glfwPollEvents(); // #TODO Better GLFW interface?
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame(); // after Input gets reset, and after glfw input polling is done
            ImGui::NewFrame();
			// #TODO Tell input manager it is a new frame and it should update key states
		}

		void Framework::Update(double deltatime)
		{
			const ConfigData config = ConfigHelper::GetConfigData();
			if (config.systems.PhysicsEnabled)
			{
				Physics::Tick();
			}

			Scenes::Update(deltatime);

			if (Input::FrameKeyAction(eKeys::eKeys_Escape, eKeyState::eKeyState_Press))
			{
				Stop();
			}
		}

		void Framework::Draw()
		{
			Scenes::DrawCurrentScene();

			// #TODO Abstract libraries
			ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            ImGuiIO io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

			m_Window->SwapBuffers();
		}

		void Framework::EndFrame()
		{
		}

		bool Framework::StillRunning()
		{
			return m_IsRunning;
		}
	}
}
