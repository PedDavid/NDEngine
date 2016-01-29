#include "logger.h"

#include <stdio.h>

#ifdef _WIN32
#	include <Windows.h>
#endif

namespace core {	namespace logger {

#ifdef _WIN32
	static HANDLE m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	static LogLevel m_logLevel = Success;

	void logMessage(LogLevel logLevel, const char *message) {
#ifdef _WIN32
		if (logLevel >= m_logLevel) {
			switch (logLevel) {
			case Fatal:
				SetConsoleTextAttribute(m_consoleHandle, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case Error:
				SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			case Warn:
				SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case Success:
				SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			}
			printf("%s\n", message);
			SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}
#endif
	}

	void setLogLevel(LogLevel logLevel) {
		m_logLevel = logLevel;
	}
}}