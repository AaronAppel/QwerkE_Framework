#include "../../Headers/QwerkE_Defines.h"
#include "../../Headers/QwerkE_Platform.h"
#include "PrintFunctions.h"

// #include <cstdio> // vsnprintf_s
#include <fstream> // vsnprintf_s
#include <cstdarg> // va_start, va_end
#include <debugapi.h> // OuputDebugStringA(buffer)

void OutputPrint(const char* message, ...)
{
#define MAX_MESSAGE 1024
	char buffer[MAX_MESSAGE];
	va_list arg;
	va_start(arg, message);
	vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, message, arg);
	va_end(arg);

	buffer[MAX_MESSAGE - 1] = 0; // vsnprintf_s might do this, but docs are unclear
	OutputDebugStringA(buffer);
}

void ConsolePrint(const char* message)
{
	fprintf(stderr, message);
}