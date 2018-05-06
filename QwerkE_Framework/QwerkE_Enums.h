// QwerkE enums for things like GameObject tagging, Components, etc
#ifndef _QwerkE_Enums_H_
#define _QwerkE_Enums_H_

#include <cstdint>

enum class eEngineMessage : std::uint8_t
{
	_QSuccess = 0,
	_QFail,

	_QMax
};

enum class eEngineServices : std::uint8_t // TODO: Rename engine to framework
{
	Resource_Manager = 0,
	Input_Manager,
	Audio_Manager,
	Data_Manager,
	// Graphics (OpenGLManager)
	Event_System,
	Scene_Manager,
	Factory_Entity,
	Factory_Mesh,
	Factory_Shader,
	PhysicsManager,
	MessageManager,
	Renderer,
	JobManager,
	WindowManager,
	NetworkManager,

	Service_Max
};

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum eCamera_Movement
{
	FORWARD = 0,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

/* Component Tagging */
enum eComponentTags
{
	/* General */
	Component_Camera = 0,
	Component_Physics,
	Component_Light,
	Component_Controller,
	Component_Render,
	Component_Print,
	Component_SkyBox,
	Component_Animation,
	Component_Character,
	Component_Max,
	Component_Null
};
/* Routines */
enum eRoutineTypes
{
	Routine_Render = 0,
	Routine_Print,
	Routine_Max,
	Routine_NULL
};

/* Input */
enum eGameButtons
{
	// Application functionality
	Button_ModifierCntrl,

	/* Mouse */
	Button_MouseLeft,
	Button_MouseRight,
	Button_MouseMiddle,

	/* Movement */
	Button_MoveUp,
	Button_MoveDown,
	Button_MoveLeft,
	Button_MoveRight,
	Button_MoveForward,
	Button_MoveBackward,

	/* Navigation */
	Button_MenuUp,
	Button_MenuDown,
	Button_MenuLeft,
	Button_MenuRight,
	Button_MenuOpen,
	Button_MenuClose,

	/* Abilities */
	Button_Ability1,

	/* Size */
	Button_Max
};

/* Scenes */
enum eSceneTypes
{
	//// list in order of opening if possible
	// fullscreen
	Scene_TestScene = 0,
	Scene_GameScene,
	// overlays
	// Scene_OverLays,
	// *options
	// **Sound
	// **etc

	Scene_Max,
	Scene_Null
};

/* Menu Windows Types */
enum eMenuTypes // Example game windows
{
	Menu_Landing = 0,
	Menu_DropDown,
	Menu_Campaign,
	Menu_DungeonRaid,
	Menu_Progression,
	Menu_Profile,
	Menu_Character,
	Menu_Max,
	Menu_NULL
};

/* Menu States */
enum eStates
{
	State_Min = 0,
	State_Disabled,
	State_Enabled,
	State_Persistent,
	State_Max
};

/* Menu Item Types */

// Camera Types
enum eCamType // TODO: Hide from program?
{
	CamType_FreeCam = 0,
	CamType_FirstPerson,
	CamType_ThirdPerson,
	CamType_Static,

	CamType_Max,
	CamType_NULL
};
// Light Types
enum eLightType // TODO: Hide from program?
{
	LightType_Point = 0,
	LightType_Area,
	LightType_Spot,

	LightType_Max,
	LightType_NULL
};

enum eGameObjectTags
{
	GO_Tag_Player = 0,
	// Cameras
	GO_Tag_Camera,
	// Lights
	GO_Tag_Light,
	// Shapes
	GO_Tag_Cube,
	GO_Tag_Plane,
	// Scenery
	GO_Tag_SkyBox,
	// Test
	GO_Tag_TestModel,

	GO_Tag_Max,
	GO_Tag_Null,
};

#endif // _QwerkE_Enums_H_