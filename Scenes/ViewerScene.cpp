#include "ViewerScene.h"
#include "../Systems/ServiceLocator.h"
#include "../Systems/ResourceManager/ResourceManager.h"
#include "../Systems/Factory/Factory.h"

ViewerScene::ViewerScene()
{
	m_ID = eSceneTypes::Scene_ViewerScene;
	m_LevelFileName = "ViewerScene.qscene";
}

ViewerScene::~ViewerScene()
{
}

void ViewerScene::Initialize()
{
	Factory* t_pFactory = (Factory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Entity);
	ResourceManager* t_pResourceManager = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	// Cameras
	t_pFactory->CreateFreeCamera(this, vec3(0, 0, 5));
	Scene::SetupCameras();

	// Lights
	t_pFactory->CreateLight(this, vec3(0, 5, -10));

	// Actors
	// none. Add one and use it to take thumbnail pictures for assets
}

void ViewerScene::p_Update(double TimePassed)
{
	Scene::p_Running(TimePassed);
}