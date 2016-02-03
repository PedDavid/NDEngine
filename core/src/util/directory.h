#pragma once

#include <windows.h>

namespace core {	namespace util {
	class DirectoryWatcher {
		private:
		union {
			FILE_NOTIFY_INFORMATION i;
			char d[sizeof(FILE_NOTIFY_INFORMATION) + MAX_PATH];
		} fni;

		OVERLAPPED o;
		HANDLE handle;
		DWORD b;

		public:
		DirectoryWatcher(const char *abspath);
		~DirectoryWatcher();

		bool updated();
	};
}}