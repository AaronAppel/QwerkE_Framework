#include "glfw_Window.h"
#include "CallbackFunctions.h"
#include "WindowManager.h"
#include "../ServiceLocator.h"
#include "../../../QwerkE_Common/Libraries/imgui/imgui_impl_glfw_gl3.h"

void close_callback(GLFWwindow* window);

glfw_Window::glfw_Window(int windowWidth, int windowHeight, const char* windowTitle) : Window(windowWidth, windowHeight, windowTitle)
{
	m_Window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	assert(m_Window);
	glfwSwapInterval(0); // TODO: Add VSynch control and toggling
	glfwMakeContextCurrent(m_Window);
	glfwFocusWindow(m_Window);
	ImGui_ImplGlfwGL3_Init(m_Window, false);
	m_IsFocused = true;
	SetupCallbacks(m_Window); // TODO: Window won't respond to clicking corner 'x'... sometimes?
	glfwSetWindowCloseCallback(m_Window, close_callback);
}

glfw_Window::~glfw_Window()
{
	glfwWindowShouldClose(m_Window); // May have issues waiting so long to close m_Window. Try to call Close() when it is requested
	glfwDestroyWindow(m_Window);
}

void close_callback(GLFWwindow* window)
{
	WindowManager* winMan = (WindowManager*)QwerkE::ServiceLocator::GetService(eEngineServices::WindowManager);
	glfw_Window* glfw_window = (glfw_Window*)winMan->GetWindow(0);
	glfw_window->SetClosing(true);
}