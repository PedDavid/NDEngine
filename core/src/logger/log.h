#pragma once

#include "logger.h"
#include <sstream>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG_FATAL(message) log_message(core::logger::LogLevel::Fatal, message, __FILENAME__, __LINE__, __FUNCTION__)

#define LOG_ERROR(message) log_message(core::logger::LogLevel::Error, message, __FILENAME__, __LINE__, __FUNCTION__)

#define LOG_WARN(message) log_message(core::logger::LogLevel::Warn, message, __FILENAME__, __LINE__, __FUNCTION__)

#define LOG_INFO(message) log_message(core::logger::LogLevel::Info, message, __FILENAME__, __LINE__, __FUNCTION__)

#define LOG_SUCCESS(message) log_message(core::logger::LogLevel::Success, message, __FILENAME__, __LINE__, __FUNCTION__)

#define GL_CHECK(stmt) log_gl_message(#stmt, __FILENAME__, __LINE__, __FUNCTION__)

namespace core {	namespace logger {

	static void log_message(LogLevel logLevel, const char *message, const char *filename, int line, char *function) {
		logMessage(logLevel, message);
		if (logLevel > core::logger::LogLevel::Info) {
			std::ostringstream sstream;
			sstream << '\t' << "File: " << filename << " | Line: " << line << " | Function: " << function;
			logMessage(logLevel, sstream.str().c_str());
		}
	}

	static void log_gl_message(const char *stmt, const char *file, int line, const char *function) {
		glCheckError(stmt, file, line, function);
	}
}}