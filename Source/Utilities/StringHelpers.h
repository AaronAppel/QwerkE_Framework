#pragma once

#include <string>

// Easy to use utility functions for use with std:string
// FEATURE: GetStringExtension()

// FEATURE: String append function that takes a variable number of char*s and appends them in order
const char* StringAppend(const char* a, const char* b);
const char* StringAppend(const char* a, const char* b, const char* c);

char* DeepCopyString(const char* string);

const char* CombineStrings(const char* a, const char* b);
const char* CombineStrings(std::string a, std::string b);

std::string DispStrCombine(const char* a, const char* b);

// TODO: Just macro define strcmp for a nicer name
bool StringCompare(std::string a, std::string b);

bool SearchForString(std::string line, std::string word);


int StringToInt(const char* string);

const char* ReverseString(std::string value);
const char* ReverseString(const char* value);
