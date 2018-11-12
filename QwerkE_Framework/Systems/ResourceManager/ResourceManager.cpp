#include "ResourceManager.h"
#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Texture.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../../Graphics/Shader/ShaderProgram.h"
#include "../FileSystem/FileSystem.h"
#include "../ServiceLocator.h"

#include <map>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	DeleteAllResources();
}

void ResourceManager::DeleteAllResources()
{
	for (auto object : m_Meshes)
		delete object.second;

	for (auto object : m_Textures)
		glDeleteTextures(1, &object.second->s_Handle);

	for (auto object : m_Materials)
		delete object.second;

	// TODO: delete fonts

	m_Meshes.clear(); // Empty std::maps
	m_Textures.clear();
	m_Materials.clear();
	// m_Fonts.clear();
}

bool ResourceManager::MeshExists(const char* name)
{
	return m_Meshes.find(name) != m_Meshes.end();
}

bool ResourceManager::TextureExists(const char* name)
{
	return m_Textures.find(name) != m_Textures.end();
}

bool ResourceManager::MaterialExists(const char* name)
{
	return m_Materials.find(name) != m_Materials.end();
}

bool ResourceManager::FontExists(const char* name)
{
	return m_Fonts.find(name) != m_Fonts.end();
}

bool ResourceManager::SoundExists(const char* name)
{
	return m_Sounds.find(name) != m_Sounds.end();
}

bool ResourceManager::ShaderProgramExists(const char* name)
{
	return m_ShaderProgram.find(name) != m_ShaderProgram.end();
}

bool ResourceManager::ShaderComponentExists(const char* name)
{
	return m_ShaderComponents.find(name) != m_ShaderComponents.end();
}

bool ResourceManager::AddMesh(const char* name, Mesh* mesh)
{
	if (MeshExists(name))
		return false;

	if (mesh == nullptr || mesh->GetName() == "Uninitialized")
		return false;

	m_Meshes[name] = mesh;
	return true;
}

bool ResourceManager::AddTexture(const char* name, Texture* texture)
{
	if (!texture)
		return false;

	if (TextureExists(name))
		return false;

	if (texture->s_Handle == 0) // || texture->name == "Uninitialized") // TODO: What should a null texture value be cross platform?
		return false;

	m_Textures[name] = texture;
	return true;
}

bool ResourceManager::AddMaterial(const char* name, Material* material)
{
	if (!material)
		return false;

	if (MaterialExists(name))
		return false;

	if (material == nullptr || material->GetMaterialName() == "Uninitialized")
		return false;

	m_Materials[name] = material;
	return true;
}

bool ResourceManager::AddFont(const char* name, FT_Face font)
{
	if (FontExists(name))
		return false;

	// TODO: How to check for null font? Also need cross library font classes
	// if (font == nullptr || material->name == "Uninitialized")
		// return false;

	m_Fonts[name] = font;
	return true;
}

bool ResourceManager::AddSound(const char* name, ALuint sound)
{
	if (SoundExists(name))
		return false;

	if (sound == 0)
		return false;

	m_Sounds[name] = sound;
	return true;
}

bool ResourceManager::AddShaderProgram(const char* name, ShaderProgram* ShaderProgram)
{
	if (ShaderProgramExists(name))
		return false;

	if (ShaderProgram == nullptr)
		return false;

	m_ShaderProgram[name] = ShaderProgram;
	return true;
}

bool ResourceManager::AddShaderComponent(const char* name, ShaderComponent* shaderComponent)
{
	if (ShaderComponentExists(name))
		return false;

	if (shaderComponent == nullptr)
		return false;

	m_ShaderComponents[name] = shaderComponent;
	return true;
}
// getters
// TODO: Return null objects
Mesh* ResourceManager::GetMesh(const char* name)
{
	if (m_Meshes.find(name) != m_Meshes.end())
	{
		return m_Meshes[name];
	}
	return InstantiateMesh(MeshFolderPath(name));
}

Mesh* ResourceManager::GetMeshFromFile(const char* fileName, const char* meshName)
{
	if (MeshExists(meshName))
		return m_Meshes[meshName];

	Mesh* result = ((FileSystem*)QwerkE::ServiceLocator::GetService(eEngineServices::FileSystem))->LoadMeshInModelByName(
		MeshFolderPath(fileName), meshName);
	if (result)
	{
		m_Meshes[meshName] = result;
		return result;
	}
	else
		return m_NullMesh;
}

Texture* ResourceManager::GetTexture(const char* name)
{
	if (m_Textures.find(name) != m_Textures.end())
		return m_Textures[name];
	
	//* <-- toggle double slash
	else
	{
		if (FileExists(TextureFolderPath(name)))
		{
			JobManager* jMan = (JobManager*)QwerkE::ServiceLocator::GetService(eEngineServices::JobManager);
			jMan->ScheduleTask(new QLoadAsset(name));
		}
		return m_Textures[null_texture]; // return temp asset to use
	}
	/*/
	return InstantiateTexture(name);
	// */
}

