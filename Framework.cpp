#include "Framework.h"
#include "QwerkE_Common/Libraries/glew/GL/glew.h"
#include "QwerkE_Common/Libraries/glfw/GLFW/glfw3.h"
#include "QwerkE_Common/Libraries/imgui/imgui.h"
#include "QwerkE_Common/Libraries/imgui/imgui_impl_glfw_gl3.h"
#include "Headers/QwerkE_Enums.h"
#include "QwerkE_Common/Utilities/Helpers.h"
#include "Headers/Libraries_Initialize.h"
#include "Systems/Events/EventManager.h"
#include "Systems/SceneManager.h"
#include "Systems/Factory/Factory.h"
#include "Graphics/Graphics_Header.h"
#include "Systems/ResourceManager/ResourceManager.h"
#include "Systems/ServiceLocator.h"
#include "Systems/Window/CallbackFunctions.h"
#include "Systems/Physics/PhysicsManager.h"
#include "Systems/DataManager/DataManager.h"
#include "Systems/DataManager/LevelLoader.h"
#include "Systems/Renderer/Renderer.h"
#include "Systems/MessageManager.h"
#include "Systems/Audio/AudioManager.h"
#include "Systems/Audio/OpenALAudioManager.h"
#include "Systems/Audio/NullAudioManager.h"
#include "Systems/Debugger/Debugger.h"
#include "Systems/ShaderFactory/ShaderFactory.h"
#include "Systems/JobManager/JobManager.h"
#include "Systems/Networking/NetworkManager.h"
#include "Systems/Window/Window.h"
#include "Systems/Window/WindowManager.h"
#include "Systems/Window/glfw_Window.h"
#include "Systems/FileSystem/FileSystem.h"
#include "Systems/DataManager/ConfigHelper.h"
#include "Modules/Time.h"
#include "Graphics/Mesh/MeshFactory.h"

// TODO: No Globals!
extern int g_WindowWidth = 1600, g_WindowHeight = 900; // (1280x720)(1600x900)(1920x1080)(2560x1440)
extern const char* g_WindowTitle = "QwerkEngine";

extern InputManager* g_InputManager = nullptr;

// private framework variables
static Window* m_Window = nullptr;
static bool m_IsRunning = false;
static SceneManager* m_SceneManager = nullptr;

namespace QwerkE
{
	namespace Framework
	{
		eEngineMessage Framework::Startup()
		{
            cJSON* root = OpencJSONStream(ConfigsFolderPath("preferences.qpref"));
            cJSON* systems = GetItemFromRootByKey(root, "Systems");

            ConfigHelper::LoadConfigData(); // Init config data
            ConfigData config = ConfigHelper::GetConfigData();

            // TODO: Load libraries dynamically. Need functions to load .dlls

			if (Libs_Setup() == false) // setup libraries
			{
				ConsolePrint("\nStartup(): Error loading libraries!\n");
				return eEngineMessage::_QFailure; // failure
			}

			// Testing //
			/*Mesh mesh;

			int verts = 2;
			int numIndices = 2;

			CollectedData data;

			data.positions = std::vector<vec3>{ vec3(0,0,0), vec3(0,0,1) };
			data.UVs = std::vector<vec2>{ vec2(0,0), vec2(0,1) };
			data.normals = std::vector<vec3>{ vec3(0,0,0), vec3(0,0,1) };

			unsigned int* indices = new unsigned int[2]{ 0, 1 };

			mesh.BufferMeshData(verts, &data, numIndices, indices);*/

			// Testing //

            // TODO: Cleanup switch or if/elseif statements below. Find a nice way to detect which library objects to load

			// TODO: Try to reduce or avoid order dependency in system creation.
			// current dependencies..
			// ResourceManager depends on itself to init null objects
			// Window depends on InputManager for input callbacks
			// SceneManager needs other systems setup to load a scene

			// load and register systems
			// Audio, Networking, Graphics (Renderer, GUI), Utilities (Conversion, FileIO, Printing),
			// Physics, Event, Debug, Memory, Window, Application, Input, Resources
			QwerkE::ServiceLocator::LockServices(false);

			FileSystem* fileSystem = new FileSystem();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::FileSystem, fileSystem);

			InputManager* inputManager = new InputManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Input_Manager, inputManager);

