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

#elif defined(_Q64Bit) // architecture
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
#include "Libraries/glew/GL/glew.h"
// window creation //
// GLFW
#include "Libraries/glfw/GLFW/glfw3.h"
//////////////////////////////

//////////////////////////////
// Audio //
//////////////////////////////
// TODO: Setup OpenAL
// https://ffainelli.github.io/openal-example/
// #include "Libraries/OpenAL/include/al.h"
// #include "Libraries/OpenAL/include/alc.h"
// #include "Libraries/OpenAL/include/efx.h"
// #include "Libraries/OpenAL/include/efx-creative.h"
// #include "Libraries/OpenAL/include/EFX-Util.h"
// #include "Libraries/OpenAL/include/xram.h"
// #include "Libraries/OpenAL/include/alut.h"
// #include "Libraries/OpenAL/include/alc.h"
// #include "alut.h"
// alutinit?
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
//////////////////////////////

//////////////////////////////
// networking
//////////////////////////////
// RakNet
// TODO: Check for architecture and debug/release
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
// Consider creating a library for bullet projects.
// #include "Libraries/Bullet3/btAabbUtil2.h"
/////////////////////////////

// TODO: Add necessary headers.
// TODO: Remove unecessary headers.

#include "Libraries_Load.h" // load .libs

#endif // !_Libraries_Include_H_
