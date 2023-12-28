#include "Windows.h"

namespace QwerkE {

    std::vector<Window*> Windows::m_Windows;
    unsigned char Windows::m_lastFocusedWindowIndex = 0;

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
        if (windowID >= 0 && windowID < m_Windows.size())
        {
            return m_Windows.at(windowID);
        }
    }

    const Window* Windows::GetLastFocusedWindow()
    {
        if (m_lastFocusedWindowIndex < m_Windows.size())
        {
            return m_Windows.at(m_lastFocusedWindowIndex);
        }
        return nullptr;
    }

}
