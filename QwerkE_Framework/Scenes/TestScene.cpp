#include "../Systems/SceneManager.h"
#include "TestScene.h"
#include "../Systems/DataManager/DataManager.h"
#include "../Systems/ServiceLocator.h"
#include "../Entities/GameObject.h"
#include "../QwerkE_Enums.h"
#include "../Systems/Factory/Factory.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Mesh/MeshFactory.h"
#include "../Systems/ServiceLocator.h"
#include "../Systems/ResourceManager/ResourceManager.h"
#include "../Components/Time.h"

TestScene::TestScene() : Scene()
{
	m_ID = eSceneTypes::Scene_TestScene;
	m_LevelFileDir = "Resources/LevelData/TestScene.json";
}

TestScene::~TestScene()
{
	m_CameraList.Clear();
}

GameObject* obj;
void TestScene::Initialize()
{
    Factory* t_pFactory = (Factory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Entity);
	ResourceManager* t_pResourceManager = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
	// TODO: Resolve feature
    //DataManager* t_pDataManager = m_pGameCore->GetDataManager();

	//t_pDataManager->LoadScene(this, m_LevelFileDir); // Load scene

	// return;
	{
		// Create scene cameras
		const int t_CamMax = 1;
		t_pFactory->CreateFreeCamera(this, vec3(0, 0, 5));
		t_pFactory->CreateFreeCamera(this, vec3(0, 0, 15));
		// setup view/projection matrices
		Scene::SetupCameras();
	}

	{	// Create scene objects
		// cubes
		int cubes = 2;
		// t_pFactory->CreateCube(this, vec3(2, 2, 30));
		// t_pFactory->CreateCube(this, vec3(-2, 1, 40));

		obj = t_pFactory->CreateCube(this, vec3(0,0, 150));
		obj->SetRotation(vec3(45,45,45));
		// plane
		// t_pFactory->CreatePlane(this, vec3(0, -1, 0));
	}

	{	// Create scene lighting
		int lights = 0;
		for (int i = 0; i < lights; i++)
		{
			t_pFactory->CreateLight(this, vec3((i + 1) * -3.0f, (i + 1) * -1.0f, (i + 1) * -3.0f));
		}
		t_pFactory->CreateLight(this, vec3(0, 5, -10));
	}
	//TEST:
	obj = t_pFactory->CreateTestModel(this, vec3(0, -5, 100));
	// obj = t_pFactory->CreateCube(this, vec3(0, 0, 10));
	obj->SetRotation(vec3(0,0,0));
}

void TestScene::p_Update(double deltatime)
{
    obj->SetRotation(vec3(obj->GetRotation().x,
        obj->GetRotation().y + 0.002f / QwerkE::Time::GetDeltaTime(),
		obj->GetRotation().z));

	if (obj->GetRotation().y >= 360.0f)
		obj->SetRotation(vec3(obj->GetRotation().x, obj->GetRotation().y - 360.0f, obj->GetRotation().z));

	Scene::p_Update(deltatime);
}

void TestScene::Draw()
{
	//g_Shader2->Use();
	//g_Shader2->SetUniformFloat4("ObjectColour", 1.0f, 0.5f, 1.0f, 1.0f);
	Scene::Draw(m_CameraList.At(m_CurrentCamera));

	//g_Shader2->Use();
	//g_Shader2->SetUniformFloat4("ObjectColour", 1.0f, 0.5f, 1.0f, 1.0f);
	//g_TestMesh->Draw();
}