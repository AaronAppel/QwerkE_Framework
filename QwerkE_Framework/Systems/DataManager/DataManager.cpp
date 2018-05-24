#include "DataManager.h"
#include "../Factory/Factory.h"
#include "../../../QwerkE_Common/Libraries/cJSON_Interface/cJSONInterface.h"
#include "../../Entities/GameObject.h"
#include "../../Entities/Components/Camera/CameraComponent.h"
#include "../../Entities/Components/LightComponent.h"

// RenderComponent
#include "../../Entities/Components/RenderComponent.h"
#include "../../Graphics/Renderable.h"
#include "../../Graphics/MaterialData.h"
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
cJSON* DataManager::ConvertGameObjectToJSON(GameObject* item)
{
	if (item == nullptr) { nullptr; }

	cJSON* t_ReturnJSON = CreateArray(item->GetName().c_str());

	AddPositionTocJSONItem(t_ReturnJSON, item);
	AddPositionTocJSONItem(t_ReturnJSON, item);
	AddScaleTocJSONItem(t_ReturnJSON, item);

	AddItemToArray(t_ReturnJSON, CreateNumber((char*)"ObjectTag", (int)item->GetTag()));

	AddComponentsTocJSONItem(t_ReturnJSON, item);

	switch (item->GetTag())
	{
	case GO_Tag_Player:
		break;
		// Cameras
	case GO_Tag_Camera:
		switch (((CameraComponent*)item->GetComponent(eComponentTags::Component_Camera))->GetType()) // What type of camera?
		{
		case CamType_FreeCam:
			AddItemToArray(t_ReturnJSON, CreateNumber((char*)"CamType", (int)CamType_FreeCam));
			break;
		case CamType_FirstPerson:
			AddItemToArray(t_ReturnJSON, CreateNumber((char*)"CamType", (int)CamType_FirstPerson));
			break;
		case CamType_ThirdPerson:
			AddItemToArray(t_ReturnJSON, CreateNumber((char*)"CamType", (int)CamType_ThirdPerson));
			break;
		}
		break;
		// Lights
	case GO_Tag_Light:
		switch (((LightComponent*)item->GetComponent(eComponentTags::Component_Light))->GetType()) // What type of camera?
		{
		case LightType_Point:
			AddItemToArray(t_ReturnJSON, CreateNumber((char*)"CamType", (int)LightType_Point));
			break;
		case LightType_Area: // TODO: Implement other light types.
			break;
		case LightType_Spot:
			break;
		}
		break;
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
// Components
void DataManager::AddComponentTocJSONItem(cJSON* item, const Component* component) const
{
	if (!component) return;

	switch (component->GetTag())
	{
	case Component_Camera:
		break;
	case Component_Physics:
		break;
	case Component_Light:
		break;
	case Component_Controller:
		break;
	case Component_Render:
	{
		cJSON * t_RenderComp = CreateArray("Render");

		AddItemToArray(t_RenderComp, CreateString("SchematicName", ((RenderComponent*)component)->GetSchematicName().c_str())); // schematic name

		cJSON * t_Renderables = CreateArray("Renderables");

		std::vector<Renderable>* renderablesList = (std::vector<Renderable>*) ((RenderComponent*)component)->LookAtRenderableList();

		for (size_t i = 0; i < renderablesList->size(); i++)
		{
			// TODO: Set the renderable names
			cJSON* renderable = CreateArray(renderablesList->at(i).GetRenderableName().c_str());

			AddItemToArray(renderable, CreateString("Shader", renderablesList->at(i).GetShaderSchematic()->GetName().c_str()));
			AddItemToArray(renderable, CreateString("Material", renderablesList->at(i).GetMaterialSchematic()->s_Name.c_str()));
			AddItemToArray(renderable, CreateString("MeshFile", renderablesList->at(i).GetMesh()->GetFileName().c_str()));
			AddItemToArray(renderable, CreateString("MeshName", renderablesList->at(i).GetMesh()->GetName().c_str()));

			AddItemToArray(t_Renderables, renderable);
		}

		AddItemToArray(t_RenderComp, t_Renderables);
		AddItemToArray(item, t_RenderComp);
	}
		break;
	case Component_Print:
		break;
	case Component_SkyBox:
		break;
	case Component_Animation:
		break;
	case Component_Character:
		break;
	}
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