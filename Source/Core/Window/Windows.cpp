#include "Windows.h"

namespace QwerkE {

    class Window;

    std::vector<Window*> Windows::m_Windows;

    void Windows::Initialize()
    {

    }

    void Windows::Shutdown()
    {
       /* int size = m_Windows.size();
        for (int i = 0; i < size; i++)
        {
            delete m_Windows.at(i);
        }*/
    }

    void Windows::AddWindow(Window* window)
    {
        m_Windows.push_back(window);
    }

    Window* Windows::GetWindow(int windowID)
    {
        return m_Windows.at(windowID);
    }

}
