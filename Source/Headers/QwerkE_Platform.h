#ifndef _QwerkE_Platform_H_
#define _QwerkE_Platform_H_

// platform includes
// #if defined(_Q32Bit) && defined(_QWindows)
// #if defined(_WIN32) && defined(_QWindows)
#if defined(_WIN32)
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(_Q64Bit) && defined(_QWindows)
#pragma warning "Include Win64!"
#else
#pragma warning "Define Platform!"
#endif // !platform

#endif // !_QwerkE_Platform_H_