			ShaderFactory* shaderFactory = new ShaderFactory();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Factory_Shader, shaderFactory); // dependency: resource manager

            if (config.libraries.Window == "GLFW3")
                m_Window = new glfw_Window(g_WindowWidth, g_WindowHeight, g_WindowTitle);
            else
            {
                QwerkE::LogError(__FILE__, __LINE__, "No window library detected! Check config libraries value.");
                assert(false);
            }

			WindowManager* windowManager = new WindowManager();
			windowManager->AddWindow(m_Window);
			inputManager->SetupCallbacks((GLFWwindow*)m_Window->GetContext());

            AudioManager* audioManager = nullptr;
            cJSON* audioEnabled = GetItemFromArrayByKey(systems, "AudioEnabled");
            bool enabled = audioEnabled != nullptr ? (bool)audioEnabled->valuedouble : false; // TODO: Improve value handling

            if (config.systems.AudioEnabled)
            {
                if (config.libraries.Audio == "OpenAL")
                {
                    audioManager = (AudioManager*) new OpenALAudioManager();
                }
            }

            if (audioManager == nullptr)
            {
                ConsolePrint("No audio library define detected! Loading NullAudioManager.");
                audioManager = (AudioManager*) new NullAudioManager();
            }
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Audio_Manager, audioManager); // resource managers needs this

			ResourceManager* resourceManager = new ResourceManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Resource_Manager, resourceManager);
			resourceManager->Init(); // self order dependency, init after adding

			glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //TEMP: avoid bright white screen while loading

			Renderer* renderer = new Renderer();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Renderer, renderer);
			renderer->DrawFont("Loading..."); // Message for user while loading
			m_Window->SwapBuffers();

			QwerkE::ServiceLocator::RegisterService(eEngineServices::WindowManager, windowManager);

			EventManager* eventManager = new EventManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Event_System, eventManager);

			m_SceneManager = new SceneManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Scene_Manager, m_SceneManager);

			Factory* entityFactory = new Factory();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Factory_Entity, entityFactory);

            PhysicsManager* physicsManager = nullptr;
            if (config.systems.PhysicsEnabled)
            {
                if (config.libraries.Physics == "Bullet3D")
                {
                    // TODO: Create Bullet3DPhyicsManager class
                    physicsManager = new PhysicsManager();
                }
            }

            if (physicsManager == nullptr)
            {
                // TODO: Create null physics manager class
                ConsolePrint("No physics library defined or enabled! Loading NullPhysicsManager.");
                physicsManager = new PhysicsManager();
            }
			QwerkE::ServiceLocator::RegisterService(eEngineServices::PhysicsManager, physicsManager);

			MessageManager* messageManager = new MessageManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::MessageManager, messageManager);

			JobManager* jobManager = new JobManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::JobManager, jobManager);

			NetworkManager* network = new NetworkManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::NetworkManager, network);

			DataManager* dataMan = new LevelLoader(entityFactory);
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Data_Manager, dataMan);

			m_SceneManager->Initialize(); // Order Dependency

			return QwerkE::ServiceLocator::ServicesLoaded();
		}

		eEngineMessage Framework::TearDown()
		{
			delete (ResourceManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Resource_Manager);

			delete ((WindowManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::WindowManager));

			delete (EventManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Event_System);

			delete m_SceneManager;

			delete (Factory*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Factory_Entity);

			delete (ShaderFactory*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Factory_Shader);

			delete (PhysicsManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::PhysicsManager);

			delete (MessageManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::MessageManager);

			delete (Renderer*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Renderer);

			delete (AudioManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Audio_Manager);

			delete (JobManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::JobManager);

			delete (NetworkManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::NetworkManager);

			delete (DataManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Data_Manager);

			delete (InputManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Input_Manager); // dependency

			delete (FileSystem*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::FileSystem); // first in, last out

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
			QwerkE::Time::SetDeltatime(&timeSinceLastFrame);
			QwerkE::Time::SetFrameRate(&frameRate);

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

			QwerkE::ServiceLocator::LockServices(true); // prevent service changes

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
				lastFrame = currentFrame; // save last frame

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

				if (timeSinceLastFrame >= FPS_MAX_DELTA) // Run frame?
				{
					/* Game Loop */
					/* New Frame */
					Framework::NewFrame();

					/* Input */
					Framework::Input();

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
					// skip frame
				}
			}

			// unlock services for clean up
			QwerkE::ServiceLocator::LockServices(false);
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
			InputManager* inputManager = (InputManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Input_Manager);
			inputManager->NewFrame();
			ImGui_ImplGlfwGL3_NewFrame(); // after InputManager gets reset
		}

		void Framework::Input()
		{
			glfwPollEvents(); // TODO: Better GLFW interface?
			// TODO: Tell input manager it is a new frame and it should update key states
		}

		void Framework::Update(double deltatime)
		{
			m_SceneManager->Update(deltatime);

			//if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE)) // DEBUG: A simple way to close the window while testing
			InputManager* inputManager = (InputManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Input_Manager);

			if (inputManager->FrameKeyAction(eKeys::eKeys_P, eKeyState::eKeyState_Press)) // pause entire scene
			{
				static bool paused = false;
				paused = !paused;
				if (paused)
				{
					m_SceneManager->GetCurrentScene()->SetState(eSceneState::SceneState_Paused);
				}
				else
				{
					m_SceneManager->GetCurrentScene()->SetState(eSceneState::SceneState_Running);
				}
			}
			if (inputManager->FrameKeyAction(eKeys::eKeys_Z, eKeyState::eKeyState_Press))// pause actor updates
			{
				static bool frozen = false;
				frozen = !frozen;
				if (frozen)
				{
					m_SceneManager->GetCurrentScene()->SetState(eSceneState::SceneState_Frozen);
				}
				else
				{
					m_SceneManager->GetCurrentScene()->SetState(eSceneState::SceneState_Running);
				}
			}
			if (inputManager->FrameKeyAction(eKeys::eKeys_Escape, eKeyState::eKeyState_Press))
			{
				WindowManager* windowManager = (WindowManager*)QwerkE::ServiceLocator::GetService(eEngineServices::WindowManager);
				windowManager->GetWindow(0)->SetClosing(true);
			}
		}

		void Framework::Draw()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // new frame
			m_SceneManager->Draw();

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			m_Window->SwapBuffers(); // Change frame buffers
		}

		bool Framework::StillRunning()
		{
			return m_IsRunning;
		}
	}
}
