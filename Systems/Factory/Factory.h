#ifndef _Factory_H_
#define _Factory_H_

#include "../../QwerkE_Common/Math_Includes.h"
#include "../../Headers/QwerkE_Enums.h"
#include "../../Entities/GameObject.h"
#include "../../Scenes/Scene.h"

namespace QwerkE {

    // TODO: Change the name to be more appropriate. Other factories exist such as MeshFactory and ShaderFactory.
    // This class could be called EntityFactory and be moved to the System/Entities folder.

    class Resources;
    class GameObject;
    class Scene;
    class RenderComponent;

    // class MenuWindow;
    // class MenuItem;
    // class Menu;

    class Factory
    {
    public:

        static void ClearResources();

        /* Object creation */
        // Shapes
        static GameObject* CreateCube(Scene* scene, vec3 position);
        static GameObject* CreatePlane(Scene* scene, vec3 position);
        static GameObject* CreateSphere(Scene* scene, vec3 position);
        static GameObject* CreateObjectFromSchematic(const char* schematicName, Scene* scene, vec3 position);

        // Systems
        static GameObject* CreateFreeCamera(Scene* scene, vec3 position);
        static GameObject* CreateFirstPersonCamera(Scene* scene, vec3 position);
        static GameObject* CreateThirdPersonCamera(Scene* scene, vec3 position);
        static GameObject* CreateStaticCamera(Scene* scene, vec3 position);

        // Lighting
        static GameObject* CreateLight(Scene* scene, vec3 position);

        // Scenery + Props
        static GameObject* CreateSkyBox(Scene* scene, vec3 position);

        // Characters

        // Testing
        static GameObject* CreateTestModel(Scene* scene, vec3 position); // Model
        static GameObject* CreateTestCube(Scene* scene, vec3 position);
        static GameObject* CreateEmptyGameObject(Scene* scene, vec3 position);

    private:
        Factory();
        ~Factory();

        // GameObjects
        static GameObject* CreateGameObject(Scene* scene); // TODO: Remove?
        static GameObject* CreateGameObject(Scene* scene, vec3 position);
        static GameObject* InternalCreateCamera(Scene* scene, vec3 position, eCamType camType);

        // Helpers
        static RenderComponent* AddModelComponentFromSchematic(GameObject* entity, const char* objectRecipeName);

    private:
        static int m_Created;
    };

}
#endif //!_Factory_H_
