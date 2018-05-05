#include "SceneManager.h"
#include "TestScene.h"
#include "../Systems/DataManager.h"
#include "../Systems/ServiceLocator.h"
#include "../Systems/Graphics/OpenGLHelpers.h"
#include "../Systems/Graphics/Sprite/Sprite.h"
#include "../Entities/GameObject.h"
#include "../QwerkE_Enums.h"
#include "../Systems/GameCore.h"
#include "../Systems/Factory/Factory.h"
#include "../Systems/Graphics/Model/Mesh/Mesh.h"
#include "../Systems/Graphics/Model/Mesh/MeshFactory.h"
#include "../Systems/Graphics/ShaderProgram/ShaderProgram.h"
#include "../Systems/Time.h"

TestScene::TestScene() : Scene()
{
	m_ID = Scene_TestScene;
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
	Scene::SetupCameras();

	// return;
	{
		// Create scene cameras
		const int t_CamMax = 1;
		t_pFactory->CreateFreeCamera(this, vec3(0, 0, 5));
		// setup view/projection matrices
		Scene::SetupCameras();
	}

	{	// Create scene objects
		// cubes
		int cubes = 2;
		t_pFactory->CreateCube(this, vec3(2, 2, 30));
		t_pFactory->CreateCube(this, vec3(-2, 1, 40));

		obj = t_pFactory->CreateCube(this, vec3(0,0, 20));
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
}

void TestScene::p_Update(double deltatime)
{
    obj->SetRotation(vec3(obj->GetRotation().x,
        obj->GetRotation().y + 0.002f / QwerkE::Time::GetDeltaTime(),
        0));
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