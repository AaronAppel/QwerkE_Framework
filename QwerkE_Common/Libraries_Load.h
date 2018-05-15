#ifndef _Libraries_Load_H_
#define _Libraries_Load_H_

// Note: 64 bit not building currently so all .libs are 32bit

// load libraries
#ifdef QwerkE_Framework
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
#else
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
#endif // 1

#endif // !_Libraries_Load_H_
