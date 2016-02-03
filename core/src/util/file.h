#pragma once

#include <string>

namespace core { namespace util {
	std::string readFile(const char *filepath);
	void directoryWatcher(const char *dirpath, int *c);
}}