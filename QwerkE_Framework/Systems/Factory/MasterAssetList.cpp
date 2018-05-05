#include "../../Systems/ResourceManager.h"
#include "../../Systems/Graphics_Header.h"
#include "../../Systems/Graphics/OpenGLHelpers.h"
#include "../../Systems/Graphics/MaterialData.h"
#include "../../Systems/Graphics/ShaderProgram/ShaderFactory.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../Math_Includes.h"
#include "../../Libraries/glew/GL/glew.h"

const char* Test(const char* a, const char* b)
{
	int size = 0;
	size = strlen(a) + strlen(b);

	char* newString = new char[size]; // RAM:
	strcpy_s(newString, strlen(a) + 1, a);
	strcat_s(newString, size + 1, b);

	return newString;
}

// TODO: Load all files in folder. This avoids hard coded assets names and allows easy adding/removal of assets even at runtime.
// Objects may need to switch to assets ids. ids would act as unique identifiers in the asset list and would prevent crashing.
void ResourceManager::Init()
{
}

// Instantiation Functions
// TODO: Handle errors and deleting assets before returning nullptr
Mesh* ResourceManager::InstantiateMesh(const char* meshName)
{
	// TODO: Use MeshDir
#define MeshDir(a) Test("../Shared_Generic/Resources/Models/", a) // Folder or shaders

	MeshFactory t_MeshFactory;
	Mesh* mesh = nullptr;
    // TODO: Dereference *s?
	if (meshName == "Box") // Asset name
	{
		mesh = new Mesh();
		t_MeshFactory.GenerateBox(mesh, vec2(1, 1));
	}
	else if (meshName == "Circle")
	{
		mesh = MeshFactory::CreateCircle(1.0f, 20, vec2(1,1));
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
		mesh = t_MeshFactory.TutorialCube(vec3(1,1,1));
	}
    else if (meshName == "Teapot")
    {
        mesh = t_MeshFactory.ImportOBJMesh(MeshDir("Teapot.obj"), vec3(0.5f,0.5f,0.5f), vec2(1,1), false);
    }
	else
	{
        ConsolePrint("\nInstantiateMesh(): Mesh not found!\n");
		return nullptr;
	}
	m_HotMeshes[meshName] = mesh; // Add to active list
	mesh->SetName(meshName);
	return mesh;
}

ShaderProgram* ResourceManager::InstantiateShader(const char* shaderName)
{
#define ShaderDir(a) Test("../Shared_Generic/Resources/Shaders/", a) // Folder or shaders

	// Read directory for file?
	ShaderProgram* shader = new ShaderProgram();
	// 2D
	if (shaderName == "Basic2DTex") // Asset name
	{
		shader->Init(ShaderDir("Basic2DTex.vert"), ShaderDir("Basic2DTex.frag"), NULL); // Asset directories
	}
	else if (shaderName == "2DMenu")
	{
		shader->Init(ShaderDir("2DMenu.vert"), ShaderDir("2DMenu.frag"), NULL);
	}
	else if (shaderName == "Basic2D")
	{
		// shader->Init(eShader_Basic2D);
		shader->Init(ShaderDir("Basic2D.vert"), ShaderDir("Basic2D.frag"), NULL);
	}
	else if (shaderName == "2DMenuText")
	{
		shader->Init(ShaderDir("2DMenuText.vert"), ShaderDir("2DMenuText.frag"), NULL);
	}
	else if (shaderName == "Basic2DTransform")
	{
		shader->Init(ShaderDir("Basic2DTransform.vert"), ShaderDir("Basic2DTransform.frag"), NULL);
	}
	else if (shaderName == "Sprite2D")
	{
		shader->Init(ShaderDir("Sprite2D.vert"), ShaderDir("Sprite2D.frag"), NULL);
	}
	// 3D
	else if (shaderName == "Basic3D")
	{
		ShaderFactory temp;
		shader = temp.CreateShader(eShader_Basic3D);
	}
	else if (shaderName == "LitMaterial")
	{
		shader->Init(ShaderDir("LitMaterial.vert"), ShaderDir("LitMaterial.frag"), NULL);
	}
	else if (shaderName == "vec3Material")
	{
		shader->Init(ShaderDir("vec3Material.vert"), ShaderDir("vec3Material.frag"), NULL);
	}
	else if (shaderName == "BasicLighting")
	{
		shader->Init(ShaderDir("vec3Material.vert"), ShaderDir("vec3Material.frag"), NULL);
	}
	else if (shaderName == "Box2D_Debug")
	{
		// InstantiateShader("Data/Shaders/Box2DDebug.vert", "Data/Shaders/Box2DDebug.frag", NULL, "Box2D_Debug");
	}
	else if (shaderName == "text")
	{
		shader->Init(ShaderDir("text.vert"), ShaderDir("text.frag"), NULL);
	}
    else if (shaderName == "TestShader")
    {
        shader->Init(ShaderDir("TestShader.vert"), ShaderDir("TestShader.frag"), NULL);
    }
	else
	{
        ConsolePrint("\nInstantiateShader(): Shader not found!\n");
		return nullptr;
	}

	m_HotShaders[shaderName] = shader;
	return shader;
}
// TODO: Look at resource creation again. Should Resource Manager create assets or just store them?
GLuint ResourceManager::InstantiateTexture(const char* textureName)
{
    // TODO: OpenGLHelpers.cpp is a different directory.
#define TextureDir(a) Test("../Shared_Generic/Resources/Textures/", a) // Folder or shaders
	GLuint textureHandle = -1;
	if (textureName == "PeriodicHeal") // Asset name
	{
		textureHandle = Load2DTexture(TextureDir("PeriodicHeal.png")); // Asset directory
	}
	else if (textureName == "FlashHeal")
	{
		textureHandle = Load2DTexture(TextureDir("FlashHeal.png"), true);
	}
	else if (textureName == "ExampleBackground")
	{
		textureHandle = Load2DTexture(TextureDir("ExampleBackground.png"));
	}
	else if (textureName == "container")
	{
		textureHandle = Load2DTexture(TextureDir("container.png"));
	}
	else if (textureName == "container_specular")
	{
		textureHandle = Load2DTexture(TextureDir("container_specular.png"));
	}
	else if (textureName == "Blue_Engine_UI1")
	{
		textureHandle = Load2DTexture(TextureDir("Blue_Engine_UI1.png"));
	}
	else if (textureName == "Blue_Engine_UI2")
	{
		textureHandle = Load2DTexture(TextureDir("Blue_Engine_UI2.png"));
	}
	else if (textureName == "UV_Map")
	{
		textureHandle = Load2DTexture(TextureDir("UV_Map.png"));
	}
	else if (textureName == "Menu_Border1")
	{
		textureHandle = Load2DTexture(TextureDir("Menu_Border1.png"));
	}
	else if (textureName == "arm_dif")
	{
		textureHandle = Load2DTexture(TextureDir("arm_dif.png"));
	}
	else if (textureName == "arm_spec")
	{
		textureHandle = Load2DTexture(TextureDir("arm_spec.png"));
	}
	else if (textureName == "white_canvas")
	{
		textureHandle = Load2DTexture(TextureDir("white_canvas.png"));
	}
	else if (textureName == "null")
	{
		textureHandle = Load2DTexture(TextureDir("null_texture.png"));
	}
	// Cube map
	else if (false)
	{

	}
	else
	{
		textureHandle = GetTexture("null"); // failure
        ConsolePrint("\nInstantiateTexture(): Texture not found!\n");
	}

	m_HotTextures[textureName] = textureHandle;
	return textureHandle;
}

