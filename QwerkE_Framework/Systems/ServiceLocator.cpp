#include "ServiceLocator.h"

#include <assert.h>

namespace QwerkE
{
	// init variables
	bool QwerkE::ServiceLocator::m_IsLocked = true; // must be unlocked to edit

	ResourceManager* QwerkE::ServiceLocator::m_ResourceManager = nullptr;
	InputManager* QwerkE::ServiceLocator::m_InputManager = nullptr;
    EventManager* QwerkE::ServiceLocator::m_EventManager = nullptr;
    SceneManager* QwerkE::ServiceLocator::m_SceneManager = nullptr;
    Factory* QwerkE::ServiceLocator::m_Factory = nullptr;
    Editor* QwerkE::ServiceLocator::m_Editor = nullptr;
	PhysicsManager* QwerkE::ServiceLocator::m_PhysicsManager = nullptr;
	MessageManager* QwerkE::ServiceLocator::m_MessageManager = nullptr;
	Renderer* QwerkE::ServiceLocator::m_Renderer = nullptr;
    AudioManager* QwerkE::ServiceLocator::m_AudioManager = nullptr;
    JobManager* QwerkE::ServiceLocator::m_JobManager = nullptr;
	Window* QwerkE::ServiceLocator::m_Window = nullptr;
    NetworkManager* QwerkE::ServiceLocator::m_NetworkManager = nullptr;

	void ServiceLocator::RegisterService(eEngineServices serviceType, void* service)
	{
		assert(m_IsLocked == false); // Services are locked

		switch (serviceType)
		{
		case eEngineServices::Resource_Manager:
			ServiceLocator::m_ResourceManager = (ResourceManager*)service;
			break;
		case eEngineServices::Input_Manager:
			ServiceLocator::m_InputManager = (InputManager*)service;
			break;
        case eEngineServices::Event_System:
            ServiceLocator::m_EventManager = (EventManager*)service;
            break;
        case eEngineServices::Scene_Manager:
            ServiceLocator::m_SceneManager = (SceneManager*)service;
            break;
        case eEngineServices::Factory_Entity:
            ServiceLocator::m_Factory = (Factory*)service;
            break;
        case eEngineServices::Editor:
            ServiceLocator::m_Editor = (Editor*)service;
            break;
		case eEngineServices::PhysicsManager:
			ServiceLocator::m_PhysicsManager = (PhysicsManager*)service;
			break;
		case eEngineServices::MessageManager:
			ServiceLocator::m_MessageManager = (MessageManager*)service;
			break;
		case eEngineServices::Renderer:
			ServiceLocator::m_Renderer = (Renderer*)service;
			break;
        case eEngineServices::Audio_Manager:
            ServiceLocator::m_AudioManager = (AudioManager*)service;
            break;
		case eEngineServices::JobManager:
			ServiceLocator::m_JobManager = (JobManager*)service;
			break;
		case eEngineServices::WindowManager:
			ServiceLocator::m_Window = (Window*)service;
			break;
        case eEngineServices::NetworkManager:
            ServiceLocator::m_NetworkManager = (NetworkManager*)service;
            break;
		default:
			ConsolePrint("ServiceLocator::RegisterService(): Invalid service!");
			break;
		}
	}

	void* ServiceLocator::UnregisterService(eEngineServices serviceType) // TODO: Potentially dangerous!
	{
		assert(m_IsLocked == false); // Services are locked

		void* temp = nullptr;
		switch (serviceType)
		{
		case eEngineServices::Resource_Manager:
			temp = ServiceLocator::m_ResourceManager;
			ServiceLocator::m_ResourceManager = nullptr;
			return temp;
			break;
		case eEngineServices::Input_Manager:
			temp = ServiceLocator::m_InputManager;
			ServiceLocator::m_InputManager = nullptr;
			return temp;
			break;
        case eEngineServices::Event_System:
            temp = ServiceLocator::m_EventManager;
            ServiceLocator::m_EventManager = nullptr;
            return temp;
        case eEngineServices::Scene_Manager:
            temp = ServiceLocator::m_SceneManager;
            ServiceLocator::m_SceneManager = nullptr;
            return temp;
            break;
        case eEngineServices::Factory_Entity:
            temp = ServiceLocator::m_Factory;
            ServiceLocator::m_Factory = nullptr;
            return temp;
            break;
        case eEngineServices::Editor:
            temp = ServiceLocator::m_Editor;
            ServiceLocator::m_Editor = nullptr;
            return temp;
            break;
		case eEngineServices::PhysicsManager:
			temp = ServiceLocator::m_PhysicsManager;
			ServiceLocator::m_PhysicsManager = nullptr;
			return temp;
			break;
		case eEngineServices::MessageManager:
			temp = ServiceLocator::m_MessageManager;
			ServiceLocator::m_MessageManager = nullptr;
			return temp;
			break;
		case eEngineServices::Renderer:
			temp = ServiceLocator::m_Renderer;
			ServiceLocator::m_Renderer = nullptr;
			return temp;
			break;
        case eEngineServices::Audio_Manager:
            temp = ServiceLocator::m_AudioManager;
            ServiceLocator::m_AudioManager = nullptr;
            return temp;
            break;
		case eEngineServices::JobManager:
			temp = ServiceLocator::m_JobManager;
			ServiceLocator::m_JobManager = nullptr;
			return temp;
			break;
		case eEngineServices::WindowManager:
			temp = ServiceLocator::m_Window;
			ServiceLocator::m_Window = nullptr;
			return temp;
			break;
        case eEngineServices::NetworkManager:
            temp = ServiceLocator::m_NetworkManager;
            ServiceLocator::m_NetworkManager = nullptr;
            return temp;
            break;
		default:
			ConsolePrint("ServiceLocator::UnregisterService(): Invalid service!");
			return nullptr;
			break;
		}
	}

