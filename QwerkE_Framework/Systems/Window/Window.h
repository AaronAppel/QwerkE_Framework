#ifndef _Window_H_
#define _Window_H_

#include "../../../QwerkE_Common/DataTypes/Vector.h"
#include "../../../QwerkE_Common/Math_Includes.h"

struct GLFWwindow;

// TODO: Create windows for different libraries
class Window // abstract
{
public:
	Window(int windowWidth, int windowHeight, const char* windowTitle);
	virtual ~Window();

	void SetResolution(vec2 resolution) { m_Resolution = resolution; }
	vec2 GetResolution() { return m_Resolution; }

	virtual void* GetContext() = 0; // TODO: Remove

	virtual void SwapBuffers() = 0;

	void SetClosing(bool closing) { m_IsClosing = closing; };
	bool IsClosing() { return m_IsClosing; };

protected:
	// TODO: Expand interface. Remember to be generic for all libraries.
	vec2 m_Resolution = vec2(16, 9);
	vec2 m_ScreenSize = m_Resolution * 0.5f;
	bool m_IsFocused = false;
	bool m_IsClosing = false;
	const char* m_WindowTitle = "null";
};

#endif // !_Window_H_
