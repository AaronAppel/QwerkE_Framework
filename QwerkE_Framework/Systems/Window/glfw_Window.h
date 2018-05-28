#ifndef _glfw_Window_H_
#define _glfw_Window_H_

#include "Window.h"
#include "../../../QwerkE_Common/Libraries/glfw/GLFW/glfw3.h"

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
