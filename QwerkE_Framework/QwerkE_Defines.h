#ifndef _QwerkE_Defines_H_
#define _QwerkE_Defines_H_

/* Defines values to be used in other ares of the framework.*/

// defines
// #define IncludeDir "../Shared_Common/Utilities/FileIO/FileUtilities.h"

// type definitions
// TODO: Is there an easy way of reducing typing without coupling files like typedef does
// typedef unsigned int uint; // less typing and easier to read

#define AssetDir FrameworkDir "QwerkE_Common/Resources/"
#define LibraryDir FrameworkDir "QwerkE_Common/Libraries/"
#define RuntimeDirectory MakeDir

// Define platform macro
#define _QWindows

// Define architecture macro
// TODO: Preprocessor defines are lame. Is there a
// better way to define the architecture?
#ifdef Win32Bit
#define _Q32Bit
// define libraries and systems to build
#define GLFW3 // TODO: Think of more explicit defines like Qdef_GLEW or w/e
#define GLEW
#define OpenGL
#define OpenAL
#define dearimgui
// #define LibUSB
#elif defined(Win64Bit)
#define _Q64Bit
#else
#pragma warning "Define architecture!"
#endif // Win32Bit

// Define debug vs release macro
#ifdef DEBUG
#define _QDebug
#elif defined(RELEASE)
#define _QRelease
#else
#pragma warning "Define Debug or Release mode!"
#endif // DEBUG

// Define API level for various functionality
// Currently not being used.
#define _QTesting // Enable testing features and suites

#define _QExample // Working example to show functionality

#define _QEasy // Beginner API
#define _QMedium // Simple control
#define _QHard // Mixed control
#define _QUltra // Full control

#include "QwerkE_Directory_Defines.h"

#endif // !_QwerkE_Defines_H_
