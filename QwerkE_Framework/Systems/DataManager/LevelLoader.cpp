#include "LevelLoader.h"
#include "../Factory/Factory.h"
#include "../../../QwerkE_Common/Libraries/cJSON_Interface/cJSONInterface.h"
#include "../../Scenes/Scene.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../QwerkE_Enums.h"

#include <string>
#include <vector>
#include <map>

LevelLoader::LevelLoader(Factory* factory) : DataManager(factory)
{
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::SaveScene(Scene* scene, const char* fileDir)
{
	// TODO: Error checking
	cJSON* root = CreateObject();

	// ADD OBJECTS
	std::map<std::string, GameObject*> t_GameObjectList = scene->GetObjectList(); // GameObjects, Lights (Not cameras)

	cJSON* t_ObjectList = CreateArray("ObjectList");
	AddItemToRoot(root, t_ObjectList);
	std::map<std::string, GameObject*>::iterator it;
	for (it = t_GameObjectList.begin(); it != t_GameObjectList.end(); it++)
	{
		AddItemToArray(t_ObjectList, ConvertGameObjectToJSON(it->second));
	}

	// ADD CAMERAS
	std::vector<GameObject*> t_CameraObjectList = scene->GetCameraList(); // Cameras only

	cJSON* t_CameraList = CreateArray("CameraList");
	AddItemToObject(root, t_CameraList);
	for (int i = 0; i < t_CameraObjectList.size(); i++)
	{
		AddItemToArray(t_CameraList, ConvertGameObjectToJSON(t_CameraObjectList.at(i)));
	}

	// ADD LIGHTS
	std::vector<GameObject*> t_LightObjectList = scene->GetLightList(); // Cameras only

	cJSON* t_LightList = CreateArray("LightList");
	AddItemToObject(root, t_LightList);
	for (int i = 0; i < t_LightObjectList.size(); i++)
	{
		AddItemToArray(t_LightList, ConvertGameObjectToJSON(t_LightObjectList.at(i)));
	}

	// WRITE TO FILE
	PrintRootObjectToFile(fileDir, root);
	OutputPrint("\nDataManager: Scene saved!\n");
	// delete root
}

void LevelLoader::LoadScene(Scene* scene, const char* fileDir)
{
	if (scene == nullptr) { return; } // null scene
	if (FileExists(fileDir) == false)
	{
		OutputPrint("\nDataManager: LoadScene() could not open file for reading.\n");
		return;
	}

	// START
	cJSON* root = OpencJSONStream(fileDir);
	if (root == nullptr) // Compile error
	{
		OutputPrint("\nDataManager: LoadScene() null root object.\n");
		return;
	}

	scene->RemoveAllObjectsFromScene(); // Empty scene of objects

	// CREATE OBJECTS
	cJSON* t_JSONObjectList = GetItemFromObjectByKey(root, "ObjectList");
	std::vector<cJSON*> t_GameObjects = GetAllItemsFromArray(t_JSONObjectList);
	for (unsigned int i = 0; i < t_GameObjects.size(); i++)
	{
		cJSON* tempObject = GetItemFromArrayByKey(t_GameObjects.at(i), "Position");
		vec3 position = GetPositionFromcJSONItem(tempObject);
		switch (GetItemFromArrayByKey(t_GameObjects.at(i), "ObjectTag")->valueint)
		{
		case (int)eGameObjectTags::GO_Tag_Cube:
			m_Factory->CreateCube(scene, position);
			break;
		case (int)eGameObjectTags::GO_Tag_Plane:
			m_Factory->CreatePlane(scene, position);
			break;
		}
	}

	// CREATE CAMERAS
	cJSON* t_JSONCameraList = GetItemFromObjectByKey(root, "CameraList");
	std::vector<cJSON*> t_CameraObjects = GetAllItemsFromArray(t_JSONCameraList);
	for (size_t i = 0; i < t_CameraObjects.size(); i++)
	{
		cJSON* tempObject = GetItemFromArrayByKey(t_CameraObjects.at(i), "Position");
		vec3 position = GetPositionFromcJSONItem(tempObject);
		switch (GetItemFromArrayByKey(t_CameraObjects.at(i), "CamType")->valueint)
		{
		case CamType_FreeCam:
			m_Factory->CreateFreeCamera(scene, position);
			break;
		case CamType_FirstPerson:
			m_Factory->CreateFirstPersonCamera(scene, position);
			break;
		case CamType_ThirdPerson:
			m_Factory->CreateThirdPersonCamera(scene, position);
			break;
		case CamType_Static:
			m_Factory->CreateStaticCamera(scene, position);
			break;
		}
	}

	// CREATE LIGHTS
	cJSON* t_JSONLightList = GetItemFromObjectByKey(root, "LightList");
	std::vector<cJSON*> t_LightObjects = GetAllItemsFromArray(t_JSONLightList);
	for (size_t i = 0; i < t_LightObjects.size(); i++)
	{
		cJSON* tempObject = GetItemFromArrayByKey(t_LightObjects.at(i), "Position");
		vec3 position = GetPositionFromcJSONItem(tempObject);
		//switch (GetItemFromArrayByKey(t_LightObjects.at(i), "LightType")->valueint)
		//{
		//case LightType_Point:
		//	m_Factory->CreateLight(scene, position);
		//	break;
		//case LightType_Area: // TODO: Change for new light types
		//	break;
		//case LightType_Spot:
		//	break;
		//}
	}

	// END
	ClosecJSONStream(root);
	OutputPrint("\nDataManager: Scene loaded!\n");
}
