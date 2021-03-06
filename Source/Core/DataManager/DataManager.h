#ifndef _DataManager_H_
#define _DataManager_H_

/*
	The DataManager() class is meant to be used to load/save
	information from/to external save files at run time.

	It is designed to be inherited by a custom user class that can load/save
	scenes/collections for a specific game or application.

	One purpose it serves is to extend the cJSONInterface library to
	work better with BLUE_Box custom GameObject() classes.
	DataManager() contains functions such as "AddVec3TocJSONObject(x, y, z)".

	User is meant to create any additional, specific functions for their uses.
	User also uses factory to create objects by creating custom object
	save/load functions some 7where in game specific code.
*/

struct cJSON;

namespace QwerkE {

    class Scene;
    class GameObject;
    class Factory;
    class Component;
    class Routine;

    namespace DataManager
    {
        void SaveScene(Scene* scene, const char* fileDir);
        void LoadScene(Scene* scene, const char* fileDir);

        // Utility
        void AddVec3ToItem(cJSON* item, const char* arrayName, const char* name1, float value1, const char* name2, float value2, const char* name3, float value3);
        cJSON* ConvertGameObjectToJSON(GameObject* item);
        void UpdateJSONArrayInFile(cJSON* array, const char* fileDir);
        GameObject* ConvertJSONToGameObject(cJSON* item, Scene* scene);

        // Getters
        vec3 GetPositionFromcJSONItem(cJSON* item);
        vec3 GetRotationFromcJSONItem(cJSON* item);
        vec3 GetScaleFromcJSONItem(cJSON* item);

        // Transform
        void AddPositionTocJSONItem(cJSON* item, GameObject* object);
        void AddRotationTocJSONItem(cJSON* item, GameObject* object);
        void AddScaleTocJSONItem(cJSON* item, GameObject* object);

        // Components
        void AddComponentTocJSONItem(cJSON* componentList, const Component* component);
        void AddComponentsTocJSONItem(cJSON* item, GameObject* object);

        void AddComponentToGameObject(GameObject* object, cJSON* item);
        void AddComponentsToGameObject(GameObject* object, cJSON* item);

        // Routines
        void AddRoutineTocJSONItem(cJSON* routineList, Routine* routine);
        void AddRoutinesTocJSONItem(cJSON* item, GameObject* object);

        void AddRoutineToGameObject(GameObject* object, cJSON* item);
        void AddRoutinesToGameObject(GameObject* object, cJSON* item);
    };

}
#endif //!_DataManager_H_
