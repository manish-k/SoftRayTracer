#pragma once

#include <string>
#include <spdlog/spdlog.h>

#define LOG_DEBUG(...)    spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...)     spdlog::info(__VA_ARGS__)
#define LOG_WARN(...)     spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...)    spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)
#define LOG_TRACE(...)    spdlog::trace(__VA_ARGS__)

inline void init_logger()
{
    spdlog::set_pattern("%^[%T] [%l] %n: %v%$");
}

inline void log_assert(const std::string& msg)
{
    spdlog::critical("Assertion failed: {}", msg);
}

inline void log_assert()
{
    spdlog::critical("Assertion failed");
}