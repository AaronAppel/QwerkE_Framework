#include "../cJSON_Interface/cJSON.h"
#include "cJSONInterface.h"
#include "../../Utilities/FileIO/FileUtilities.h"
#include "../../Utilities/PrintFunctions.h"

#include <vector>

cJSON* OpencJSONStream(const char* fileDirectory)
{
	if (json_FileExists(fileDirectory))
	{
		char* str = LoadFile(fileDirectory);
		cJSON* root = cJSON_Parse(str);

		delete[] str; // cleanup

		if (root == nullptr)
		{
			OutputPrint("\nOpencJSONStream(): Could not open cJSON stream. Possible compile error. Check %s file for typos!\n\n", fileDirectory);
		}
		return root;
	}
	return nullptr;
}

void ClosecJSONStream(cJSON* root)
{
	if (root)
	{
		cJSON_Delete(root); // cleanup
	}
}

std::vector<cJSON*> GetAllItemsFromObject(cJSON* cJSONObject)
{
	int arraySize = GetObjectSize(cJSONObject);

	std::vector<cJSON *> returnList;

	for (int i = 0; i < arraySize; i++)
	{
		returnList.push_back(cJSON_GetArrayItem(cJSONObject, i));
	}
	return returnList;
}

std::vector<cJSON*> GetItemsFromObjectByKey(cJSON* cJSONObject, const char* key)
{
	int arraySize = cJSON_GetArraySize(cJSONObject);

	std::vector<cJSON *> returnList;

	for (int i = 0; i < arraySize; i++)
	{
		cJSON* item = cJSON_GetArrayItem(cJSONObject, i);
		if (*item->string == *key)
		{
			returnList.push_back(item);
		}
	}
	return returnList;
}

std::vector<cJSON*> GetItemsFromObjectByString(cJSON* cJSONObject, const char* value)
{
	int arraySize = cJSON_GetArraySize(cJSONObject);

	std::vector<cJSON *> returnList;

	for (int i = 0; i < arraySize; i++)
	{
		cJSON* item = cJSON_GetArrayItem(cJSONObject, i);
		if (item->valuestring == nullptr)
		{
			continue;
		}
		if (*item->valuestring == *value)
		{
			returnList.push_back(item);
		}
	}
	return returnList;
}

std::vector<cJSON*> GetItemsFromObjectByIndexRange(cJSON* cJSONObject, int minimum, int maximum)
{
	std::vector<cJSON*> returnList;

	int range = maximum - minimum + 1;

	for (int i = 0; i < range; i++)
	{
		returnList.push_back(cJSON_GetArrayItem(cJSONObject, minimum + i));
	}
	return returnList;
}

cJSON* GetItemFromObjectByKey(cJSON* cJSONObject, const char* key)
{
	int arraySize = cJSON_GetArraySize(cJSONObject);

	for (int i = 0; i < arraySize; i++)
	{
		cJSON* item = cJSON_GetArrayItem(cJSONObject, i);
		if (*item->string == *key)
		{
			return item;
		}
	}
	return nullptr;
}

cJSON* GetItemFromObjectByString(cJSON* cJSONObject, const char* value)
{
	int arraySize = cJSON_GetArraySize(cJSONObject);

	for (int i = 0; i < arraySize; i++)
	{
		cJSON* item = cJSON_GetArrayItem(cJSONObject, i);
		if (item->valuestring == nullptr)
		{
			continue;
		}
		if (*item->valuestring == *value)
		{
			return item;
		}
	}
	return nullptr;
}

cJSON* GetItemFromObjectByIndex(cJSON* cJSONObject, int index)
{
	return cJSON_GetArrayItem(cJSONObject, index);
}

std::vector<cJSON *> GetAllItemsFromArray(cJSON* arrayObject) // return array of objects inside of an objectArray
{
	std::vector<cJSON *> itemList;

	if (arrayObject->child == nullptr)
	{
		return itemList; // not an array
	}

	int t_ArraySize = cJSON_GetArraySize(arrayObject->child);
	for (int i = 0; i < t_ArraySize; i++)
	{
		itemList.push_back(cJSON_GetArrayItem(arrayObject->child, i));
	}

	return itemList;
}

