#ifndef _Scene_H_
#define _Scene_H_

#include "../../Headers/QwerkE_Enums.h"
#include "../../Headers/QwerkE_Global_Constants.h"

#include <map>
#include <vector>
#include <string>

namespace QwerkE {

    extern int g_WindowWidth, g_WindowHeight; // TODO: Remove

    class GameCore;
    class MyMatrix;
    class Scenes;
    class GameObject;

    class Scene; // forward declare for function* typedef

    typedef void (Scene::* StateFunc)(double deltatime); // Scene state function

    class Scene // Abstract class
    {
    public:
        Scene();
        Scene(const char* sceneFileName) { m_LevelFileName = sceneFileName; }
        virtual ~Scene();

        virtual void Initialize();

        virtual void OnWindowResize(unsigned int width, unsigned int height);
        virtual void ResetScene();

        virtual void Update(double deltatime) { (this->*m_UpdateFunc)(deltatime); }
        virtual void Draw();

        // cameras
        virtual bool AddCamera(GameObject* camera);
        virtual void RemoveCamera(GameObject* camera);
        virtual void SetupCameras();

        // lights
        virtual bool AddLight(GameObject* light);
        virtual void RemoveLight(GameObject* light);
        virtual void SetupLights();

        virtual bool AddObjectToScene(GameObject* object);
        virtual void RemoveObjectFromScene(GameObject* object);

        virtual void RemoveAllObjectsFromScene(); // Possibly a scene reset

        // Save/Load
        virtual void SaveScene();
        virtual void LoadScene(const char* sceneFileName);
        virtual void ReloadScene();

        /* Getters + Setters */
        // getters
        GameObject* GetGameObject(const char* name);
        bool GetIsEnabled() { return m_IsEnabled; };
        std::vector<GameObject*> GetCameraList() { return m_CameraList; };
        std::map<std::string, GameObject*> GetObjectList() { return m_pGameObjects; };
        int GetCurrentCamera() { return m_CurrentCamera; };
        std::vector<GameObject*> GetLightList() { return m_LightList; };
        eSceneTypes GetSceneID() { return m_ID; }
        eSceneState GetState() { return m_State; }

        // setters
        void SetIsEnabled(bool isEnabled) { m_IsEnabled = isEnabled; };
        void SetCurrentCamera(int camera) { m_CurrentCamera = camera; }; // TODO:: Better way for ImGUI to change camera
        void SetState(eSceneState newState);
        // TODO: void ToggleFrozenState() { SetIsFrozen(!m_IsFrozen); }

    protected:
        virtual void p_Running(double deltatime);
        virtual void p_Frozen(double deltatime); // only update cameras
        virtual void p_Paused(double deltatime) {} // Currently empty to avoid updating
        virtual void p_Animating(double deltatime); // for testing animations
        virtual void p_SlowMotion(double deltatime);
        StateFunc m_UpdateFunc = &Scene::p_Running;

        void CameraInput(double deltatime);

        bool m_IsEnabled = false;
        eSceneState m_State = eSceneState::SceneState_Running;
        std::string m_LevelFileName = gc_DefaultCharPtrValue;// "Uninitialized"; // TODO: Find out why I can't assign gc_DefaultCharPtrValue
        MyMatrix* m_pViewMatrix = nullptr; // TODO:: create cameras with different view matrices

        std::map<std::string, GameObject*> m_pGameObjects;
        eSceneTypes m_ID = eSceneTypes::Scene_Null;

        int m_CurrentCamera = 0;
        std::vector<GameObject*> m_CameraList;

        std::vector<GameObject*> m_LightList;

        std::vector<GameObject*> m_SceneDrawList; // TODO: sort by render order
    };

}
#endif //!_Scene_H_
