#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Graphics/MaterialData.h"
#include "../../Graphics/Shader/ShaderProgram.h"
#include "../../Graphics/Shader/ShaderComponent.h"
#include "../../Systems/ShaderFactory/ShaderFactory.h"
#include "../../Systems/ServiceLocator.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileLoader/FileLoader.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../Math_Includes.h"
#include "../../Libraries/glew/GL/glew.h"
#include "../../QwerkE_Framework/QwerkE_Directory_Defines.h"

// TODO: Look at resource creation again. Should Resource Manager create assets or just store them?
// TODO: Load all files in folder. This avoids hard coded assets names and allows easy adding/removal of assets even at runtime.
// Objects may need to switch to assets ids. ids would act as unique identifiers in the asset list and would prevent crashing.
void ResourceManager::Init()
{
	m_NullMesh = InstantiateMesh(null_mesh);
	m_NullTexture = InstantiateTexture(null_texture); // TODO: Create a Texture class
	m_NullMaterial = InstantiateMaterial(null_material_schematic);
	m_NullFont = InstantiateFont(null_font); // TODO: Create a valid null font
	m_NullShader = InstantiateShaderProgram(null_shader_schematic);
	m_NullShaderComponent = InstantiateShaderComponent("LitMateial.vert"); // TODO: Handle frag and geo shaders
	// m_NullSound = InstantiateSound(null_sound); // TODO: Create a sound object class
}

// Instantiation Functions
// TODO: Handle errors and deleting assets before returning nullptr
Mesh* ResourceManager::InstantiateMesh(const char* meshName)
{
	MeshFactory t_MeshFactory;
	Mesh* mesh = nullptr;

	if (FileExists(MeshFolderPath(meshName)))
	{
		QwerkE::FileLoader::LoadModelFileToMeshes(MeshFolderPath(meshName));
		if (MeshExists(meshName))
			return m_Meshes[meshName];
		else
			return m_NullMesh;
	}
	else
	{
		// TODO: Dereference *s?
		if (meshName == "Box") // Asset name
		{
			mesh = new Mesh();
			t_MeshFactory.GenerateBox(mesh, vec2(1, 1));
		}
		else if (meshName == null_mesh)
		{
			mesh = t_MeshFactory.ImportOBJMesh(MeshFolderPath(null_mesh), vec3(0.5f, 0.5f, 0.5f), vec2(1, 1), false);
		}
		else if (meshName == "Circle")
		{
			mesh = MeshFactory::CreateCircle(1.0f, 20, vec2(1, 1));
		}
		else if (meshName == "Cube")
		{
			mesh = new Mesh();
			t_MeshFactory.GenerateCube(mesh, vec3(1, 1, 1)); // TODO: Has UV issues
		}
		else if (meshName == "CreBox")
		{
			mesh = t_MeshFactory.CreateBox(vec2(1, 1));
		}
		else if (meshName == "CreCube")
		{
			mesh = t_MeshFactory.CreateCube(vec3(1, 1, 1), vec2(1, 1), true);
		}
		else if (meshName == "Plane")
		{
			mesh = t_MeshFactory.CreatePlane(vec2(10, 10), vec2(2, 2), vec2(1, 1));
		}
		else if (meshName == "TutorialCube")
		{
			mesh = t_MeshFactory.TutorialCube(vec3(1, 1, 1));
		}
		// update to use new model loading capabilities
		/*
		else if (meshName == "Teapot.obj")
		{
			mesh = t_MeshFactory.ImportOBJMesh(MeshPath("Teapot.obj"), vec3(0.5f,0.5f,0.5f), vec2(1,1), false);
		}
		*/
		else
		{
			ConsolePrint("\nInstantiateMesh(): Mesh not found!\n");
			return m_NullMesh;
		}
		m_Meshes[meshName] = mesh; // Add to active list
		mesh->SetName(meshName);
		return mesh;
	}
}