MaterialData* ResourceManager::InstantiateMaterial(const char* matName)
{
	// TODO: Use MaterialDir
#define MaterialDir(a) Test("../Shared_Generic/Resources/Textures/", a) // Folder or shaders
	MaterialData* material = nullptr;
	if (matName == "container") // Asset name
	{
		material = new MaterialData(GetTexture("container"), GetTexture("container"), GetTexture("container_specular")); // Asset names
	}
	else if (matName == "nanosuit_visor")
	{
		// material = new MaterialData(GetTexture("container"), GetTexture("container"), GetTexture("container_specular"));
	}
	else if (matName == "nanosuit_legs")
	{
		// material = new MaterialData(GetTexture("container"), GetTexture("container"), GetTexture("container_specular"));
	}
	else if (matName == "UV_Map")
	{
		material = new MaterialData(GetTexture("UV_Map"), GetTexture("UV_Map"), GetTexture("white_canvas"));
	}
    else if (matName == "null")
    {
        material = new MaterialData(GetTexture("null"), GetTexture("null"), GetTexture("null"));
    }
	else
	{
        ConsolePrint("\nInstantiateMaterial(): Material not found!\n");
		return GetMaterial("null");
	}

	m_HotMaterials[matName] = material;
	material->name = matName;
	return material;
}

Model* ResourceManager::InstantiateModel(const char* modelName)
{
	// TODO: Use ModelDir
#define ModelDir(a) Test("../Shared_Generic/Resources/Textures/", a) // Folder or shaders

	MeshFactory meshFact;
	Model* model;
	if (modelName == "LightBulb") // Asset name
	{
		model = meshFact.ImportOBJModel("Resources/Models/Light_Bulb.obj"); // Asset directory
	}
	else if (modelName == "CubeModel")
	{
		model = meshFact.ImportOBJModel("Resources/Models/1M_CubeModel.obj", vec3(0.05f, 0.05f, 0.05f));
	}
	else if (modelName == "Pyramid")
	{
		model = meshFact.ImportOBJModel("Resources/Models/Pyramid.obj");
	}
	else if (modelName == "Nano_Suit")
	{
		model = meshFact.ImportOBJModel("Resources/Models/Crysis_Nanosuit/nanosuit.obj");
	}
	else if (modelName == "NullMesh")
	{
		model = meshFact.ImportOBJModel("Resources/Models/Teapot.obj");
	}
	else
	{
        ConsolePrint("\nInstantiateModel(): Model not found!\n");
		return nullptr;
	}
	// TODO: nullptr checks
	m_HotModels[modelName] = model;
	model->SetName(modelName);
	return model;
}
