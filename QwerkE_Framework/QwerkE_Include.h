#ifndef _QwerkE_Include_H_
#define _QwerkE_Include_H_

//////////////////////////////
// QwerkE_Include.h
// #includes crucial files for building like defines for platform.
// Also includes some files for easier access or build time using
// precompiled headers
//////////////////////////////

#include "QwerkE_Defines.h" // platform, architecture,
#include "QwerkE_Platform.h" // platform libraries

// enums, constants
#include "QwerkE_Enums.h"
#include "Global_Constants.h"

//////////////////////////////
// Libraries //
//////////////////////////////
#include "../QwerkE_Common/Libraries_Include.h" // openGL, Bullet, GLFW, etc
//////////////////////////////

//////////////////////////////
// Framework //
//////////////////////////////
#include "Framework.h"
//////////////////////////////

//////////////////////////////
// Infrastructure/Systems //
//////////////////////////////
// Graphics //
#include "Systems/Graphics/Graphics_Header.h"

// Input //
#include "Systems/Input/Input.h"

// Scene //
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"

#include "Systems/ServiceLocator.h" // Audio, Input, Graphics, etc
//////////////////////////////

#endif // !_QwerkE_Include_H_
