#include "StringHelpers.h"
#include <sstream>

const char* StringAppend(const char* a, const char* b)
{
	int size = 0;
	size = strlen(a) + strlen(b);

	char* newString = new char[size]; // RAM:
	strcpy_s(newString, strlen(a) + 1, a);
	strcat_s(newString, size + 1, b);

	return newString;
}

const char* StringAppend(const char* a, const char* b, const char* c)
{
	int size = 0;
	size = strlen(a) + strlen(b) + strlen(c);

	char* newString = new char[size]; // RAM:
	strcpy_s(newString, strlen(a) + 1, a);
	strcat_s(newString, size + 1, b);
	strcat_s(newString, size + 1, c);

	return newString;
}

const char* DeepCopyString(const char* string)
{
	if (string == 0) return nullptr;

	char* returnString = new char[strlen(string) + 1]; // TODO: +1?

	memcpy(returnString, string, strlen(string) +1); // TODO: +1?

	/*
	for (int i = 0; i < strlen(string) + 1; i++)
	{
		returnString[i] = string[i]; // Inefficient
	}
	*/

	// return _strdup(string); // Careful of malloc, free()

	return returnString;
}

const char* CombineStrings(const char* a, const char* b)
{
	// Cannot use an initialized string
	int size = strlen(a) + strlen(b) + 1;
	char* buffer = new char[size];

	// overwrite "string" to buffer
	strcpy_s(buffer, size, a); // (char* buffer, bufferSize, const char* "string")
	// append "string" to buffer
	strcat_s(buffer, size, b); // (buffer, totalSize, "string")

	return buffer;
}

const char* CombineStrings(std::string a, std::string b)
{
	return CombineStrings(a.c_str(), b.c_str());
}

std::string DispStrCombine(const char* a, const char* b)
{
	std::string value;
	value.append(a);
	value.append(b);

	return value;
}

bool StringCompare(const char* a, const char* b)
{
	return strcmp(a, b) == 0; // 0 means they are equal
}

bool StringCompare(std::string a, std::string b)
{
	return strcmp(a.c_str(), b.c_str()) == 0; // 0 means they are equal
}

bool SearchForString(std::string line, std::string word)
{
	return line.find(word) != line.npos;
}

int StringToInt(const char* string)
{
	std::stringstream stream(string);
	int x = 0;
	stream >> x;
	return x;
}

const char* ReverseString(std::string value)
{
	return ReverseString(value.c_str());
}

const char* ReverseString(const char* value)
{
	// TODO: Debug
	std::string t_temp;
	int size = strlen(value);
	for (int i = 0; i < size; i++)
	{
		t_temp.push_back(value[size - i - 1]);
	}

	memcpy((char*)value, t_temp.c_str(), size + 1);
	return value; // return in case value chould be passed by value
}