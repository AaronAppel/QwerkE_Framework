#include "Window.h"
#include "../../Headers/Libraries_Include.h"

namespace QwerkE {

    Window::Window(int windowWidth, int windowHeight, const char* windowTitle)
        : m_Resolution(windowWidth, windowHeight), m_WindowTitle(windowTitle)
    {
    }

    void Window::SetResolution(vec2 resolution)
    {
        m_Resolution = resolution;
        m_AspectRatio = vec2(16.f, 9.0f); // #TODO Calculate aspect ratio
    }
}
