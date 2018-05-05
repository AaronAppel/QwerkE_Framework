#ifndef _Debugger_H_
#define _Debugger_H_

#include "../QwerkE_Defines.h"

#ifdef _QDebug
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
