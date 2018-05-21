#include "Factory.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Systems/ServiceLocator.h"
#include "../../Entities/Components/ModelComponent.h"

Factory::Factory()
{
	m_pResources = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
}

Factory::~Factory()
{
}

void Factory::ClearResources()
{
	m_pResources->DeleteAllResources(); // TODO: Shouldn't have access to resources through factory
}
GameObject* Factory::CreateGameObject(Scene* scene)
{
	return new GameObject(scene);
}
GameObject* Factory::CreateGameObject(Scene* scene, vec3 position)
{
	return new GameObject(scene, position);
}

ModelComponent* Factory::AddModelComponent(GameObject* entity, const char* objectRecipeName)
{
	ModelComponent* mComp = new ModelComponent();

	// object recipe
	// ObjectReciper1.orec
	mComp->SetData();
	// renderComp->SetShader(m_pResources->GetShader("LitMaterial"));
	// renderComp->SetModel(m_pResources->GetModel("Plane.obj"));
	// renderComp->SetMaterial(m_pResources->GetMaterial("container.mat"));
	// renderComp->SetColour(vec4(RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), RandFloatInRange(0.0f, 1.0f), 1)); // random intial colour

	// TODO: Read model file and load matching values
	mComp->SetData(); // TODO:
	entity->AddComponent((Component*)mComp);
	return mComp;
}