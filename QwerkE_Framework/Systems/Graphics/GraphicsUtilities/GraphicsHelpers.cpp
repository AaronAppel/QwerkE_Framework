#include "GraphicsHelpers.h"
#include "../../../Entities/Components/RenderComponent.h"
#include "../../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../../QwerkE_Common/Libraries/cJSON_Interface/cJSONInterface.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ServiceLocator.h"
#include "../Gfx_Classes/MaterialData.h"

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

void SaveObjectRecipe(RenderComponent* rComp) // save to file
{
	const char* filePath = StringAppend(AssetDir, "Recipes/ObjectRecipe1", ".orec");

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

RenderComponent* LoadObjectRecipe(const char* recipePath) // load from file
{
	RenderComponent* rComp = new RenderComponent();

	cJSON* root = OpencJSONStream(recipePath);

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

			rComp->SetShaderAtIndex(0, resMan->GetShader(GetItemFromArrayByKey(currRenderable, "Shader")->valuestring));
			rComp->SetMaterialAtIndex(0, resMan->GetMaterial(GetItemFromArrayByKey(currRenderable, "Material")->valuestring));
			rComp->SetMeshAtIndex(0, resMan->GetMesh(GetItemFromArrayByKey(currRenderable, "Mesh")->valuestring));
		}
	}

	ClosecJSONStream(root);

	return rComp;
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