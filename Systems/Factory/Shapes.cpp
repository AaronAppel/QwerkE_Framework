#include "Factory.h"
#include "../../Scenes/Scene.h"
#include "../../QwerkE_Common/Utilities/Helpers.h"
#include "../../Headers/QwerkE_Enums.h"
#include "../../Entities/Components/Component.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Entities/Routines/RenderRoutine.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../../Graphics/Material.h"

namespace QwerkE {

    /* Shapes */
    GameObject* Factory::CreateCube(Scene* scene, vec3 position)
    {
        GameObject* t_Cube = new GameObject(scene, position);
        t_Cube->SetName("Cube" + std::to_string(helpers_GetUniqueID()));
        t_Cube->SetTag(eGameObjectTags::GO_Tag_Cube);
        t_Cube->SetRenderOrder(50);

        AddModelComponentFromSchematic(t_Cube, "Cube_UVd.osch");

        t_Cube->AddRoutine((Routine*)new RenderRoutine());

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

        AddModelComponentFromSchematic(t_Plane, "Plane.osch");

        t_Plane->AddRoutine((Routine*)new RenderRoutine());

        if (scene->AddObjectToScene(t_Plane))
        {
            m_Created++;
            return t_Plane;
        }

        delete t_Plane;
        return nullptr;
    }

    GameObject* Factory::CreateSphere(Scene* scene, vec3 position)
    {
        GameObject* t_Sphere = new GameObject(scene, position);
        t_Sphere->SetName("Sphere" + std::to_string(helpers_GetUniqueID()));
        t_Sphere->SetTag(eGameObjectTags::GO_Tag_Sphere);
        t_Sphere->SetRenderOrder(50);

        AddModelComponentFromSchematic(t_Sphere, "Sphere.osch");

        t_Sphere->AddRoutine((Routine*)new RenderRoutine());

        if (scene->AddObjectToScene(t_Sphere))
        {
            m_Created++;
            return t_Sphere;
        }

        delete t_Sphere;
        return nullptr;
    }

}
