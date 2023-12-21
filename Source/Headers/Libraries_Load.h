#ifndef _Libraries_Load_H_
#define _Libraries_Load_H_

#include "QwerkE_Defines.h"

// load libraries
#ifdef _DEBUG
// OpenGL
#define OpenGL // Temp build fix
#ifdef OpenGL
#pragma comment( lib, "opengl32.lib" ) // Found by Visual Studio
#elif defined(Direct3D)
#else
#pragma error "Define graphics library!"
#endif

// libusb
// #pragma comment( lib, LibrariesDir "libusb/Debug/libusb-1.0.lib" )

// assimp
#pragma comment( lib, LibrariesDir "assimp/Release/x86/assimp-vc140-mt.lib" )

// freetype2
#pragma comment( lib, LibrariesDir "freetype2/x86/freetype.lib" )

#define GLEW // Temp build fix
#ifdef GLEW
// TODO: Check for architecture and debug/release
#pragma comment( lib, LibrariesDir "glew/glew32d.lib" )
#endif // GLEW

#define GLFW3 // Temp build fix
#ifdef GLFW3
// TODO: Check for architecture and debug/release
// #pragma comment( lib, LibrariesDir "glfw/glfw3.lib" )
#pragma comment( lib, LibrariesDir "glfw/glfw3dll.lib" )
#endif // GLFW3

#define OpenAL // Temp build fix
#ifdef OpenAL
// OpenAL
#pragma comment( lib, LibrariesDir "OpenAL/libs/Win32/OpenAL32.lib" )
#elif defined(XAudio)
#else
#pragma error "Define audio library!"
#endif

// pThreads
#pragma comment( lib, LibrariesDir "pThreads/lib/x86/pthreadVC2.lib" )

// RakNet
#pragma comment( lib, LibrariesDir "RakNet/RakNet_VS2008_DLL_Debug_Win32.lib" )

// Bullet3
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Debug/BulletCollision.lib" )
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Debug/BulletDynamics.lib" )
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Debug/LinearMath.lib" )

#elif defined(RELEASE)
// OpenGL
#define OpenGL
#pragma comment( lib, "opengl32.lib" ) // load
// assimp
#pragma comment( lib, LibrariesDir "Libraries/assimp/Release/x86/assimp-vc140-mt.lib" )
// freetype2
#pragma comment( lib, LibrariesDir "freetype2/x86/Release/freetype271MT.lib" )
// TODO: Check for architecture and debug/release
#pragma comment( lib, LibrariesDir "glew/glew32d.lib" )
// TODO: Check for architecture and debug/release
#pragma comment( lib, LibrariesDir "glfw/x86/Release/glfw3_32Release.lib" )
// OpenAL
#pragma comment( lib, LibrariesDir "OpenAL/libs/Win32/OpenAL32.lib" )
// pThreads
#pragma comment( lib, LibrariesDir "pThreads/lib/x86/pthreadVC2.lib" )
// RakNet
#pragma comment( lib, LibrariesDir "RakNet/RakNet_VS2008_DLL_Release_Win32.lib" )
// Bullet3
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Release/BulletCollision.lib" )
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Release/BulletDynamics.lib" )
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Release/LinearMath.lib" )
#endif // Engine or other project

#endif // !_Libraries_Load_H_