std::vector<cJSON *> GetItemsFromArrayByKey(cJSON* jObjectArray, const char* key) // TODO:: BROKEN
{
	int t_ArraySize = cJSON_GetArraySize(jObjectArray->child);

	std::vector<cJSON *> itemList;

	for (int i = 0; i < t_ArraySize; i++) // each immediate Object inside root
	{
		cJSON* temp = cJSON_GetArrayItem(jObjectArray->child, i);
		if (*temp->string == *key) // <- false comparison
		{
			itemList.push_back(temp);
		}
	}

	return itemList;
}

std::vector<cJSON *> GetItemsFromArrayByString(cJSON* cJSONArray, const char* value)
{
	int arraySize = cJSON_GetArraySize(cJSONArray->child);

	std::vector<cJSON *> returnList;

	for (int i = 0; i < arraySize; i++)
	{
		cJSON* item = cJSON_GetArrayItem(cJSONArray->child, i);
		if (item->valuestring == nullptr)
		{
			continue;
		}
		if (*item->valuestring == *value)
		{
			returnList.push_back(item);
		}
	}
	return returnList;
}

std::vector<cJSON*> GetItemsFromArrayByIndexRange(cJSON* cJSONObject, int min, int max)
{
	std::vector<cJSON*> returnList;

	int range = max - min + 1;

	cJSON* item = cJSONObject->child->child; // get first item

	for (int i = 0; i < min; i++)
	{
		item = item->next;
	}

	for (int i = 0; i < range; i++)
	{
		returnList.push_back(item);
		item = item->next;
	}

	return returnList;
}

cJSON* GetItemFromArrayByKey(cJSON* cJSONArray, const char* key) // TODO:: BROKEN // <-- deprecated
{
	int arraySize = cJSON_GetArraySize(cJSONArray->child);

	for (int i = 0; i < arraySize; i++)
	{
		cJSON* item = cJSON_GetArrayItem(cJSONArray->child, i);
		if (strcmp(item->string, key) == 0) // TODO:: TEST
		{
			return item;
		}
		if (*item->string == *key)
		{
			//return item; // TODO:: remove
		}
	}
	return nullptr;
}

cJSON* GetItemFromArrayByString(cJSON* cJSONArray, const char* value) // <-- deprecated
{
	int arraySize = cJSON_GetArraySize(cJSONArray->child);

	for (int i = 0; i < arraySize; i++)
	{
		cJSON* item = cJSON_GetArrayItem(cJSONArray->child, i);
		if (item->valuestring == nullptr)
		{
			continue;
		}
		if (*item->valuestring == *value)
		{
			return item;
		}
	}
	return nullptr;
}

cJSON* GetItemFromArrayByIndex(cJSON* cJSONarray, int index)
{
	cJSON* cJSONItem = cJSONarray->child->child;

	for (int i = 0; i < index; i++)
	{
		cJSONItem = cJSONItem->next;
	}
	return cJSONItem;
}

void AddItemsToObject(cJSON* cJSONObject, std::vector<cJSON*> cJSONItems)
{
	// TODO::
}

void AddItemToObject(cJSON* cJSONObject, cJSON* item)
{
	cJSON_AddItemToArray(cJSONObject, item);
}

void AddItemsToArray(cJSON* cJSONArray, std::vector<cJSON*> cJSONItems)
{
	// TODO::
}

