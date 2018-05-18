#ifndef _QwerkE_Defines_H_
#define _QwerkE_Defines_H_

/* Defines values to be used in other ares of code.*/

// defines
// #define IncludeDir "../Shared_Common/Utilities/FileIO/FileUtilities.h"

// type definitions
// TODO: Is there an easy way of reducing typing without coupling files like typedef does
// typedef unsigned int uint; // less typing and easier to read

// Define platform macro
#define _QWindows

// Define architecture macro
// TODO: Preprocessor defines are lame. Is there a
// better way to define the architecture?
#ifdef Win32Bit
#define _Q32Bit
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
