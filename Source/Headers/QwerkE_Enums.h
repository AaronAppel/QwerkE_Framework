#pragma once

#include <cstdint>

// QwerkE enums for things like GameObject tagging, Components, etc

namespace QwerkE {

    enum class eInputDeviceTypes : std::uint8_t
    {
        Keyboard_Min = 0,
        Keyboard_Device0,
        Keyboard_Device1,
        Keyboard_Device2,
        Keyboard_Device3,
        Keyboard_Max,

        Mouse_Min,
        Mouse_Device0,
        Mouse_Device1,
        Mouse_Device2,
        Mouse_Device3,
        Mouse_Max,

        GamePad_Min,
        GamePad_Device0,
        GamePad_Device1,
        GamePad_Device2,
        GamePad_Device3,
        GamePad_Device4,
        GamePad_Device5,
        GamePad_Device6,
        GamePad_Device7,
        GamePad_Max,

        Max_Device
    };

    enum class eMaterialMaps : std::uint8_t
    {
        MatMap_Ambient = 0,
        MatMap_Diffuse,
        MatMap_Specular,
        MatMap_Emissive,
        MatMap_Height,
        MatMap_Normals,
        MatMap_Shininess,
        MatMap_Opacity,
        MatMap_Displacement,
        MatMap_LightMap,
        MatMap_Reflection,
        MatMap_Albedo,
        MatMap_Metallic,
        MatMap_AmbientOcclusion,
        MatMap_Roughness,

        MatMap_Vec3Colour,
        MatMap_Max,
        MatMap_Null
    };

    enum class eEngineMessage : std::uint8_t
    {
        _QFailure = 0,
        _QSuccess,

        _QMax
    };

    enum class eSceneState : std::uint8_t
    {
        SceneState_Running = 0,
        SceneState_Frozen, // Cameras can move
        SceneState_Paused, // No updating
        SceneState_SlowMo, // Smaller deltatime
        SceneState_Animating, // Cameras and Animation only

        SceneState_Max
    };

    enum class eEngineServices : std::uint8_t // TODO: Rename engine to framework
    {
        // Resource_Manager = 0,
        // Input_Manager,
        // Audio_Manager,
        // Data_Manager,
        // Graphics (OpenGLManager)
        // Event_System,
        // Scene_Manager,
        // Factory_Entity,
        // Factory_Mesh,
        // Factory_Shader,
        // Physics,
        // MessageManager,
        // Renderer,
        // Jobs,
        // Windows,
        // Network,
        // FileSystem,

        Service_Max
    };

    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum eCamera_Movement : std::uint8_t
    {
        FORWARD = 0,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        RROTATE,
        LROTATE
    };

    /* Component Tagging */
    enum eComponentTags : std::uint8_t
    {
        /* General */
        Component_Camera = 0,
        Component_Physics,
        Component_Light,
        Component_Controller,
        Component_Render,
        Component_Print, // #TODO Rename to debug component or something better if applicable
        Component_SkyBox,
        Component_SoundPlayer,
        Component_SoundListener,
        Component_Max,
        Component_Null
    };
    /* Routines */
    enum eRoutineTypes : std::uint8_t
    {
        Routine_Render = 0,
        Routine_Physics,
        Routine_Print,
        Routine_Transform,
        Routine_Max,
        Routine_NULL
    };

    /* Input */
    enum eGameButtons : std::uint8_t
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
    // TODO: Remove
    enum eSceneTypes : std::uint8_t
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

        // "special" scenes
        Scene_ViewerScene,
        Scene_PBR_Test1,

        Scene_Null
    };

    /* Menu Windows Types */
    enum eMenuTypes : std::uint8_t // Example game windows
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
    enum eStates : std::uint8_t
    {
        State_Min = 0,
        State_Disabled,
        State_Enabled,
        State_Persistent,
        State_Max
    };

    /* Menu Item Types */

    // Camera Types
    enum eCamType : std::uint8_t // TODO: Hide from program?
    {
        CamType_FreeCam = 0,
        CamType_FirstPerson,
        CamType_ThirdPerson,
        CamType_Static,

        CamType_Max,
        CamType_NULL
    };
    // Light Types
    enum eLightType : std::uint8_t // TODO: Hide from program?
    {
        LightType_Point = 0,
        LightType_Area,
        LightType_Spot,

        LightType_Max,
        LightType_NULL
    };

    // TODO: Adding object tags ruins object saving and loading. Fix!
    enum eGameObjectTags : std::uint8_t
    {
        GO_Tag_Player = 0,
        // Cameras
        GO_Tag_Camera,
        // Lights
        GO_Tag_Light,
        // Shapes
        GO_Tag_Cube,
        GO_Tag_Plane,
        GO_Tag_Sphere,
        // Scenery
        GO_Tag_SkyBox,
        // Test
        GO_Tag_TestModel,

        GO_Tag_Max,
        GO_Tag_Null,
    };

}