void AddItemToArray(cJSON* cJSONArray, cJSON* item)
{
	int arraySize = 0;

	if (cJSONArray->child)
	{
		arraySize = cJSON_GetArraySize(cJSONArray->child);
	}
	else
	{
		cJSONArray->child = CreateObject(); // create array object [{}]
	}

	if (arraySize > 0)
	{
		cJSON* lastSibling = GetItemFromArrayByIndex(cJSONArray, arraySize - 1);
		lastSibling->next = item;
		item->prev = lastSibling;
	}
	else
	{
		if (cJSONArray->child->child == nullptr)
		{
			cJSONArray->child->child = item; // First element
		}
	}
}
//// Replacing Items In File ////
//*- Replacing Object Items -*
void ReplaceItemInObject(cJSON* cJSONObject, cJSON* oldItem, cJSON* newItem)
{
	int size = GetObjectSize(cJSONObject);

	for (int i = 0; i < size; i++)
	{
		cJSON* temp = GetItemFromObjectByIndex(cJSONObject, i);

		if (*temp->string == *oldItem->string)
		{
			cJSON_ReplaceItemInArray(cJSONObject, i, newItem); // TODO:: test
		}
	}
}
//*- Replacing Array Items -*
void ReplaceItemInArray(cJSON* cJSONArray, cJSON* oldItem, cJSON* newItem)
{
	ReplaceItemInObject(cJSONArray->child, oldItem, newItem); // TODO:: test
}
//// Updating Items In File //// <- updating vs flat replacement
// Updating items in objects
void UpdateItemInObject(cJSON* cJSONObject)
{
	// TODO::
}
// Updating items in arrays // TODO::
void UpdateItemInArray(cJSON* cJSONObject)
{
	// TODO::
}

//// Removing Items From File ////
//*- Removing From Object -*
void RemoveItemFromObject(cJSON* cJSONObject, cJSON* item)
{
	RemoveItemFromObjectByKey(cJSONObject, item->string);
}

void RemoveItemFromObjectByKey(cJSON* cJSONObject, const char* key)
{
	cJSON_DetachItemFromObject(cJSONObject, key);
}

void RemoveItemFromObjectByString(cJSON* cJSONObject, const char* value)
{
	int size = GetObjectSize(cJSONObject);

	for (int i = 0; i < size; i++)
	{
		cJSON* temp = GetItemFromObjectByIndex(cJSONObject, i);
		if (TypeIsString(temp))
		{
			if (*temp->valuestring == *value)
			{
				cJSON_DeleteItemFromArray(cJSONObject, i);
				return;
			}
		}
	}
}
//*- Removing From Array -*
void RemoveItemsFromArray()
{
	// TODO::
}

void RemoveItemFromArray(cJSON* cJSONArray, cJSON* item)
{
	RemoveItemFromArrayByKey(cJSONArray, item->string);
}

void RemoveItemFromArrayByKey(cJSON* cJSONArray, const char* key)
{
	cJSON_DetachItemFromObject(cJSONArray->child, key);
}

void RemoveItemFromArrayByString(cJSON* cJSONArray, const char* value)
{
	int size = GetArraySize(cJSONArray);

	for (int i = 0; i < size; i++)
	{
		cJSON* temp = GetItemFromArrayByIndex(cJSONArray, i);
		if (TypeIsString(temp))
		{
			if (*temp->valuestring == *value)
			{
				cJSON_DeleteItemFromArray(cJSONArray->child, i);
				return;
			}
		}
	}
}

void RemoveItemFromArrayByIndex(cJSON* cJSONArray, int index) // remove from back to front
{
	cJSON_DeleteItemFromArray(cJSONArray->child, index);
}

bool TypeIsBool(cJSON* item)
{
	if (item->type == cJSON_False || item->type == cJSON_True)
		return true;
	else
		return false;
}

bool TypeIsNull(cJSON* item)
{
	if (item->type == cJSON_NULL)
		return true;
	else
		return false;
}

bool TypeIsNumber(cJSON* item)
{
	if (item->type == cJSON_Number)
		return true;
	else
		return false;
}

bool TypeIsString(cJSON* item)
{
	if (item->type == cJSON_String)
		return true;
	else
		return false;
}

bool TypeIsArray(cJSON* item)
{
	if (item->type == cJSON_Array)
		return true;
	else
		return false;
}

bool TypeIsObject(cJSON* item)
{
	if (item->type == cJSON_Object)
		return true;
	else
		return false;
}

cJSON* CreateBool(const char* key, bool value)
{
	cJSON* returnBool = cJSON_CreateBool(value);
	returnBool->string = _strdup(key); // TODO:: Check for redundant memory allocations
	return returnBool;
}

cJSON* CreateInt(const char* key, double value)
{
	cJSON* returnNumber = cJSON_CreateNumber(value);
	returnNumber->string = _strdup(key);
	return returnNumber;
}

