#pragma once

#include "logger.h"
#include <sstream>
#include <cstdarg>
#include <cstdlib>
#include <iostream>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG(level, channel, message, ...) core::logger::log_message(core::logger::LogLevel::level,  \
			"[%s] " message, __FILENAME__, __LINE__, __FUNCTION__, channel, ##__VA_ARGS__)

#define GL_LOG(stmt) \
		stmt; \
		core::logger::log_gl_message(#stmt, __FILENAME__, __LINE__, __FUNCTION__)

namespace core {	namespace logger {

	static void log_message(LogLevel logLevel, const char *message, const char *filename, int line, char *function, ...) {
		char buffer[1024];
		va_list args;
		va_start(args, function);
		vsnprintf(buffer, 1024, message, args);
		logMessage(logLevel, buffer);
		va_end(args);
		if (logLevel > -1) {
			sprintf_s(buffer, 1024, "\tFile: %s | Line: %d | Function: %s", filename, line, function);
			logMessage(logLevel, buffer);
		}
	}

	static void log_gl_message(const char *stmt, const char *file, int line, const char *function) {
		glCheckError(stmt, file, line, function);
	}
}}