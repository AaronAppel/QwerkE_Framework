#pragma once

#include <vector>

#include "cJSON.h"

//////////////////////////
// possible TODO:: Add classes for easy root creation
// ex. RootObject* root = new RootObject();
// root.add(item);
//////////////////////////

/* Abstract the extra [{object}] from the user */

// #TODO Check for memory leaks. There are many...

//// Defines For Deliberate Root Accessing ////
//*- Getting -*
#define GetAllRootItems(root) GetAllItemsFromObject(root)
#define GetItemsFromRootByKey(root, key) GetItemsFromObjectByKey(root, key)
#define GetItemsFromRootByString(root, value) GetItemsFromObjectByString(root, value)
#define GetItemsFromRootByIndexRange(root, minimum, maximum) GetItemsFromObjectByIndexRange(root, minimum, maximum)

#define GetItemFromRootByKey(root, key) GetItemFromObjectByKey(root, key)
#define GetItemFromRootByString(root, value) GetItemFromObjectByString(root, value)
//*- Adding -*
#define AddItemToRoot(root, item) AddItemToObject(root, item)

//// File I/O ////
//*- File Reading -*
cJSON* OpencJSONStream(const char* fileDirectory);
void ClosecJSONStream(cJSON* root); // clean up

//*- File Writing -*
void AddItemToRootOfFile(cJSON* object, char* filename);
void PrintRootObjectToFile(const char* filename, cJSON* root);

//// Getting Items From File ////
//*- Getting From Objects -*
std::vector<cJSON*> GetAllItemsFromObject(cJSON* cJSONObject);
std::vector<cJSON*> GetItemsFromObjectByKey(cJSON* cJSONObject, const char* key);
std::vector<cJSON*> GetItemsFromObjectByString(cJSON* cJSONObject, char* value);
std::vector<cJSON*> GetItemsFromObjectByIndexRange(cJSON* cJSONObject, int min, int max);

cJSON* GetItemFromObjectByKey(cJSON* cJSONObject, const char* key);
cJSON* GetItemFromObjectByString(cJSON* cJSONObject, const char* value);
cJSON* GetItemFromObjectByIndex(cJSON* cJSONObject, int index);

//*- Getting From Arrays -*
std::vector<cJSON*> GetAllItemsFromArray(cJSON* jItem);
std::vector<cJSON*> GetItemsFromArrayByKey(cJSON* jObjectArray, char* key);
std::vector<cJSON*> GetItemsFromArrayByString(cJSON* jObjectArray, char* value);
std::vector<cJSON*> GetItemsFromArrayByIndexRange(cJSON* root, int min, int max);

cJSON* GetItemFromArrayByKey(cJSON* jObjectArray, const char* targetObjectName);
cJSON* GetItemFromArrayByString(cJSON* jObjectArray, const char* value);
cJSON* GetItemFromArrayByIndex(cJSON* jObjectArray, int index);

//// Adding Items To File ////
//*- Adding To Objects -*
void AddItemsToObject(cJSON* cJSONObject, std::vector<cJSON*> cJSONItems);

void AddItemToObject(cJSON* cJSONObject, cJSON* item);

//*- Adding To Arrays -*
void AddItemsToArray(cJSON* cJSONArray, std::vector<cJSON*> cJSONItems);

void AddItemToArray(cJSON* cJSONArray, cJSON* item); // TODO:: Think of returning the new item to be used?

//// Replacing Items In File ////
//*- Replacing Object Items -*
void ReplaceItemInObject(cJSON* cJSONObject, cJSON* oldItem, cJSON* newItem);

//*- Replacing Array Items -*
void ReplaceItemInArray(cJSON* cJSONArray, cJSON* oldItem, cJSON* newItem);

//// Updating Items In File //// #TODO Review updating vs replacement/overwriting
// Updating items in objects //
void UpdateItemInObject(cJSON* cJSONObject);

// Updating items in arrays //
void UpdateItemInArray(cJSON* cJSONObject);

//// Removing Items From File ////
//*- Removing From Object -*
void RemoveItemFromObject(cJSON* cJSONObject, cJSON* item);
void RemoveItemFromObjectByKey(cJSON* cJSONObject, const char* key);
void RemoveItemFromObjectByString(cJSON* cJSONObject, const char* value);

//*- Removing From Array -*
void RemoveItemsFromArray();

void RemoveItemFromArray(cJSON* cJSONArray, cJSON* item);
void RemoveItemFromArrayByKey(cJSON* cJSONArray, const char* key);
void RemoveItemFromArrayByString(cJSON* cJSONArray, const char* value);
void RemoveItemFromArrayByIndex(cJSON* cJSONArray, int index);

//// Type Check Convenience ////
bool TypeIsBool(cJSON* item);
bool TypeIsNull(cJSON* item);
bool TypeIsNumber(cJSON* item);
bool TypeIsString(cJSON* item);
bool TypeIsArray(cJSON* item);
bool TypeIsObject(cJSON* item);

//// Conversion Functions ////
/*create conversion functions for each data type you wish to convert between*/
//cJSON* ConvertObjectTocJSONObject() { return nullptr; }; // #TODO Provide examples
//void ConvertObjectFromcJSONObject() {}; // #TODO Provide examples

//// Creation Functions ////
cJSON* CreateBool(const char* key, bool value);
cJSON* CreateNumber(const char* key, double value);
cJSON* CreateString(const char* key, const char* value);
cJSON* CreateObject();
cJSON* CreateArray(const char* key);
cJSON* CreateTestModel();

// TODO:: Creation functions that also add
void AddStringToObject();
void AddNumberToArray();

//// Copy Root ////
cJSON* CopyRootObject(cJSON* root);

//// Helpers ////
bool json_FileExists(const char* filename);
void json_CreateNewFile(const char* filename);
void CreateEmptycJSONFile(const char* filePath); // #TODO Consider returning an error status

unsigned int GetObjectSize(cJSON* cJSONObject);
unsigned int GetArraySize(cJSON* cJSONArray);

//cJSON* DuplicatecJSON(cJSON* cJSON) { return nullptr; }; // #TODO Implement

// search entire .json file for item key
// *search order is different per file so ensure the search value is unique for best results*
cJSON* DeepSearchForItemByKey(cJSON* object, const char* key); // #TODO Test
//cJSON* DeepSearchForItemByString(cJSON* object, char* value); // #TODO Implement

// add search by number, bool value.
// add GetItemIndexFromObject/Array for convenience inside and out of library
// Cleanup variable and function names for readability
// organize .h and .cpp files to be correct order and properly commented
