#include "Framework.h"
#include "../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../QwerkE_Common/Libraries/glfw/GLFW/glfw3.h"
#include "../QwerkE_Common/Libraries/imgui/imgui.h"
#include "../QwerkE_Common/Libraries/imgui/imgui_impl_glfw_gl3.h"
#include "Systems/ResourceManager.h"
#include "Systems/ServiceLocator.h"
#include "QwerkE_Enums.h"
#include "../QwerkE_Common/Utilities/Helpers.h"
#include "../QwerkE_Common/Libraries_Initialize.h"
#include "Systems/Events/EventManager.h"
#include "Scene/SceneManager.h"
#include "Systems/Factory/Factory.h"
#include "Systems/Graphics/Sprite/Sprite.h"
#include "Systems/Graphics_Header.h"
#include "Systems/Graphics/FBO/FrameBufferObject.h"
#include "CallbackFunctions.h"
#include "Systems/Physics/PhysicsManager.h"
#include "Systems/Renderer.h"
#include "Systems/MessageManager.h"
#include "Systems/Audio/AudioManager.h"
#include "Systems/Debugger.h"
#include "Systems/Time.h"
#include "Systems/Graphics/Model/Mesh/MeshFactory.h"
#include "Systems/Graphics/ShaderProgram/ShaderFactory.h"
#include "Systems/JobManager.h"
#include "Systems/Networking/NetworkManager.h"
#include "Systems/Window/Window.h"
#include "Systems/Window/WindowManager.h"
#include "Systems/Window/glfw_Window.h"

// TODO: No Globals!
extern int g_WindowWidth = 1280, g_WindowHeight = 720; // (1280x720)(1600x900)(1920x1080)(2560x1440)
extern const char* g_WindowTitle = "QwerkE";

extern GameCore* g_GameCore = nullptr;
extern const int g_NumPlayers; // Defined in InputManager.h
extern InputManager* g_InputManager = nullptr;
extern Controller* g_Player1Controller = nullptr;
extern bool g_Debugging = false;

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
			if (Libs_Setup() == false) // setup libraries
			{
				ConsolePrint("\nStartup(): Error loading libraries!\n");
				return eEngineMessage::_QFail; // failure
			}

			// TODO: Try to reduce or avoid order dependency in system creation

			// load and register systems
			// Audio, Networking, Graphics (Renderer, GUI), Utilities (Conversion, FileIO, Printing),
			// Physics, Event, Debug, Memory, Window, Application, Input, Resources
			QwerkE::ServiceLocator::LockServices(false);

			ResourceManager* resourceManager = new ResourceManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Resource_Manager, resourceManager);

			InputManager* inputManager = new InputManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Input_Manager, inputManager);

		#ifdef _glfw3_h_
			m_Window = new glfw_Window(g_WindowWidth, g_WindowHeight, g_WindowTitle);
		#else
			// win32 window or something
			Window* window = new Window(g_WindowWidth, g_WindowHeight, g_WindowTitle);
		#endif // !_glfw3_h_

			WindowManager* windowManager = new WindowManager();
			windowManager->AddWindow(m_Window);

			QwerkE::ServiceLocator::RegisterService(eEngineServices::WindowManager, windowManager);

			EventManager* eventManager = new EventManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Event_System, eventManager);

			m_SceneManager = new SceneManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Scene_Manager, m_SceneManager);

			Factory* factory = new Factory();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Factory_Entity, factory);

			PhysicsManager* physicsManager = new PhysicsManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::PhysicsManager, physicsManager);

			MessageManager* messageManager = new MessageManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::MessageManager, messageManager);

			Renderer* renderer = new Renderer();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Renderer, renderer);

			AudioManager* audioManager = new AudioManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::Audio_Manager, audioManager);

			JobManager* jobManager = new JobManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::JobManager, jobManager);

			NetworkManager* network = new NetworkManager();
			QwerkE::ServiceLocator::RegisterService(eEngineServices::NetworkManager, network);

			m_SceneManager->Initialize(); // Order Dependency

			return QwerkE::ServiceLocator::ServicesLoaded();
		}

		eEngineMessage Framework::TearDown()
		{
			delete (ResourceManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Resource_Manager);

			delete (InputManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Input_Manager);

			delete ((WindowManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::WindowManager));

			delete (EventManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Event_System);

			delete m_SceneManager;

			delete (Factory*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Factory_Entity);

			delete (PhysicsManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::PhysicsManager);

			delete (MessageManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::MessageManager);

			delete (Renderer*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Renderer);

			delete (AudioManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::Audio_Manager);

			delete (JobManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::JobManager);

			delete (NetworkManager*)QwerkE::ServiceLocator::UnregisterService(eEngineServices::NetworkManager);

			Libs_TearDown(); // unload libraries

							 // TODO: Safety checks?
			return eEngineMessage::_QSuccess;
		}

		void Framework::Run()
		{
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

			// depth cull for efficiency
			// Testing: glEnable(GL_CULL_FACE);
			// Testing: glCullFace(GL_BACK);
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
		}

		void Framework::NewFrame()
		{
			/* Reset */
			// TODO: Reset things...
			ImGui_ImplGlfwGL3_NewFrame();
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
			if (inputManager->GetIsKeyDown(eKeys::eKeys_Escape))
			{
				WindowManager* windowManager = (WindowManager*)QwerkE::ServiceLocator::GetService(eEngineServices::WindowManager);
				windowManager->GetWindow(0)->SetClosing(true);
			}
		}

		void Framework::Draw()
		{
			//m_SceneManager->Draw();

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
