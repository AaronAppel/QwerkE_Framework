#ifndef _QwerkE_Include_H_
#define _QwerkE_Include_H_

//////////////////////////////
// QwerkE_Include.h
// #include crucial files for building like defines for platform.
// TODO: Remove. Also includes some files for easier access or faster build time
// using pre compiled headers.
//////////////////////////////

// Defines
#include "QwerkE_Defines.h" // platform, architecture,
#include "QwerkE_Platform.h" // platform libraries

// Enums, constants
#include "QwerkE_Enums.h"
#include "QwerkE_Flags.h"
#include "QwerkE_Global_Constants.h"

//////////////////////////////
// Libraries //
//////////////////////////////
#include "Libraries_Include.h" // openGL, Bullet, GLFW, etc
//////////////////////////////

//////////////////////////////
// Framework //
//////////////////////////////
#include "../Framework.h"
//////////////////////////////

//////////////////////////////
// Infrastructure/Systems //
//////////////////////////////

// Input //
#include "../Core/Input/QwerKE_eKeys.h"
#include "../Core/Input/Input.h"

// Scene //
#include "../Core/Scenes/Scene.h"

// Audio //
#include "../Core/Audio/Audio.h"

// Data management //
#include "../Core/DataManager/DataManager.h"
#include "../Core/DataManager/ConfigHelper.h"

// Debugger //
#include "../Debug/Debugger/Debugger.h"

// Events //
#include "../Core/Events/Event.h"
#include "../Core/Events/EventManager.h"
#include "../Core/Events/InputEvent.h"

// Factory //
#include "../Core/Factory/Factory.h"

// Graphics //
#include "../Core/Graphics/Graphics_Header.h"

// Rendering //
#include "../Core/Graphics/Renderer.h"

#include "../Core/Jobs/Jobs.h"

#include "../Debug/Log/Log.h"

// Networking //
#include "../Core/Network/Network.h"

// Physics //
#include "../Core/Physics/Physics.h"
#include "../Core/Physics/PhysicsWorld.h"

#include "../Core/Resources/Resources.h"

#include "../Core/Scenes/Scenes.h"

#include "../Core/Window/Window.h"
#include "../Core/Window/Windows.h"
//////////////////////////////

//////////////////////////////
// Entities //
//////////////////////////////
// Gameobject
#include "../Core/Scenes/Entities/GameObject.h"
// TODO: #include components and routines

// components

// routines

//////////////////////////////

#endif // !_QwerkE_Include_H_
