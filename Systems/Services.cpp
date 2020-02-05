#include "Services.h"
#include "../Headers/QwerkE_Enums.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"

#include <assert.h>

namespace QwerkE {

	// Init variables
    bool QwerkE::Services::m_IsLocked = true; // Must be unlocked to edit

    ResourceManager Services::Resources;

    InputManager* Services::m_InputManager = nullptr;
    EventManager* Services::m_EventManager = nullptr;
    SceneManager* Services::m_SceneManager = nullptr;
	Factory* Services::m_Factory = nullptr;
	ShaderFactory* Services::m_ShaderFactory = nullptr;
	PhysicsManager* Services::m_PhysicsManager = nullptr;
	MessageManager* Services::m_MessageManager = nullptr;
	Renderer* Services::m_Renderer = nullptr;
	AudioManager* Services::m_AudioManager = nullptr;
	JobManager* Services::m_JobManager = nullptr;
	Window* Services::m_Window = nullptr;
	NetworkManager* Services::m_NetworkManager = nullptr;
	DataManager* Services::m_DataManager = nullptr;
	FileSystem* Services::m_FileSystem = nullptr;

    Services::Services()
    {
    }

	Services::~Services()
    {
    }

    void Services::RegisterService(eEngineServices serviceType, void* service)
    {
        assert(service != nullptr);
		assert(m_IsLocked == false); // Services are locked

		switch (serviceType)
		{
		case eEngineServices::Input_Manager:
			Services::m_InputManager = (InputManager*)service;
			break;
		case eEngineServices::Event_System:
			Services::m_EventManager = (EventManager*)service;
			break;
		case eEngineServices::Scene_Manager:
			Services::m_SceneManager = (SceneManager*)service;
			break;
		case eEngineServices::Factory_Entity:
			Services::m_Factory = (Factory*)service;
			break;
		case eEngineServices::Factory_Shader:
			Services::m_ShaderFactory = (ShaderFactory*)service;
			break;
		case eEngineServices::PhysicsManager:
			Services::m_PhysicsManager = (PhysicsManager*)service;
			break;
		case eEngineServices::MessageManager:
			Services::m_MessageManager = (MessageManager*)service;
			break;
		case eEngineServices::Renderer:
			Services::m_Renderer = (Renderer*)service;
			break;
		case eEngineServices::Audio_Manager:
			Services::m_AudioManager = (AudioManager*)service;
			break;
		case eEngineServices::JobManager:
			Services::m_JobManager = (JobManager*)service;
			break;
		case eEngineServices::WindowManager:
			Services::m_Window = (Window*)service;
			break;
		case eEngineServices::NetworkManager:
			Services::m_NetworkManager = (NetworkManager*)service;
			break;
		case eEngineServices::Data_Manager:
			Services::m_DataManager = (DataManager*)service;
			break;
		case eEngineServices::FileSystem:
			Services::m_FileSystem = (FileSystem*)service;
			break;
		default:
			ConsolePrint("Services::RegisterService(): Invalid service!");
			break;
		}
	}

