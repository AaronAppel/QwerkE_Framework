#ifndef __CJSONINTERFACE_H__
#define __CJSONINTERFACE_H_

#include "cJSON.h"
#include <vector>

//////////////////////////
// possible TODO:: Add classes for easy root creation
// ex. RootObject* root = new RootObject();
// root.add(item);
//////////////////////////

/* Abstract the extra [{object}] from the user */

//class cJSON;

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
cJSON* OpencJSONStream(const char* fileDirectory); // open stream
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
void AddItemsToObject(cJSON* cJSONObject, std::vector<cJSON*> cJSONItems); // TODO::

void AddItemToObject(cJSON* cJSONObject, cJSON* item);

//*- Adding To Arrays -*
void AddItemsToArray(cJSON* cJSONArray, std::vector<cJSON*> cJSONItems); // TODO::

void AddItemToArray(cJSON* cJSONArray, cJSON* item); // TODO::

//// Replacing Items In File ////
//*- Replacing Object Items -*
void ReplaceItemInObject(cJSON* cJSONObject, cJSON* oldItem, cJSON* newItem); // TODO::

//*- Replacing Array Items -*
void ReplaceItemInArray(cJSON* cJSONArray, cJSON* oldItem, cJSON* newItem); // TODO::

//// Updating Items In File //// <- updating vs flat replacement
// Updating items in objects // TODO::
void UpdateItemInObject(cJSON* cJSONObject); // TODO::

// Updating items in arrays // TODO::
void UpdateItemInArray(cJSON* cJSONObject); // TODO::

//// Removing Items From File ////
//*- Removing From Object -*
void RemoveItemFromObject(cJSON* cJSONObject, cJSON* item);
void RemoveItemFromObjectByKey(cJSON* cJSONObject, const char* key);
void RemoveItemFromObjectByString(cJSON* cJSONObject, const char* value);

//*- Removing From Array -*
void RemoveItemsFromArray(); // TODO::

void RemoveItemFromArray(cJSON* cJSONArray, cJSON* item);
void RemoveItemFromArrayByKey(cJSON* cJSONArray, const char* key);
void RemoveItemFromArrayByString(cJSON* cJSONArray, const char* value);
void RemoveItemFromArrayByIndex(cJSON* cJSONArray, int index); // remove from back to front

//// Type Check Convenience ////
bool TypeIsBool(cJSON* item);
bool TypeIsNull(cJSON* item);
bool TypeIsNumber(cJSON* item);
bool TypeIsString(cJSON* item);
bool TypeIsArray(cJSON* item);
bool TypeIsObject(cJSON* item);

//// Conversion Functions ////
/*create conversion functions for each data type you wish to convert between*/
//cJSON* ConvertObjectTocJSONObject() { return nullptr; }; // TODO:: examples
//void ConvertObjectFromcJSONObject() {}; // TODO:: examples

//// Creation Functions ////
cJSON* CreateBool(const char* key, bool value);
cJSON* CreateNumber(char* key, double value);
cJSON* CreateString(const char* key, char* value);
cJSON* CreateObject();
cJSON* CreateArray(const char* key);
cJSON* CreateTestModel();

// TODO:: Creation functions that also add
void AddStringToObject();
void AddNumberToArray();

//// Copy Root ////
cJSON* CopyRootObject(cJSON* root);

//// Heplers ////
bool FileExists(const char* filename);
void CreateNewFile(const char* filename);

int GetObjectSize(cJSON* cJSONObject);
int GetArraySize(cJSON* cJSONArray);

//cJSON* DuplicatecJSON(cJSON* cJSON) { return nullptr; }; // TODO::

// search entire .json file for item key
// *search order is different per file so ensure the search value is unique for best results*
cJSON* DeepSearchForItemByKey(cJSON* object, const char* key); // TODO:: Test
//cJSON* DeepSearchForItemByString(cJSON* object, char* value); // TODO::

// TODO:: Polish
// add search by number, bool value.
// add GetItemIndexFromObject/Array for convenience inside and out of library
// Cleanup variable and function names for readability
// organize .h and .cpp files to be correct order and properly commented

#endif //__CJSONINTERFACE_H__