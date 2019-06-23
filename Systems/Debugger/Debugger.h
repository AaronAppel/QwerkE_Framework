#ifndef _Debugger_H_
#define _Debugger_H_

#include "../../Headers/QwerkE_Defines.h"
#include "../../QwerkE_Common/Utilities/PrintFunctions.h"

#ifdef _QDebug

// Error stack like OpenGL and OpenAL for pushing errors.
// User can manipulate stack to get errors.

namespace QwerkE
{
    // TODO: How should these functions be made static and global, but in the debug namespace/class
    // TODO: These functions inject dependencies into files. Look at a good way of minimizing coupling
    // TODO: Move the functionality to a Logger class
    static void LogError(const char* filePath, int line, const char* message, ...)
    {
        OutputPrint("\n%s(%i): Q error: %s", filePath, line, message);
    }
    static void LogWarning(const char* filePath, int line, const char* message, ...)
    {
        OutputPrint("\n%s(%i): Q warning: %s", filePath, line, message);
    }

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
#else
namespace QwerkE // If #if cannot be used somewhere, this prevents missing symbols
{
    static void LogError(const char* filePath, int line, const char* message, ...)
    {
    }
    static void LogWarning(const char* filePath, int line, const char* message, ...)
    {
    }
}
#endif // !_QDEBUG

#endif // !_Debugger_H_
