#include "Window.h"
#include "../../Shared_Generic/Libraries_Include.h"

Window::Window(int windowWidth, int windowHeight, const char* windowTitle) :
    m_Resolution(windowWidth, windowHeight),
    m_WindowTitle(windowTitle)
{
}

Window::~Window()
{
}
