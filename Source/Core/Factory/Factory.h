#pragma once

#include "../../Headers/QwerkE_Enums.h"
#include "../Scenes/Entities/GameObject.h"

namespace QwerkE {

    // #TODO Change the name to be more appropriate. Other factories exist such as MeshFactory and ShaderFactory.
    //  This class could be called EntityFactory and be moved to the System/Entities folder.

    class GameObject;
    class Scene;
    class RenderComponent;

    class Factory
    {
    public:

        static GameObject* CreateCube(Scene* scene, vec3 position);
        static GameObject* CreatePlane(Scene* scene, vec3 position);
        static GameObject* CreateSphere(Scene* scene, vec3 position);
        static GameObject* CreateObjectFromSchematic(const char* schematicName, Scene* scene, vec3 position);

        static GameObject* CreateFreeCamera(Scene* scene, vec3 position);
        static GameObject* CreateFirstPersonCamera(Scene* scene, vec3 position);
        static GameObject* CreateThirdPersonCamera(Scene* scene, vec3 position);
        static GameObject* CreateStaticCamera(Scene* scene, vec3 position);

        static GameObject* CreateLight(Scene* scene, vec3 position);

        static GameObject* CreateSkyBox(Scene* scene, vec3 position);

        static GameObject* CreateTestModel(Scene* scene, vec3 position);
        static GameObject* CreateTestCube(Scene* scene, vec3 position);
        static GameObject* CreateEmptyGameObject(Scene* scene, vec3 position);

    private:
        Factory() = default;
        ~Factory() = default;

        static GameObject* CreateGameObject(Scene* scene);
        static GameObject* CreateGameObject(Scene* scene, vec3 position);
        static GameObject* InternalCreateCamera(Scene* scene, vec3 position, eCamType camType);

        static RenderComponent* AddModelComponentFromSchematic(GameObject* entity, const char* objectRecipeName);

    private:
        static int m_CreatedCount;
    };

}
