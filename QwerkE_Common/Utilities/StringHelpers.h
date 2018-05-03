#ifndef __StringHelpers_H_
#define __StringHelpers_H_

#include <string>
// Easy to use utility functions for use with std:string
// TODO: GetStringExtension()

const char* DeepCopyString(const char* string);

const char* CombineStrings(const char* a, const char* b);
const char* CombineStrings(std::string a, std::string b);

std::string DispStrCombine(const char* a, const char* b);

bool StringCompare(std::string a, std::string b);

bool SearchForString(std::string line, std::string word);

int StringToInt(const char* string);

const char* ReverseString(std::string value);
const char* ReverseString(const char* value);

#endif // __StringHelpers_H_