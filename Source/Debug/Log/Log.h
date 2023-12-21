#ifndef _Log_H_
#define _Log_H_

#pragma warning( disable : 26437 )
#pragma warning( disable : 26451 )
#pragma warning( disable : 26495 )
#pragma warning( disable : 26498 )
#pragma warning( disable : 6387 )
#include <spdlog/spdlog.h>
#pragma warning( default : 26437 )
#pragma warning( default : 26451 )
#pragma warning( default : 26495 )
#pragma warning( default : 26498 )
#pragma warning( default : 6387 )

#include "../../Headers/QwerkE_Defines.h"

namespace QwerkE {

    class Log
    {
    public:
        static void Initialize();
        static void Shutdown();

        static void Safe(const char* message...);

    private:
        Log() {}
        ~Log() {}

        static bool m_initialized;
    };

}

// Asserting : https://www.youtube.com/watch?v=DQCkMnMNFBI&ab_channel=Progrematic

// Core log macros
// #TODO Fix spdlog null error exception
#if 1
#define LOG_TRACE(...)      QwerkE::Log::Safe(__VA_ARGS__);
#define LOG_INFO(...)       QwerkE::Log::Safe(__VA_ARGS__);
#define LOG_WARN(...)       QwerkE::Log::Safe(__VA_ARGS__);
#define LOG_ERROR(...)      QwerkE::Log::Safe(__VA_ARGS__);
#define LOG_CRITICAL(...)   QwerkE::Log::Safe(__VA_ARGS__);

// #ifdef _QDebug
#elif _DEBUG
// #define LOG_TRACE(...)    ::QwerkE::LOG_TRACE(__VA_ARGS__) // TODO: Contain spdlog code inside Log.cpp only
// TODO: File and Line info
#define LOG_TRACE(...)      if (spdlog::get(ProjectName) != nullptr) { spdlog::get(ProjectName)->trace(__VA_ARGS__); }
#define LOG_INFO(...)       if (spdlog::get(ProjectName) != nullptr) { spdlog::get(ProjectName)->info(__VA_ARGS__); }
#define LOG_WARN(...)       if (spdlog::get(ProjectName) != nullptr) { spdlog::get(ProjectName)->warn(__VA_ARGS__); }
#define LOG_ERROR(...)      if (spdlog::get(ProjectName) != nullptr) { spdlog::get(ProjectName)->error(__VA_ARGS__); }
#define LOG_CRITICAL(...)   if (spdlog::get(ProjectName) != nullptr) { spdlog::get(ProjectName)->critical(__VA_ARGS__); }

#else
#define LOG_TRACE(...)      (void)0
#define LOG_INFO(...)       (void)0
#define LOG_WARN(...)       (void)0
#define LOG_ERROR(...)      (void)0
#define LOG_CRITICAL(...)   (void)0
#endif // _QDebug

#endif // _Log_H_
