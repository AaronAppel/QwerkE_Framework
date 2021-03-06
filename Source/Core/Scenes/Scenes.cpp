#include "Scenes.h"
#include "../Scenes/TestScene.h"
#include "../Scenes/ViewerScene.h"
#include "../Scenes/PBR_Test1.h"
#include "../Scenes/Scene.h"
#include "../../Headers/QwerkE_Enums.h"
#include "../../FileSystem/FileIO/FileUtilities.h"
#include "../../Debug/Profiler/Profiler.h"

#include <map>

namespace QwerkE {

    bool Scenes::m_IsRunning = true;
    Scene* Scenes::m_CurrentScene = nullptr;
    std::map<eSceneTypes, Scene*> Scenes::m_Scenes;

	Scenes::Scenes()
	{
		//m_pController = new PlayerController();
	}

	Scenes::~Scenes()
	{
		for (unsigned int i = 0; i < m_Scenes.size(); i++)
		{
			delete m_Scenes[(eSceneTypes)i];
		}
	}

	void Scenes::Initialize()
	{
        // TODO: Scenes should be added somewhere else
        // TODO: Load scenes from the Resources/Scenes/... folder to use persistent data
	 	// auto scenes = Resources::SeeScenes();
		// if (scenes.empty())
		// {
		//      Create empty scene
		// }

		const char* prefPath = ConfigsFolderPath("preferences.qpref");
		// TODO: does this free memory correctly? std::string pref = ConfigsFolderPath("preferences.qpref");

		if (FileExists(prefPath))
		{
			cJSON* root = OpencJSONStream(prefPath);
			cJSON* scenesArray = GetItemFromRootByKey(root, "Scenes");

			unsigned int numScenes = GetArraySize(scenesArray);
			for (unsigned int i = 0; i < numScenes; i++)
			{
				cJSON* scene = GetItemFromArrayByIndex(scenesArray, i);

				const char* sceneFileName = scene->valuestring;

				if (FileExists(SceneFolderPath(sceneFileName)) == false)
                {
                    LOG_WARN("Scenes::Initialize(): File not found: {0}", sceneFileName);
					continue;
				}

				Scene* newScene = new Scene(sceneFileName); // TODO: Improve how scene file names are assigned

				newScene->LoadScene(sceneFileName);

				if (i == 0)
					m_CurrentScene = newScene; // TODO: Improve default starting scene selection/specification

				// TODO: m_Scenes[sceneFileName] = temp;
				m_Scenes[(eSceneTypes)i] = newScene; // TODO: Deprecate enum type
			}

			ClosecJSONStream(root);
		}

		if (m_Scenes.empty())
        {
			Scene* emptyScene = new Scene();
			emptyScene->Initialize();
			emptyScene->SetIsEnabled(true);
            m_CurrentScene = emptyScene;
            LOG_WARN("Null scene loaded because no valid scene was found in: {0}", prefPath);
		}
		// TODO: free prefPath memory
	}

	void Scenes::ResetScene(eSceneTypes type)
	{
		m_Scenes[type]->ResetScene();
	}

	void Scenes::ResetAll()
	{
		for (int i = 0; i < Scene_Max; i++)
		{
			Scene* temp = m_Scenes[(eSceneTypes)i];
			temp->ResetScene();
		}
	}

	void Scenes::EnableScene(eSceneTypes type)
	{
		m_Scenes[type]->SetIsEnabled(true);
	}

	void Scenes::SetCurrentScene(eSceneTypes type)
	{
		// TODO: Make sure scene exists
		// m_CurrentScene = m_Scenes[type];
		// TODO: Enable new current scene?
	}

	void Scenes::DisableScene(eSceneTypes type)
	{
		m_Scenes[type]->SetIsEnabled(false);
	}

	void Scenes::DisableAll()
	{
		for (unsigned int i = 0; i < m_Scenes.size(); i++)
		{
			Scene* temp = m_Scenes[(eSceneTypes)i];
			temp->SetIsEnabled(false);
		}
	}

	void Scenes::AddScene(Scene* scene)
	{
		if (m_Scenes.find(scene->GetSceneID()) == m_Scenes.end())
		{
			m_Scenes[scene->GetSceneID()] = scene;
		}
	}

	Scene* Scenes::RemoveScene(Scene* scene)
	{
		if (m_Scenes.find(scene->GetSceneID()) != m_Scenes.end())
		{
			m_Scenes.erase(scene->GetSceneID());
			Scene* returnScene = m_Scenes[scene->GetSceneID()];
			return returnScene;
		}
		else
			return nullptr;
	}

	void Scenes::Update(double deltatime) // update SceneTypes from bottom up (Max-)
	{
		PROFILE_SCOPE("Scene Manager Update");

		if (Input::FrameKeyAction(eKeys::eKeys_P, eKeyState::eKeyState_Press)) // pause entire scene
		{
			static bool paused = false;
			paused = !paused;
			if (paused)
			{
				GetCurrentScene()->SetState(eSceneState::SceneState_Paused);
			}
			else
			{
				GetCurrentScene()->SetState(eSceneState::SceneState_Running);
			}
		}
		else if (Input::FrameKeyAction(eKeys::eKeys_Z, eKeyState::eKeyState_Press))// pause actor updates
		{
			static bool frozen = false;
			frozen = !frozen;
			if (frozen)
			{
				GetCurrentScene()->SetState(eSceneState::SceneState_Frozen);
			}
			else
			{
				GetCurrentScene()->SetState(eSceneState::SceneState_Running);
			}
		}

		if (m_CurrentScene)
		{
			if (m_IsRunning) // Add step-through and pause/play button functionality in debug mode
			{
				if (m_CurrentScene->GetIsEnabled())
				{
					m_CurrentScene->Update(deltatime);
				}
			}
		}
	}

	void Scenes::DrawCurrentScene() // draw SceneTypes from top down (0+)
    {
        PROFILE_SCOPE("Scene Manager Render");
		if (m_CurrentScene && m_CurrentScene->GetIsEnabled())
		{
			m_CurrentScene->Draw();
		}
	}

	void Scenes::DrawScene(eSceneTypes scene)
	{
		m_Scenes[scene]->Draw();
	}

	//void Scenes::QueueEvent(Event* pEvent)
	//{
	//	m_EventQueue.push(pEvent);
	//}

	//void Scenes::ProcessEvents()
	//{
	//	while (m_EventQueue.size() != 0)
	//	{
	//		Event* pEvent = m_EventQueue.front();
	//		m_EventQueue.pop();
	//
	//		this->OnEvent(pEvent);
	//		delete pEvent;
	//	}
	//}

	//void Scenes::OnEvent(Event* pEvent)
	//{
	//#if _WIN32
	//#endif // _WIN32
	//	// other event types...
	//}

}
