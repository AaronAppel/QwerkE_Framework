#include "GraphicsHelpers.h"
#include "../../../Entities/Components/RenderComponent.h"
#include "../../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../../QwerkE_Common/Libraries/cJSON_Interface/cJSONInterface.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ServiceLocator.h"
#include "../Gfx_Classes/MaterialData.h"
#include "../Gfx_Classes/ShaderProgramData.h"

#include "../Shared_Engine/Engine_Defines.h"

void CheckAllGraphicsErrors()
{
	// TODO: Handle all sorts of graphics system errors?
}

#ifdef OpenGL
#include "OpenGL/OpenGLHelpers.h"
void CheckGraphicsErrors()
{
	GLCheckforErrors();
}

void CheckGraphicsErrors(char* file, int line)
{
	GLCheckforErrors(file, line);
}

void CheckGraphicsErrors(const char* file, int line)
{
	GLCheckforErrors(file, line);
}

// TODO: Return a valid handle and try to avoid a stack frame if not necessary
GLuint Load2DTexture(const char* filename, bool flipVertically)
{
	return GLLoad2DTexture(filename, flipVertically);
}

GLuint LoadCubeMapTexture(const char* filename)
{
	return GLLoadCubeMapTexture(filename);
}

GLuint CopyFBOToTexture(FrameBufferObject& fbo, int w, int h, int x, int y)
{
	// TODO: abstract from library specific implementation
	// Note: You can specify what region of the framebuffer to take which
	// means you can easily capture a specified square from the scene.

	// bind framebuffer
	fbo.Bind();
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, w, h, 0);

	// create return texture
	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);

	// copy data
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, w, h, 1);
	CheckGraphicsErrors(__FILE__, __LINE__);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // , , GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// return handle to newly created texture
	fbo.UnBind();
	glBindTexture(GL_TEXTURE_2D, 0); // unbind
	return result;
}

#elif defined(Vulcan)
#include "OpenGL/VulcanHelpers.h"

#elif defined(Direct3D)
#include "OpenGL/Direct3DHelpers.h"
#else
#pragma error "Define graphics library!"

#endif // OpenGL

void SaveObjectSchematic(RenderComponent* rComp) // save to file
{
	const char* filePath = StringAppend(AssetDir, "BluePrints_Prefabs_Schematic/ObjectRecipe1", object_schematic_ext);

	// if file does not exist, create one,otherwise overwrite data
	if (!FileExists(filePath))
	{
		CreateEmptycJSONFile(filePath);
	}
	else
	{
		EmptycJSONFile(filePath);
	}

	cJSON* root = OpencJSONStream(filePath);

	AddItemToRoot(root, CreateString("Name", "ObjectRecipe1.orec"));

	cJSON* renderables = CreateArray("Renderables");
	cJSON* r1 = CreateArray("R1");

	AddItemToArray(r1, CreateString("Shader", "null_shader"));
	AddItemToArray(r1, CreateString("Material", "null_material.mat"));
	AddItemToArray(r1, CreateString("Mesh", "null_model.obj"));

	AddItemToArray(renderables, r1);
	AddItemToRoot(root, renderables);

	PrintRootObjectToFile(filePath, root);
	ClosecJSONStream(root);
}

RenderComponent* LoadObjectSchematic(const char* schematicPath) // load from file
{
	RenderComponent* rComp = new RenderComponent();

	cJSON* root = OpencJSONStream(schematicPath);

	if (root)
	{
		ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

		cJSON* name = GetItemFromRootByKey(root, "Name");
		// rComp.name = name->valuestring;
		cJSON* renderables = GetItemFromRootByKey(root, "Renderables");
		int size = GetArraySize(renderables);

		rComp->AppendEmptyRenderables(size);

		for (int i = 0; i < size; i++) // per renderable
		{
			cJSON* currRenderable = GetItemFromArrayByIndex(renderables, i);

			rComp->SetShaderAtIndex(i, resMan->GetShader(GetItemFromArrayByKey(currRenderable, "Shader")->valuestring));
			rComp->SetMaterialAtIndex(i, resMan->GetMaterial(GetItemFromArrayByKey(currRenderable, "Material")->valuestring));
			rComp->SetMeshAtIndex(i, resMan->GetMesh(GetItemFromArrayByKey(currRenderable, "Mesh")->valuestring));
		}
	}

	ClosecJSONStream(root);

	return rComp;
}

