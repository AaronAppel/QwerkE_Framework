#include "LevelLoader.h"
#include "../Factory/Factory.h"
#include "../../Scenes/Scene.h"
#include "../../QwerkE_Common/Libraries/cJSON_Interface/cJSONInterface.h"
#include "../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../Headers/QwerkE_Enums.h"

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

    // Scene settings
    cJSON* t_Settings = CreateArray("Settings");
    AddItemToArray(t_Settings, CreateNumber("State", (int)scene->GetState()));
    AddItemToArray(t_Settings, CreateNumber("Enabled", scene->GetIsEnabled()));

	// Scene entities
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
	OutputPrint("\nDataManager: Scene file %s saved\n", fileDir);
	// delete root
}

void LevelLoader::LoadScene(Scene* scene, const char* fileDir)
{
	if (scene == nullptr) { return; } // TODO: Load a null scene
	if (FileExists(fileDir) == false)
	{
		OutputPrint("\nDataManager: LoadScene() could not open file for reading.\n");
		return;
	}

	// Read scene json file
	cJSON* root = OpencJSONStream(fileDir);
	if (root == nullptr) // Compile error
	{
		OutputPrint("\nDataManager: LoadScene() null root object.\n");
		return;
	}

	scene->RemoveAllObjectsFromScene(); // Empty scene of objects

    // TODO: Improve below loops. A lot of copied code

    // Scene settings
    cJSON* t_Settings = GetItemFromRootByKey(root, "Settings");

    if (t_Settings != nullptr)
    {
        scene->SetState((eSceneState)((int)(GetItemFromArrayByKey(t_Settings, "State")->valuedouble)));
        scene->SetIsEnabled((bool)GetItemFromArrayByKey(t_Settings, "Enabled")->valuedouble);
    }

	// CREATE OBJECTS
    {
        cJSON* t_JSONObjectList = GetItemFromObjectByKey(root, "ObjectList");
        std::vector<cJSON*> t_GameObjects = GetAllItemsFromArray(t_JSONObjectList);

        for (unsigned int i = 0; i < t_GameObjects.size(); i++)
        {
            GameObject* t_TempObject = ConvertJSONToGameObject(t_GameObjects.at(i), scene);
            scene->AddObjectToScene(t_TempObject);
        }
    }

    // CREATE CAMERAS
    {
        cJSON* t_JSONCameraList = GetItemFromObjectByKey(root, "CameraList");
        std::vector<cJSON*> t_CameraObjects = GetAllItemsFromArray(t_JSONCameraList);

        for (unsigned int i = 0; i < t_CameraObjects.size(); i++)
        {
            GameObject* t_TempObject = ConvertJSONToGameObject(t_CameraObjects.at(i), scene);
            scene->AddCamera(t_TempObject);
        }
    }

	// CREATE LIGHTS
    {
        cJSON* t_JSONLightList = GetItemFromObjectByKey(root, "LightList");
        std::vector<cJSON*> t_LightObjects = GetAllItemsFromArray(t_JSONLightList);

        for (unsigned int i = 0; i < t_LightObjects.size(); i++)
        {
            GameObject* t_TempObject = ConvertJSONToGameObject(t_LightObjects.at(i), scene);
            scene->AddLight(t_TempObject);
        }
    }

	// END
	ClosecJSONStream(root);
	OutputPrint("\nDataManager: Scene file %s loaded\n", fileDir);
}
