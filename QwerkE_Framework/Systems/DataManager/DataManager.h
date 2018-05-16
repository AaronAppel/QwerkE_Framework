#ifndef __DataManager_H__
#define __DataManager_H__

/*
	The DataManager() class is meant to be used to load/save and store
	information from external save files at run time.

	It is designed to be inherited by a custom user class that can load/save
	scenes/collections for a specific game or application.

	One purpose it serves is to extend the cJSONInterface library to
	work better with BLUE_Box custom GameObject() classes.
	DataManager() contains functions such as "AddVec3TocJSONObject(x, y, z)".

	User is meant to create any additional, specific functions for their uses.
	User also uses factory to create objects by creating custom object
	save/load functions some 7where in game specific code.
*/
#include "../../QwerkE_Common/Math_Includes.h"

class Scene;
class GameObject;
class Factory;
struct cJSON;

class DataManager
{
public:
	DataManager(Factory* factory);
    virtual ~DataManager();

	virtual void SaveScene(Scene* scene, const char* fileDir) = 0;
	virtual void LoadScene(Scene* scene, const char* fileDir) = 0;

protected:
	// Utility
	cJSON* ConvertGameObjectToJSON(GameObject* item);
	void UpdateJSONArrayInFile(cJSON* array, const char* fileDir);

	// Getters
	vec3 GetPositionFromcJSONItem(cJSON* item);
	Factory* m_Factory = nullptr;

	// Adders
	void AddPositionTocJSONItem(cJSON* item, GameObject* object);
};

#endif //__ResourceManager_H__
