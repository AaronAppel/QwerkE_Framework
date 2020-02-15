#ifndef _Program_Args_H_
#define _Program_Args_H_

bool ArgumentExists(unsigned int argc, char** argv, const char* argumentString);
std::map<const char*, const char*> ArgumentKeyValuePairs(unsigned int argc, char** argv);

#endif // !_Program_Args_H_