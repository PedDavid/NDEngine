#include "logger.h"
#include <glew.h>

#include <stdio.h>
#include <sstream>

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
		FILE *ostream = stdout;
		if (logLevel >= m_logLevel) {
			switch (logLevel) {
			case Fatal:
				SetConsoleTextAttribute(m_consoleHandle, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				ostream = stderr;
				break;
			case Error:
				SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				ostream = stderr;
				break;
			case Warn:
				SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case Info:
				break;
			case Success:
				SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			}
			fprintf(ostream, "%s\n", message);
			/* Set default console settings	*/
			SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}
#endif
	}

	void setLogLevel(LogLevel logLevel) {
		m_logLevel = logLevel;
	}

	void glCheckError(const char *stmt, const char *file, int line, const char *function) {
		GLenum err = glGetError();

		while (err != GL_NO_ERROR) {
			std::string error;
			switch (err) {
				case GL_INVALID_ENUM:					error = "INVALID ENUM";						break;
				case GL_INVALID_VALUE:					error = "INVALID VALUE";					break;
				case GL_INVALID_OPERATION:				error = "INVALID OPERATION";				break;
				case GL_STACK_OVERFLOW:					error = "STACK OVERFLOW";					break;
				case GL_STACK_UNDERFLOW:				error = "STACK UNDEFLOW";					break;
				case GL_OUT_OF_MEMORY:					error = "OUT OF MEMORY";					break;
				case GL_CONTEXT_LOST:					error = "CONTEXT LOST";						break;
				case GL_TABLE_TOO_LARGE:				error = "TABLE TO LARGE";					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:	error = "INVALID FRAMEBUFFER OPERATION";	break;
				default:								error = "UNKNOWN ERROR";					break;
			}
			std::ostringstream sstream;
			sstream << "[OpenGL] " << error << " " << err << " | Call: " << stmt <<
				"\n\tFile: " << file << " | Line: " << std::to_string(line) << " | Function: " << function;
			logMessage(Error, sstream.str().c_str());
			err = glGetError();
		}
	}
}}