#include "Factory.h"
#include "../Resources/Resources.h"
#include "../Scenes/Entities/Components/Camera/CameraComponent.h"
#include "../Scenes/Entities/Components/Camera/FirstPersonCameraComponent.h"
#include "../Scenes/Entities/Components/Camera/FreeCameraComponent.h"
#include "../Scenes/Entities/Components/Camera/StaticCameraComponent.h"
#include "../Scenes/Entities/Components/Camera/ThirdPersonCameraComponent.h"
#include "../Scenes/Entities/Routines/RenderRoutine.h"
#include "../Scenes/Entities/Components/RenderComponent.h"
#include "../Scenes/Entities/GameObject.h"
#include "../../Utilities/Helpers.h"
#include "../../Utilities/StringHelpers.h"
#include "../../FileSystem/FileSystem.h"

#include <string>

namespace QwerkE {

    /* Cameras */
    GameObject* Factory::CreateFreeCamera(Scene* scene, vec3 position)
    {
        return InternalCreateCamera(scene, position, CamType_FreeCam); // TODO: Is this a good way of re-using CreateCamera()?
    }

    GameObject* Factory::CreateFirstPersonCamera(Scene* scene, vec3 position)
    {
        return InternalCreateCamera(scene, position, CamType_FirstPerson);
    }

    GameObject* Factory::CreateThirdPersonCamera(Scene* scene, vec3 position)
    {
        return InternalCreateCamera(scene, position, CamType_ThirdPerson);
    }

    GameObject* Factory::CreateStaticCamera(Scene* scene, vec3 position)
    {
        return InternalCreateCamera(scene, position, CamType_Static);
    }

    GameObject* Factory::InternalCreateCamera(Scene* scene, vec3 position, eCamType camType)
    {
        GameObject* t_pCamera = CreateGameObject(scene);
        t_pCamera->SetTag(GO_Tag_Camera);
        t_pCamera->SetPosition(position);
        t_pCamera->SetRenderOrder(-1);
        t_pCamera->SetName("Camera" + std::to_string(helpers_GetUniqueID()));

        CameraComponent* t_pCamComp = nullptr;

        switch (camType)
        {
        case CamType_FreeCam:
            t_pCamComp = new FreeCameraComponent();
            t_pCamComp->SetType(CamType_FreeCam);
            break;
        case CamType_FirstPerson:
            t_pCamComp = new FirstPersonCameraComponent();
            t_pCamComp->SetType(CamType_FirstPerson);
            break;
        case CamType_ThirdPerson:
            t_pCamComp = new ThirdPersonCameraComponent();
            t_pCamComp->SetType(CamType_ThirdPerson);
            break;
        case CamType_Static:
            t_pCamComp = new StaticCameraComponent();
            t_pCamComp->SetType(CamType_Static); // TODO: Set in component constructor.
            break;
        }

        t_pCamera->AddComponent(t_pCamComp); // add to object
        t_pCamComp->Setup();
        t_pCamComp->SetTargetPosition(vec3(0, 0, 0));

        // ((FileSystem*)QwerkE::Services::GetService(eEngineServices::FileSystem))->LoadModelFileToMeshes(MeshFolderPath("Camera.obj"));
        AddModelComponentFromSchematic(t_pCamera, "camera.osch");

        RenderRoutine* renderRoutine = new RenderRoutine();
        t_pCamera->AddRoutine((Routine*)renderRoutine);

        if (scene->AddCamera(t_pCamera)) // add to scene
        {
            m_CreatedCount++;
            return t_pCamera; // Success
        }

        delete t_pCamera;
        delete t_pCamComp;
        return nullptr; // Failed
    }

}