cJSON* CreateNumber(const char* key, double value)
{
	cJSON* returnNumber = cJSON_CreateNumber(value);
	returnNumber->string = _strdup(key);
	return returnNumber;
}

cJSON* CreateString(const char* key, const char* value)
{
	cJSON* returnString = cJSON_CreateString(value);
	returnString->string = _strdup(key);
	return returnString;
}

cJSON* CreateObject()
{
	cJSON* returnObject = cJSON_CreateObject();
	return returnObject;
}

cJSON* CreateArray(const char* key)
{
	cJSON* returnArray = cJSON_CreateArray();
	returnArray->child = CreateObject();
	returnArray->string = _strdup(key);
	return returnArray;
}

cJSON* CreateTestModel()
{
	return cJSON_CreateObject();
}

void AddStringToObject()
{

}

void AddNumberToArray()
{

}

cJSON* CopyRootObject(cJSON* root)
{
	char* newRoot = cJSON_Print(root); // memory allocation
	return cJSON_Parse(newRoot);
}

int GetObjectSize(cJSON* cJSONObject)
{
	return cJSON_GetArraySize(cJSONObject);
}

int GetArraySize(cJSON* cJSONArray)
{
	return cJSON_GetArraySize(cJSONArray->child);
}

// recursive search through whole object tree
cJSON* DeepSearchForItemByKey(cJSON* object, const char* key) // returns first instance of an item by char* key. pseudo random order
{
	cJSON* search = object->child;

	while (search)
	{
		if (search->string)
		{
			if (*search->string == *key)
			{
				return search; // found item
			}
		}

		if (search->next) // check siblings
		{
			std::vector<cJSON*> siblings;

			cJSON* siblingObj = search->next;

			while (siblingObj)
			{
				siblings.push_back(siblingObj);
				siblingObj = siblingObj->next;
			}

			for (cJSON* temp : siblings)
			{
				cJSON* variable;
				variable = DeepSearchForItemByKey(temp, key);
				if (variable)
				{
					if (variable->string)
					{
						if (*variable->string == *key)
						{
							return variable;
						}
					}
				}
			}
		}
		search = search->child;
	}
	return nullptr;
}

// utility helpers
bool json_FileExists(const char* filename) // TODO:: Move to helpers.h/.cpp
{
	FILE* filehandle;
	fopen_s(&filehandle, filename, "r"); // returns error if no file to read
										 //errno_t error = fopen_s(&filehandle, filename, "r");
	if (filehandle)
	{
		fclose(filehandle); // close file stream
		return true; // file exists already
	}
	else
	{
		// OutputPrint("\nFileExists(): Could not find file. Ensure %s exists!\n\n", filename);
		return false; // could not find file
	}
}
void json_CreateNewFile(const char* filename) // checks if file already exists
{
	FILE* filehandle;
	errno_t error = fopen_s(&filehandle, filename, "r");

	if (error == 0)
	{
		OutputPrint("\nCreateNewFile(): %s already exists\n\n", filename);
		fclose(filehandle);
	}
	else if (filehandle == nullptr)
	{
		errno_t error = fopen_s(&filehandle, filename, "w+");
		fclose(filehandle);
	}
}
// Create empty file with "{\n}" to fill cJSON structure
void CreateEmptycJSONFile(const char* filePath)
{
	FILE* f;
	fopen_s(&f, filePath, "w+");
	if (f)
	{
		char buffer[] = { '{', '\n', '}' };
		fwrite(buffer, sizeof(char), sizeof(buffer), f);
		fclose(f);
	}
}
// writing
void AddItemToRootOfFile(cJSON* item, const char* filename)
{
	cJSON* root = OpencJSONStream(filename);
	if (root)
	{
		AddItemToRoot(root, item);
		PrintRootObjectToFile(filename, root);
		ClosecJSONStream(root);
	}
}
void PrintRootObjectToFile(const char* filename, cJSON* root)
{
	const char* jSonstr = cJSON_Print(root);
	WriteStringToFile(filename, jSonstr);
	free((char*)jSonstr);
}
