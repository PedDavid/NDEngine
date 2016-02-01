#pragma once

#include "logger.h"
#include <sstream>
#include <cstdarg>
#include <cstdlib>
#include <iostream>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG(level, channel, message, ...) core::logger::log_message(core::logger::LogLevel::level, \
			"[%s] " message "\0", __FILENAME__, __LINE__, __FUNCTION__, channel, ##__VA_ARGS__)

#define GL_LOG(stmt) \
		stmt; \
		core::logger::log_gl_message(#stmt, __FILENAME__, __LINE__, __FUNCTION__)

namespace core {	namespace logger {

	static void log_message(LogLevel logLevel, const char *message, const char *filename, int line, char *function, const char *channel, ...) {
		char buffer[1024];
		va_list args;
		va_start(args, function);
		vsprintf_s(buffer, 1024, message, args);
		va_end(args);
		logMessage(logLevel, buffer);
		if (logLevel > -1) {
			std::ostringstream sstream;
			sstream << '\t' << "File: " << filename << " | Line: " << line << " | Function: " << function << std::ends;
			logMessage(logLevel, sstream.str().c_str());
		}
	}

	static void log_gl_message(const char *stmt, const char *file, int line, const char *function) {
		glCheckError(stmt, file, line, function);
	}
}}