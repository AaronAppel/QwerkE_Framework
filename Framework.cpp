#include "Framework.h"
#include "Libraries/glew/GL/glew.h"
#include "Libraries/glfw/GLFW/glfw3.h"
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw.h"
#include "Libraries/imgui/imgui_impl_opengl3.h"
#include "Headers/QwerkE_Enums.h"
#include "Systems/Misc/Helpers.h"
#include "Headers/Libraries_Initialize.h"
#include "Systems/Events/EventManager.h"
#include "Systems/Scenes.h"
#include "Systems/Factory/Factory.h"
#include "Graphics/Graphics_Header.h"
#include "Systems/Window/CallbackFunctions.h"
#include "Systems/Physics/Physics.h"
#include "Systems/DataManager/DataManager.h"
#include "Systems/Renderer/Renderer.h"
#include "Systems/MessageManager.h"
#include "Systems/Audio/Audio.h"
#include "Systems/Audio/OpenALAudioManager.h"
#include "Systems/Debugger/Debugger.h"
#include "Systems/ShaderFactory/ShaderFactory.h"
#include "Systems/Jobs/Jobs.h"
#include "Systems/Window/Window.h"
#include "Systems/Window/Windows.h"
#include "Systems/Window/glfw_Window.h"
#include "Systems/FileSystem/FileSystem.h"
#include "Systems/DataManager/ConfigHelper.h"
#include "Modules/Time/Time.h"
#include "Graphics/Mesh/MeshFactory.h"
#include "Systems/Input/Input.h"
#include "Systems/Log/Log.h"

namespace QwerkE {

    // TODO: No Globals!
    extern int g_WindowWidth = 1600, g_WindowHeight = 900; // (1280x720)(1600x900)(1920x1080)(2560x1440)
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
			// TODO: Log loading and skipping. Everything!

			cJSON* root = OpencJSONStream(configFilePath.c_str()); // TODO: Remove engine behaviour
			cJSON* systems = GetItemFromRootByKey(root, "Systems"); // TODO: Use flags to see if systems are enabled/disabled

            ConfigHelper::LoadConfigData(configFilePath); // Init config data
            ConfigData config = ConfigHelper::GetConfigData();

            // TODO: Load libraries dynamically. Need functions to load .dlls
			// TODO: Avoid loading unused libraries. React to system flags

			if (Libs_Setup() == false) // setup libraries
			{
				Log::Safe("\nStartup(): Error loading libraries!\n");
				return eEngineMessage::_QFailure; // failure
            }

            // TODO: Cleanup switch or if/else if statements below. Find a nice way to detect which library objects to load

			// TODO: Try to reduce or avoid order dependency in system creation.
			// current dependencies..
			// Resources depends on itself to init null objects
			// Window depends on Input for input callbacks
			// Scenes needs other systems setup to load a scene

			// load and register systems
			// Audio, Networking, Graphics (Renderer, GUI), Utilities (Conversion, FileIO, Printing),
            // Physics, Event, Debug, Memory, Window, Application, Input, Resources

			// ShaderFactory// Dependency: resource manager

            if (config.libraries.Window == "GLFW3")
                m_Window = new glfw_Window(g_WindowWidth, g_WindowHeight, g_WindowTitle);
            else
            {
				LOG_ERROR("No window library detected! Check config libraries value.");
                assert(false);
            }

            Windows::AddWindow(m_Window);

            Input::Initialize((GLFWwindow*)Windows::GetWindow(0)->GetContext());

            Resources::Initialize(); // OpenGL init order dependency (Window?)

			cJSON* audioEnabled = GetItemFromArrayByKey(systems, "AudioEnabled");
            bool enabled = audioEnabled != nullptr ? (bool)audioEnabled->valuedouble : false; // TODO: Improve value handling

            if (config.systems.AudioEnabled)
            {
				// TODO: Read audio library value and load proper audio library
                Audio::Initialize();
                Log::Info("Audio system initialized with OpenAL.");
            }
			else
            {
				Log::Info("No audio system loaded.");
			}

			glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // TEMP: avoid bright white screen while loading

			Renderer::DrawFont("Loading..."); // Message for user while loading
			m_Window->SwapBuffers();

			EventManager::Initialize();

            if (config.systems.PhysicsEnabled)
            {
                if (config.libraries.Physics == "Bullet3D")
                {
                    // TODO: Create Bullet3DPhyicsManager class
					Physics::Initialize();
                }
            }
			else
            {
                Log::Info("No physics system loaded.");
			}

			// MessageManager::Initialize();

			cJSON* jobManagerMultiThreaded = GetItemFromArrayByKey(systems, "JobsMultiThreadedEnabled");

			if (jobManagerMultiThreaded != nullptr && jobManagerMultiThreaded->valueint == 1)
            {
                // TODO: Define max thread behaviour
				// Jobs::MaxThreads(10)  (Enable multi threading)
			}
			else
			{
				// TODO: Setup single threaded job manager
				// Jobs::MaxThreads(1)
			}

			// Network::Initialize();

			Scenes::Initialize(); // Order Dependency

