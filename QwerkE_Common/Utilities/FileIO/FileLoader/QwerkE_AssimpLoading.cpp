#include "QwerkE_AssimpLoading.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Model.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Mesh.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/VertexData.h"
#include "../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../../QwerkE_Framework/Systems/ResourceManager.h"

// https://learnopengl.com/Model-Loading/Model

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