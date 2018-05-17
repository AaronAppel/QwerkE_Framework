#include "QwerkE_AssimpLoading.h"
#include "../../../../QwerkE_Framework/Systems/Graphics/Mesh/Mesh.h"
#include "../../../../QwerkE_Framework/Systems/Graphics/Mesh/VertexData.h"
#include "../../../../QwerkE_Framework/Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../../QwerkE_Framework/Systems/ResourceManager.h"
#include "../../../../QwerkE_Framework/Systems/Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../StringHelpers.h"

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
	std::vector<VertexData> vertices;
	VertexData vertex; // create outside? not a major improvement but still...
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertex.position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			vertex.UV = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		vertex.normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vertex.color = vec4(1, 1, 1, 1);

		vertices.push_back(vertex);
	}
	// process indices
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	Mesh* rMesh = nullptr;

	// TODO: More error checking + handling
	if (vertices.size() > 0)
	{
		// init mesh and return it
		rMesh = new Mesh();
		rMesh->BufferMeshData(vertices.size(), vertices.data(), indices.size(), indices.data());
		rMesh->SetName(mesh->mName.C_Str());
	}
	else
		rMesh = ((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMesh("null_mesh");

	return rMesh;
}

void QwerkE_assimp_loadMaterialTextures(aiMaterial *mat, std::string directory, std::vector<std::string>& matNames)
{
	// process material
	//// std::vector<Texture> textures; // TODO: handle materials and textures
	//if (mesh->mMaterialIndex >= 0)
	//{
	//	std::vector<Texture> textures;
	//	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	//	std::vector<Texture> diffuseMaps = QwerkE_assimp_loadMaterialTextures(material,
	//		aiTextureType_DIFFUSE, "texture_diffuse", textures);
	//	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//	std::vector<Texture> specularMaps = QwerkE_assimp_loadMaterialTextures(material,
	//		aiTextureType_SPECULAR, "texture_specular", textures);
	//	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	//}

	for (unsigned int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

		aiString name;
		mat->Get(AI_MATKEY_NAME, name);

		// check for unique material
		if (resMan->MaterialExists(name.C_Str()) == false)
		{
			MaterialData* data = new MaterialData();
			data->name = name.C_Str();

			// iterate through all known texture types, then load the textures
			// into the ResourceManager and assign handles to the return material.
			// mat->GetTextureCount(); // optimization
			aiString str;
			int num = aiTextureType_UNKNOWN - 1;
			for (int i = aiTextureType_NONE + 1; i < num; i++)
			{
				GLuint handle = 0;

				mat->GetTexture((aiTextureType)i, 0, &str);
				if (resMan->TextureExists(str.C_Str()) == false)
				{
					handle = Load2DTexture(StringAppend(directory.c_str(), str.C_Str()));
					resMan->AddTexture(str.C_Str(), handle);
				}
				else
					handle = resMan->GetTexture(str.C_Str());

				switch (i)
				{
				case aiTextureType_DIFFUSE:
					data->diffuseHandle = handle;
					data->diffuseName = str.C_Str();
					break;
				case aiTextureType_SPECULAR:
					data->specularHandle = handle;
					data->specularName = str.C_Str();
					break;
				case aiTextureType_AMBIENT:
					break;
				case aiTextureType_EMISSIVE:
					break;
				case aiTextureType_HEIGHT:
					break;
				case aiTextureType_NORMALS:
					break;
				case aiTextureType_SHININESS:
					break;
				case aiTextureType_OPACITY:
					break;
				case aiTextureType_DISPLACEMENT:
					break;
				case aiTextureType_LIGHTMAP:
					break;
				case aiTextureType_REFLECTION:
					break;
				}
			}

			resMan->AddMaterial(data->name.c_str(), data); // add initialized material
		}

		matNames.push_back(name.C_Str()); // get name for mat loading later
	}
}
