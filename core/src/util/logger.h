#pragma once

namespace util {

	enum LogLevel {
		Fatal = 0x01, Error = 0x03, Warn = 0x07, Info = 0x0F, Success = 0x1F
	};

	void log_message(LogLevel logLevel, const char *message);
}