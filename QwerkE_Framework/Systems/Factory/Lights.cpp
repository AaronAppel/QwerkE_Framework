#include "Factory.h"
#include "../../Scenes/Scene.h"
#include "../../../QwerkE_Common/Utilities/Helpers.h"
#include "../../Entities/Components/RenderComponent.h"
#include "../../Entities/Components/LightComponent.h"
#include "../../Systems/ResourceManager.h"
#include "../../Entities/Routines/RenderRoutine.h"

/* Lights */
// Point Light
GameObject* Factory::CreateLight(Scene* scene, vec3 position)
{
	GameObject* t_pLight = this->CreateGameObject(scene);
	t_pLight->SetTag(eGameObjectTags::GO_Tag_Light);
	t_pLight->SetPosition(position);
	t_pLight->SetRenderOrder(-1);
	t_pLight->SetName("Light" + std::to_string(helpers_GetUniqueID()));

	LightComponent* t_pLightComp = new LightComponent();
	t_pLightComp->SetColour(vec3(1.0f, 1.0f, 1.0f));

	// Rendering
	RenderComponent* renderComp = new RenderComponent();
	renderComp->SetModel(m_pResources->GetModel("Light_Bulb.obj"));

	renderComp->SetShader(m_pResources->GetShader("Basic3D"));

	renderComp->SetColour(vec4(t_pLightComp->GetColour(), 1.0f));

	RenderRoutine* renderRoutine = new RenderRoutine();
	// Add
	t_pLight->AddComponent(t_pLightComp);
	t_pLight->AddComponent(renderComp);
	t_pLight->AddRoutine((Routine*)renderRoutine);

	if (scene->AddLight(t_pLight))
	{
		m_Created++;
		return t_pLight;
	}

	delete t_pLight;
	return nullptr;
}