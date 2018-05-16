#include "Factory.h"
#include "../../Systems/Graphics/Model/Model.h"
#include "../../Scenes/Scene.h"
#include "../../../QwerkE_Common/Utilities/Helpers.h"
#include "../../Entities/Components/RenderComponent.h"
#include "../../Systems/ResourceManager.h"
#include "../../Entities/Routines/RenderRoutine.h"
#include "../../Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../Systems/ResourceManager.h"

// Scenery + Props
GameObject* Factory::CreateSkyBox(Scene* scene, vec3 position)
{
	GameObject* t_SkyBox = this->CreateGameObject(scene);
	t_SkyBox->SetPosition(position);
	t_SkyBox->SetTag(GO_Tag_SkyBox);
	t_SkyBox->SetRenderOrder(-1);
	t_SkyBox->SetName("SkyBox" + std::to_string(helpers_GetUniqueID()));

	// Rendering
	RenderComponent* renderComp = new RenderComponent();
	renderComp->SetModel(m_pResources->GetModel("Cube"));

	renderComp->SetShader(m_pResources->GetShader("SkyBox"));

	RenderRoutine* renderRoutine = new RenderRoutine();
	// Add
	t_SkyBox->AddComponent((Component*)renderComp);
	t_SkyBox->AddRoutine((Routine*)renderRoutine);

	if (scene->AddObjectToScene(t_SkyBox)) // Add to render list
	{
		m_Created++;
		return t_SkyBox;
	}

	delete t_SkyBox;
	return nullptr;
}
// Testing
GameObject* Factory::CreateTestModel(Scene* scene, vec3 position)
{
	GameObject* t_Model = new GameObject(scene);
	t_Model->SetName("Object" + std::to_string(helpers_GetUniqueID()));
	t_Model->SetRenderOrder(50);
	t_Model->SetTag(GO_Tag_TestModel);
	RenderComponent* renderComp = new RenderComponent();
	renderComp->SetModel(m_pResources->GetModel("nanosuit/nanosuit.obj"));

	// renderComp->SetShader(m_pResources->GetShader("Basic3D"));
	renderComp->SetShader(m_pResources->GetShader("LitMaterial"));
	renderComp->GetModel()->SetupMeshes(renderComp->GetShader());
	// renderComp->SetMaterial(m_pResources->GetMaterial("nanosuit_arms"));
	// renderComp->SetMaterial(m_pResources->GetMaterial("nanosuit_legs"));
	// renderComp->SetMaterial(m_pResources->GetMaterial("nanosuit_body"));
	// renderComp->SetMaterial(m_pResources->GetMaterial("nanosuit_glass"));
	// renderComp->SetMaterial(m_pResources->GetMaterial("nanosuit_helmet"));
	renderComp->SetMaterial(m_pResources->GetMaterial("nanosuit_hand.mat"));

	renderComp->SetColour(vec4(RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), 1));
	t_Model->AddComponent((Component*)renderComp);

	RenderRoutine* renderRoutine = new RenderRoutine();
	t_Model->AddRoutine((Routine*)renderRoutine);
	t_Model->SetPosition(position);

	if (scene->AddObjectToScene(t_Model))
	{
		m_Created++;
		return t_Model;
	}

	delete t_Model;
	return nullptr;
}