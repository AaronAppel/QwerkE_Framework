#include "ResourceManager.h"
#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../Graphics/Gfx_Classes/MaterialData.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/ShaderProgram/ShaderProgram.h"

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

	for (auto object : m_Shaders)
		delete object.second;

	for (auto object : m_Textures)
		glDeleteTextures(1, &object.second);

	for (auto object : m_Materials)
		delete object.second;
	
	// TODO: delete fonts

	m_Meshes.clear(); // Empty std::maps
	m_Shaders.clear();
	m_Textures.clear();
	m_Materials.clear();
	// m_Fonts.clear();
}

bool ResourceManager::MeshExists(const char* name)
{
	return m_Meshes.find(name) != m_Meshes.end();
}

bool ResourceManager::ShaderExists(const char* name)
{
	return m_Shaders.find(name) != m_Shaders.end();
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

bool ResourceManager::AddMesh(const char* name, Mesh* mesh)
{
	if (MeshExists(name))
		return false;

	if (mesh == nullptr || mesh->GetName() == "Uninitialized")
		return false;

	m_Meshes[name] = mesh;
	return true;
}

bool ResourceManager::AddShader(const char* name, ShaderProgram* shader)
{
	if (ShaderExists(name))
		return false;

	if (shader == nullptr ) // || shader->GetName() == "Uninitialized")
		return false;

	m_Shaders[name] = shader;
	return true;
}

bool ResourceManager::AddTexture(const char* name, GLuint texture)
{
	if (TextureExists(name))
		return false;

	if (texture == 0) // || texture->name == "Uninitialized") // TODO: What should a null texture value be cross platform?
		return false;

	m_Textures[name] = texture;
	return true;
}

bool ResourceManager::AddMaterial(const char* name, MaterialData* material)
{
	if (MaterialExists(name))
		return false;

	if (material == nullptr || material->name == "Uninitialized")
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

// getters
// TODO: Return null objects
Mesh* ResourceManager::GetMesh(const char* name)
{
	if (m_Meshes.find(name) != m_Meshes.end())
	{
		return m_Meshes[name];
	}
	return InstantiateMesh(name);
}

ShaderProgram* ResourceManager::GetShader(const char* name)
{
	if (m_Shaders.find(name) != m_Shaders.end()) // unique name
	{
		return m_Shaders[name];
	}
	return InstantiateShader(name); // TODO: Should The resource manager create assets?
}

GLuint ResourceManager::GetTexture(const char* name)
{
	if (m_Textures.find(name) != m_Textures.end())
	{
		return m_Textures[name];
	}
	return InstantiateTexture(name);
}

MaterialData* ResourceManager::GetMaterial(const char* name)
{
	if (m_Materials.find(name) != m_Materials.end())
	{
		return m_Materials[name];
	}
	return InstantiateMaterial(name);
}

FT_Face ResourceManager::GetFont(const char* name)
{
	if (m_Fonts.find(name) != m_Fonts.end())
	{
		return m_Fonts[name];
	}
	return InstantiateFont(name);
}

ALuint ResourceManager::GetSound(const char* name)
{
	if (!SoundExists(name))
	{
		return m_Sounds[name];
	}
	// TODO:
	// return InstantiateSound(name);
	return 0;
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

bool ResourceManager::isUnique(ShaderProgram* shader)
{
	std::map<std::string, ShaderProgram*>::iterator it;
	for (it = m_Shaders.begin(); it != m_Shaders.end(); it++)
	{
		if (it->second == shader) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(GLuint texturehandle)
{
	std::map<std::string, GLuint>::iterator it;
	for (it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		if (it->second == texturehandle) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(MaterialData* material)
{
	std::map<std::string, MaterialData*>::iterator it;
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