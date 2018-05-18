#include "Factory.h"
#include "../../../QwerkE_Common/Utilities/Helpers.h"
#include "../../Entities/Components/CameraComponent.h"
#include "../../Entities/Components/FirstPersonCameraComponent.h"
#include "../../Entities/Components/FreeCameraComponent.h"
#include "../../Entities/Components/StaticCameraComponent.h"
#include "../../Entities/Components/ThirdPersonCameraComponent.h"
#include "../../Entities/GameObject.h"

#include <string>

/* Cameras */
//First Person
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
	GameObject* t_pCamera = this->CreateGameObject(scene);
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
	t_pCamComp->SetTargetPosition(vec3(0,0,0));

	if (scene->AddCamera(t_pCamera)) // add to scene
	{
		m_Created++;
		return t_pCamera; // Success
	}

	delete t_pCamera;
	delete t_pCamComp;
	return nullptr; // Failed
}