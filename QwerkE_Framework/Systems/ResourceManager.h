#ifndef _ResourceManager_H_
#define _ResourceManager_H_

#include "../../Shared_Generic/Libraries/glew/GL/glew.h"
#include <string>
#include <map>

class Mesh;
class ShaderProgram;
class Model;
class MaterialData;

// For instances where 1 asset may be shared between objects in
// possibly many scenes, the ResourceManager() may want to count
// the number of instances of an asset and only off load any
// memory when all objects are finished with that asset.

struct AssetInfo
{
	AssetInfo(std::string name, std::string directory) { m_ID = name, m_Directory = directory; }
	std::string m_ID = "Uninitialized";
	std::string m_Directory = "Uninitialized";
	short m_References = 0; // When not 0, it is in RAM
};

class ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager();
	void Init();

	// getters
	Mesh* GetMesh(const char* name);
	ShaderProgram* GetShader(const char* name);
	GLuint GetTexture(const char* name);
	MaterialData* GetMaterial(const char* name);
	Model* GetModel(const char* name);

	// Load directory
	// void LoadDirectory(const char* folder);

	// Cleanup
	void DeleteAllResources();

private:
	// Hot lists
	std::map<std::string, Mesh*> m_HotMeshes; // TODO: Rename
	std::map<std::string, ShaderProgram*> m_HotShaders;
	std::map<std::string, GLuint> m_HotTextures;
	std::map<std::string, MaterialData*> m_HotMaterials;
    std::map<std::string, Model*> m_HotModels;

	// Utilities
	bool isUnique(Mesh* mesh);
	bool isUnique(ShaderProgram* shader);
	bool isUnique(GLuint texturehandle);
	bool isUnique(MaterialData* material);
	bool isUnique(Model* model);

	// Allocations
	Mesh* InstantiateMesh(const char* name);
	ShaderProgram* InstantiateShader(const char* name);
	GLuint InstantiateTexture(const char* name);
	MaterialData* InstantiateMaterial(const char* name);
	Model* InstantiateModel(const char* name);

	// Deletions
	bool DeleteMesh(const char* name) {};
	bool DeleteShader(const char* name) {};
	bool DeleteTexture(const char* name) {};
	bool DeleteMaterial(const char* name) {};
	bool DeleteModel(const char* name) {};

	// Directories
	const char* m_TextureDir = "Resources/Textures/";
};

#endif //!_ResourceManager_H_
