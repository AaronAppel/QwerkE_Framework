#include "Factory.h"
#include "../../Scenes/Scene.h"
#include "../../QwerkE_Common/Utilities/Helpers.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Entities/Routines/RenderRoutine.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../../Entities/Components/RenderComponent.h"

#include "../FileSystem/FileSystem.h"
#include "../ServiceLocator.h"
#include "../../QwerkE_Framework/QwerkE_Common/Utilities/StringHelpers.h"
#include "../../Headers/QwerkE_Directory_Defines.h"
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
	AddModelComponentFromSchematic(t_SkyBox, null_object_schematic);

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
GameObject* Factory::CreateTestCube(Scene* scene, vec3 position)
{
	GameObject* t_Cube = new GameObject(scene, position);
	// info //
	t_Cube->SetName("Object" + std::to_string(helpers_GetUniqueID()));
	t_Cube->SetRenderOrder(50);
	t_Cube->SetTag(GO_Tag_TestModel);

	// Rendering //
	// AddModelComponentFromSchematic(t_Cube, "nanosuit.osch");

	RenderComponent* rComp = new RenderComponent();

	Renderable renderable;
	renderable.SetMaterial(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("brickwall.msch"));
	renderable.SetShader(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetShaderProgram("LitMaterialNormal.ssch"));

	Mesh* mesh = new Mesh();
	mesh = MeshFactory::CreateCube(vec3(10, 10, 10), vec2(1, 1), false);
	mesh->SetName("Cube");
	mesh->SetFileName("None");
	((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->AddMesh("Cube", mesh);
	renderable.SetMesh(mesh);

	rComp->AddRenderable(renderable);

	t_Cube->AddComponent(rComp);

	// render routine
	t_Cube->AddRoutine((Routine*)new RenderRoutine());

	if (scene->AddObjectToScene(t_Cube))
	{
		m_Created++;
		return t_Cube;
	}

	delete t_Cube;
	return nullptr;
}

GameObject* Factory::CreateTestModel(Scene* scene, vec3 position)
{
	GameObject* t_Model = new GameObject(scene, position);
	// info //
	t_Model->SetName("Object" + std::to_string(helpers_GetUniqueID()));
	t_Model->SetRenderOrder(50);
	t_Model->SetTag(GO_Tag_TestModel);

	// Rendering //
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