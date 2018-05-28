#ifndef _Libraries_Load_H_
#define _Libraries_Load_H_

//////////////////////////////
// Libraries_Load.h
// Loads all .lib fils for static or dynamic libraries used throughout the project.
// Instead of using project settings I prefer to load through code for convenience
// and in some cases more dynamic control.
//////////////////////////////

// Note: 64 bit not building currently so all .libs are 32bit
// TODO: Fix 64 bit

// load libraries
#ifdef QwerkE_Framework
#ifdef DEBUG
// OpenGL
#define OpenGL
#pragma comment( lib, "opengl32.lib" ) // load
// assimp
#pragma comment( lib, "../QwerkE_Common/Libraries/assimp/Release/x86/assimp-vc140-mt.lib" )
// freetype2
#pragma comment( lib, "../QwerkE_Common/Libraries/freetype2/x86/freetype.lib" ) // load
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Common/Libraries/glew/glew32d.lib" )
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Common/Libraries/glfw/glfw3.lib" )
// OpenAL
#pragma comment( lib, "../QwerkE_Common/Libraries/OpenAL/libs/Win32/OpenAL32.lib" )
// pThreads
#pragma comment( lib, "../QwerkE_Common/Libraries/pThreads/lib/x86/pthreadVC2.lib" )
// RakNet
#pragma comment( lib, "../QwerkE_Common/Libraries/RakNet/RakNet_VS2008_DLL_Debug_Win32.lib" )
// Bullet3
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/BulletCollision.lib" )
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/BulletDynamics.lib" )
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/LinearMath.lib" )
//
#elif defined(RELEASE)
// OpenGL
#define OpenGL
#pragma comment( lib, "opengl32.lib" ) // load
// assimp
#pragma comment( lib, "../QwerkE_Common/Libraries/assimp/Release/x86/assimp-vc140-mt.lib" )
// freetype2
#pragma comment( lib, "../QwerkE_Common/Libraries/freetype2/x86/Release/freetype271MT.lib" ) // load
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Common/Libraries/glew/glew32d.lib" )
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Common/Libraries/glfw/glfw3_32Release.lib" )
// OpenAL
#pragma comment( lib, "../QwerkE_Common/Libraries/OpenAL/libs/Win32/OpenAL32.lib" )
// pThreads
#pragma comment( lib, "../QwerkE_Common/Libraries/pThreads/lib/x86/pthreadVC2.lib" )
// RakNet
#pragma comment( lib, "../QwerkE_Common/Libraries/RakNet/RakNet_VS2008_DLL_Release_Win32.lib" )
// Bullet3
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/BulletCollision.lib" )
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/BulletDynamics.lib" )
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/LinearMath.lib" )
#endif // Framework
//
#else // Engine or other project
#ifdef DEBUG
// OpenGL
#ifdef OpenGL
#pragma comment( lib, "opengl32.lib" ) // load
#endif
// assimp
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/assimp/Release/x86/assimp-vc140-mt.lib" )
// freetype2
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/freetype2/x86/freetype.lib" )
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/glew/glew32d.lib" )
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/glfw/glfw3.lib" )
// OpenAL
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/OpenAL/libs/Win32/OpenAL32.lib" )
// pThreads
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/pThreads/lib/x86/pthreadVC2.lib" )
// RakNet
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/RakNet/RakNet_VS2008_DLL_Debug_Win32.lib" )
// Bullet3
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/BulletCollision.lib" )
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/BulletDynamics.lib" )
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/LinearMath.lib" )
//
#elif defined(RELEASE)
// OpenGL
#define OpenGL
#pragma comment( lib, "opengl32.lib" ) // load
// assimp
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/assimp/Release/x86/assimp-vc140-mt.lib" )
// freetype2
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/freetype2/x86/Release/freetype271MT.lib" )
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/glew/glew32d.lib" )
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/glfw/x86/Release/glfw3_32Release.lib" )
// OpenAL
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/OpenAL/libs/Win32/OpenAL32.lib" )
// pThreads
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/pThreads/lib/x86/pthreadVC2.lib" )
// RakNet
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/RakNet/RakNet_VS2008_DLL_Release_Win32.lib" )
// Bullet3
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/BulletCollision.lib" )
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/BulletDynamics.lib" )
#pragma comment( lib, "../QwerkE_Framework/QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/LinearMath.lib" )
#endif // Engine or other project

#endif // !QwerkE_Framework

#endif // !_Libraries_Load_H_