			return eEngineMessage::_QSuccess;
		}

		eEngineMessage Framework::TearDown()
        {
			// TODO: ShutdownSystems();
            EventManager::Shutdown();

			Libs_TearDown(); // unload libraries

			// TODO: Safety checks?
			return eEngineMessage::_QSuccess;
		}

		void Framework::Run()
        {
            assert(m_Window != nullptr); // Don't forget to call Framework::Startup() to initiailize the framework

			// TODO: check if(initialized) in case user defined simple API.
			// Might want to create another function for the game loop and
			// leave Run() smaller and abstracted from the functionality.
			m_IsRunning = true;

			double timeSinceLastFrame = 0.0;
			float frameRate = 0.0f;
			Time::SetDeltatime(&timeSinceLastFrame);
			Time::SetFrameRate(&frameRate);

			// TODO: GL state init should be in a Window() or OpenGLManager()
			// class or some type of ::Graphics() system.
			glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
			// turn on depth buffer testing
			glEnable(GL_DEPTH_TEST);
			glPointSize(10);
			glLineWidth(10);

			// depth cull for efficiency
			glEnable(GL_CULL_FACE);
			// glDisable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			if(Wind_CCW) glFrontFace(GL_CCW);
			else glFrontFace(GL_CW);

			// turn on alpha blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glViewport(0, 0, g_WindowWidth, g_WindowHeight);

			// Deltatime + FPS Tracking //
			// deltatime
			double deltaTime = 0.0f; // Time between current frame and last frame
			double lastFrame = helpers_Time(); // Time of last frame initialized to current time
			// Limit framerate
			int FPS_MAX = 120; // maximum number of frames that can be run be second
			float FPS_MAX_DELTA = 1.0f / FPS_MAX;
			timeSinceLastFrame = FPS_MAX; // Amount of seconds since the last frame ran initialized to run 1st time
			// Printing framerate
			float printPeriod = 3.0f; // Print period in seconds
			float timeSincePrint = printPeriod; // Seconds since last print initialized to print 1st frame
			short framesSincePrint = 0;

			// Application Loop
			while (m_Window->IsClosing() == false) // Run until close requested
			{
				// setup frame
				// Calculate deltatime of current frame
				double currentFrame = helpers_Time();
				deltaTime = currentFrame - lastFrame; // time since last frame
				lastFrame = currentFrame; // save last frame time

				// FPS display + tracking
				if (timeSincePrint >= printPeriod) // print period
				{
					frameRate = 1.0f / timeSincePrint * framesSincePrint;
					// OutputPrint("\nFPS: %f", frameRate); // FPS printout
					// OutputPrint("\nFrames: %i", framesSincePrint); // Frames printout
					timeSincePrint = 0.0f;
					framesSincePrint = 0;
				}

				timeSincePrint += (float)deltaTime;
				timeSinceLastFrame += deltaTime;

				/* Game Loop */
				if (timeSinceLastFrame >= FPS_MAX_DELTA)
				{
					/* New Frame */
					Framework::NewFrame();

					/* Input */
					Framework::PollInput();

					/* Logic */
					Framework::Update(timeSinceLastFrame);

					/* Render */
					Framework::Draw();

					// FPS
					framesSincePrint++; // Framerate tracking
					timeSinceLastFrame = 0.0; // FPS_Max
				}
				else
				{
					Yield();
				}
			}
		}

		void Framework::Stop()
		{
			m_IsRunning = false;
			m_Window->SetClosing(true);
		}

		void Framework::NewFrame()
		{
			/* Reset */
			// TODO: Reset things...
			Input::NewFrame(); // TODO Replace with static instance call

			// TODO: Process events every frame
			EventManager::ProcessEvents();
		}

		void Framework::PollInput()
		{
            glfwPollEvents(); // TODO: Better GLFW interface?
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame(); // after Input gets reset, and after glfw input polling is done
            ImGui::NewFrame();
			// TODO: Tell input manager it is a new frame and it should update key states
		}

		void Framework::Update(double deltatime)
		{
			Scenes::Update(deltatime);

			//if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE)) // DEBUG: A simple way to close the window while testing

			if (Input::FrameKeyAction(eKeys::eKeys_P, eKeyState::eKeyState_Press)) // pause entire scene
			{
				static bool paused = false;
				paused = !paused;
				if (paused)
				{
					Scenes::GetCurrentScene()->SetState(eSceneState::SceneState_Paused);
				}
				else
				{
					Scenes::GetCurrentScene()->SetState(eSceneState::SceneState_Running);
				}
			}
			if (Input::FrameKeyAction(eKeys::eKeys_Z, eKeyState::eKeyState_Press))// pause actor updates
			{
				static bool frozen = false;
				frozen = !frozen;
				if (frozen)
				{
					Scenes::GetCurrentScene()->SetState(eSceneState::SceneState_Frozen);
				}
				else
				{
					Scenes::GetCurrentScene()->SetState(eSceneState::SceneState_Running);
				}
			}
			if (Input::FrameKeyAction(eKeys::eKeys_Escape, eKeyState::eKeyState_Press))
			{
				Windows::GetWindow(0)->SetClosing(true);
			}
		}

		void Framework::Draw()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // new frame
			Scenes::Draw();

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

			m_Window->SwapBuffers(); // Change frame buffers
		}

		void Framework::EndFrame()
		{
			// Post frame cleanup? Maybe tell memory manager to clean up 1 frame stacks?
		}

		bool Framework::StillRunning()
		{
			return m_IsRunning;
		}
	}
}