Texture* ResourceManager::GetTextureFromPath(const char* filePath)
{
	if (TextureExists(GetFileNameWithExt(filePath).c_str()))
		return m_Textures[GetFileNameWithExt(filePath).c_str()];

	InstantiateTexture(filePath);
}

Material* ResourceManager::GetMaterial(const char* name)
{
	if (m_Materials.find(name) != m_Materials.end())
		return m_Materials[name];

	return InstantiateMaterial(TextureFolderPath(name));
}

Material* ResourceManager::GetMaterialFromPath(const char* filePath)
{
	if (m_Materials.find(GetFileNameWithExt(filePath).c_str()) != m_Materials.end())
		return m_Materials[GetFileNameWithExt(filePath).c_str()];

	return InstantiateMaterial(filePath);
}

FT_Face ResourceManager::GetFont(const char* name)
{
	if (m_Fonts.find(name) != m_Fonts.end())
		return m_Fonts[name];

	return InstantiateFont(FontFolderPath(name));
}

FT_Face ResourceManager::GetFontFromPath(const char* filePath)
{
	if (m_Fonts.find(GetFileNameWithExt(filePath).c_str()) != m_Fonts.end())
		return m_Fonts[GetFileNameWithExt(filePath).c_str()];

	return InstantiateFont(filePath);
}

ALuint ResourceManager::GetSound(const char* name)
{
	if (SoundExists(name))
		return m_Sounds[name];

	return InstantiateSound(SoundFolderPath(name));
}

ALuint ResourceManager::GetSoundFromPath(const char* filePath)
{
	if (SoundExists(GetFileNameWithExt(filePath).c_str()))
		return m_Sounds[GetFileNameWithExt(filePath).c_str()];

	return InstantiateSound(filePath);
}

ShaderProgram* ResourceManager::GetShaderProgram(const char* name)
{
	if (ShaderProgramExists(name))
		return m_ShaderProgram[name];

	return InstantiateShaderProgram(ShaderFolderPath(name));
}

ShaderProgram* ResourceManager::GetShaderProgramFromPath(const char* filePath)
{
	if (ShaderProgramExists(GetFileNameWithExt(filePath).c_str()))
		return m_ShaderProgram[GetFileNameWithExt(filePath).c_str()];

	return InstantiateShaderProgram(filePath);
}

ShaderComponent* ResourceManager::GetShaderComponent(const char* name)
{
	if (ShaderComponentExists(name))
		return m_ShaderComponents[name];

	return InstantiateShaderComponent(ShaderFolderPath(name));
}

ShaderComponent* ResourceManager::GetShaderComponentFromPath(const char* filePath)
{
	if (ShaderComponentExists(GetFileNameWithExt(filePath).c_str()))
		return m_ShaderComponents[GetFileNameWithExt(filePath).c_str()];

	return InstantiateShaderComponent(filePath);
}

// Utilities
bool ResourceManager::isUnique(Mesh* mesh)
{
	std::map<std::string, Mesh*>::iterator it;
	for (it = m_Meshes.begin(); it != m_Meshes.end(); it++)
	{
		if (it->second == mesh) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(Texture* texturehandle)
{
	std::map<std::string, Texture*>::iterator it;
	for (it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		if (it->second == texturehandle)
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(Material* material)
{
	std::map<std::string, Material*>::iterator it;
	for (it = m_Materials.begin(); it != m_Materials.end(); it++)
	{
		if (it->second == material) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(FT_Face font)
{
	std::map<std::string, FT_Face>::iterator it;
	for (it = m_Fonts.begin(); it != m_Fonts.end(); it++)
	{
		if (it->second == font) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isSoundUnique(ALuint sound)
{
	std::map<std::string, ALuint>::iterator it;
	for (it = m_Sounds.begin(); it != m_Sounds.end(); it++)
	{
		if (it->second == sound) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isShaderProgramUnique(ShaderProgram* shaderProgram)
{
	std::map<std::string, ShaderProgram*>::iterator it;
	for (it = m_ShaderProgram.begin(); it != m_ShaderProgram.end(); it++)
	{
		if (it->second == shaderProgram) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isShaderComponentsUnique(ShaderComponent* shaderComponent)
{
	std::map<std::string, ShaderComponent*>::iterator it;
	for (it = m_ShaderComponents.begin(); it != m_ShaderComponents.end(); it++)
	{
		if (it->second == shaderComponent) // pointer comparison
			return false;
	}
	return true;
}