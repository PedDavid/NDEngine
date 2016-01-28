#pragma once

#include "logger.h"
#include <sstream>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG_FATAL(message) m_log_message(util::LogLevel::Fatal, message, __FILENAME__, __LINE__)

#define LOG_ERROR(message) m_log_message(util::LogLevel::Error, message, __FILENAME__, __LINE__)

#define LOG_WARN(message) m_log_message(util::LogLevel::Warn, message, __FILENAME__, __LINE__)

#define LOG_INFO(message) m_log_message(util::LogLevel::Info, message, __FILENAME__, __LINE__)

#define LOG_SUCCESS(message) m_log_message(util::LogLevel::Success, message, __FILENAME__, __LINE__)

static void m_log_message(util::LogLevel level, const char *message, const char *filename, int line) {
	log_message(level, message);
	if (level & util::LogLevel::Info) {
		std::ostringstream sstream;
		sstream << '\t' << "File: " << filename << " | Line: " << line;
		log_message(level, sstream.str().c_str());
	}
}