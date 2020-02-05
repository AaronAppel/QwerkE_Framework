#ifndef _QwerkE_Defines_H_
#define _QwerkE_Defines_H_

/* Defines values to be used in other ares of the framework.*/

// defines
// #define IncludeDir "../Shared_Common/Utilities/FileIO/FileUtilities.h"

// type definitions
#define QNULL 0 // Standardized NULL value
// TODO: Is there an easy way of reducing typing without coupling files like typedef does
// typedef unsigned int uint; // less typing and easier to read

#ifndef FrameworkDir
#pragma error "Define FrameworkDir!"
#define FrameworkDir "../../QwerkE_Framework/" // TODO: Find out why RenderingEnv cannot define FrameworkDir
// string pointing to the QwerkE_Framework folder from your project working directory
#endif // !FrameworkDir

// TODO: Move to Engine folder (not a part of framework)
#ifndef ProjectsDir
#define ProjectsDir FrameworkDir "Projects/"
#endif // !ProjectsDir

// TODO: Move to directory defines file
#ifndef AssetsDir
#define AssetsDir FrameworkDir "QwerkE_Common/Assets/" // Default uses QwerkE_Common Assets
#endif // !AssetsDir

#ifndef LibrariesDir
#define LibrariesDir FrameworkDir "QwerkE_Common/Libraries/" // Default uses QwerkE_Common Libraries
#endif // LibrariesDir

#define RuntimeDirectory "" // TODO: MakeDir

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
#include "QwerkE_File_Defines.h"

#endif // !_QwerkE_Defines_H_
