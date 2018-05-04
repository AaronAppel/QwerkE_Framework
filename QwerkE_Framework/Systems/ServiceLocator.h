#ifndef _ServiceLocator_H_
#define _ServiceLocator_H_

// Class ServiceLocator provides global access for systems
// necessary throughout the code such as memory management,
// audio playback, input, etc.
// To add a system add it to RegisterService(), UnregisterService,
// GetService(), and ServicesLoaded().

#include "../Engine_Enums.h"
#include "./../../Shared_Generic/Utilities/PrintFunctions.h"
#include "ResourceManager.h"
#include "Input/InputManager.h"

class ResourceManager;
class InputManager;
class EventManager;
class SceneManager;
class Factory;
class Editor;
class PhysicsManager;
class MessageManager;
class Renderer;
class AudioManager;
class JobManager;
class Window;
class NetworkManager;

namespace QwerkE
{
	// TODO: Improve service accessing
	// Think of toggling register/unregister
    // Should code ask for system*s to keep or is this dangerous because
    //  a system could change during runtime?
    // Consider inline ing service locator sunctions for runtime efficiency

    // To avoid dependencies redesign how services are registered/unregistered
    // for order dependency issues.
    
    // Consider returning NULL objects if service is nullptr;
    // Try to avoid if(null) check inside a getter(). Make sure services are
    // initialized at start to null and have null checks inside a register() call.
    
    // Consider limiting accessible scope on systems like NetworkManager to only a
    // few classes. Maybe create a INetwork interface that needs to be implemented
    // by a class to access the network service... or something like that.

	class ServiceLocator
	{
	public:
		// Services need to be instantiated, then registered
		// TODO: Services...
		// Networking, Graphics, Utilities (some type of file managers?),
		// Debug, Memory, Application
		static void RegisterService(eEngineServices serviceType, void* service);

		static void* UnregisterService(eEngineServices serviceType); // TODO: Potentially dangerous!

		static void* GetService(eEngineServices serviceType);
		// TODO: Improve logic and code design
		static eEngineMessage ServicesLoaded(); // determine if all services are loaded

		static void LockServices(bool locking) { m_IsLocked = locking; }

	private:
		static bool m_IsLocked; // TODO: Improve security/error prevention

		static ResourceManager* m_ResourceManager;
		static InputManager* m_InputManager;
        static EventManager* m_EventManager;
        static SceneManager* m_SceneManager;
        static Factory* m_Factory;
        static Editor* m_Editor;
		static PhysicsManager* m_PhysicsManager;
		static MessageManager* m_MessageManager;
		static Renderer* m_Renderer;
        static AudioManager* m_AudioManager;
		static JobManager* m_JobManager;
		static Window* m_Window;
        static NetworkManager* m_NetworkManager;
	};
}

#endif //!_ServiceLocator_H_
