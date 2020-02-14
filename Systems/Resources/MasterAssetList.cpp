#include "../../Systems/Resources/Resources.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Shader/ShaderProgram.h"
#include "../../Graphics/Shader/ShaderComponent.h"
#include "../../Systems/ShaderFactory/ShaderFactory.h"
#include "QwerkE_Common/Utilities/StringHelpers.h"
#include "QwerkE_Common/Utilities/PrintFunctions.h"
#include "../FileSystem/FileSystem.h"
#include "../FileSystem/FileSystem.h"
#include "Utilities/FileIO/FileUtilities.h"
#include "Math_Includes.h"
#include "../../Libraries/glew/GL/glew.h"
#include "../../Headers/QwerkE_Directory_Defines.h"
#include "../../Graphics/Texture.h"
#include "../Jobs/Jobs.h"

namespace QwerkE {

    std::map<std::string, Mesh*> Resources::m_Meshes;
    std::map<std::string, Texture*> Resources::m_Textures;
    std::map<std::string, Material*> Resources::m_Materials;
    std::map<std::string, FT_Face> Resources::m_Fonts;
    std::map<std::string, ALuint> Resources::m_Sounds; // TODO: Abstract OpenAL
    std::map<std::string, ShaderProgram*> Resources::m_ShaderPrograms;
    std::map<std::string, ShaderComponent*> Resources::m_ShaderComponents;

	// TODO: Look at resource creation again. Should Resource Manager create assets or just store them?
	// TODO: Load all files in folder. This avoids hard coded assets names and allows easy adding/removal of assets even at runtime.
	// Objects may need to switch to assets ids. ids would act as unique identifiers in the asset list and would prevent crashing.
	void Resources::Initialize()
	{
		// TODO: Handle, or consider preventing, multiple Init() calls to avoid duplicated/leaked data issues

		InstantiateMesh(NullFolderPath(null_mesh_filename));
		InstantiateTexture(NullFolderPath(null_texture)); // TODO: Create a Texture class
		InstantiateMaterial(NullFolderPath(null_material_schematic));
        InstantiateFont(NullFolderPath(null_font)); // TODO: Create a valid null font
        InstantiateShaderComponent(NullFolderPath(null_vert_component)); // TODO: Remove null component references. Store components and reference them in shader programs
        InstantiateShaderComponent(NullFolderPath(null_frag_component)); // TODO: Remove null component references. Store components and reference them in shader programs
		// TODO: InstantiateShaderComponent(NullFolderPath(null_geo_component));  // TODO: Remove null component references. Store components and reference them in shader programs
		InstantiateShaderProgram(NullFolderPath(null_shader_schematic));
		InstantiateSound(NullFolderPath(null_sound));
	}

	// Instantiation Functions
	// TODO: Handle errors and deleting assets before returning nullptr
	Mesh* Resources::InstantiateMesh(const char* meshFilePath)
	{
		Mesh* mesh = nullptr;

		if (FileExists(meshFilePath))
		{
			FileSystem::LoadModelFileToMeshes(meshFilePath);
			if (MeshExists(GetFileNameNoExt(meshFilePath).c_str())) // TODO: Better way to handle file paths and resource names
				return m_Meshes[GetFileNameNoExt(meshFilePath).c_str()];
			else
				return m_Meshes[null_mesh];
		}
		else
		{
			if (strcmp(meshFilePath, MeshFolderPath("Create_Quad")) == 0)
			{
				mesh = MeshFactory::CreateQuad(vec2(10, 10));
			}
			else if (strcmp(meshFilePath, null_mesh) == 0)
			{
				mesh = MeshFactory::ImportOBJMesh(null_mesh, vec3(0.5f, 0.5f, 0.5f), vec2(1, 1), false);
			}
			else if (strcmp(meshFilePath, MeshFolderPath("Create_Circle")) == 0)
			{
				mesh = MeshFactory::CreateCircle(1.0f, 20, vec2(1, 1));
			}
			else if (strcmp(meshFilePath, MeshFolderPath("Create_Cube")) == 0)
			{
				mesh = MeshFactory::CreateCube(vec3(1, 1, 1), vec2(1, 1), true);
			}
			else if (strcmp(meshFilePath, MeshFolderPath("Tutorial_Cube")) == 0)
			{
				mesh = MeshFactory::TutorialCube(vec3(1, 1, 1));
			}
			else if (strcmp(meshFilePath, MeshFolderPath("Test_Plane")) == 0)
			{
				mesh = MeshFactory::CreateTestPlane();
			}
			// update to use new model loading capabilities
			/*
			else if (meshName == "Teapot.obj")
			{
				mesh = MeshFactory::ImportOBJMesh(MeshPath("Teapot.obj"), vec3(0.5f,0.5f,0.5f), vec2(1,1), false);
			}
			*/
			else
			{
				LOG_ERROR("InstantiateMesh(): Mesh not found! {0}", meshFilePath);
				return m_Meshes[null_mesh];
			}

			m_Meshes[GetFileNameWithExt(meshFilePath).c_str()] = mesh; // Add to active list
			mesh->SetName(GetFileNameWithExt(meshFilePath).c_str());
			return mesh;
		}
	}

