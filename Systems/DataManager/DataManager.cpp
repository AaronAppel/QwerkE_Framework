#include "DataManager.h"
#include "../Factory/Factory.h"
#include "../../QwerkE_Common/Libraries/cJSON_Interface/cJSONInterface.h"
#include "../../Entities/GameObject.h"
#include "../../Entities/Components/Camera/CameraComponent.h"
#include "../../Entities/Components/Camera/FreeCameraComponent.h"
#include "../../Entities/Components/Camera/FirstPersonCameraComponent.h"
#include "../../Entities/Components/Camera/StaticCameraComponent.h"
#include "../../Entities/Components/Camera/ThirdPersonCameraComponent.h"
#include "../../Entities/Components/LightComponent.h"
#include "../../Entities/Routines/RenderRoutine.h"

// RenderComponent
#include "../../Entities/Components/RenderComponent.h"
#include "../../Graphics/Renderable.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Shader/ShaderComponent.h"
#include "../../Graphics/Shader/ShaderProgram.h"

DataManager::DataManager(Factory* factory)
{
	m_Factory = factory;
}

DataManager::~DataManager()
{
}
// Utility
void DataManager::AddVec3ToItem(cJSON* item, const char* arrayName, const char* name1, float value1, const char* name2, float value2, const char* name3, float value3) const
{
	cJSON* vec3Array = CreateObject();
	vec3Array->string = DeepCopyString(arrayName);
	AddItemToArray(vec3Array, CreateNumber(name1, value1));
	AddItemToArray(vec3Array, CreateNumber(name2, value2));
	AddItemToArray(vec3Array, CreateNumber(name3, value3));

	AddItemToArray(item, vec3Array);
}

cJSON* DataManager::ConvertGameObjectToJSON(GameObject* object)
{
	if (object == nullptr) { nullptr; }

	cJSON* t_ReturnJSON = CreateArray(object->GetName().c_str());

	AddPositionTocJSONItem(t_ReturnJSON, object); // Can put this in a SaveTransform() function
	AddRotationTocJSONItem(t_ReturnJSON, object);
	AddScaleTocJSONItem(t_ReturnJSON, object);

	AddItemToArray(t_ReturnJSON, CreateNumber((char*)"ObjectTag", (int)object->GetTag()));

	AddComponentsTocJSONItem(t_ReturnJSON, object);

    // Handle special cases for certain components
	switch (object->GetTag())
	{
	case GO_Tag_Player:
		break;
		// Cameras
	case GO_Tag_Camera:
		break;
		// Lights
	case GO_Tag_Light:
		break;
		// Shapes
	case GO_Tag_Cube:
		break;
	case GO_Tag_Plane:
		break;
		// Scenery
	case GO_Tag_SkyBox:
		break;
		// Test
	case GO_Tag_TestModel:
		break;
	}

	return t_ReturnJSON;
}

GameObject* DataManager::ConvertJSONToGameObject(cJSON* item, Scene* scene)
{
    if (item == nullptr || scene == nullptr) { nullptr; }

    GameObject* object = new GameObject(scene);

    object->SetName(item->string);

    AddComponentsToGameObject(object, item);

    return object; // TODO: Finish
}

void DataManager::UpdateJSONArrayInFile(cJSON* array, const char* fileDir)
{
	// Open file stream
	// find object and overwrite it
	// save new cJSON string to file
}
// Getters
vec3 DataManager::GetPositionFromcJSONItem(cJSON* item)
{
	vec3 Position;
	Position.x = (float)GetItemFromArrayByKey(item, "PositionX")->valuedouble;
	Position.y = (float)GetItemFromArrayByKey(item, "PositionY")->valuedouble;
	Position.z = (float)GetItemFromArrayByKey(item, "PositionZ")->valuedouble;
	return Position;
}
vec3 DataManager::GetRotationFromcJSONItem(cJSON* item)
{
    vec3 Rotation;
    Rotation.x = (float)GetItemFromArrayByKey(item, "RotationX")->valuedouble;
    Rotation.y = (float)GetItemFromArrayByKey(item, "RotationY")->valuedouble;
    Rotation.z = (float)GetItemFromArrayByKey(item, "RotationZ")->valuedouble;
    return Rotation;
}
vec3 DataManager::GetScaleFromcJSONItem(cJSON* item)
{
    vec3 Scale;
    Scale.x = (float)GetItemFromArrayByKey(item, "ScaleX")->valuedouble;
    Scale.y = (float)GetItemFromArrayByKey(item, "ScaleY")->valuedouble;
    Scale.z = (float)GetItemFromArrayByKey(item, "ScaleZ")->valuedouble;
    return Scale;
}
 // TODO: Getters for data types: float vec3, etc. Not specific to names, but just per type

 // Transform
