#ifndef _QwerkE_Include_H_
#define _QwerkE_Include_H_

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
// Engine //
//////////////////////////////
#include "Framework.h"
//////////////////////////////

//////////////////////////////
// Infrastructure/Systems //
//////////////////////////////
// Graphics //
#include "Systems/Graphics_Header.h"

// Input //
#include "Systems/Input/Input.h"

// Scene //
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

// GameCore //
#include "Systems/GameCore.h"

#include "Systems/ServiceLocator.h" // Audio, Input, Graphics, etc
//////////////////////////////

#endif // !_QwerkE_Include_H_
