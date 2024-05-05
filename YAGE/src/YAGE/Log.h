#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Yage
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

#define YAGE_ERROR(...) ::Yage::Log::GetCoreLogger()->error(__VA_ARGS__)
#define YAGE_WARN(...) ::Yage::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YAGE_INFO(...) ::Yage::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YAGE_TRACE(...) ::Yage::Log::GetCoreLogger()->trace(__VA_ARGS__)