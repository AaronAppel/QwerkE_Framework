#include "Factory.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Systems/ServiceLocator.h"
#include "../../Entities/Components/RenderComponent.h"

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

RenderComponent* Factory::AddModelComponent(GameObject* entity, const char* objectRecipeName)
{
	RenderComponent* mComp = new RenderComponent();

	// object recipe
	// TODO: Read recipe file and load matching values
	// ObjectReciper1.orec

	mComp->AppendEmptyRenderables(1);

	mComp->SetShaderAtIndex(0, m_pResources->GetShader("LitMaterial"));
	mComp->SetMaterialAtIndex(0, m_pResources->GetMaterial("container.mat"));
	mComp->SetMeshAtIndex(0, m_pResources->GetMesh("Cube.obj"));


	entity->AddComponent((Component*)mComp);
	return mComp;
}