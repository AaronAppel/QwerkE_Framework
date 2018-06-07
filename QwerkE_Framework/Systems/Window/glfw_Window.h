#ifndef _glfw_Window_H_
#define _glfw_Window_H_

#include "Window.h"
#include "../../../QwerkE_Common/Libraries/glfw/GLFW/glfw3.h"

// TODO: Extend window to handle more info such as in the link below
// http://www.glfw.org/docs/latest/group__native.html

// TODO: Look at handling raw input for multiple mice as below
// https://hannespfeiffer.net/2016/07/07/how-to-use-multiple-mice-with-glfw/

class glfw_Window : public Window
{
public:
	glfw_Window(int windowWidth, int windowHeight, const char* windowTitle);
	~glfw_Window();

	void* GetContext() { return m_Window; }; // TODO: Remove

	void SwapBuffers() { glfwSwapBuffers(m_Window); };

private:
	// TODO: glfwSetClipboardString();
	// TODO: glfwSetGamma()
	// TODO: glfwSetInputMode()
	// TODO: glfwSetWindowAspectRatio()
	// TODO: glfwSetWindowIcon()
	// TODO: glfwSetWindowMonitor()
	// TODO: glfwSetMonitorCallback()
	// TODO: glfwSetWindowTitle()
	// TODO: glfwSetWindowSizeLimits()
	// TODO: glfwSetWindowUserPointer()
	GLFWwindow * m_Window = nullptr;
};

#endif // !_glfw_Window_H_