void SaveMaterialSchematic(MaterialData* mat)
{
	const char* filePath = TextureFolderPath(StringAppend(mat->s_Name.c_str(), material_schematic_ext));

	// if file does not exist, create one,otherwise overwrite data
	if (!FileExists(filePath))
	{
		CreateEmptycJSONFile(filePath);
	}
	else
	{
		EmptycJSONFile(filePath);
	}

	// save data
	// Note: I am not saving texture handles because they are not reliable.
	// TODO: Should I use struct member names like "s_Name"?
	cJSON* root = OpencJSONStream(filePath);

	AddItemToRoot(root, CreateString("Name", "MaterialSchematic1.msch"));

	cJSON* OtherData = CreateArray("OtherData");
	AddItemToArray(OtherData, CreateNumber("Shine", mat->s_Shine));
	// TODO: LightData AddItemToArray(OtherData, CreateNumber("LightData", mat->s_Shine)); {r,g,b,a}

	cJSON* Names = CreateArray("TextureNames");
	AddItemToArray(Names, CreateString("AmbientName", mat->s_AmbientName.c_str()));
	AddItemToArray(Names, CreateString("DiffuseName", mat->s_DiffuseName.c_str()));
	AddItemToArray(Names, CreateString("SpecularName", mat->s_SpecularName.c_str()));
	AddItemToArray(Names, CreateString("EmissiveName", mat->s_EmissiveName.c_str()));
	AddItemToArray(Names, CreateString("HeightName", mat->s_HeightName.c_str()));
	AddItemToArray(Names, CreateString("NormalName", mat->s_NormalsName.c_str()));
	AddItemToArray(Names, CreateString("ShininessName", mat->s_ShininessName.c_str()));
	AddItemToArray(Names, CreateString("OpacityName", mat->s_OpacityName.c_str()));
	AddItemToArray(Names, CreateString("DisplacementName", mat->s_DisplacementName.c_str()));
	AddItemToArray(Names, CreateString("LightMapName", mat->s_LightMapName.c_str()));
	AddItemToArray(Names, CreateString("ReflectionName", mat->s_ReflectionName.c_str()));

	AddItemToRoot(root, OtherData);
	AddItemToRoot(root, Names);

	PrintRootObjectToFile(filePath, root);
	ClosecJSONStream(root);
}

