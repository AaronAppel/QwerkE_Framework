#include "Debugger.h"

#ifdef _QDebug
namespace QwerkE {

    bool Debugger::m_ConsoleIsOpen = false;

    Debugger::Debugger()
    {
    }

    Debugger::~Debugger()
    {
    }

    void Debugger::ToggleConsole()
    {
        m_ConsoleIsOpen = !m_ConsoleIsOpen;
        if (m_ConsoleIsOpen)
        {
            LOG_INFO("Console opened");
        }
        else
        {
            LOG_INFO("Console closed");
        }
    }

    void Debugger::SetConsoleVisible(bool visibility)
    {
        m_ConsoleIsOpen = visibility;
        if (m_ConsoleIsOpen)
        {
            LOG_INFO("Console opened");
        }
        else
        {
            LOG_INFO("Console closed");
        }
    }
}
#endif // !_QDebug
