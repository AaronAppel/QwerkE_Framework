#ifndef _ResourceManager_H_
#define _ResourceManager_H_

#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../QwerkE_Common/Libraries/freetype2/freetype/freetype.h" // TODO: create a font class?
#include "../../QwerkE_Common/Libraries/OpenAL/include/al.h"

#include <string>
#include <map>

class Mesh;
class ShaderComponent;
class Texture;
struct Material;
class ShaderProgram;

// For instances where 1 asset may be shared between objects in
// possibly many scenes, the ResourceManager() may want to count
// the number of instances of an asset and only off load any
// memory when all objects are finished with that asset.

struct AssetInfo
{
	AssetInfo(std::string name, std::string directory) { m_ID = name, m_Directory = directory; }
	std::string m_ID = gc_DefaultStringValue;
	std::string m_Directory = gc_DefaultStringValue;
	short m_References = 0; // When not 0, it is in RAM
};

class ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager();
	void Init();

	bool MeshExists(const char* name);
	bool TextureExists(const char* name);
	bool MaterialExists(const char* name);
	bool FontExists(const char* name);
	bool SoundExists(const char* name);
	bool ShaderProgramExists(const char* name);
	bool ShaderComponentExists(const char* name);

	bool AddMesh(const char* name, Mesh* mesh);
	bool AddTexture(const char* name, Texture* texture);
	bool AddMaterial(const char* name, Material* material);
	bool AddFont(const char* name, FT_Face font);
	bool AddSound(const char* name, ALuint sound);
	bool AddShaderProgram(const char* name, ShaderProgram* ShaderProgram);
	bool AddShaderComponent(const char* name, ShaderComponent* shaderComponent);
	// TODO: Other add functions

	// getters
	// TODO: return const*s so they cannot be modified externally
	// The following functions guarantee a valid return variable using null or error objects
	// TODO: Should getters generate objects? What would be a better way?
	Mesh* GetMesh(const char* name); // specify .ext
    Mesh* GetMeshFromFile(const char* filePath, const char* meshName); // specify .ext
    void UpdateTexture(const char* name, int handle); // TESTING:
	Texture* GetTexture(const char* name); // specify .ext
	Texture* GetTextureFromPath(const char* filePath);
	Material* GetMaterial(const char* name); // specify .ext
	Material* GetMaterialFromPath(const char* filePath);
	FT_Face GetFont(const char* name); // specify .ext
	FT_Face GetFontFromPath(const char* filePath);
	ALuint GetSound(const char* name); // specify .ext
	ALuint GetSoundFromPath(const char* filePath);
	ShaderProgram* GetShaderProgram(const char* name); // specify .ext
	ShaderProgram* GetShaderProgramFromPath(const char* filePath);
	ShaderComponent* GetShaderComponent(const char* name); // specify .ext
	ShaderComponent* GetShaderComponentFromPath(const char* filePath);

	const std::map<std::string, Mesh*>* SeeMeshes() { return &m_Meshes; };
	const std::map<std::string, Texture*>* SeeTextures() { return &m_Textures; };
	const std::map<std::string, Material*>* SeeMaterials() { return &m_Materials; };
	// const std::map<std::string, >* LookAtFonts() { return &; };
	const std::map<std::string, ALuint>* SeeSounds() { return &m_Sounds; };
	const std::map<std::string, ShaderProgram*>* SeeShaderPrograms() { return &m_ShaderProgram; };
	const std::map<std::string, ShaderComponent*>* SeeShaderComponents() { return &m_ShaderComponents; };

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
	std::map<std::string, Mesh*> m_Meshes;
	std::map<std::string, Texture*> m_Textures;
	std::map<std::string, Material*> m_Materials;
	std::map<std::string, FT_Face> m_Fonts;
	std::map<std::string, ALuint> m_Sounds; // TODO: Abstract OpenAL
	std::map<std::string, ShaderProgram*> m_ShaderProgram;
	std::map<std::string, ShaderComponent*> m_ShaderComponents;

	// Utilities
	bool isUnique(Mesh* mesh);
	bool isUnique(Texture* texturehandle);
	bool isUnique(Material* material);
	bool isUnique(FT_Face font);
	bool isSoundUnique(ALuint sound);
	bool isShaderProgramUnique(ShaderProgram* ShaderProgram);
	bool isShaderComponentsUnique(ShaderComponent* shaderComponents);

	// Allocations
	Mesh* InstantiateMesh(const char* name);
	Texture* InstantiateTexture(const char* name);
	Material* InstantiateMaterial(const char* name);
	FT_Face InstantiateFont(const char* fontName);
	ALuint InstantiateSound(const char* soundName);
	ShaderProgram* InstantiateShaderProgram(const char* schematicName);
	ShaderComponent* InstantiateShaderComponent(const char* componentName);

	// Deletions
	// TODO: void* return? Actually write functions.
	// Remember that smart pointers may be necessary for references.
	bool DeleteMesh(const char* name) {}
	bool DeleteTexture(const char* name) {}
	bool DeleteMaterial(const char* name) {}
	bool DeleteFont(const char* name) {}
	bool DeleteSound(const char* name) {}
	bool DeleteShaderProgram(const char* name) {}
	bool DeleteShaderComponent(const char* name) {}

	// Directories
	const char* m_TextureDir = "Resources/Textures/";

	// null objects
	// TODO: Find a better place to store objects. ResourceManager should not "own" objects
	// TODO: Instantiate null objects
	Mesh* m_NullMesh = nullptr;
	Texture* m_NullTexture = nullptr;
	Material* m_NullMaterial = nullptr;
	FT_Face m_NullFont;
	ALuint m_NullSound = 0;

	ShaderProgram* m_NullShader = nullptr;
	ShaderComponent* m_NullVertComponent = nullptr;
	ShaderComponent* m_NullFragComponent = nullptr;
	ShaderComponent* m_NullGeoComponent = nullptr;
};

#endif //!_ResourceManager_H_