MaterialData* LoadMaterialSchematic(const char* schematicPath)
{
	MaterialData* mat = new MaterialData();

	cJSON* root = OpencJSONStream(schematicPath);

	if (root)
	{
		// load mat data from file
		mat->s_Name = GetItemFromRootByKey(root, "Name")->valuestring;

		// load "other" data
		cJSON* otherData = GetItemFromRootByKey(root, "OtherData");
		mat->s_Shine = GetItemFromArrayByKey(otherData, "Shine")->valuedouble;
		// TODO: mat->s_LightValue = GetItemFromArrayByKey(otherData, "LightData")->valuedouble;

		// set texture names
		cJSON* textureNames = GetItemFromRootByKey(root, "TextureNames");
		mat->s_AmbientName = GetItemFromArrayByKey(textureNames, "AmbientName")->valuestring;
		mat->s_DiffuseName = GetItemFromArrayByKey(textureNames, "DiffuseName")->valuestring;
		mat->s_SpecularName = GetItemFromArrayByKey(textureNames, "SpecularName")->valuestring;
		mat->s_EmissiveName = GetItemFromArrayByKey(textureNames, "EmissiveName")->valuestring;
		mat->s_HeightName = GetItemFromArrayByKey(textureNames, "HeightName")->valuestring;
		mat->s_NormalsName = GetItemFromArrayByKey(textureNames, "NormalName")->valuestring;
		mat->s_ShininessName = GetItemFromArrayByKey(textureNames, "ShininessName")->valuestring;
		mat->s_OpacityName = GetItemFromArrayByKey(textureNames, "OpacityName")->valuestring;
		mat->s_DisplacementName = GetItemFromArrayByKey(textureNames, "DisplacementName")->valuestring;
		mat->s_LightMapName = GetItemFromArrayByKey(textureNames, "LightMapName")->valuestring;
		mat->s_ReflectionName = GetItemFromArrayByKey(textureNames, "ReflectionName")->valuestring;
	}

	ClosecJSONStream(root);

	// load texture handles from ResourceManager
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	// TODO: Stop trying to load "Empty" files
	mat->s_AmbientHandle = resMan->GetTexture(mat->s_AmbientName.c_str());
	mat->s_DiffuseHandle = resMan->GetTexture(mat->s_DiffuseName.c_str());
	mat->s_SpecularHandle = resMan->GetTexture(mat->s_SpecularName.c_str());
	mat->s_EmissiveHandle = resMan->GetTexture(mat->s_EmissiveName.c_str());
	mat->s_HeightHandle = resMan->GetTexture(mat->s_HeightName.c_str());
	mat->s_NormalsHandle = resMan->GetTexture(mat->s_NormalsName.c_str());
	mat->s_ShininessHandle = resMan->GetTexture(mat->s_ShininessName.c_str());
	mat->s_OpacityHandle = resMan->GetTexture(mat->s_OpacityName.c_str());
	mat->s_DisplacementHandle = resMan->GetTexture(mat->s_DisplacementName.c_str());
	mat->s_LightMapHandle = resMan->GetTexture(mat->s_LightMapName.c_str());
	mat->s_ReflectionHandle = resMan->GetTexture(mat->s_ReflectionName.c_str());

	return mat;
}

void SaveShaderSchematic(ShaderProgramData* shader)
{
	const char* filePath = StringAppend(AssetDir, "Shaders/LitMaterial", shader_schematic_ext);

	// if file does not exist, create one,otherwise overwrite data
	if (!FileExists(filePath))
	{
		CreateEmptycJSONFile(filePath);
	}
	else
	{
		EmptycJSONFile(filePath);
	}

	cJSON* root = OpencJSONStream(filePath);

	if (root)
	{
		AddItemToRoot(root, CreateString("Name", shader->s_Name.c_str()));

		AddItemToRoot(root, CreateString("vert", shader->s_vertName.c_str()));
		AddItemToRoot(root, CreateString("frag", shader->s_fragName.c_str()));
		AddItemToRoot(root, CreateString("geo", shader->s_geoName.c_str()));

		PrintRootObjectToFile(filePath, root);
	}
	ClosecJSONStream(root);
}

ShaderProgramData* LoadShaderSchematic(const char* schematicPath)
{
	ShaderProgramData* shader = new ShaderProgramData();
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	cJSON* root = OpencJSONStream(schematicPath);

	if (root)
	{
		shader->s_Name = GetItemFromRootByKey(root, "Name")->valuestring;

		shader->s_vertName = GetItemFromRootByKey(root, "vert")->valuestring;
		shader->s_fragName = GetItemFromRootByKey(root, "frag")->valuestring;
		shader->s_geoName = GetItemFromRootByKey(root, "geo")->valuestring;
	}

	// shader->s_vertHandle = resMan->GetShader(shader->s_vertName.c_str());

	ClosecJSONStream(root);

	return shader;
}

// Shader variable prefixes
char* Helper_GetAttributePrefix()
{
	return (char*)"a_"; // for attributes or i_ for inputs
}

char* Helper_GetUniformPrefix()
{
	return (char*)"u_"; // uniforms
}

char* Helper_GetTransferPrefix()
{
	return (char*)"t_"; // for transfers or v_ for varyings
}