#include "QwerkE_AssimpLoading.h"
#include "../../../../QwerkE_Framework/Graphics/Mesh/Mesh.h"
#include "../../../../QwerkE_Framework/Graphics/Mesh/VertexData.h"
#include "../../../../QwerkE_Framework/Graphics/MaterialData.h"
#include "../../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../../QwerkE_Framework/Systems/ResourceManager/ResourceManager.h"
#include "../../../../QwerkE_Framework/Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../StringHelpers.h"

// TODO: Support triangle and quad rendering? Set a macro to define the number of verts per face?

// private functions
Mesh* QwerkE_assimp_loadVertexData(aiMesh *mesh, const aiScene *scene);
void QwerkE_assimp_loadMaterialTextures(aiMaterial *mat, std::string directory, std::vector<std::string>& matNames);

void QwerkE_assimp_loadSceneNodeData(aiNode *node, const aiScene *scene, std::vector<Mesh*>& meshes, std::string directory, std::vector<std::string>& matNames)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// load VertexData
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(QwerkE_assimp_loadVertexData(mesh, scene));

		// load Textures + materials
		if (mesh->mMaterialIndex >= 0) // has material?
			QwerkE_assimp_loadMaterialTextures(scene->mMaterials[mesh->mMaterialIndex], directory, matNames);
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		QwerkE_assimp_loadSceneNodeData(node->mChildren[i], scene, meshes, directory, matNames);
	}
}

Mesh* QwerkE_assimp_loadVertexData(aiMesh *mesh, const aiScene *scene)
{
	// process vertex positions, normals and texture coordinates
	unsigned int totalVerts = mesh->mNumVertices;
	std::vector<VertexData> vertices(totalVerts); // TODO: Swap to array? // PERF: really good use of a 1 frame stack allocation
	VertexData vertex; // create outside? not a major improvement but still...
	for (unsigned int i = 0; i < totalVerts; i++)
	{
		// vertex positions
		// vertex.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			vertex.UV = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		// normals
		vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		// color
		// vertex.color = vec4(mesh->mColors[i]->r, mesh->mColors[i]->g, mesh->mColors[i]->b, mesh->mColors[i]->a);

		vertices[i] = vertex;
	}

	// process indices
	unsigned int totalFaces = mesh->mNumFaces;
	std::vector<unsigned int> indices(totalFaces * 3); // TODO: Swap to array? // PERF: really good use of a 1 frame stack allocation
	aiFace face;
	int counter = 0;
	for (unsigned int i = 0; i < totalFaces; i++)
	{
		face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices[counter++] = face.mIndices[j];
	}

	Mesh* rMesh = nullptr;

	// TODO: More error checking + handling
	if (totalVerts > 0)
	{
		// init mesh and return it
		rMesh = new Mesh();
		rMesh->BufferMeshData(totalVerts, &vertices[0], totalFaces * 3, &indices[0]);
		rMesh->SetName(mesh->mName.C_Str());
	}
	else
		rMesh = ((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMesh("null_mesh");

	return rMesh;
}

void QwerkE_assimp_loadMaterialTextures(aiMaterial *mat, std::string directory, std::vector<std::string>& matNames)
{
	// check if material is already loaded
	aiString name;
	mat->Get(AI_MATKEY_NAME, name);
	// TODO: Support "DefaultMaterial"
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
	if (resMan->MaterialExists(name.C_Str()))
	{
		// material exists already
	}
	else
	{
		//create new material
		MaterialData* data = new MaterialData(); // TODO: delete if null
		data->s_Name = name.C_Str();
		// load each map/texture into a new material

		// iterate through all known texture types, then load the textures
		// into the ResourceManager and assign handles to the return material.
		// mat->GetTextureCount(); // optimization
		int num = aiTextureType_UNKNOWN - 1;
		for (int i = aiTextureType_NONE + 1; i < num; i++)
		{
			aiString str;
			GLuint handle = 0;

			mat->GetTexture((aiTextureType)i, 0, &str);

			if (strcmp(str.C_Str(), "") != 0)
			{
				// null name == no map/texture
				if (resMan->TextureExists(str.C_Str()) == false)
				{
					// no texture with that name is loaded
					handle = Load2DTexture(TextureFolderPath(str.C_Str())); // new texture
					if (handle != 0)
					{
						resMan->AddTexture(str.C_Str(), handle);
					}
					else
					{
						handle = resMan->GetTexture("null_texture.png");
						str.Set("No-Load"); // handle = resMan->GetTexture("glass_dif.png");
					}
				}
				else
					handle = resMan->GetTexture(str.C_Str()); // grab existing texture with same name
			}
			else
			{
				handle = resMan->GetTexture("null_texture.png");
				str.Set("Empty"); // handle = resMan->GetTexture("glass_dif.png");
			}
			//handle = 1;
			switch (i)
			{
			case aiTextureType_DIFFUSE:
				data->s_DiffuseHandle = handle;
				data->s_DiffuseName = str.C_Str();
				break;
			case aiTextureType_SPECULAR:
				data->s_SpecularHandle = handle;
				data->s_SpecularName = str.C_Str();
				break;
			case aiTextureType_AMBIENT:
				data->s_AmbientHandle = handle;
				data->s_AmbientName = str.C_Str();
				break;
			case aiTextureType_EMISSIVE:
				data->s_EmissiveHandle = handle;
				data->s_EmissiveName = str.C_Str();
				break;
			case aiTextureType_HEIGHT:
				data->s_HeightHandle = handle;
				data->s_HeightName = str.C_Str();
				break;
			case aiTextureType_NORMALS:
				data->s_NormalsHandle = handle;
				data->s_NormalsName = str.C_Str();
				break;
			case aiTextureType_SHININESS:
				data->s_ShininessHandle = handle;
				data->s_ShininessName = str.C_Str();
				break;
			case aiTextureType_OPACITY:
				data->s_OpacityHandle = handle;
				data->s_OpacityName = str.C_Str();
				break;
			case aiTextureType_DISPLACEMENT:
				data->s_DisplacementHandle = handle;
				data->s_DisplacementName = str.C_Str();
				break;
			case aiTextureType_LIGHTMAP:
				data->s_LightMapHandle = handle;
				data->s_LightMapName = str.C_Str();
				break;
			case aiTextureType_REFLECTION:
				data->s_ReflectionHandle = handle;
				data->s_ReflectionName = str.C_Str();
				break;
			}
		}

		// TODO: Support external material loading
		// resMan->AddMaterial(data->s_Name.c_str(), data); // add initialized material
	}

	matNames.push_back(name.C_Str()); // get name for mat loading later
}

void QwerkE_assimp_loadMeshByName(aiNode *node, const aiScene *scene, Mesh*& mesh, const char* meshName)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// load VertexData
		aiMesh *aimesh = scene->mMeshes[node->mMeshes[i]];
		if (strcmp(aimesh->mName.C_Str(), meshName) == 0)
		{
			mesh = QwerkE_assimp_loadVertexData(aimesh, scene);
			return;
		}
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		QwerkE_assimp_loadMeshByName(node->mChildren[i], scene, mesh, meshName);
	}
}
