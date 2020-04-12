#ifndef _Scenes_H_
#define _Scenes_H_

#include "../Headers/QwerkE_Enums.h"
#include <map>

namespace QwerkE {

    class Scenes
    {
    public:
        Scenes();
        ~Scenes();

        static void Initialize();

        static void ResetScene(eSceneTypes type);
        static void ResetAll();

        // TODO: Scene loading
        static void EnableScene(eSceneTypes type);
        static void SetCurrentScene(eSceneTypes type);
        static void DisableScene(eSceneTypes type);
        static void DisableAll();

        static void AddScene(Scene* scene);
        static Scene* RemoveScene(Scene* scene);

        //void QueueEvent(Event* pEvent);

        static void Update(double deltatime);
        static void DrawCurrentScene();
        static void DrawScene(eSceneTypes scene);

        /* Getters + Setters */
        // getters
        static Scene* GetScene(eSceneTypes a_SceneType) { return m_Scenes[a_SceneType]; };
        static Scene* GetCurrentScene() { return m_CurrentScene; };
        static int SceneCount() { return m_Scenes.size(); };
        static const std::map<eSceneTypes, Scene*>* LookAtScenes() { return &m_Scenes; };

    private:
        // functions
        //void ProcessEvents();
        //void OnEvent(Event* pEvent);

        // variables
        static bool m_IsRunning; // Add step-through and pause/play button functionality in debug mode
        static Scene* m_CurrentScene;
        //std::queue<Event*> m_EventQueue;
        static std::map<eSceneTypes, Scene*> m_Scenes;
        //PlayerController* m_pController = nullptr;
    };

}
#endif // _Scenes_H_