	void* ServiceLocator::GetService(eEngineServices serviceType)
	{
		switch (serviceType)
		{
		case eEngineServices::Resource_Manager:
			return ServiceLocator::m_ResourceManager;
			break;
		case eEngineServices::Input_Manager:
			return ServiceLocator::m_InputManager;
			break;
        case eEngineServices::Event_System:
            return ServiceLocator::m_EventManager;
            break;
        case eEngineServices::Scene_Manager:
            return ServiceLocator::m_SceneManager;
            break;
        case eEngineServices::Factory_Entity:
            return ServiceLocator::m_Factory;
            break;
        case eEngineServices::Editor:
            return ServiceLocator::m_Editor;
            break;
		case eEngineServices::PhysicsManager:
			return ServiceLocator::m_PhysicsManager;
			break;
		case eEngineServices::MessageManager:
			return ServiceLocator::m_MessageManager;
			break;
		case eEngineServices::Renderer:
			return ServiceLocator::m_Renderer;
			break;
        case eEngineServices::Audio_Manager:
            return ServiceLocator::m_AudioManager;
            break;
		case eEngineServices::JobManager:
			return ServiceLocator::m_JobManager;
			break;
		case eEngineServices::WindowManager:
			return ServiceLocator::m_Window;
			break;
        case eEngineServices::NetworkManager:
            return ServiceLocator::m_NetworkManager;
            break;
		default:
			ConsolePrint("ServiceLocator::GetService(): Invalid service!");
			return nullptr;
			break;
		}
	}
	// TODO: Improve logic and code design
	eEngineMessage ServiceLocator::ServicesLoaded() // determine if all services are loaded
	{
		for (eEngineServices i = (eEngineServices)0; i < eEngineServices::Service_Max;)
		{
			switch (i)
			{
			case eEngineServices::Resource_Manager:
				if (ServiceLocator::m_ResourceManager == nullptr)
					return eEngineMessage::_QFail; // not loaded
				break;
			case eEngineServices::Input_Manager:
				if (ServiceLocator::m_InputManager == nullptr)
					return eEngineMessage::_QFail; // not loaded
				break;
            case eEngineServices::Event_System:
                if (ServiceLocator::m_EventManager == nullptr)
                    return eEngineMessage::_QFail; // not loaded
                break;
            case eEngineServices::Scene_Manager:
                if (ServiceLocator::m_SceneManager == nullptr)
                    return eEngineMessage::_QFail; // not loaded
                break;
            case eEngineServices::Factory_Entity:
                if (ServiceLocator::m_Factory == nullptr)
                    return eEngineMessage::_QFail; // not loaded
                break;
            case eEngineServices::Editor:
                if (ServiceLocator::m_Editor == nullptr)
                    return eEngineMessage::_QFail; // not loaded
                break;
			case eEngineServices::PhysicsManager:
				if (ServiceLocator::m_PhysicsManager == nullptr)
					return eEngineMessage::_QFail; // not loaded
				break;
			case eEngineServices::MessageManager:
				if (ServiceLocator::m_MessageManager == nullptr)
					return eEngineMessage::_QFail; // not loaded
				break;
			case eEngineServices::Renderer:
				if (ServiceLocator::m_Renderer == nullptr)
					return eEngineMessage::_QFail; // not loaded
				break;
            case eEngineServices::Audio_Manager:
                if (ServiceLocator::m_AudioManager == nullptr)
                    return eEngineMessage::_QFail; // not loaded
                break;
			case eEngineServices::JobManager:
				if (ServiceLocator::m_JobManager == nullptr)
					return eEngineMessage::_QFail; // not loaded
				break;
			case eEngineServices::WindowManager:
				if (ServiceLocator::m_Window == nullptr)
					return eEngineMessage::_QFail; // not loaded
				break;
            case eEngineServices::NetworkManager:
                if (ServiceLocator::m_NetworkManager == nullptr)
                    return eEngineMessage::_QFail; // not loaded
                break;
			}

			i = (eEngineServices)((int)i + 1); // increment service
		}
		return eEngineMessage::_QSuccess;
	}
}