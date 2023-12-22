#pragma once

#include "QwerkE_Defines.h" // #TODO Determine which libraries to load using #defines

#ifdef _DEBUG
#define OpenGL
#ifdef OpenGL
#pragma comment( lib, "opengl32.lib" ) // #TODO Found by Visual Studio, but explore better solution
#elif defined(Direct3D)
#else
#pragma error "Define graphics library!"
#endif

// #FEATURE Explorer usage of libusb
// #pragma comment( lib, LibrariesDir "libusb/Debug/libusb-1.0.lib" )

#pragma comment( lib, LibrariesDir "assimp/Release/x86/assimp-vc140-mt.lib" )

#pragma comment( lib, LibrariesDir "freetype2/x86/freetype.lib" )

#define GLEW
#ifdef GLEW
#pragma comment( lib, LibrariesDir "glew/glew32d.lib" )
#endif

#define GLFW3
#ifdef GLFW3
// #pragma comment( lib, LibrariesDir "glfw/glfw3.lib" )
#pragma comment( lib, LibrariesDir "glfw/glfw3dll.lib" )
#endif

#define OpenAL
#ifdef OpenAL
#pragma comment( lib, LibrariesDir "OpenAL/libs/Win32/OpenAL32.lib" )
#elif defined(XAudio)
#else
#pragma error "Define audio library!"
#endif

#pragma comment( lib, LibrariesDir "pThreads/lib/x86/pthreadVC2.lib" )

#pragma comment( lib, LibrariesDir "RakNet/RakNet_VS2008_DLL_Debug_Win32.lib" )

#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Debug/BulletCollision.lib" )
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Debug/BulletDynamics.lib" )
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Debug/LinearMath.lib" )

#elif defined(RELEASE)
#define OpenGL
#pragma comment( lib, "opengl64.lib" ) // #TODO Found by Visual Studio, but explore better solution

#pragma comment( lib, LibrariesDir "Libraries/assimp/Release/x86/assimp-vc140-mt.lib" )

#pragma comment( lib, LibrariesDir "freetype2/x86/Release/freetype271MT.lib" )

#pragma comment( lib, LibrariesDir "glew/glew32d.lib" )

#pragma comment( lib, LibrariesDir "glfw/x86/Release/glfw3_32Release.lib" )

#pragma comment( lib, LibrariesDir "OpenAL/libs/Win32/OpenAL32.lib" )

#pragma comment( lib, LibrariesDir "pThreads/lib/x86/pthreadVC2.lib" )

#pragma comment( lib, LibrariesDir "RakNet/RakNet_VS2008_DLL_Release_Win32.lib" )

#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Release/BulletCollision.lib" )
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Release/BulletDynamics.lib" )
#pragma comment( lib, LibrariesDir "Bullet3/lib/Win32/Release/LinearMath.lib" )
#endif
