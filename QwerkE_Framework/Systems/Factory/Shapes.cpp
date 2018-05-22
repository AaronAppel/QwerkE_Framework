#include "Factory.h"
#include "../../Scenes/Scene.h"
#include "../../../QwerkE_Common/Utilities/Helpers.h"
#include "../../QwerkE_Enums.h"
#include "../../Entities/Components/Component.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Entities/Routines/RenderRoutine.h"
#include "../../Systems/Graphics/Mesh/Mesh.h"
#include "../../Systems/Graphics/Gfx_Classes/MaterialData.h"

/* Shapes */
GameObject* Factory::CreateCube(Scene* scene, vec3 position)
{
	GameObject* t_Cube = new GameObject(scene, position);
	t_Cube->SetName("Cube" + std::to_string(helpers_GetUniqueID()));
	t_Cube->SetTag(eGameObjectTags::GO_Tag_Cube);
	t_Cube->SetRenderOrder(50);

	AddModelComponent(t_Cube, "Cube.osch");

	RenderRoutine* renderRoutine = new RenderRoutine();
	t_Cube->AddRoutine((Routine*)renderRoutine);

	if (scene->AddObjectToScene(t_Cube))
	{
		m_Created++;
		return t_Cube;
	}

	// delete t_Cube;
	return t_Cube;
}

GameObject* Factory::CreatePlane(Scene* scene, vec3 position)
{
	GameObject* t_Plane = new GameObject(scene, position);
	t_Plane->SetName("Plane" + std::to_string(helpers_GetUniqueID()));
	t_Plane->SetTag(eGameObjectTags::GO_Tag_Plane);
	t_Plane->SetRenderOrder(50);

	AddModelComponent(t_Plane, "Cube.osch");

	RenderRoutine* renderRoutine = new RenderRoutine();
	t_Plane->AddRoutine((Routine*)renderRoutine);

	if (scene->AddObjectToScene(t_Plane))
	{
		m_Created++;
		return t_Plane;
	}

	delete t_Plane;
	return nullptr;
}