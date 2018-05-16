#include "ResourceManager.h"
#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"

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

    for (auto object : m_Models)
        delete object.second;

	// TODO: delete fonts

	m_Meshes.clear(); // Empty std::maps
	m_Shaders.clear();
	m_Textures.clear();
	m_Materials.clear();
	m_Models.clear();
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

bool ResourceManager::ModelExists(const char* name)
{
	return m_Models.find(name) != m_Models.end();
}

bool ResourceManager::FontExists(const char* name)
{
	return m_Fonts.find(name) != m_Fonts.end();
}
// getters
// TODO: Return nullptr values
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

Model* ResourceManager::GetModel(const char* name)
{
	if (m_Models.find(name) != m_Models.end())
	{
		return m_Models[name];
	}
	return InstantiateModel(name);
}

FT_Face ResourceManager::GetFont(const char* name)
{
	if (m_Fonts.find(name) != m_Fonts.end())
	{
		return m_Fonts[name];
	}
	return InstantiateFont(name);
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

bool ResourceManager::isUnique(Model* model)
{
	std::map<std::string, Model*>::iterator it;
	for (it = m_Models.begin(); it != m_Models.end(); it++)
	{
		if (it->second == model) // pointer comparison
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