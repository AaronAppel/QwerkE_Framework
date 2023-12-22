#include "Factory.h"

#include "../Graphics/Mesh/MeshFactory.h"
#include "../Resources/Resources.h"
#include "../Scenes/Scene.h"
#include "../Scenes/Entities/Routines/RenderRoutine.h"
#include "../Scenes/Entities/Components/RenderComponent.h"
#include "../Graphics/DataTypes/Material.h"
#include "../Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../../FileSystem/FileSystem.h"
#include "../../Utilities/StringHelpers.h"
#include "../../Utilities/Helpers.h"
#include "../../Headers/QwerkE_Defines.h"

namespace QwerkE {

    // Scenery + Props
    GameObject* Factory::CreateSkyBox(Scene* scene, vec3 position)
    {
        if (!scene)
            return nullptr;

        GameObject* t_SkyBox = CreateGameObject(scene);
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
            m_CreatedCount++;
            return t_SkyBox;
        }

        delete t_SkyBox;
        return nullptr;
    }
    // Testing
    GameObject* Factory::CreateTestCube(Scene* scene, vec3 position)
    {
        if (!scene)
            return nullptr;

        GameObject* t_Cube = new GameObject(scene, position);
        // info //
        t_Cube->SetName("Object" + std::to_string(helpers_GetUniqueID()));
        t_Cube->SetRenderOrder(50);
        t_Cube->SetTag(GO_Tag_TestModel);

        // Rendering //
        // AddModelComponentFromSchematic(t_Cube, "nanosuit.osch");

        RenderComponent* rComp = new RenderComponent();

        Renderable renderable;
        renderable.SetMaterial(Resources::GetMaterial("brickwall.msch"));
        renderable.SetShader(Resources::GetShaderProgram("LitMaterialNormal.ssch"));

        Mesh* mesh = new Mesh();
        mesh = MeshFactory::CreateCube(vec3(10, 10, 10), vec2(1, 1), false);
        mesh->SetName("Cube");
        mesh->SetFileName("None");
        Resources::AddMesh("Cube", mesh);
        renderable.SetMesh(mesh);

        rComp->AddRenderable(renderable);

        t_Cube->AddComponent(rComp);

        // render routine
        t_Cube->AddRoutine((Routine*)new RenderRoutine());

        if (scene->AddObjectToScene(t_Cube))
        {
            m_CreatedCount++;
            return t_Cube;
        }

        delete t_Cube;
        return nullptr;
    }

    GameObject* Factory::CreateTestModel(Scene* scene, vec3 position)
    {
        if (!scene) return nullptr;

        GameObject* t_Model = new GameObject(scene, position);
        t_Model->SetName("Object" + std::to_string(helpers_GetUniqueID()));
        t_Model->SetRenderOrder(50);
        t_Model->SetTag(GO_Tag_TestModel);

        AddModelComponentFromSchematic(t_Model, "nanosuit.osch");

        t_Model->AddRoutine((Routine*)new RenderRoutine());

        if (scene->AddObjectToScene(t_Model))
        {
            m_CreatedCount++;
            return t_Model;
        }

        delete t_Model;
        return nullptr;
    }

    GameObject* Factory::CreateEmptyGameObject(Scene* scene, vec3 position)
    {
        if (scene == nullptr) return nullptr;

        GameObject* t_Object = new GameObject(scene, position);

        if (scene)
        {
            if (scene->AddObjectToScene(t_Object))
            {
                m_CreatedCount++;
                t_Object->SetName(std::string("abc") + std::to_string(m_CreatedCount)); // #TODO Improve string concatenation
                return t_Object;
            }
        }

        delete t_Object;
        return nullptr;
    }

}
