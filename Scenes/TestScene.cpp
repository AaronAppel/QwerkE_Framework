#include "../Systems/SceneManager.h"
#include "TestScene.h"
#include "../Systems/DataManager/DataManager.h"
#include "../Systems/Services.h"
#include "../Entities/GameObject.h"
#include "../Headers/QwerkE_Enums.h"
#include "../Systems/Factory/Factory.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Mesh/MeshFactory.h"
#include "../Systems/Services.h"
#include "../Systems/Resources/Resources.h"

namespace QwerkE {

	TestScene::TestScene() : Scene()
	{
		m_ID = eSceneTypes::Scene_TestScene;
		m_LevelFileName = "TestScene.qscene";
	}

	TestScene::~TestScene()
	{
	}

	GameObject* obj;
	void TestScene::Initialize()
	{
		Factory* t_pFactory = (Factory*)QwerkE::Services::GetService(eEngineServices::Factory_Entity);
		// TODO: Resolve feature
		//DataManager* t_pDataManager = m_pGameCore->GetDataManager();

		//t_pDataManager->LoadScene(this, m_LevelFileDir); // Load scene

		// return;
		{
			// Create scene cameras
			const int t_CamMax = 1;
			t_pFactory->CreateFreeCamera(this, vec3(0, 0, 5));
			// t_pFactory->CreateFreeCamera(this, vec3(0, 0, 15));
			// setup view/projection matrices
			Scene::SetupCameras();
		}

		{	// Create scene objects
			// cubes
			int cubes = 2;
			t_pFactory->CreateTestCube(this, vec3(0, 0, 50));
			// t_pFactory->CreateCube(this, vec3(2, 2, 30));
			// t_pFactory->CreateCube(this, vec3(-2, 1, 40));

			// TEST:
			// obj = t_pFactory->CreateTestModel(this, vec3(0, -2, 30));
			// obj->SetRotation(vec3(0, 0, 0));

			for (int i = 0; i < 10; i++)
			{
				// t_pFactory->CreateCube(this, vec3(0, i - 5, 50));
			}
			// plane
			// t_pFactory->CreatePlane(this, vec3(0, -1, 0));
		}

		{	// Create scene lighting
			int lights = 3;
			for (int i = 0; i < lights; i++)
			{
				// t_pFactory->CreateLight(this, vec3((i + 1) * -3.0f, (i + 1) * -1.0f, (i + 1) * -3.0f));
			}
			t_pFactory->CreateLight(this, vec3(0, 5, -10));
		}
	}

	void TestScene::p_Running(double deltatime)
	{
		/*obj->SetRotation(vec3(obj->GetRotation().x,
			obj->GetRotation().y + 90.0f * deltatime,
			obj->GetRotation().z));

		if (obj->GetRotation().y >= 360.0f)
			obj->SetRotation(vec3(obj->GetRotation().x, obj->GetRotation().y - 360.0f, obj->GetRotation().z));*/

		Scene::p_Running(deltatime);
	}

}
