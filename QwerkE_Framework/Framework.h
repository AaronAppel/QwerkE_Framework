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
// service. Or just find a nother way to prevent multiple instances
// while offering a nice interface.

class Framework // TODO: Might not need this class
{
public: // External API
	Framework();
	~Framework();

	eEngineMessage Startup();
	eEngineMessage TearDown();

	void Run();

	void NewFrame();
	void Input();
	void Update(double deltatime);
	void Draw();

	bool StillRunning() { return m_IsRunning; };

private:
    Window* m_Window = nullptr;
	bool m_IsRunning = false;
	SceneManager* m_SceneManager = nullptr;
    Editor* m_Editor = nullptr;
};

#endif // !_Framework_H_
