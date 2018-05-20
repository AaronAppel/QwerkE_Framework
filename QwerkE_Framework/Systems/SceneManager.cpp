#include "SceneManager.h"
#include "../Scenes/TestScene.h"
#include "../Scenes/ViewerScene.h"
#include "../QwerkE_Enums.h"
#include "../Scenes/Scene.h"

#include <map>

SceneManager::SceneManager()
{
	//m_pController = new PlayerController();
}

SceneManager::~SceneManager()
{
	//delete m_pController;
	/*while (m_EventQueue.size() != 0)
	{
		Event* pEvent = m_EventQueue.front();
		m_EventQueue.pop();
		delete pEvent;
	}*/
	for (int i = 0; i < m_Scenes.size(); i++)
	{
		Scene* temp = m_Scenes[(eSceneTypes)i];
		delete temp;
	}
}

void SceneManager::Initialize()
{
	// instantiate and LoadScene() (splash, main menu, game etc...)
	// test screen
	Scene* temp = new TestScene();
	temp->Initialize();
	temp->SetIsEnabled(true);
	m_CurrentScene = temp; // Set current
	m_Scenes[temp->GetSceneID()] = temp;
}

void SceneManager::ResetScene(eSceneTypes type)
{
	m_Scenes[type]->ResetScene();
}

void SceneManager::ResetAll()
{
	for (int i = 0; i < Scene_Max; i++)
	{
		Scene* temp = m_Scenes[(eSceneTypes)i];
		temp->ResetScene();
	}
}

void SceneManager::EnableScene(eSceneTypes type)
{
	m_Scenes[type]->SetIsEnabled(true);
}

void SceneManager::SetCurrentScene(eSceneTypes type)
{
    // TODO: Make sure scene exists
    m_CurrentScene = m_Scenes[type];
	// TODO: Enable new current scene?
}

void SceneManager::DisableScene(eSceneTypes type)
{
	m_Scenes[type]->SetIsEnabled(false);
}

void SceneManager::DisableAll()
{
	for (int i = 0; i < m_Scenes.size(); i++)
	{
		Scene* temp = m_Scenes[(eSceneTypes)i];
		temp->SetIsEnabled(false);
	}
}

void SceneManager::AddScene(Scene* scene)
{
	if (m_Scenes.find(scene->GetSceneID()) == m_Scenes.end())
	{
		m_Scenes[scene->GetSceneID()] = scene;
	}
}

Scene* SceneManager::RemoveScene(Scene* scene)
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

void SceneManager::Update(double deltatime) // update SceneTypes from bottom up (Max-)
{
	if (m_CurrentScene)
	{
		if (m_IsRunning) // Add step-through and pause/play button functionality in debug mode
		if (m_CurrentScene->GetIsEnabled())
		{
			m_CurrentScene->Update(deltatime);
		}
	}
}

void SceneManager::Draw() // draw SceneTypes from top down (0+)
{
	// TODO:: might want to only draw specific scenes
	if (m_CurrentScene)
	{
		if (m_CurrentScene->GetIsEnabled())
		{
			m_CurrentScene->Draw();
		}
	}
}

void SceneManager::DrawScene(eSceneTypes scene)
{
	m_Scenes[scene]->Draw();
}

//void SceneManager::QueueEvent(Event* pEvent)
//{
//	m_EventQueue.push(pEvent);
//}

//void SceneManager::ProcessEvents()
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

//void SceneManager::OnEvent(Event* pEvent)
//{
//#if _WIN32
//#endif // _WIN32
//	// other event types...
//}