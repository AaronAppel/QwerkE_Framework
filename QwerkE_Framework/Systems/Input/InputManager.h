#ifndef _InputManager_H_
#define _InputManager_H_

#include "QwerKE_eKeys.h"
#include "../../QwerkE_Defines.h"
#include "../../QwerkE_Platform.h"
#include "../../../QwerkE_Common/Libraries_Include.h"

class Controller;

static int g_NumPlayers = 1;
const char QWERKE_ONE_FRAME_MAX_INPUT = 12; // no more than QWERKE_ONE_FRAME_MAX_INPUT key events per frame. Is that enough?

// TODO: Create GLFW callback functions to link for GLFW projects
// TODO: Add input functions for non-GLFW projects
// TODO: Add input query functions such as WNDPROC for getting input and CheckInput() game loop function.
// TODO: Think of abstracting class for different libraries and platforms
// TODO: Key event callback registration. Should that be handled by the event system? probably...
class InputManager
{
public:
	InputManager();
	~InputManager();

	// Controller* GetController(int controllerIndex) { return m_Controllers[controllerIndex]; };

	void NewFrame(); // reset frame input buffer

	// TODO: ProcessMouseScroll
	void ProcessMouseMove(vec2 position);
	void ProcessMouseMove(float x, float y);
	void ProcessMouseClick(eKeys key, eKeyState state);

	void ProcessKeyEvent(eKeys key, eKeyState state);

	eKeys GetKeyCode(int key); // TOOD: Better way for public access to m_KeyCode?

	// check if keyIsDown
	vec2 GetMouseDragDelta();
	bool GetIsKeyDown(eKeys key) { return m_KeyStates[key];	}

	// check if keyIsDown this frame
	bool FrameKeyAction(eKeys key, eKeyState state);

private:
	// mouse
	vec2 m_MousePos = vec2(0,0); // position change from last frame
	vec2 m_MouseDelta = vec2(0,0);
	vec2 m_MouseDragStart = vec2(0,0);
	bool m_DragReset = false;

	// keyboard
	unsigned short* m_KeyCodex; // [eKeys_MAX] = { 0 }; // initialize to 0
	bool m_KeyStates[eKeys_MAX] = { false }; // initialize to false

	// frame by frame input tracking
	bool m_OneFrameBuffersAreDirty = true; // wipe at init
	unsigned short m_OneFrameKeyBuffer[QWERKE_ONE_FRAME_MAX_INPUT];
	bool m_OneFrameValueBuffer[QWERKE_ONE_FRAME_MAX_INPUT] = { false };

	// Setup system key maps
	void AssignGLFWKeys();
	void AssignWin32Keys();
	void AssignMacKeys() {} // TODO:
	void AssignLinuxKeys() {} // TODO:

#ifdef _glfw3_h_
	void AssignSystemKeys()
	{
		// TODO: Reduce the size of array
		m_KeyCodex = new unsigned short[GLFW_KEY_LAST]; // number of recognized glfw keys
		AssignGLFWKeys();
	}
#elif _QWin32
	void AssignSystemKeys()
	{
		AssignWin32Keys();
	}
#elif _QMac32 // 64
	void AssignSystemKeys()
	{
		AssignMacKeys();
	}
#elif _QMac32 // 64
	void AssignSystemKeys()
	{
		AssignLinuxKeys();
	}
#else
	// Other Platforms or default layout
	// TODO: Map ascii default layout
	// https://www.asciitable.com/index/asciifull.gif
#error "InputManager(): No platform defined! Cannot assign keys!"
#endif
	// Controller* m_Controllers[g_NumPlayers];
	void SetupControllers();
};

#endif // !_InputManager_H_