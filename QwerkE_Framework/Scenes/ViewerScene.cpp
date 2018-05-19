#include "ViewerScene.h"
#include "../Systems/ServiceLocator.h"
#include "../Systems/ResourceManager.h"
#include "../Systems/Factory/Factory.h"

ViewerScene::ViewerScene()
{
	m_ID = eSceneTypes::Scene_ViewerScene;
}

ViewerScene::~ViewerScene()
{
	m_CameraList.Clear();
}

void ViewerScene::Initialize()
{
	Factory* t_pFactory = (Factory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Entity);
	ResourceManager* t_pResourceManager = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	// cameras
	t_pFactory->CreateThirdPersonCamera(this, vec3(0, 0, 5));
	Scene::SetupCameras();

	// lights
	t_pFactory->CreateLight(this, vec3(0, 5, -10));

	// actor
	// none. Add one and use it to take thumbnail pictures for assets
	t_pFactory->CreateCube(this, vec3(0,0,10));
}

void ViewerScene::p_Update(double TimePassed)
{
	Scene::p_Update(TimePassed);
}

void ViewerScene::Draw()
{
	Scene::Draw(m_CameraList.At(m_CurrentCamera));
}