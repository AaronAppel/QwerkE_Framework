#ifndef _Framework_H_
#define _Framework_H_

// Try to keep this class properly abstracted so it
// can perform on multiple platforms without needing
// inherited subclasses.

#include "QwerkE_Enums.h" // eEngineMessage

struct GLFWwindow;
class Editor;
class SceneManager;
class Window;

// If only 1 engine should exist at a time then it could be wrapped in
// the QwerkE namespace and have static functions like a singleton or
// service. Or just find another way to prevent multiple instances
// while offering a nice interface.

namespace QwerkE
{
	namespace Framework
	{
		eEngineMessage Startup();
		eEngineMessage TearDown();

		void Run();
		void Stop();

		void NewFrame();
		void Input();
		void Update(double deltatime);
		void Draw();

		bool StillRunning();
	}
}

#endif // !_Framework_H_
