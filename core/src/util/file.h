#pragma once

#include <string>

namespace core { namespace util {
	std::string readFile(const std::string filePath);
	void directoryWatcher(const char *dirpath, int *c);
}}