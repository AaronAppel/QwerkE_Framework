#ifndef _Log_H_
#define _Log_H_

#include <memory>

#pragma warning( disable : 26437 )
#pragma warning( disable : 26451 )
#pragma warning( disable : 26495 )
#pragma warning( disable : 26498 )
#pragma warning( disable : 6387 )
#include <spdlog/spdlog.h>
#pragma warning( enable : 26437 )
#pragma warning( enable : 26451 )
#pragma warning( enable : 26495 )
#pragma warning( enable : 26498 )
#pragma warning( enable : 6387 )

namespace QwerkE {

    class Log
    {
    public:
        static void Initialize();
        static void Shutdown();

        static std::shared_ptr<spdlog::logger>& Get() { return s_SpdInstance; }

        static void Safe(const char* message);

        static void Trace(const std::string& message);
        static void Info(const std::string& message);
        static void Warn(const std::string& message);
        static void Error(const std::string& message);
        static void Critical(const std::string& message);

        // TODO: Getters for log buffers (setup, memory, etc)

    private:
        Log() {}
        ~Log() {}

        static std::shared_ptr<spdlog::logger> s_SpdInstance;
    };

}

// Core log macros
#ifdef _QDebug
// #define LOG_TRACE(...)    ::QwerkE::Log::Trace(__VA_ARGS__) // TODO: Contain spdlog code inside Log.cpp only
// TODO: File and Line info
#define LOG_TRACE(...)    ::QwerkE::Log::Get()->trace(__VA_ARGS__)
#define LOG_INFO(...)     ::QwerkE::Log::Get()->info(__VA_ARGS__) // Name Collision
#define LOG_WARN(...)     ::QwerkE::Log::Get()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::QwerkE::Log::Get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::QwerkE::Log::Get()->critical(__VA_ARGS__)

#else
#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)
#endif // _QDebug

#endif // _Log_H_
