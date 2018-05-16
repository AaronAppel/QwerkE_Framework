#include "DataManager.h"
#include "../Factory/Factory.h"
#include "../../../QwerkE_Common/Libraries/cJSON_Interface/cJSONInterface.h"
#include "../../Entities/GameObject.h"
#include "../../Entities/Components/CameraComponent.h"
#include "../../Entities/Components/LightComponent.h"

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
	AddItemToArray(t_ReturnJSON, CreateNumber((char*)"ObjectTag", (int)item->GetTag()));

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

	AddPositionTocJSONItem(t_ReturnJSON, item);

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
// Adders
void DataManager::AddPositionTocJSONItem(cJSON* item, GameObject* object)
{
	cJSON* t_Position = CreateArray("Position");
	AddItemToArray(t_Position, CreateNumber((char*)"PositionX", object->GetPosition().x));
	AddItemToArray(t_Position, CreateNumber((char*)"PositionY", object->GetPosition().y));
	AddItemToArray(t_Position, CreateNumber((char*)"PositionZ", object->GetPosition().z));
	AddItemToArray(item, t_Position);
}