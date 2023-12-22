#pragma once

#if _WIN32 || _WIN64
#define _QWindows
#endif

#ifdef _WIN64
#pragma warning "Support _WIN64!"
#elif (_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <Windows.h>
#else
#pragma warning "Define Platform!"
#endif
