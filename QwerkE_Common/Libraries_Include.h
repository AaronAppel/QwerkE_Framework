#ifndef _Libraries_Include_H_
#define _Libraries_Include_H_

// TODO: Consider having multiple Library_Include files for each platform. Easier management
// Include/Exclude libraries based on platform, architecture, configuration
// TODO: Hide loading/unloading behind load/splash screen?
// TODO: Clean up #ifs
// TODO: Remove QwerkE specific defines
#ifdef _Q32Bit // architecture
// platform
#ifdef _QWindows
// TODO: Add libraries

#elif _Android
#elif _Mac
#elif _Linux
#endif

#elif _Q64Bit // architecture
// platform
#ifdef _QWindows
#elif _Android
#elif _Mac
#elif _Linux
#endif

#else
#pragma warning "Define Platform!"
#endif // !platform

//////////////////////////////
// FILES //
//////////////////////////////
// JSON //
// cJSON
#include "Libraries/cJSON_Interface/cJSONInterface.h"

// images //
// lodepng
#include "Libraries/lodepng/lodepng.h"
// stb
#include "Libraries/stb_image.h"

// font loading/rendering
// freetype2
#pragma comment( lib, "../QwerkE_Common/Libraries/freetype2/freetype.lib" ) // load
#include "Libraries/freetype2/ft2build.h"
#include "Libraries/freetype2/freetype/freetype.h"
//////////////////////////////

//////////////////////////////
// HID //
//////////////////////////////
// XBOX Controller //
// xinput
#include "Libraries/EasyXinput/EasyXinput.h"
//////////////////////////////

//////////////////////////////
// Graphics //
//////////////////////////////
// OpenGL //
// open graphics library
#ifdef _Q32Bit
#pragma comment( lib, "opengl32.lib" ) // load
#else
#pragma comment( lib, "opengl32.lib" ) // still the same name...
#endif
// openGL extensions wrangler //
// GLEW
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Common/Libraries/glew/glew32d.lib" ) // load
#include "Libraries/glew/GL/glew.h"
// window creation //
// GLFW
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Common/Libraries/glfw/glfw3.lib" ) // load
#include "Libraries/glfw/GLFW/glfw3.h"
//////////////////////////////

//////////////////////////////
// Audio //
//////////////////////////////
// TODO: Setup OpenAL
// https://ffainelli.github.io/openal-example/
// TODO: Crashing if I uninstall SDK
#pragma comment( lib, "../QwerkE_Common/Libraries/OpenAL/libs/Win32/OpenAL32.lib" ) // load
//#pragma comment( lib, "../QwerkE_Common/Libraries/OpenAL/libs/Win32/EFX-Util_MT/EFX-Util.lib" ) // load
#include "Libraries/OpenAL/include/al.h"
//#include "Libraries/OpenAL/include/alc.h"
//////////////////////////////

//////////////////////////////
// GUIs //
//////////////////////////////
// immediate mode //
// imgui
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw_gl3.h"
// BlockMenu
#include "Libraries/Block_Menu/Block_Menu.h"
//////////////////////////////

//////////////////////////////
// threading //
//////////////////////////////
// pthreads
// TODO: Check for architecture and debug/release
// TODO: Remove have struct order dependency
#ifndef HAVE_STRUCT_TIMESPEC
#define HAVE_STRUCT_TIMESPEC
#endif
#pragma comment( lib, "../QwerkE_Common/Libraries/pThreads/lib/x86/pthreadVC2.lib" ) // load
//////////////////////////////

//////////////////////////////
// networking
//////////////////////////////
// RakNet
// TODO: Check for architecture and debug/release
#pragma comment( lib, "../QwerkE_Common/Libraries/RakNet/RakNet_VS2008_DLL_Debug_Win32.lib" ) // load
// http://www.raknet.net/raknet/manual/tutorialsample3.html
//////////////////////////////

//////////////////////////////
// math
//////////////////////////////
#include "Math_Includes.h" // all math related files included in here
/////////////////////////////

//////////////////////////////
// physics
//////////////////////////////
#include "Utilities/Tween/Tween.h"
#include "Utilities/Tween/TweenFuncs.h"
//////////////////////////////

//////////////////////////////
// physics
//////////////////////////////
// Bullet3
// TODO: Check for architecture
#if _DEBUG // and windows specific?
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/BulletCollision.lib" ) // load
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/BulletDynamics.lib" ) // load
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Debug/LinearMath.lib" ) // load
#else // Release
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/BulletCollision.lib" ) // load
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/BulletDynamics.lib" ) // load
#pragma comment( lib, "../QwerkE_Common/Libraries/Bullet3/lib/Win32/Release/LinearMath.lib" ) // load
#endif

// TODO: Add necessary headers.
// TODO: Remove unecessary headers.
// Consider creating a library for bullet projects.
// #include "Libraries/Bullet3/btAabbUtil2.h"
/////////////////////////////

#endif // !_Libraries_Include_H_
