#ifndef _Debugger_H_
#define _Debugger_H_

#include "../Engine_Defines.h"

#ifdef _QDEBUG
namespace QwerkE
{
    class Debugger
    {
    public:
        Debugger();
        ~Debugger();

        static void ToggleConsole();
        static void SetConsoleVisible(bool visibility);

    private:
        static bool m_ConsoleIsOpen;
    };
}
#endif // !_QDEBUG

#endif // !_Debugger_H_
