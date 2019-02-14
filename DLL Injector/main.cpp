#include <iostream>
#include <string>
#include <vector>

static void parse_args(int argc, char *argv[], const char **processPath, const char ***dllPaths);

int main(int argc, char *argv[])
{
	// A list of paths to DLL's to inject into the process
	std::vector<std::string> dllPaths;

	// The path of the process to inject the DLL's into
	std::string processPath;

	parse_args(argc, argv, processPath, dllPaths);

	return 0;
}

static void parse_args(int argc, char *argv[], std::string &processPath,
	std::vector<std::string> &dllPaths)
{
	if (argc < 3)
	{
		std::cerr << "Usage: injector process-path dll-path..." << std::endl;
		exit(EXIT_FAILURE);
	}

	processPath = argv[1];
	for (size_t i = 3; i < argc; ++i)
	{
		dllPaths.emplace_back(argv[i]);
	}
}
