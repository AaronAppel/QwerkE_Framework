#pragma once

#include <map>
#include <vector>
#include <string>

#include "../../Headers/QwerkE_Enums.h"
#include "../../Headers/QwerkE_Global_Constants.h"

namespace QwerkE {

    class GameCore;
    class MyMatrix;
    class Scenes;
    class GameObject;

    class Scene
    {
    public:
        Scene() = default;
        Scene(const char* sceneFileName) { m_LevelFileName = sceneFileName; }
        ~Scene();

        virtual void Initialize();

        void OnWindowResize(unsigned int width, unsigned int height);

        virtual void Update(float deltatime);
        void Draw();

        bool AddCamera(GameObject* camera);
        void RemoveCamera(GameObject* camera);
        void SetupCameras();

        bool AddLight(GameObject* light);
        void RemoveLight(GameObject* light);

        bool AddObjectToScene(GameObject* object);
        void RemoveObjectFromScene(GameObject* object);

        void RemoveAllObjectsFromScene();

        void SaveScene();
        void LoadScene(const char* sceneFileName);
        void ReloadScene();

        GameObject* GetGameObject(const char* name);
        bool GetIsEnabled() { return m_IsEnabled; };
        bool GetIsPaused() { return m_IsPaused; };
        std::vector<GameObject*> GetCameraList() { return m_CameraList; };
        std::map<std::string, GameObject*> GetObjectList() { return m_pGameObjects; };
        int GetCurrentCamera() { return m_CurrentCamera; };
        std::vector<GameObject*> GetLightList() { return m_LightList; };
        eSceneTypes GetSceneID() { return m_ID; }

        void SetIsEnabled(bool isEnabled) { m_IsEnabled = isEnabled; };
        void SetIsPaused(bool isPaused) { m_IsPaused = isPaused; };
        void SetCurrentCamera(int camera) { m_CurrentCamera = camera; };

        void ToggleIsPaused() { m_IsPaused = !m_IsPaused; };

    protected:
        void CameraInput(float deltatime);

        bool m_IsEnabled = false;
        bool m_IsPaused = false;
        std::string m_LevelFileName = gc_DefaultCharPtrValue;// "Uninitialized"; // TODO: Find out why I can't assign gc_DefaultCharPtrValue
        MyMatrix* m_pViewMatrix = nullptr; // TODO:: create cameras with different view matrices

        std::map<std::string, GameObject*> m_pGameObjects;
        eSceneTypes m_ID = eSceneTypes::Scene_Null;

        int m_CurrentCamera = 0;
        std::vector<GameObject*> m_CameraList;

        std::vector<GameObject*> m_LightList;

        std::vector<GameObject*> m_SceneDrawList;
    };

}
