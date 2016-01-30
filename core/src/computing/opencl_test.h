#pragma once

#include <CL\cl2.hpp>
#include <iostream>

inline void checkErr(cl_int err, const char *name) {
	if (err != CL_SUCCESS) {
		std::cerr << "ERROR: " << name << "(" << err << ")" << std::endl;
		exit(EXIT_FAILURE);
	}
}