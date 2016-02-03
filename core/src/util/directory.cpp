#include "directory.h"

#include "..\logger\log.h"

namespace core {	namespace util {

	DirectoryWatcher::DirectoryWatcher(const char *abspath) {
		handle = CreateFile(abspath,
			FILE_LIST_DIRECTORY | GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			0,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
			0
			);
		o.hEvent = CreateEvent(0, 0, 0, 0);
	}

	DirectoryWatcher::~DirectoryWatcher() {

	}

	bool DirectoryWatcher::updated() {
		ReadDirectoryChangesW(handle,
			&fni,
			sizeof(fni),
			TRUE,
			FILE_NOTIFY_CHANGE_LAST_WRITE,
			&b,
			&o,
			0);
		if (fni.i.Action != 0) {
			LOG(Info, "DirWatch", "Action %d, b: %d, %s", fni.i.Action, b, (char *)fni.i.FileName);
			fni.i.Action = 0;
			return 1;
		}
		return 0;
	}
}}