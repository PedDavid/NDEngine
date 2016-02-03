#include "log.h"

#include <cstdarg>
#include <iostream>

namespace core {	namespace logger {
	void log_message(LogLevel logLevel, const char *message, const char *filename, int line, char *function, ...) {
		char buffer[1024];
		va_list args;
		va_start(args, function);
		vsnprintf(buffer, 1024, message, args);
		logMessage(logLevel, buffer);
		va_end(args);
		if (logLevel > Warn) {
			sprintf_s(buffer, 1024, "\tFile: %s | Line: %d | Function: %s", filename, line, function);
			logMessage(logLevel, buffer);
		}
	}

	void AskUser() {
		printf("(I)gnore, (B)reak\n");
		char option;
		std::cin >> option;
		switch (option) {
			case 'I':
			case 'i':
				return;
			default:
				__debugbreak();
		}
	}

	void log_gl_message(const char *stmt, const char *file, int line, const char *function) {
		glCheckError(stmt, file, line, function);
	}
}}