GLuint ResourceManager::InstantiateTexture(const char* textureName)
{
	GLuint textureHandle = 0;
	if (FileExists(TextureFolderPath(textureName)))
	{
		textureHandle = Load2DTexture(TextureFolderPath(textureName));
	}

	if (textureHandle != 0)
		m_Textures[textureName] = textureHandle;
	else
	{
		ConsolePrint("\nInstantiateTexture(): Texture not found!\n");
		textureHandle = m_NullTexture;
	}

	return textureHandle;
}

MaterialData* ResourceManager::InstantiateMaterial(const char* matName)
{
	MaterialData* material = nullptr;

	// TODO: Set null data for handles and names like "Empty"
	if (strcmp(GetFileExtension(matName).c_str(), "msch") == 0)
	{
		// TODO: Handle null or corrupt data
		material = LoadMaterialSchematic(TextureFolderPath(matName));
	}
	else
	{
		ConsolePrint("\nInstantiateMaterial(): Not a .msch file!\n");
	}

	if(!material)
	{
        ConsolePrint("\nInstantiateMaterial(): Material not found!\n");
		return m_NullMaterial; // do not add another material
	}

	m_Materials[matName] = material;
	return material;
}

FT_Face ResourceManager::InstantiateFont(const char* fontName)
{
	FT_Face font;
	FT_Library ft; // TODO: No need to reload ft library

	if (FT_Init_FreeType(&ft))
		ConsolePrint("ERROR::FREETYPE: Could not init FreeType Library");

	if (FT_New_Face(ft, FontFolderPath(fontName), 0, &font))
	{
		ConsolePrint("ERROR::FREETYPE: Failed to load font");
		return NULL;
	}
	m_Fonts[fontName] = font;
	FT_Done_FreeType(ft);
	assert(font != NULL);
	return font;
}

ALuint ResourceManager::InstantiateSound(const char* soundName, DWORD& bufferSize, unsigned short& channels)
{
	// TODO: QwerkE::FileLoader::LoadSoundFile(SoundFolderPath(soundName), bufferSize, channels, frequency);
	return 0;
}

ShaderProgram* ResourceManager::InstantiateShaderProgram(const char* schematicName)
{
	if (FileExists(ShaderFolderPath(schematicName)))
	{
		ShaderProgram* result = LoadShaderSchematic(ShaderFolderPath(schematicName));
		if (result)
		{
			result->SetVertShader(GetShaderComponent(result->GetVertName().c_str()));
			result->SetFragShader(GetShaderComponent(result->GetFragName().c_str()));
			// result->s_geoShader = GetShaderComponentData(result->s_geoName.c_str());

			if (((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->BuildShaderProgram(result))
			{
				m_ShaderProgram[schematicName] = result;
				return result;
			}
			else
			{
				return m_NullShader;
			}
		}
		else
		{
			return m_NullShader;
		}
	}
	else
	{
		return m_NullShader;
	}
}

ShaderComponent* ResourceManager::InstantiateShaderComponent(const char* componentName)
{
	if (FileExists(ShaderFolderPath(componentName)))
	{
		ShaderComponent* result = nullptr;
		if (strcmp(GetFileExtension(componentName).c_str(), "vert") == 0)
		{
			 result = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateShaderComponent(
				GL_VERTEX_SHADER, ShaderFolderPath(componentName));
		}
		else if (strcmp(GetFileExtension(componentName).c_str(), "frag") == 0)
		{
			result = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateShaderComponent(
				GL_FRAGMENT_SHADER, ShaderFolderPath(componentName));
		}
		else if (strcmp(GetFileExtension(componentName).c_str(), "geo") == 0)
		{
			result = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateShaderComponent(
				GL_GEOMETRY_SHADER, ShaderFolderPath(componentName));
		}

		if (result)
		{
			m_ShaderComponents[componentName] = result;
			return result;
		}
		else
		{
			return m_NullShaderComponent;
		}
	}
	else
	{
		return m_NullShaderComponent;
	}
}