	void* Services::UnregisterService(eEngineServices serviceType) // TODO: Potentially dangerous!
	{
		assert(m_IsLocked == false); // Services are locked

		void* temp = nullptr;
		switch (serviceType)
		{
		case eEngineServices::Input_Manager:
			temp = Services::m_InputManager;
			Services::m_InputManager = nullptr;
			return temp;
			break;
		case eEngineServices::Event_System:
			temp = Services::m_EventManager;
			Services::m_EventManager = nullptr;
			return temp;
		case eEngineServices::Scene_Manager:
			temp = Services::m_SceneManager;
			Services::m_SceneManager = nullptr;
			return temp;
			break;
		case eEngineServices::Factory_Entity:
			temp = Services::m_Factory;
			Services::m_Factory = nullptr;
			return temp;
			break;
		case eEngineServices::Factory_Shader:
			temp = Services::m_ShaderFactory;
			Services::m_ShaderFactory = nullptr;
			return temp;
			break;
		case eEngineServices::PhysicsManager:
			temp = Services::m_PhysicsManager;
			Services::m_PhysicsManager = nullptr;
			return temp;
			break;
		case eEngineServices::MessageManager:
			temp = Services::m_MessageManager;
			Services::m_MessageManager = nullptr;
			return temp;
			break;
		case eEngineServices::Renderer:
			temp = Services::m_Renderer;
			Services::m_Renderer = nullptr;
			return temp;
			break;
		case eEngineServices::Audio_Manager:
			temp = Services::m_AudioManager;
			Services::m_AudioManager = nullptr;
			return temp;
			break;
		case eEngineServices::JobManager:
			temp = Services::m_JobManager;
			Services::m_JobManager = nullptr;
			return temp;
			break;
		case eEngineServices::WindowManager:
			temp = Services::m_Window;
			Services::m_Window = nullptr;
			return temp;
			break;
		case eEngineServices::NetworkManager:
			temp = Services::m_NetworkManager;
			Services::m_NetworkManager = nullptr;
			return temp;
			break;
		case eEngineServices::Data_Manager:
			temp = Services::m_DataManager;
			Services::m_DataManager = nullptr;
			return temp;
			break;
		case eEngineServices::FileSystem:
			temp = Services::m_FileSystem;
			Services::m_FileSystem = nullptr;
			return temp;
			break;
		default:
			ConsolePrint("Services::UnregisterService(): Invalid service!");
			return nullptr;
			break;
		}
	}

	void* Services::GetService(eEngineServices serviceType)
	{
		switch (serviceType)
		{
		case eEngineServices::Input_Manager:
			return Services::m_InputManager;
			break;
		case eEngineServices::Event_System:
			return Services::m_EventManager;
			break;
		case eEngineServices::Scene_Manager:
			return Services::m_SceneManager;
			break;
		case eEngineServices::Factory_Entity:
			return Services::m_Factory;
			break;
		case eEngineServices::Factory_Shader:
			return Services::m_ShaderFactory;
			break;
		case eEngineServices::PhysicsManager:
			return Services::m_PhysicsManager;
			break;
		case eEngineServices::MessageManager:
			return Services::m_MessageManager;
			break;
		case eEngineServices::Renderer:
			return Services::m_Renderer;
			break;
		case eEngineServices::Audio_Manager:
			return Services::m_AudioManager;
			break;
		case eEngineServices::JobManager:
			return Services::m_JobManager;
			break;
		case eEngineServices::WindowManager:
			return Services::m_Window;
			break;
		case eEngineServices::NetworkManager:
			return Services::m_NetworkManager;
			break;
		case eEngineServices::Data_Manager:
			return Services::m_DataManager;
			break;
		case eEngineServices::FileSystem:
			return Services::m_FileSystem;
			break;
		default:
			ConsolePrint("Services::GetService(): Invalid service!");
			return nullptr;
			break;
		}
	}
	// TODO: Improve logic and code design
	eEngineMessage Services::ServicesLoaded() // determine if all services are loaded
	{
		for (eEngineServices i = (eEngineServices)0; i < eEngineServices::Service_Max;)
		{
			switch (i)
			{
			case eEngineServices::Input_Manager:
				if (Services::m_InputManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::Event_System:
				if (Services::m_EventManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::Scene_Manager:
				if (Services::m_SceneManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::Factory_Entity:
				if (Services::m_Factory == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::Factory_Shader:
				if (Services::m_ShaderFactory == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::PhysicsManager:
				if (Services::m_PhysicsManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::MessageManager:
				if (Services::m_MessageManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::Renderer:
				if (Services::m_Renderer == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::Audio_Manager:
				if (Services::m_AudioManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::JobManager:
				if (Services::m_JobManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::WindowManager:
				if (Services::m_Window == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::NetworkManager:
				if (Services::m_NetworkManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::Data_Manager:
				if (Services::m_DataManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::FileSystem:
				if (Services::m_FileSystem == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			}

			i = (eEngineServices)((int)i + 1); // increment service
		}
		return eEngineMessage::_QSuccess;
	}
}