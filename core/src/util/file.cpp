#include "file.h"

#include "..\logger\log.h"

#include <Windows.h>
#include <fstream>

#include <thread>

namespace core {	namespace util {

	std::string readFile(const char *filepath) {
		std::ifstream in(filepath, std::ifstream::in | std::ios::binary);
		ASSERT(in);
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize((size_t)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}

	OVERLAPPED o = { 0 };
	union {
		FILE_NOTIFY_INFORMATION i;
		char d[sizeof(FILE_NOTIFY_INFORMATION) + MAX_PATH];
	} fni;

	static void watch(HANDLE handle, int *c);

	void directoryWatcher(const char *dirpath, int *c) {
		HANDLE hDirectory = CreateFile(dirpath,
			FILE_LIST_DIRECTORY | GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			0,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
			0
			);
		o.hEvent = CreateEvent(0, 0, 0, 0);
		std::thread f(watch, hDirectory, c);
		f.detach();
	}

	static void watch(HANDLE handle, int *c) {
		DWORD b;
		while (true) {
			ReadDirectoryChangesW(handle,
				&fni,
				sizeof(fni),
				TRUE,
				FILE_NOTIFY_CHANGE_LAST_WRITE,
				&b,
				&o,
				0);
			if (fni.i.Action != 0) {
				wprintf(L"action %d, b: %d, %s\n", fni.i.Action, b, fni.i.FileName);
				fni.i.Action = 0;
				*c = 1;
			}
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}

	}
}}