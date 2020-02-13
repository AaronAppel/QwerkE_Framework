#ifndef _Debugger_H_
#define _Debugger_H_

#include "../../Headers/QwerkE_Defines.h"

// #include <fstream> // vsnprintf_s
// #include <cstdarg> // va_start, va_end
// #include <debugapi.h> // OuputDebugStringA(buffer)
// #define MAX_MESSAGE 1024

#ifdef _QDebug

// Error stack like OpenGL and OpenAL for pushing errors.
// User can manipulate stack to get errors.

namespace QwerkE {

    // TODO: How should these functions be made static and global, but in the debug namespace/class
    // TODO: These functions inject dependencies into files. Look at a good way of minimizing coupling
    // TODO: Move the functionality to a Logger class
    // TODO: Consider creating function pointers for outputting. Different settings could print to different
    //     places using the currently assigned function pointer. Examples: OutputToConsole, OutputToVS, OutputToAll, etc

    // #define WARN(message) LogWarning(message, __FILE__, __LINE__)
    //static void LogError(const char* filePath, int line, const char* message, ...)
    //{
    //    OutputPrint("\n%s(%i): Q error: %s", filePath, line, message);
    //    // ConsolePrint(message);
    //}
    //static void LogWarning(const char* filePath, int line, const char* message, ...)
    //{
    //    // char buffer[MAX_MESSAGE];
    //    // va_list arg;
    //    // va_start(arg, message);
    //    // vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, message, arg);
    //    // va_end(arg);

    //    // buffer[MAX_MESSAGE - 1] = 0; // vsnprintf_s might do this, but docs are unclear

    //    OutputPrint("\n%s(%i): Q warning: %s", filePath, line, message);
    //    ConsolePrint(message);
    //}
    //static void LogOutput(const char* filePath, int line, const char* message, ...)
    //{
    //    OutputPrint("\n%s(%i): Q output: %s", filePath, line, message);
    //    ConsolePrint(message);
    //}

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
namespace QwerkE { // If _QDebug is undefined, this prevents missing symbol errors
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
