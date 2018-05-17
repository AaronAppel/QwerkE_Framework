#include "FileLoader.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Model.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Mesh.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/VertexData.h"
#include "../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../../QwerkE_Framework/Systems/ResourceManager.h"

#include <iostream>
#include <vector>
#include <string>

// https://learnopengl.com/Model-Loading/Model

struct Texture
{
	std::string name;
	// std::string directory;
	GLuint handle;
};

#ifdef AI_CONFIG_H_INC // assimp
#include "../../Libraries/assimp/Importer.hpp"
#include "../../Libraries/assimp/scene.h"
#include "../../Libraries/assimp/postprocess.h"
#include "../../Libraries/assimp/config.h"

std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, std::vector<Texture>& textures)
{
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.name = str.C_Str();
		// texture.handle = ;
		// texture.type = typeName;
		// texture.directory = str.C_Str();
		textures.push_back(texture);
	}
	return textures;
}
Mesh* processMesh(aiMesh *mesh, const aiScene *scene)
{
	Mesh* rMesh = new Mesh();

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

	// process material
	// std::vector<Texture> textures; // TODO: handle materials and textures
	if (mesh->mMaterialIndex >= 0)
	{
		std::vector<Texture> textures;
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
		aiTextureType_DIFFUSE, "texture_diffuse", textures);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
		aiTextureType_SPECULAR, "texture_specular", textures);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	rMesh->BufferMeshData(vertices.size(), vertices.data(), indices.size(), indices.data());
	rMesh->SetName(mesh->mName.C_Str());
	return rMesh; // Mesh(vertices, indices, textures);
}
void processNode(aiNode *node, const aiScene *scene, std::vector<Mesh*>& meshes)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, meshes);
	}
}
#endif AI_CONFIG_H_INC

namespace QwerkE
{
	namespace FileLoader
	{
		Model* LoadModelFile(const char* path)
		{
#ifdef AI_CONFIG_H_INC // assimp
			Assimp::Importer importer;
		    /*
			aiProcess_GenNormals: actually creates normals for each vertex if the model didn't contain normal vectors.
			aiProcess_SplitLargeMeshes : splits large meshes into smaller sub - meshes which is useful if your rendering has a maximum number of vertices allowed and can only process smaller meshes.
			aiProcess_OptimizeMeshes : actually does the reverse by trying to join several meshes into one larger mesh, reducing drawing calls for optimization.
			*/
			const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
				return nullptr;
			}
			// directory = path.substr(0, path.find_last_of('/'));

			Model* model = new Model();
			std::vector<Mesh*> meshes;
			processNode(scene->mRootNode, scene, meshes);

			model->Init(meshes);
			model->SetName(scene->mRootNode->mName.C_Str());

			// TEMP: Set mat data
			// MaterialData* mat = ((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("nanosuit_legs.mat");
			for (size_t i = 0; i < model->m_Meshes.size(); i++)
			{
				switch (i)
				{
				case 0:
					model->m_Materials.push_back(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("nanosuit_glass.mat"));
					break;
				case 1:
					model->m_Materials.push_back(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("nanosuit_legs.mat"));
					break;
				case 2:
					model->m_Materials.push_back(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("nanosuit_hand.mat"));
					break;
				case 3:
					model->m_Materials.push_back(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("UV_Map.mat"));
					break;
				case 4:
					model->m_Materials.push_back(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("nanosuit_arms.mat"));
					break;
				case 5:
					model->m_Materials.push_back(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("nanosuit_helmet.mat"));
					break;
				case 6:
					model->m_Materials.push_back(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMaterial("nanosuit_body.mat"));
					break;
				default:
					break;
				}
				// model->m_Materials.push_back(mat);
			}

			return model;
#else
// separate model loading library
#pragma error "Define model loading library!"
#endif // AI_CONFIG_H_INC
		}
	}
}