#ifndef _Framework_H_
#define _Framework_H_

// Try to keep this class properly abstracted so it
// can perform on multiple platforms without needing
// inherited subclasses.

#include "Headers/QwerkE_Enums.h" // eEngineMessage

#include <string>

// If only 1 engine should exist at a time then it could be wrapped in
// the QwerkE namespace and have static functions like a singleton or
// service. Or just find another way to prevent multiple instances
// while offering a nice interface.

struct GLFWwindow;

namespace QwerkE {
    class Editor;
    class SceneManager;
    class Window;

	// TODO: What is this namespace useful for besides separating the engine run method
	namespace Framework
	{
		eEngineMessage Startup();
		eEngineMessage Startup(std::string configFilePath, std::uint_fast8_t flags);
		eEngineMessage TearDown();

		void Run();
		void Stop();

		void NewFrame();
		void PollInput();
		void Update(double deltatime);
		void Draw();
		void EndFrame();

		bool StillRunning();
	}
}

#endif // !_Framework_H_
