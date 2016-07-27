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

}}