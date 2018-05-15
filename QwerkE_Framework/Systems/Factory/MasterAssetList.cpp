#include "../../Systems/ResourceManager.h"
#include "../../Systems/Graphics_Header.h"
#include "../../Systems/Graphics/OpenGLHelpers.h"
#include "../../Systems/Graphics/MaterialData.h"
#include "../../Systems/Graphics/ShaderProgram/ShaderFactory.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileLoader/FileLoader.h"
#include "../../Math_Includes.h"
#include "../../Libraries/glew/GL/glew.h"

#ifdef QwerkE_Framework
#define AssetDir "../QwerkE_Common/Resources/"
#else
#define AssetDir "../QwerkE_FrameWork/QwerkE_Common/Resources/" // TEMP: Engine is 1 directory up
#endif // QwerkE_Engine

// TODO: Look at resource creation again. Should Resource Manager create assets or just store them?
// TODO: Load all files in folder. This avoids hard coded assets names and allows easy adding/removal of assets even at runtime.
// Objects may need to switch to assets ids. ids would act as unique identifiers in the asset list and would prevent crashing.
void ResourceManager::Init()
{
}

// Instantiation Functions
// TODO: Handle errors and deleting assets before returning nullptr
Mesh* ResourceManager::InstantiateMesh(const char* meshName)
{
#define MeshPath(a) StringAppend(AssetDir, "Models/", a) // Folder or shaders

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
        mesh = t_MeshFactory.ImportOBJMesh(MeshPath("Teapot.obj"), vec3(0.5f,0.5f,0.5f), vec2(1,1), false);
    }
	else
	{
        ConsolePrint("\nInstantiateMesh(): Mesh not found!\n");
		return nullptr;
	}
	m_Meshes[meshName] = mesh; // Add to active list
	mesh->SetName(meshName);
	return mesh;
}

ShaderProgram* ResourceManager::InstantiateShader(const char* shaderName)
{
#define ShaderPath(a) StringAppend(AssetDir, "Shaders/", a) // Folder or shaders

	// Read directory for file?
	ShaderProgram* shader = new ShaderProgram();
	// 2D
	if (shaderName == "Basic2DTex") // Asset name
	{
		shader->Init(ShaderPath("Basic2DTex.vert"), ShaderPath("Basic2DTex.frag"), NULL); // Asset directories
	}
	else if (shaderName == "2DMenu")
	{
		shader->Init(ShaderPath("2DMenu.vert"), ShaderPath("2DMenu.frag"), NULL);
	}
	else if (shaderName == "Basic2D")
	{
		// shader->Init(eShader_Basic2D);
		shader->Init(ShaderPath("Basic2D.vert"), ShaderPath("Basic2D.frag"), NULL);
	}
	else if (shaderName == "2DMenuText")
	{
		shader->Init(ShaderPath("2DMenuText.vert"), ShaderPath("2DMenuText.frag"), NULL);
	}
	else if (shaderName == "Basic2DTransform")
	{
		shader->Init(ShaderPath("Basic2DTransform.vert"), ShaderPath("Basic2DTransform.frag"), NULL);
	}
	else if (shaderName == "Sprite2D")
	{
		shader->Init(ShaderPath("Sprite2D.vert"), ShaderPath("Sprite2D.frag"), NULL);
	}
	// 3D
	else if (shaderName == "Basic3D")
	{
		ShaderFactory temp;
		shader = temp.CreateShader(eShader_Basic3D);
	}
	else if (shaderName == "LitMaterial")
	{
		shader->Init(ShaderPath("LitMaterial.vert"), ShaderPath("LitMaterial.frag"), NULL);
	}
	else if (shaderName == "vec3Material")
	{
		shader->Init(ShaderPath("vec3Material.vert"), ShaderPath("vec3Material.frag"), NULL);
	}
	else if (shaderName == "BasicLighting")
	{
		shader->Init(ShaderPath("vec3Material.vert"), ShaderPath("vec3Material.frag"), NULL);
	}
	else if (shaderName == "Box2D_Debug")
	{
		// InstantiateShader("Data/Shaders/Box2DDebug.vert", "Data/Shaders/Box2DDebug.frag", NULL, "Box2D_Debug");
	}
	else if (shaderName == "text")
	{
		shader->Init(ShaderPath("text.vert"), ShaderPath("text.frag"), NULL);
	}
    else if (shaderName == "TestShader")
    {
        shader->Init(ShaderPath("TestShader.vert"), ShaderPath("TestShader.frag"), NULL);
    }
	else
	{
        ConsolePrint("\nInstantiateShader(): Shader not found!\n");
		return nullptr;
	}

	m_Shaders[shaderName] = shader;
	return shader;
}

GLuint ResourceManager::InstantiateTexture(const char* textureName)
{
#define TexturePath(a) StringAppend(AssetDir, "Textures/", a)

	GLuint textureHandle = -1;
	textureHandle = Load2DTexture(TexturePath(textureName));

	if (textureHandle != 0)
		m_Textures[textureName] = textureHandle;
	else
	{
		ConsolePrint("\nInstantiateTexture(): Texture not found!\n");
		textureHandle = GetTexture("null_texture.png"); // fail nicely
	}

	return textureHandle;
}

