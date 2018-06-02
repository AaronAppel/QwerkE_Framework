#ifndef _OpenGLManager_H_
#define _OpenGLManager_H_

// graphics
// #define Wind_CCW 1 // For invert faces
#include "../../QwerkE_Common/Math_Includes.h"

// TODO: Rip these functions out and put them in a new opengl_window class that extends the Window class
class OpenGLManager
{
public:
	OpenGLManager();
	~OpenGLManager();

	void Init();
	void ResetGLState();
	void ViewPortSize(int x, int y, int width, int height);
	void ClearScreen();
	void SetZBufferLock(bool lock);
	void SetVSynchON(bool VSynchIsON) { m_VSync = VSynchIsON; };  // TODO: Handle VSynch Toggling

	void SetClearColor(vec4 color) { m_ClearColor = color; };

private:
	vec4 m_ClearColor = vec4(0.2f, 0.3f, 0.4f, 1);

	bool m_DepthTestingOn = true;
	bool m_BackfaceCullingOn = true;
	bool m_BlendingOn = true;
    bool m_VSync = true; // TODO: Handle VSync Toggling
};


#endif // !_OpenGLManager_H_
