#include "Debugger.h"
#include "../../QwerkE_Common/Utilities/PrintFunctions.h"

#ifdef _QDebug
namespace QwerkE
{
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
            ConsolePrint("\nConsole opened!");
        }
        else
        {
            ConsolePrint("\nConsole closed!");
        }
    }

    void Debugger::SetConsoleVisible(bool visibility)
    {
        m_ConsoleIsOpen = visibility;
        if (m_ConsoleIsOpen)
        {
            ConsolePrint("\nConsole opened!");
        }
        else
        {
            ConsolePrint("\nConsole closed!");
        }
    }
}
#endif // !_QDebug