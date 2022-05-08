#pragma once

#ifdef APPLICATION_USE_SPDLOG
#include <spdlog/spdlog.h>

template<typename FormatString, typename... Args>
inline void LOG_INFO(const FormatString& fmt, Args&&...args) {
	spdlog::info(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
inline void LOG_ERROR(const FormatString& fmt, Args&&...args) {
	spdlog::error(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
inline void LOG_WARNING(const FormatString& fmt, Args&&...args) {
	spdlog::warn(fmt, std::forward<Args>(args)...);
}
#else
#define LOG_INFO(fmt, ...)
#define LOG_ERROR(fmt, ...)
#define LOG_WARNING(fmt, ...)
#endif

