#ifndef _Factory_H_
#define _Factory_H_

#include "../../QwerkE_Common/Math_Includes.h"
#include "../../Headers/QwerkE_Enums.h"
#include "../../Entities/GameObject.h"
#include "../../Scenes/Scene.h"

class ResourceManager;
class GameObject;
class Scene;
class MenuWindow;
class MenuItem;
class Menu;
class RenderComponent;

class Factory
{
public:
	Factory();
	~Factory();

	void ClearResources();

	/* Object creation */
	// Shapes
	GameObject* CreateCube(Scene* scene, vec3 position);
	GameObject* CreatePlane(Scene* scene, vec3 position);
	GameObject* CreateSphere(Scene* scene, vec3 position);
	GameObject* CreateObjectFromSchematic(const char* schematicName, Scene* scene, vec3 position);

	// Systems
	GameObject* CreateFreeCamera(Scene* scene, vec3 position);
	GameObject* CreateFirstPersonCamera(Scene* scene, vec3 position);
	GameObject* CreateThirdPersonCamera(Scene* scene, vec3 position);
	GameObject* CreateStaticCamera(Scene* scene, vec3 position);

	// Lighting
	GameObject* CreateLight(Scene* scene, vec3 position);

	// Scenery + Props
	GameObject* CreateSkyBox(Scene* scene, vec3 position);

	// Characters

	// Testing
	GameObject* CreateTestModel(Scene* scene, vec3 position); // Model
	GameObject* CreateTestCube(Scene* scene, vec3 position);

private:
	// Variables
	int m_Created = 0;
	ResourceManager* m_pResources = nullptr;

	/* Private functions */
	// GameObjects
	GameObject* CreateGameObject(Scene* scene); // TODO: Remove?
	GameObject* CreateGameObject(Scene* scene, vec3 position);
	GameObject* InternalCreateCamera(Scene* scene, vec3 position, eCamType camType);

	// helpers
	RenderComponent* AddModelComponentFromSchematic(GameObject* entity, const char* objectRecipeName);
};

#endif //!_Factory_H_
