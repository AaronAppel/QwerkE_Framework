#include "Window.h"
#include "../../../QwerkE_Common/Libraries_Include.h"

Window::Window(int windowWidth, int windowHeight, const char* windowTitle) :
	m_Resolution(windowWidth, windowHeight),
	m_WindowTitle(windowTitle)
{
}

Window::~Window()
{
}
