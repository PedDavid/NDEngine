#pragma once

#include "logger.h"

#include <cstring>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG(level, channel, message, ...) core::logger::log_message(core::logger::LogLevel::level,  \
			"[%s] " message, __FILENAME__, __LINE__, __FUNCTION__, channel, __VA_ARGS__)

#define GL_LOG(stmt) \
		stmt; \
		core::logger::log_gl_message(#stmt, __FILENAME__, __LINE__, __FUNCTION__)

#define ASSERT(x)									\
		do{											\
			if (!(x)) {								\
				LOG(Fatal, "Assertion", "%s", #x);	\
				core::logger::ask_user();			\
			}										\
		} while (0)

namespace core {	namespace logger {

	void log_message(LogLevel logLevel, const char *message, const char *filename, int line, char *function, ...);

	void ask_user();

	void log_gl_message(const char *stmt, const char *file, int line, const char *function);
}}