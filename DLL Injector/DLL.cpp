#include "DLL.h"

void DLL::inject(HANDLE processHandle)
{
	// Open the DLL
	HANDLE dllHandle = CreateFileA(fullPath, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, nullptr);
	if (dllHandle == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error(win_error_to_string(GetLastError()));
	}
	size_t dllFileSize = GetFileSize(dllHandle, nullptr);

	// Allocate space in the process's memory to store the DLL
	void *baseAddr = VirtualAllocEx(processHandle, nullptr, dllFileSize,
		MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (baseAddr == nullptr)
	{
		throw std::runtime_error(win_error_to_string(GetLastError()));
	}

	// Copy the DLL into the process's memory
	void *dllBuffer = malloc(dllFileSize);
	if (malloc == nullptr)
	{
		throw std::runtime_error("malloc(" + std::to_string(dllFileSize) + ") failed");
	}
	DWORD bytesRead;
	if (!ReadFile(dllHandle, dllBuffer, dllFileSize, &bytesRead, NULL))
	{
		throw std::runtime_error(win_error_to_string(GetLastError()));
	}

	if (!WriteProcessMemory(processHandle, baseAddr, dllBuffer, dllFileSize, nullptr))
	{
		throw std::runtime_error(win_error_to_string(GetLastError()));
	}

	CloseHandle(dllHandle);
}

DLL::DLL(const std::string &path)
{
	if (GetFullPathNameA(path.c_str(), MAX_FULL_PATH_LENGTH, fullPath, nullptr) == 0)
	{
		throw std::runtime_error(win_error_to_string(GetLastError()));
	}
}