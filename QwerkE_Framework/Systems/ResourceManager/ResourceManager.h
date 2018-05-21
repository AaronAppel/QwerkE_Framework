#ifndef _ResourceManager_H_
#define _ResourceManager_H_

#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../QwerkE_Common/Libraries/freetype2/freetype/freetype.h" // TODO: create a font class?
#include "../../QwerkE_Common/Libraries/OpenAL/include/al.h"

#include <string>
#include <map>

class Mesh;
class ShaderProgram;
struct MaterialData;

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

	bool MeshExists(const char* name);
	bool ShaderExists(const char* name);
	bool TextureExists(const char* name);
	bool MaterialExists(const char* name);
	bool FontExists(const char* name);
	bool SoundExists(const char* name);

	bool AddMesh(const char* name, Mesh* mesh);
	bool AddShader(const char* name, ShaderProgram* shader);
	bool AddTexture(const char* name, GLuint texture);
	bool AddMaterial(const char* name, MaterialData* material);
	bool AddFont(const char* name, FT_Face font);
	bool AddSound(const char* name, ALuint sound);
	// TODO: Other add functions

	// getters
	// TODO: return const*s so they cannot be modified externally
	// The following functions guarantee a valid return variable using null or error objects
	Mesh* GetMesh(const char* name); // specify .ext
	ShaderProgram* GetShader(const char* name); // specify .ext
	GLuint GetTexture(const char* name); // specify .ext
	MaterialData* GetMaterial(const char* name); // specify .ext
	FT_Face GetFont(const char* name); // specify .ext
	ALuint GetSound(const char* name); // specify .ext

	// TEST:
	const std::map<std::string, Mesh*>* LookAtMeshes() { return &m_Meshes; };
	const std::map<std::string, ShaderProgram*>* LookAtShaders() { return &m_Shaders; };
	const std::map<std::string, GLuint>* LookAtTextures() { return &m_Textures; };
	const std::map<std::string, MaterialData*>* LookAtMaterials() { return &m_Materials; };
	// const std::map<std::string, >* LookAtFonts() { return &; };
	const std::map<std::string, ALuint>* LookAtSounds() { return &m_Sounds; };

	// TODO: Handle loading additional resources
	// CubeMap* GetCubeMap(const char* name); // specify .ext
	// FBO* GetFBO(const char* name); // specify .ext
	// Sound* GetSound(const char* name); // specify .ext

	// Load directory
	// void LoadDirectory(const char* folder); // TODO: Move outside and into a FileLoader object

	// Cleanup
	void DeleteAllResources();

private:
	// resource storage
	std::map<std::string, Mesh*> m_Meshes; // TODO: Rename
	std::map<std::string, ShaderProgram*> m_Shaders;
	std::map<std::string, GLuint> m_Textures;
	std::map<std::string, MaterialData*> m_Materials;
	std::map<std::string, FT_Face> m_Fonts;
	std::map<std::string, ALuint> m_Sounds;

	// Utilities
	bool isUnique(Mesh* mesh);
	bool isUnique(ShaderProgram* shader);
	bool isUnique(GLuint texturehandle);
	bool isUnique(MaterialData* material);
	bool isUnique(FT_Face font);
	bool isSoundUnique(ALuint sound);

	// Allocations
	Mesh* InstantiateMesh(const char* name);
	ShaderProgram* InstantiateShader(const char* name);
	GLuint InstantiateTexture(const char* name);
	MaterialData* InstantiateMaterial(const char* name);
	FT_Face InstantiateFont(const char* fontName);
	ALuint InstantiateSound(const char* soundName, DWORD& bufferSize, unsigned short& channels);

	// Deletions
	// TODO: void* return? Actually write functions.
	// Remember that smart pointers may be necessary for references.
	bool DeleteMesh(const char* name) {};
	bool DeleteShader(const char* name) {};
	bool DeleteTexture(const char* name) {};
	bool DeleteMaterial(const char* name) {};
	bool DeleteFont(const char* name) {};
	bool DeleteSound(const char* name) {};

	// Directories
	const char* m_TextureDir = "Resources/Textures/";

	// null objects
	// TODO: Find a better place to store objects. ResourceManager should not "own" objects
	// TODO: Instatiate null objects
	Mesh* m_NullMesh = nullptr;
	ShaderProgram* m_NullShader = nullptr;
	GLuint m_NullTexture = 0;
	MaterialData* m_NullMaterial = nullptr;
	FT_Face m_NullFont;
	ALuint m_NullSound;
};

#endif //!_ResourceManager_H_
