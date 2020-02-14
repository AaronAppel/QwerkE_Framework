#ifndef _Resources_H_
#define _Resources_H_

// TODO: Remove includes for all types if possible
#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../QwerkE_Common/Libraries/freetype2/freetype/freetype.h" // TODO: create a font class?
#include "../../QwerkE_Common/Libraries/OpenAL/include/al.h"

#include <string>
#include <map>

// For instances where 1 asset may be shared between objects in
// possibly many scenes, the Resources() may want to count
// the number of instances of an asset and only off load any
// memory when all objects are finished with that asset.

namespace QwerkE {

    struct Texture;
    class Mesh;
    class ShaderComponent;
    class Material;
    class Resources;

    // TODO: Move to own file
    struct AssetInfo
    {
        AssetInfo(std::string name, std::string directory) { m_ID = name, m_Directory = directory; }
        std::string m_ID = gc_DefaultStringValue;
        std::string m_Directory = gc_DefaultStringValue;
        short m_References = 0; // When not 0, it is in RAM
    };

    class Resources
    {
    public:
        static void Initialize();

        static bool MeshExists(const char* name);
        static bool TextureExists(const char* name);
        static bool MaterialExists(const char* name);
        static bool FontExists(const char* name);
        static bool SoundExists(const char* name);
        static bool ShaderProgramExists(const char* name);
        static bool ShaderComponentExists(const char* name);

        static bool AddMesh(const char* name, Mesh* mesh);
        static bool AddTexture(const char* name, Texture* texture);
        static bool AddMaterial(const char* name, Material* material);
        static bool AddFont(const char* name, FT_Face font);
        static bool AddSound(const char* name, ALuint sound);
        static bool AddShaderProgram(const char* name, ShaderProgram* ShaderProgram);
        static bool AddShaderComponent(const char* name, ShaderComponent* shaderComponent);
        // TODO: Other add functions

        // getters
        // TODO: return const*s so they cannot be modified externally
        // The following functions guarantee a valid return variable using null or error objects
        // TODO: Should getters generate objects? What would be a better way?
        static Mesh* GetMesh(const char* name); // specify .ext
        static Mesh* GetMeshFromFile(const char* filePath, const char* meshName); // specify .ext
        static void UpdateTexture(const char* name, int handle); // TESTING:
        static Texture* GetTexture(const char* name); // specify .ext
        static Texture* GetTextureFromPath(const char* filePath);
        static Material* GetMaterial(const char* name); // specify .ext
        static Material* GetMaterialFromPath(const char* filePath);
        static FT_Face GetFont(const char* name); // specify .ext
        static FT_Face GetFontFromPath(const char* filePath);
        static ALuint GetSound(const char* name); // specify .ext
        static ALuint GetSoundFromPath(const char* filePath);
        static ShaderProgram* GetShaderProgram(const char* name); // specify .ext
        static ShaderProgram* GetShaderProgramFromPath(const char* filePath);
        static ShaderComponent* GetShaderComponent(const char* name); // specify .ext
        static ShaderComponent* GetShaderComponentFromPath(const char* filePath);

        static const std::map<std::string, Mesh*>* SeeMeshes() { return &m_Meshes; };
        static const std::map<std::string, Texture*>* SeeTextures() { return &m_Textures; };
        static const std::map<std::string, Material*>* SeeMaterials() { return &m_Materials; };
        // static const std::map<std::string, >* LookAtFonts() { return &; };
        static const std::map<std::string, ALuint>* SeeSounds() { return &m_Sounds; };
        static const std::map<std::string, ShaderProgram*>* SeeShaderPrograms() { return &m_ShaderPrograms; };
        static const std::map<std::string, ShaderComponent*>* SeeShaderComponents() { return &m_ShaderComponents; };

        // TODO: Handle loading additional resources
        // CubeMap* GetCubeMap(const char* name); // specify .ext
        // FBO* GetFBO(const char* name); // specify .ext
        // Sound* GetSound(const char* name); // specify .ext

        // Load directory
        // void LoadDirectory(const char* folder); // TODO: Move outside and into a FileLoader object

        // Cleanup
        static void DeleteAllResources();

    private:
        Resources();
        ~Resources();

        // TODO: Consider using unordered maps
        // resource storage
        static std::map<std::string, Mesh*> m_Meshes;
        static std::map<std::string, Texture*> m_Textures;
        static std::map<std::string, Material*> m_Materials;
        static std::map<std::string, FT_Face> m_Fonts;
        static std::map<std::string, ALuint> m_Sounds; // TODO: Abstract OpenAL
        static std::map<std::string, ShaderProgram*> m_ShaderPrograms;
        static std::map<std::string, ShaderComponent*> m_ShaderComponents;

        // Utilities
        static bool isUnique(Mesh* mesh);
        static bool isUnique(Texture* texturehandle);
        static bool isUnique(Material* material);
        static bool isUnique(FT_Face font);
        static bool isSoundUnique(ALuint sound);
        static bool isShaderProgramUnique(ShaderProgram* ShaderProgram);
        static bool isShaderComponentsUnique(ShaderComponent* shaderComponents);

        // Allocations
        static Mesh* InstantiateMesh(const char* name);
        static Texture* InstantiateTexture(const char* name);
        static Material* InstantiateMaterial(const char* name);
        static FT_Face InstantiateFont(const char* fontName);
        static ALuint InstantiateSound(const char* soundName);
        static ShaderProgram* InstantiateShaderProgram(const char* schematicName);
        static ShaderComponent* InstantiateShaderComponent(const char* componentName);

        // Deletions
        // TODO: void* return? Actually write functions.
        // Remember that smart pointers may be necessary for references.
        static bool DeleteMesh(const char* name) {}
        static bool DeleteTexture(const char* name) {}
        static bool DeleteMaterial(const char* name) {}
        static bool DeleteFont(const char* name) {}
        static bool DeleteSound(const char* name) {}
        static bool DeleteShaderProgram(const char* name) {}
        static bool DeleteShaderComponent(const char* name) {}
    };

}
#endif // !_Resources_H_
