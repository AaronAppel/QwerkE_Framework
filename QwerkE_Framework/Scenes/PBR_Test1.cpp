#include "PBR_Test1.h"
#include "../Systems/SceneManager.h"
#include "../Systems/DataManager/DataManager.h"
#include "../Systems/ServiceLocator.h"
#include "../Entities/GameObject.h"
#include "../QwerkE_Enums.h"
#include "../Systems/Factory/Factory.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Mesh/MeshFactory.h"
#include "../Systems/ServiceLocator.h"
#include "../Graphics/Shader/ShaderProgram.h"
#include "../Systems/ResourceManager/ResourceManager.h"
#include "../Components/Time.h"

PBR_Test1::PBR_Test1() : Scene()
{
	m_ID = eSceneTypes::Scene_PBR_Test1;
	m_LevelFileName = "PBR_Test1.qscene";
}

PBR_Test1::~PBR_Test1()
{
	m_CameraList.clear();
}

void PBR_Test1::Initialize()
{
    Factory* t_pFactory = (Factory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Entity);
	ResourceManager* t_pResourceManager = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	// load shaders to make them available at launch
	t_pResourceManager->GetShaderProgram("PBR1.ssch");
	t_pResourceManager->GetSound("bounce.wav");
	// t_pResourceManager->GetShaderProgram("test_normal.ssch");

	{
		// Create scene cameras
		t_pFactory->CreateFreeCamera(this, vec3(2, 0, -2))->SetRotation(vec3(0,45,0));
		Scene::SetupCameras();
	}

	{	// Create scene objects
		for (int i = 0; i < 10; i++)
		{
			t_pFactory->CreateCube(this, vec3(i -5, i - 5, i));
			t_pFactory->CreateSphere(this, vec3(i - 5, i - 5, i));
		}

		GameObject* plane = t_pFactory->CreatePlane(this, vec3(0, 0, 20));
		plane->SetScale(vec3(10, 10, 10));
		plane->SetRotation(vec3(90, 0, 0));

		m_Subjects.push_back(t_pFactory->CreateCube(this, vec3(0, 0, -5)));
		t_pFactory->CreatePlane(this, vec3(2, 0, -5))->SetRotation(vec3(90, 0, 0));
		m_Subjects.push_back(t_pFactory->CreateSphere(this, vec3(-2, 0, -5)));
	}

	{	// Create scene lights
		t_pFactory->CreateLight(this, vec3(10, 5, -10));
	}
}

void PBR_Test1::p_Running(double deltatime)
{
	for (size_t i = 0; i < m_Subjects.size(); i++)
	{
		m_Subjects[i]->SetRotation(vec3(m_Subjects[i]->GetRotation().x,
			m_Subjects[i]->GetRotation().y + 45.0f * deltatime,
			m_Subjects[i]->GetRotation().z));

		if (m_Subjects[i]->GetRotation().y >= 360.0f)
			m_Subjects[i]->SetRotation(vec3(m_Subjects[i]->GetRotation().x, m_Subjects[i]->GetRotation().y - 360.0f, m_Subjects[i]->GetRotation().z));

	}
	Scene::p_Running(deltatime);
}

void PBR_Test1::Draw()
{
	//g_Shader2->Use();
	//g_Shader2->SetUniformFloat4("ObjectColour", 1.0f, 0.5f, 1.0f, 1.0f);
	Scene::Draw(m_CameraList.at(m_CurrentCamera));

	//g_Shader2->Use();
	//g_Shader2->SetUniformFloat4("ObjectColour", 1.0f, 0.5f, 1.0f, 1.0f);
	//g_TestMesh->Draw();
}