	Texture* Resources::InstantiateTexture(const char* textureName)
	{
		if (FileExists(textureName))
		{
			Texture* texture = nullptr;
			texture = new Texture();
			texture->s_Handle = Load2DTexture(textureName);
			texture->s_Name = GetFileNameWithExt(textureName);

			if (texture->s_Handle != 0)
			{
				m_Textures[texture->s_Name] = texture;
				return texture;
			}
			else
			{
				delete texture;
				return m_Textures[null_texture];
			}
		}
		else
		{
            ConsolePrint("\nInstantiateTexture(): Texture not found!\n");
            return m_Textures[null_texture];
		}
	}

	Material* Resources::InstantiateMaterial(const char* matName)
	{
		Material* material = nullptr;

		// TODO: Set null data for handles and names like "Empty"
		if (strcmp(GetFileExtension(matName).c_str(), material_schematic_ext) == 0)
		{
			// TODO: Handle null or corrupt data
			if (FileExists(matName))
				material = LoadMaterialSchematic(matName);
			else
				material = LoadMaterialSchematic(TextureFolderPath(matName));
		}
		else
		{
			ConsolePrint("\nInstantiateMaterial(): Not a .msch file!\n");
		}

		if (!material)
		{
			ConsolePrint("\nInstantiateMaterial(): Material not found!\n");
			return m_Materials[null_material]; // Do not add another material
		}

		m_Materials[GetFileNameWithExt(matName).c_str()] = material;
		return material;
	}

	FT_Face Resources::InstantiateFont(const char* fontName)
	{
		FT_Face font;
		FT_Library ft = NULL; // TODO: No need to reload ft library

		static bool triedInit = false; // TODO: Improve logic
		if (triedInit == false)
		{
			triedInit = true;

			if (FT_Init_FreeType(&ft))
				ConsolePrint("ERROR::FREETYPE: Could not init FreeType Library");
		}

		if (FT_New_Face(ft, fontName, 0, &font))
		{
			ConsolePrint("ERROR::FREETYPE: Failed to load font");
			return m_Fonts[null_font];
		}
		m_Fonts[fontName] = font;
		FT_Done_FreeType(ft);
		assert(font != NULL);
		return font;
	}

	ALuint Resources::InstantiateSound(const char* soundPath)
	{
		ALuint handle = 0;
		handle = FileSystem::LoadSound(soundPath);

		if (handle != 0)
		{
            m_Sounds[GetFileNameWithExt(soundPath)] = handle;
			return handle;
		}
		else
		{
			return m_Sounds[null_sound];
		}
	}

	ShaderProgram* Resources::InstantiateShaderProgram(const char* schematicFile)
	{
		if (FileExists(schematicFile))
		{
			ShaderProgram* result = LoadShaderSchematic(schematicFile); // TODO: Free memory on error
			if (result)
			{
				result->SetVertShader(GetShaderComponent(result->GetVertName().c_str()));
				result->SetFragShader(GetShaderComponent(result->GetFragName().c_str()));
				// result->s_geoShader = GetShaderComponentData(result->s_geoName.c_str());

				if (ShaderFactory::LinkCreatedShaderProgram(result))
				{
					m_ShaderPrograms[GetFileNameWithExt(schematicFile)] = result;
					result->FindAttributesAndUniforms();
					return result;
				}
			}
        }
        return m_ShaderPrograms[null_shader_schematic];
	}

	ShaderComponent* Resources::InstantiateShaderComponent(const char* componentName)
	{
		// TODO: Add assert for geometry shaders
		if (FileExists(componentName))
		{
			ShaderComponent* result = nullptr;
			if (strcmp(GetFileExtension(componentName).c_str(), vertex_shader_ext) == 0)
			{
				result = ShaderFactory::CreateShaderComponent(GL_VERTEX_SHADER, componentName);

				if (result)
				{
					m_ShaderComponents[componentName] = result;
					return result;
				}
				else
				{
					return m_ShaderComponents[null_vert_component];
				}
			}
			else if (strcmp(GetFileExtension(componentName).c_str(), fragment_shader_ext) == 0)
			{
				result = ShaderFactory::CreateShaderComponent(GL_FRAGMENT_SHADER, componentName);

				if (result)
				{
					m_ShaderComponents[componentName] = result;
					return result;
				}
				else
                {
                    return m_ShaderComponents[null_frag_component];
				}
			}
			// TODO: Support geometry shaders
			/*else if (strcmp(GetFileExtension(componentName).c_str(), geometry_shader_ext) == 0)
			{
				result = ((ShaderFactory*)QwerkE::Services::GetService(eEngineServices::Factory_Shader))->CreateShaderComponent(
					GL_GEOMETRY_SHADER, componentName);

				if (result)
				{
					m_ShaderComponents[componentName] = result;
					return result;
				}
				else
                {
                    return m_ShaderComponents[null_geo_component];
				}
			}*/
		}

		// TODO: Find a nice way to return a valid value
		return nullptr;
	}

}
