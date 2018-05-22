#include "Factory.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Systems/ServiceLocator.h"
#include "../../Entities/Components/RenderComponent.h"
#include "../Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../QwerkE_Common/Utilities/StringHelpers.h"

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
	RenderComponent* mComp = LoadObjectSchematic(SchematicFolderPath(objectRecipeName));
	entity->AddComponent((Component*)mComp);
	return mComp;
}