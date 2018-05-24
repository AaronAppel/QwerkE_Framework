#include "Factory.h"
#include "../../Scenes/Scene.h"
#include "../../../QwerkE_Common/Utilities/Helpers.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Entities/Routines/RenderRoutine.h"
#include "../../Graphics/MaterialData.h"
#include "../../Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../../Entities/Components/RenderComponent.h"

#include "../../../QwerkE_Framework/QwerkE_Common/Utilities/FileIO/FileLoader/FileLoader.h"
#include "../../../QwerkE_Framework/QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../QwerkE_Framework/QwerkE_Directory_Defines.h"
#include "../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../QwerkE_Framework/Systems/ResourceManager/ResourceManager.h"

// Scenery + Props
GameObject* Factory::CreateSkyBox(Scene* scene, vec3 position)
{
	GameObject* t_SkyBox = this->CreateGameObject(scene);
	t_SkyBox->SetPosition(position);
	t_SkyBox->SetTag(GO_Tag_SkyBox);
	t_SkyBox->SetRenderOrder(-1);
	t_SkyBox->SetName("SkyBox" + std::to_string(helpers_GetUniqueID()));

	// Rendering
	AddModelComponentFromSchematic(t_SkyBox, "ObjectRecipe1");

	RenderRoutine* renderRoutine = new RenderRoutine();
	// Add
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
	GameObject* t_Model = new GameObject(scene, position);
	// info //
	t_Model->SetName("Object" + std::to_string(helpers_GetUniqueID()));
	t_Model->SetRenderOrder(50);
	t_Model->SetTag(GO_Tag_TestModel);

	// Rendering //
	QwerkE::FileLoader::LoadModelFileToMeshes(MeshFolderPath("nanosuit.obj"));
	QwerkE::FileLoader::LoadMeshInModelByName(MeshFolderPath("nanosuit.obj"), "Arms");

	AddModelComponentFromSchematic(t_Model, "nanosuit.osch");

	// render routine
	t_Model->AddRoutine((Routine*)new RenderRoutine());

	if (scene->AddObjectToScene(t_Model))
	{
		m_Created++;
		return t_Model;
	}

	delete t_Model;
	return nullptr;
}