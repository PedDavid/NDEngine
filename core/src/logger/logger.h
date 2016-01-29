#pragma once

namespace core {	namespace logger {
	enum LogLevel {
		Fatal = 4, Error = 3, Warn = 2, Info = 1, Success = 0
	};

	void logMessage(LogLevel logLevel, const char *message);
	void setLogLevel(LogLevel logLevel);
	void glCheckError(const char *stmt, const char *file, int line, const char *funtion);
}}