void DataManager::AddPositionTocJSONItem(cJSON* item, GameObject* object)
{
	cJSON* t_Position = CreateArray("Position");
	AddItemToArray(t_Position, CreateNumber((char*)"PositionX", object->GetPosition().x));
	AddItemToArray(t_Position, CreateNumber((char*)"PositionY", object->GetPosition().y));
	AddItemToArray(t_Position, CreateNumber((char*)"PositionZ", object->GetPosition().z));
	AddItemToArray(item, t_Position);
}
void DataManager::AddRotationTocJSONItem(cJSON* item, GameObject* object)
{
	cJSON* t_Rotation = CreateArray("Rotation");
	AddItemToArray(t_Rotation, CreateNumber((char*)"RotationX", object->GetRotation().x));
	AddItemToArray(t_Rotation, CreateNumber((char*)"RotationY", object->GetRotation().y));
	AddItemToArray(t_Rotation, CreateNumber((char*)"RotationZ", object->GetRotation().z));
	AddItemToArray(item, t_Rotation);
}
void DataManager::AddScaleTocJSONItem(cJSON* item, GameObject* object)
{
	cJSON* t_Scale = CreateArray("Scale");
	AddItemToArray(t_Scale, CreateNumber((char*)"ScaleX", object->GetScale().x));
	AddItemToArray(t_Scale, CreateNumber((char*)"ScaleY", object->GetScale().y));
	AddItemToArray(t_Scale, CreateNumber((char*)"ScaleZ", object->GetScale().z));
	AddItemToArray(item, t_Scale);
}
/* Components */
// Add
void DataManager::AddComponentTocJSONItem(cJSON* componentList, const Component* component) const
{
	if (!component) return;

    cJSON * t_Component = CreateArray(std::to_string(component->GetTag()).c_str());

	switch (component->GetTag())
	{
	case Component_Camera:
        {
            AddItemToArray(t_Component, CreateString("ComponentName", "Camera"));
            eCamType camType = ((CameraComponent*)component)->GetType();
            AddItemToArray(t_Component, CreateNumber("CamType", (int)camType));
        }
        //{
        //case eCamType::CamType_FreeCam:
        //    AddItemToArray(t_Component, CreateNumber("CamType", (int)CamType_FreeCam));
        //    // AddVec3ToItem(t_Component, "LightColour", "Red", ((LightComponent*)component)->GetColour().x, "Green", ((LightComponent*)component)->GetColour().y,
        //       // "Blue", ((LightComponent*)component)->GetColour().z);
        //    break;
        //case eCamType::CamType_FirstPerson: // TODO: Implement other camera types
        //    break;
        //case eCamType::CamType_Static: // TODO: Implement other camera types
        //    break;
        //case eCamType::CamType_ThirdPerson: // TODO: Implement other camera types
        //    break;
        //}
		break;
	case Component_Physics:
		break;
	case Component_Light:
	{
        AddItemToArray(t_Component, CreateString("ComponentName", "Light"));
		switch (((LightComponent*)component)->GetType())
		{
		case LightType_Point:
			// AddItemToArray(t_Component, CreateNumber("LightType", (int)LightType_Point));
			// AddVec3ToItem(t_Component, "LightColour",
            //     "Red", ((LightComponent*)component)->GetColour().x,
            //     "Green", ((LightComponent*)component)->GetColour().y,
			// 	   "Blue", ((LightComponent*)component)->GetColour().z);
			break;
		case LightType_Area: // TODO: Implement other light types.
			break;
		case LightType_Spot: // TODO: Implement other light types.
			break;
		}
	}
		break;
	case Component_Controller:
		break;
	case Component_Render:
	{
        AddItemToArray(t_Component, CreateString("ComponentName", "Render"));
		AddItemToArray(t_Component, CreateString("SchematicName", ((RenderComponent*)component)->GetSchematicName().c_str()));

		cJSON * t_Renderables = CreateArray("Renderables");

		std::vector<Renderable>* renderablesList = (std::vector<Renderable>*) ((RenderComponent*)component)->LookAtRenderableList();

		for (size_t i = 0; i < renderablesList->size(); i++)
		{
			// TODO: Set the renderable names
			cJSON* renderable = CreateArray(renderablesList->at(i).GetRenderableName().c_str());

			AddItemToArray(renderable, CreateString("Shader", renderablesList->at(i).GetShaderSchematic()->GetName().c_str()));
			AddItemToArray(renderable, CreateString("Material", renderablesList->at(i).GetMaterialSchematic()->GetMaterialName().c_str()));
			AddItemToArray(renderable, CreateString("MeshFile", renderablesList->at(i).GetMesh()->GetFileName().c_str()));
			AddItemToArray(renderable, CreateString("MeshName", renderablesList->at(i).GetMesh()->GetName().c_str()));

			AddItemToArray(t_Renderables, renderable);
		}

		AddItemToArray(t_Component, t_Renderables);
	}
		break;
	case Component_Print:
		break;
	case Component_SkyBox:
		break;
    }
    AddItemToArray(componentList, t_Component);
}
void DataManager::AddComponentsTocJSONItem(cJSON* item, GameObject* object)
{
	const std::map<eComponentTags, Component*>* t_ComponentList = object->SeeComponents();

	cJSON* t_Components = CreateArray("ComponentList");

	for (auto p : *t_ComponentList)
	{
		AddComponentTocJSONItem(t_Components, p.second);
	}
	AddItemToArray(item, t_Components);
}
// Get
void DataManager::AddComponentToGameObject(GameObject* object, cJSON* item)
{
    if (!item) { return; }

    eComponentTags value = (eComponentTags)std::stoi(item->string); // eComponentTags::Component_Render; // GetItemFromArrayByKey(item, "");
    // Reference : https://www.techiedelight.com/convert-string-to-int-cpp/

    ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
    Factory* fact = (Factory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Entity);

    switch (value)
    {
    case Component_Camera:
        {
            CameraComponent* t_pCamComp = nullptr;
            eCamType camType = eCamType::CamType_FreeCam; // TODO: Get dynamically
            switch (camType)
            {
            case CamType_FreeCam:
                t_pCamComp = new FreeCameraComponent();
                break;
            case CamType_FirstPerson:
                t_pCamComp = new FirstPersonCameraComponent();
                break;
            case CamType_ThirdPerson:
                t_pCamComp = new ThirdPersonCameraComponent();
                break;
            case CamType_Static:
                t_pCamComp = new StaticCameraComponent();
                break;
            }
            t_pCamComp->SetType(camType); // TODO: Set in component constructor.
            object->AddComponent(t_pCamComp);
        }
        break;
    case Component_Physics:
        break;
    case Component_Light:
        {
            LightComponent* t_pLightComp = new LightComponent();
            t_pLightComp->SetColour(vec3(1.0f, 1.0f, 1.0f));

            // fact->AddModelComponentFromSchematic(t_pLight, "light.osch");
            object->AddComponent(t_pLightComp);
        }
        break;
    case Component_Controller:
        break;
    case Component_Render:
        {
            RenderComponent* rComp = new RenderComponent();
            cJSON* renderables = GetItemFromArrayByKey(item, "Renderables");

            for (size_t i = 0; i < GetArraySize(renderables); i++)
            {
                cJSON* renderableArray = GetItemFromArrayByIndex(renderables, i); // renderables->child->child;

                Renderable renderable;
                renderable.SetRenderableName(renderableArray->string);

                cJSON* shader = GetItemFromArrayByKey(renderableArray, "Shader");
                cJSON* material = GetItemFromArrayByKey(renderableArray, "Material");
                cJSON* meshFile = GetItemFromArrayByKey(renderableArray, "MeshFile");
                cJSON* meshName = GetItemFromArrayByKey(renderableArray, "MeshName");

                renderable.SetShader(resMan->GetShaderProgram(shader->valuestring));
                renderable.SetMaterial(resMan->GetMaterial(material->valuestring));
                renderable.SetMesh(resMan->GetMeshFromFile(MeshFolderPath(meshFile->valuestring), meshName->valuestring)); // TODO: How to handle mesh name vs meshFileName

                rComp->AddRenderable(renderable);
            }

            object->AddComponent(rComp);

            RenderRoutine* renderRoutine = new RenderRoutine(); // TEMP: Add a routine
            object->AddRoutine((Routine*)renderRoutine);
            // TODO: Add Renderables
        }
        break;
    case Component_Print:
        break;
    case Component_SkyBox:
        break;
    case Component_SoundPlayer:
        break;
    case Component_SoundListener:
        break;
    case Component_Max:
        break;
    case Component_Null:
        break;
    default:
        break;
    }

}
void DataManager::AddComponentsToGameObject(GameObject* object, cJSON* item)
{
    cJSON* t_ComponentsList = GetItemFromArrayByKey(item, "ComponentList");
    std::vector<cJSON*> t_Components = GetAllItemsFromArray(t_ComponentsList);

    for (size_t i = 0; i < t_Components.size(); i++)
    {
        AddComponentToGameObject(object, t_Components[i]);
    }
    int bp = 1;
}