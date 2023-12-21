#include "Log.h"

#include <stdio.h> // fprintf
#include <memory> // std::make_shared
#include <corecrt_wstdio.h> // stderr

#include <spdlog/sinks/stdout_color_sinks.h>

namespace QwerkE {

    bool Log::m_initialized = false;

    void Log::Initialize()
    {
        if (!m_initialized)
        {
            // https://github.com/gabime/spdlog
            // #TODO Look at "Logger with multi sinks - each with a different format and log level" example
            // to setup different kinds of logging for different levels of logs

            auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            consoleSink->set_pattern("%^[%T] %n: %v%$");

            std::vector<spdlog::sink_ptr> sinks{consoleSink};
            auto logger = std::make_shared<spdlog::logger>(ProjectName, sinks.begin(), sinks.end());
            logger->set_level(spdlog::level::trace);
            logger->flush_on(spdlog::level::trace);
            spdlog::register_logger(logger);

            m_initialized = true;
        }
        else
        {
            LOG_ERROR("Log is already initialized!");
        }
    }

    void Log::Shutdown()
    {
        if (m_initialized)
        {
            spdlog::shutdown();
            m_initialized = false;
        }
    }

    void Log::Safe(const char* message...)
    {
        fprintf(stderr, message);
    }

}
