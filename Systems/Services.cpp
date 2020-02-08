#include "Services.h"
#include "../Headers/QwerkE_Enums.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"

#include <assert.h>

namespace QwerkE {

	// Init variables
    bool QwerkE::Services::m_IsLocked = true; // Must be unlocked to edit

    // Resources Services::Resources;

    EventManager* Services::m_EventManager = nullptr;
	Physics* Services::m_Physics = nullptr;
	MessageManager* Services::m_MessageManager = nullptr;
	Audio* Services::m_AudioManager = nullptr;
	Window* Services::m_Window = nullptr;
	Network* Services::m_NetworkManager = nullptr;
	DataManager* Services::m_DataManager = nullptr;

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
		case eEngineServices::Event_System:
			Services::m_EventManager = (EventManager*)service;
			break;
		case eEngineServices::WindowManager:
			Services::m_Window = (Window*)service;
			break;
		case eEngineServices::Data_Manager:
			Services::m_DataManager = (DataManager*)service;
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
		case eEngineServices::Event_System:
			temp = Services::m_EventManager;
			Services::m_EventManager = nullptr;
			return temp;
		case eEngineServices::WindowManager:
			temp = Services::m_Window;
			Services::m_Window = nullptr;
			return temp;
			break;
		case eEngineServices::Data_Manager:
			temp = Services::m_DataManager;
			Services::m_DataManager = nullptr;
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
		case eEngineServices::Event_System:
			return Services::m_EventManager;
			break;
		case eEngineServices::WindowManager:
			return Services::m_Window;
			break;
		case eEngineServices::Data_Manager:
			return Services::m_DataManager;
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
			case eEngineServices::Event_System:
				if (Services::m_EventManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::WindowManager:
				if (Services::m_Window == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			case eEngineServices::Data_Manager:
				if (Services::m_DataManager == nullptr)
					return eEngineMessage::_QFailure; // not loaded
				break;
			}

			i = (eEngineServices)((int)i + 1); // increment service
		}
		return eEngineMessage::_QSuccess;
	}
}