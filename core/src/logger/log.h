#pragma once

#include "logger.h"
#include <sstream>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG(level, channel, message) core::logger::log_message(core::logger::LogLevel::level, \
			"[" channel "] ", message, __FILENAME__, __LINE__, __FUNCTION__)

#define GL_LOG(stmt) \
		stmt; \
		core::logger::log_gl_message(#stmt, __FILENAME__, __LINE__, __FUNCTION__)

namespace core {	namespace logger {

	static void log_message(LogLevel logLevel, const char *channel, const char *message, const char *filename, int line, char *function) {
		std::ostringstream sstream;
		sstream << channel << message << std::ends;
		logMessage(logLevel, sstream.str().c_str());
		if (logLevel > Info) {
			/*	Doesn't clear, only resets put pointer, no problems yet using C strings and std::ends(\0)	*/
			sstream.seekp(0);
			sstream << '\t' << "File: " << filename << " | Line: " << line << " | Function: " << function << std::ends;
			logMessage(logLevel, sstream.str().c_str());
		}
	}

	static void log_gl_message(const char *stmt, const char *file, int line, const char *function) {
		glCheckError(stmt, file, line, function);
	}
}}