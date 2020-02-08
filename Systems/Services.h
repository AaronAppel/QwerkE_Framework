#ifndef _Services_H_
#define _Services_H_

// Class Services provides global access for systems
// necessary throughout the code such as memory management,
// audio playback, input, etc.
// To add a system add it to RegisterService(), UnregisterService,
// GetService(), and ServicesLoaded().

namespace QwerkE {

	enum class eEngineMessage : std::uint8_t;
	enum class eEngineServices : std::uint8_t;

    class EventManager;
    class Scenes;
    class Factory;
    class Physics;
    class MessageManager;
    class Audio;
    class Window;
    class Network;
    class DataManager;

	// TODO: Improve service accessing
	// Think of toggling register/unregister
    // Should code ask for system*s to keep or is this dangerous because
    //  a system could change during runtime?
    // Consider inline ing service locator functions for runtime efficiency

    // TODO: To avoid dependencies redesign how services are registered/unregistered
    // for order dependency issues.

    // TODO: Consider returning NULL objects if service is nullptr like NullAudioManager() or
	// something more elegant.

    // TODO: Try to avoid if(null) check inside a getter(). Make sure services are
    // initialized at start to null and have null checks inside a register() call.

    // TODO: Consider limiting accessible scope on systems like Network to only a
    // few classes. Maybe create a INetwork interface that needs to be implemented
    // by a class to access the network service... or something like that.

	// TODO: May want to create a ServicePtr<Resource*> that points to another pointer
	// so that services can be easily swapped. This ServicePtr can also act
	// as a smart pointer to reference count and ensure deletion and global pointer
	// re-assignment if needed. Also return these ServicePtrs as const to avoid altering.
	// Note: By abstracting to raw pointer value order dependency becomes less important
	// during initialization unless the services really rely on each other, rather than
	// just storing convenience pointers.

	class Services
	{
	public:

		// Services need to be instantiated else where, then registered
		// TODO: Services...
		// Networking, Graphics, Utilities (some type of file managers?),
		// Debug, Memory, Application
		static void RegisterService(eEngineServices serviceType, void* service);

		static void* UnregisterService(eEngineServices serviceType); // TODO: Potentially dangerous!

		static void* GetService(eEngineServices serviceType);
		// TODO: Improve logic and code design
		static eEngineMessage ServicesLoaded(); // Determine if all services are loaded

		static void LockServices(bool locking) { m_IsLocked = locking; }

    private:

        Services();
        ~Services();

		static bool m_IsLocked; // TODO: Improve security/error prevention

        static EventManager* m_EventManager;
		static Physics* m_Physics;
		static MessageManager* m_MessageManager;
        static Audio* m_AudioManager;
		static Window* m_Window;
        static Network* m_NetworkManager;
		static DataManager* m_DataManager;
	};

}
#endif // _Services_H_
