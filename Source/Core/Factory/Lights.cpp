#include "Factory.h"

#include "../../Utilities/Helpers.h"

#include "../Resources/Resources.h"

#include "../Scenes/Scene.h"
#include "../Scenes/Entities/Components/LightComponent.h"
#include "../Scenes/Entities/Routines/RenderRoutine.h"
#include "../Scenes/Entities/Components/RenderComponent.h"

namespace QwerkE {

    GameObject* Factory::CreateLight(Scene* scene, vec3 position)
    {
        GameObject* t_pLight = CreateGameObject(scene);
        t_pLight->SetTag(eGameObjectTags::GO_Tag_Light);
        t_pLight->SetPosition(position);
        t_pLight->SetRenderOrder(-1);
        t_pLight->SetName("Light" + std::to_string(helpers_GetUniqueID()));

        LightComponent* t_pLightComp = new LightComponent();
        t_pLightComp->SetColour(vec3(1.0f, 1.0f, 1.0f));
        // t_pLightComp->SetType(eLightType::LightType_Point); // #TODO Change default type
        t_pLight->AddComponent(t_pLightComp);

        AddModelComponentFromSchematic(t_pLight, "light.osch");

        RenderRoutine* renderRoutine = new RenderRoutine();
        t_pLight->AddRoutine((Routine*)renderRoutine);

        if (scene->AddLight(t_pLight))
        {
            m_CreatedCount++;
            return t_pLight;
        }

        delete t_pLight;
        return nullptr;
    }

}