MaterialData* ResourceManager::InstantiateMaterial(const char* matName)
{
	// TODO: Use MaterialDir
#define MaterialPath(a) StringAppend(AssetDir, "Models/", a) // Folder or shaders
	MaterialData* material = nullptr;
	if (matName == "container.mat") // Asset name
	{
		material = new MaterialData(GetTexture("container.png"), GetTexture("container.png"), GetTexture("container_specular.png")); // Asset names
	}
	else if (matName == "nanosuit_arms.mat") // TODO: Re-use textures
	{
		GLuint dif, spec, norm;

		dif = Load2DTexture(MaterialPath("nanosuit/arm_dif.png"));
		spec = Load2DTexture(MaterialPath("nanosuit/arm_showroom_spec.png"));
		// norm = Load2DTexture(MaterialDir("nanosuit/arm_showroom_ddn.png")); // currently unused

		material = new MaterialData(dif, dif, spec);
	}
	else if (matName == "nanosuit_legs.mat") // TODO: Re-use textures
	{
		GLuint dif, spec, norm;

		dif = Load2DTexture(MaterialPath("nanosuit/leg_dif.png"));
		spec = Load2DTexture(MaterialPath("nanosuit/leg_showroom_spec.png"));
		// norm = Load2DTexture(MaterialDir("nanosuit/leg_showroom_ddn.png")); // currently unused

		material = new MaterialData(dif, dif, spec);
	}
	else if (matName == "nanosuit_body.mat") // TODO: Re-use textures
	{
		GLuint dif, spec, norm;

		dif = Load2DTexture(MaterialPath("nanosuit/body_dif.png"));
		spec = Load2DTexture(MaterialPath("nanosuit/body_showroom_spec.png"));
		// norm = Load2DTexture(MaterialDir("nanosuit/body_showroom_ddn.png")); // currently unused

		material = new MaterialData(dif, dif, spec);
	}
	else if (matName == "nanosuit_glass.mat") // TODO: Re-use textures
	{
		GLuint dif, spec, norm;

		dif = Load2DTexture(MaterialPath("nanosuit/glass_dif.png"));
		// spec = Load2DTexture(MaterialDir("nanosuit/?????.png"));
		// norm = Load2DTexture(MaterialDir("nanosuit/glass_ddn.png")); // currently unused

		material = new MaterialData(dif, dif, dif);
	}
	else if (matName == "nanosuit_helmet.mat") // TODO: Re-use textures
	{
		GLuint dif, spec, norm;

		dif = Load2DTexture(MaterialPath("nanosuit/helmet_diff.png"));
		spec = Load2DTexture(MaterialPath("nanosuit/helmet_showroom_spec.png"));
		// norm = Load2DTexture(MaterialDir("nanosuit/helmet_showroom_ddn.png")); // currently unused

		material = new MaterialData(dif, dif, spec);
	}
	else if (matName == "nanosuit_hand.mat") // TODO: Re-use textures
	{
		GLuint dif, spec, norm;

		dif = Load2DTexture(MaterialPath("nanosuit/hand_dif.png"));
		spec = Load2DTexture(MaterialPath("nanosuit/hand_showroom_spec.png"));
		// norm = Load2DTexture(MaterialDir("nanosuit/hand_showroom_ddn.png")); // currently unused

		material = new MaterialData(dif, dif, spec);
	}
	else if (matName == "UV_Map.mat")
	{
		material = new MaterialData(GetTexture("UV_Map.png"), GetTexture("UV_Map.png"), GetTexture("UV_Map.png"));
	}
    else if (matName == "null_texture.mat")
    {
        material = new MaterialData(GetTexture("null_texture.png"), GetTexture("null_texture.png"), GetTexture("null_texture.png"));
    }
	else if (matName == "Test.qmat") // could just check for extension, then handle that
	{
		// TODO: Try to load a .qmat file
	}
	else
	{
        ConsolePrint("\nInstantiateMaterial(): Material not found!\n");
		return GetMaterial("null_texture.mat");
	}

	m_Materials[matName] = material;
	material->name = matName;
	return material;
}

Model* ResourceManager::InstantiateModel(const char* modelName)
{
#define ModelPath(a) StringAppend(AssetDir, "Models/", a) // Folder or shaders

	// MeshFactory meshFact; // out dated
	// if (modelName == "LightBulb") // Asset name
	// model = meshFact.ImportOBJModel("Resources/Models/Light_Bulb.obj"); // Asset directory

	Model* model = QwerkE::FileLoader::LoadModelFile(ModelPath(modelName));

	// null check
	if (model != nullptr)
	{
		m_Models[modelName] = model;
		model->SetName(modelName);
		return model;
	}
	else
	{
		ConsolePrint("\nInstantiateModel(): Model not found!\n");
		return nullptr;
	}
}

FT_Face ResourceManager::InstantiateFont(const char* fontName)
{
#define FontPath(a) StringAppend(AssetDir, "Fonts/", a) // Folder or shaders

	FT_Face font;
	FT_Library ft; // TODO: No need to reload ft library

	if (FT_Init_FreeType(&ft))
		ConsolePrint("ERROR::FREETYPE: Could not init FreeType Library");

	if (FT_New_Face(ft, FontPath(fontName), 0, &font))
	{
		ConsolePrint("ERROR::FREETYPE: Failed to load font");
		return NULL;
	}
	m_Fonts[fontName] = font;
	return font;
}