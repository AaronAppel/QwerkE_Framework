#pragma once

#include <map>

bool ArgumentExists(unsigned int argc, char** argv, const char* argumentString);
std::map<const char*, const char*> ArgumentKeyValuePairs(unsigned int argc, char** argv);
