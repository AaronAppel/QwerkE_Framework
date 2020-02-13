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
#include "../Systems/Debugger/Debugger.h"
#include "../Framework.h"
//////////////////////////////

//////////////////////////////
// Infrastructure/Systems //
//////////////////////////////

// Input //
#include "../Systems/Input/QwerKE_eKeys.h"
#include "../Systems/Input/Input.h"

// Scene //
#include "../Scenes/Scene.h"

// Audio //
#include "../Systems/Audio/Audio.h"

// Data management //
#include "../Systems/DataManager/DataManager.h"
#include "../Systems/DataManager/ConfigHelper.h"

// Debugger //
#include "../Systems/Debugger/Debugger.h"

// Events //
#include "../Systems/Events/Event.h"
#include "../Systems/Events/EventManager.h"
#include "../Systems/Events/InputEvent.h"

// Factory //
#include "../Systems/Factory/Factory.h"

// Graphics //
#include "../Graphics/Graphics_Header.h"

// Rendering //
#include "../Systems/Renderer/Renderer.h"

#include "../Systems/Jobs/Jobs.h"

#include "../Systems/Log/Log.h"

#include "../Systems/MessageManager.h"

// Networking //
#include "../Systems/Network/Network.h"

// Physics //
#include "../Systems/Physics/Physics.h"
#include "../Systems/Physics/PhysicsWorld.h"

#include "../Systems/Resources/Resources.h"

#include "../Systems/Scenes.h"

#include "../Systems/Window/Window.h"
#include "../Systems/Window/Windows.h"
//////////////////////////////

//////////////////////////////
// Entities //
//////////////////////////////
// Gameobject
#include "../Entities/GameObject.h"
// TODO: #include components and routines

// components

// routines

//////////////////////////////

#endif // !_QwerkE_Include_H_
