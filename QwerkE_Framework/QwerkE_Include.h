#ifndef _QwerkE_Include_H_
#define _QwerkE_Include_H_

//////////////////////////////
// QwerkE_Include.h
// #includes crucial files for building like defines for platform.
// Also includes some files for easier access or build time using
// precompiled headers.
//////////////////////////////

#include "QwerkE_Defines.h" // platform, architecture,
#include "QwerkE_Platform.h" // platform libraries

// enums, constants
#include "QwerkE_Enums.h"
#include "QwerkE_Global_Constants.h"

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
#include "Systems/ServiceLocator.h" // Access point for all QwerkE services

// Input //
#include "Systems/Input/Input.h"

// Scene //
#include "Scenes/Scene.h"

// Audio //
#include "Systems/Audio/AudioManager.h"

// Data management //
#include "Systems/DataManager/DataManager.h"

#include "Systems/Debugger/Debugger.h"

// Events //
#include "Systems/Events/Event.h"
#include "Systems/Events/EventManager.h"
#include "Systems/Events/InputEvent.h"

#include "Systems/Factory/Factory.h"
#include "Systems/Factory/LevelLoader.h"

// Graphics //
#include "Graphics/Graphics_Header.h"

// Rendering //
#include "Systems/Renderer/Renderer.h"

// Input //
#include "Systems/Input/Input.h"
#include "Systems/Input/InputManager.h"
#include "Systems/Input/Controller.h"
#include "Systems/Input/QwerKE_eKeys.h"

#include "Systems/JobManager/JobManager.h"

#include "Systems/Logger/Logger.h"

#include "Systems/MessageManager.h"

// networking //
#include "Systems/Networking/NetworkManager.h"

#include "Systems/Physics/PhysicsWorld.h"
#include "Systems/Physics/PhysicsManager.h"

#include "Systems/ResourceManager/ResourceManager.h"

#include "Systems/SceneManager.h"

#include "Systems/Window/Window.h"
#include "Systems/Window/WindowManager.h"
//////////////////////////////

//////////////////////////////
// Entities //
//////////////////////////////
// gameobject
#include "Entities/GameObject.h"
// TODO: #include components and routines

// components

// routines

//////////////////////////////

#endif // !_QwerkE_Include_H_
