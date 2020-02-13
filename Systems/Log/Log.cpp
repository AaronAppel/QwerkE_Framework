#include "Log.h"
#include "Utilities/PrintFunctions.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace QwerkE {

    std::shared_ptr<spdlog::logger> Log::s_SpdInstance = nullptr;

    void Log::Initialize()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_SpdInstance = spdlog::stderr_color_mt("QwerkE");
        s_SpdInstance->set_level(spdlog::level::trace);
    }

    void Log::Shutdown()
    {
        spdlog::shutdown();
    }

    void Log::Safe(const char* message)
    {
        ConsolePrint(message);
    }

    void Log::Trace(const std::string& message)
    {
        s_SpdInstance->trace(message);
    }

    void Log::Info(const std::string& message)
    {
        s_SpdInstance->info(message);
    }

    void Log::Warn(const std::string& message)
    {
        s_SpdInstance->warn(message);
    }

    void Log::Error(const std::string& message)
    {
        s_SpdInstance->error(message);
    }

    void Log::Critical(const std::string& message)
    {
        s_SpdInstance->critical(message);
    }

}
