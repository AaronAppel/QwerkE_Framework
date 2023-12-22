#pragma once

#include "QwerkE_Defines.h" // #TODO Determine which libraries to load using #defines

#pragma warning( disable : 26437 )
#pragma warning( disable : 26451 )
#pragma warning( disable : 26495 )
#pragma warning( disable : 26498 )
#pragma warning( disable : 6387 )
#include <spdlog/spdlog.h>
#pragma warning( default : 26437 )
#pragma warning( default : 26451 )
#pragma warning( default : 26495 )
#pragma warning( default : 26498 )
#pragma warning( default : 6387 )

#pragma warning( disable : 4267 )
#pragma warning( disable : 4244 )
#include "../Libraries/cJSON_Interface/cJSONInterface.h"
#pragma warning( default : 4267)
#pragma warning( default : 4244)

#include "../Libraries/lodepng/lodepng.h"

// stb_image
// TODO: stb_image needs to be loaded later on, after some other ???? library
// #define STB_IMAGE_IMPLEMENTATION
// #include "Libraries/stb_image.h"
// SOIL
// TODO: get soil

#pragma warning( disable : 26495 )
#include "../Libraries/assimp/config.h"
#pragma warning( default : 26495 )

#include "../Libraries/freetype2/ft2build.h"
#include "../Libraries/freetype2/freetype/freetype.h"

#include "../Libraries/EasyXinput/EasyXinput.h"

// #include "../Libraries/libusb/libusb.h"

#include "../Libraries/glew/GL/glew.h"

#include "../Libraries/glfw/GLFW/glfw3.h"

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

#pragma warning( disable : 4244 )
#include "../Libraries/imgui/imgui.h"
#include "../Libraries/imgui/imgui_impl_glfw.h"
#include "../Libraries/imgui/imgui_impl_opengl3.h"
#pragma warning( default : 4244 )

// pthreads
// TODO: Check for architecture and debug/release
// TODO: Remove have struct order dependency
#ifndef HAVE_STRUCT_TIMESPEC
#define HAVE_STRUCT_TIMESPEC
#endif
#include "../Libraries/pThreads/pthread.h"

// TODO: Check for architecture and debug/release
// http://www.raknet.net/raknet/manual/tutorialsample3.html

#pragma warning( disable : 26495 )
#include "../Libraries/glm/glm/glm.hpp"
#include "../Libraries/glm/glm/gtc/matrix_transform.hpp"
#include "../Libraries/glm/glm//gtc/type_ptr.hpp"
#pragma warning( default : 26495 )

#include "../Source/Core/Math/Vector.h"
#include "../Source/Core/Math/MyQuaternion.h"
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )
#pragma warning( disable : 26495 )
#include "../Source/Core/Math/MyMatrix.h"
#pragma warning( default : 4244 )
#pragma warning( default : 4305 )
#pragma warning( disable : 26495 )

#pragma warning( disable : 4244 )
#include "../Source/Core/Math/Tween/Tween.h"
#include "../Source/Core/Math/Tween/TweenFuncs.h"
#pragma warning( default : 4244 )

#pragma warning( disable : 26495 )
#pragma warning( disable : 4099 )
#pragma warning( disable : 26495 )
#include "../Libraries/Bullet3/LinearMath/btAlignedObjectArray.h"
#include "../Libraries/Bullet3/BulletCollision/BroadphaseCollision/btAxisSweep3.h"
#include "../Libraries/Bullet3/BulletDynamics/Character/btCharacterControllerInterface.h"
#include "../Libraries/Bullet3/LinearMath/btAabbUtil2.h"
#include "../Libraries/Bullet3/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "../Libraries/Bullet3/BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "../Libraries/Bullet3/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "../Libraries/Bullet3/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#pragma warning( default : 26495 )
#pragma warning( default : 4099 )
#pragma warning( default : 26495 )
