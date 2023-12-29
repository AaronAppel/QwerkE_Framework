#include "StringHelpers.h"

const char* StringAppend(const char* a, const char* b)
{
	const size_t size = strlen(a) + strlen(b);

	char* newString = new char[size]; // #TODO Delete memory. Maybe use a smart pointer.
	strcpy_s(newString, strlen(a) + 1, a);
	strcat_s(newString, size + 1, b);

	return newString;
}

const char* StringAppend(const char* a, const char* b, const char* c)
{
	const size_t size = strlen(a) + strlen(b) + strlen(c);

	const char* newString = new char[size]; // #TODO Delete memory. Maybe use a smart pointer.
	strcpy_s((char*)newString, strlen(a) + 1, a);
	strcat_s((char*)newString, size + 1, b);
	strcat_s((char*)newString, size + 1, c);

	return newString;
}

char* DeepCopyString(const char* string)
{
	if (string == 0) return nullptr;

	// #TODO Is the +1 necessary?
	char* returnString = new char[strlen(string) + 1]; // #TODO Delete memory. Maybe use a smart pointer.

	// #TODO Is the +1 necessary?
	memcpy(returnString, string, strlen(string) +1);

	// #TODO Review strdup
	// return _strdup(string); // Careful of malloc, free()
	return returnString;
}

const char* CombineStrings(const char* a, const char* b) // #TODO Review const return value
{
	// #TODO Review method
	// Cannot use an initialized string
	const size_t size = strlen(a) + strlen(b) + 1;
	char* buffer = new char[size];

	// Overwrite "string" to buffer
	strcpy_s(buffer, size, a); // (char* buffer, bufferSize, const char* "string")
	// Append "string" to buffer
	strcat_s(buffer, size, b); // (buffer, totalSize, "string")

	return buffer;
}

const char* CombineStrings(std::string a, std::string b)
{
	return CombineStrings(a.c_str(), b.c_str());
}

std::string DispStrCombine(const char* a, const char* b) // #TODO Improve naming
{
	std::string value;
	value.append(a);
	value.append(b);

	return value;
}

bool StringCompare(const char* a, const char* b) // #TODO Rename for boolean return type
{
	return strcmp(a, b) == 0;
}

bool StringCompare(std::string a, std::string b) // #TODO Rename for boolean return type
{
	return strcmp(a.c_str(), b.c_str()) == 0;
}

bool SearchForString(std::string line, std::string word)
{
	return line.find(word) != line.npos;
}

int StringToInt(const char* string)
{
	return std::strtol(string, nullptr, 10);
}

const char* ReverseString(std::string value)
{
	return ReverseString(value.c_str());
}

const char* ReverseString(const char* value)
{
	// #TODO Debug
	const size_t size = strlen(value);
	std::string t_temp = std::string(size, ' ');

	for (size_t i = 0; i < size; i++)
	{
		t_temp.push_back(value[size - i - 1]);
	}

	memcpy((char*)value, t_temp.c_str(), size + 1);
	return value; // #TODO Review removing return value
}