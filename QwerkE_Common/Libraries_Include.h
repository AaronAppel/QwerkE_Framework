#ifndef _Libraries_Include_H_
#define _Libraries_Include_H_

//////////////////////////////
// Libraries_Include.h
// #include library files for use throughout program.
// This is mainly for use with precompiled headers to
// speed up build time.

// Code that needs to know what library is in use can #include
// this file instead of directly #including library files that
// might not be needed otherwise. This allows preprocessor defines
// to define function bodies for each platform.
//////////////////////////////

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
// stb_image
// TODO: stb_image needs to be loaded later on, after some other ???? library
// #define STB_IMAGE_IMPLEMENTATION
// #include "Libraries/stb_image.h"
// SOIL
// TODO: get soil

// models //
// assimp
#include "Libraries/assimp/config.h"

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
#include "Libraries/pThreads/pthread.h"
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
// glm and other math related includes
#include "Math_Includes.h"
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
#include "Libraries/Bullet3/LinearMath/btAlignedObjectArray.h"
#include "Libraries/Bullet3/BulletCollision/BroadphaseCollision/btAxisSweep3.h"
#include "Libraries/Bullet3/BulletDynamics/Character/btCharacterControllerInterface.h"
#include "Libraries/Bullet3/LinearMath/btAabbUtil2.h"
#include "Libraries/Bullet3/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "Libraries/Bullet3/BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "Libraries/Bullet3/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "Libraries/Bullet3/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
/////////////////////////////

// TODO: Add necessary headers.
// TODO: Remove unnecessary headers.

#include "Libraries_Load.h" // load .libs

#endif // !_Libraries_Include_H_
