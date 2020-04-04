#include "ProgramArgs.h"

bool ArgumentExists(unsigned  int argc, char** argv, const char* argumentString)
{
	for (size_t i = 0; i < argc; i++)
		if (strcmp(argv[i], argumentString) == 0)
		{
			return true;
		}
	return false;
}

std::map<const char*, const char*> ArgumentKeyValuePairs(unsigned int argc, char** argv)
{
	std::map<const char*, const char*> pairs; // TODO: Avoid creating map, then returning a copy. Take in a map by reference?
	for (size_t i = 0; i < argc - 1; ++i)
		if (argv[i][0] == '-')
		{
			if (argv[i + 1])
			{
				pairs.insert(std::pair<const char*, const char*>(argv[i], argv[i + 1]));
				++i;
			}
		}
	return pairs;
}