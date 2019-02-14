#pragma once

#include <winnt.h>
#include <fileapi.h>
#include <cstdlib>
#include <iostream>
#include <exception>

#include "utils.h"

class DLL
{
public:
	void inject(HANDLE process);

	DLL(const std::string &path);

private:
	static const size_t MAX_FULL_PATH_LENGTH = 1024;

	char fullPath[MAX_FULL_PATH_LENGTH];
	size_t size;
};

