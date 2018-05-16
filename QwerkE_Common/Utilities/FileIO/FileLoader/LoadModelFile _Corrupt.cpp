#include "FileLoader.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Model.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Mesh.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/VertexData.h"
#include "../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../../QwerkE_Framework/Systems/ResourceManager.h"
#include "../../StringHelpers.h"

#include <iostream>
#include <vector>
#include <string>

namespace QwerkE
{
	namespace FileLoader
	{
		Model* LoadModelFile(const char* path)
		{
			// check if a model with the same name already exists
			std::string fileName = path;
			fileName = fileName.substr(fileName.find_last_of('/') + 1, fileName.size()); // get name + ext
			if ((((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->ModelExists(fileName.c_str())))
				return (((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetModel(fileName.c_str())); // already loaded

			std::string dir = fileName.substr(0, fileName.find_last_of('/') + 1); // folder absolute path

			std::vector<Mesh*> meshes;
			std::vector<MaterialData*> materials;

#ifdef AI_CONFIG_H_INC // assimp

// #include "QwerkE_AssimpLoading.h"

#include "../../Libraries/assimp/Importer.hpp"
#include "../../Libraries/assimp/scene.h"
#include "../../Libraries/assimp/postprocess.h"
#include "../../Libraries/assimp/config.h"
#include "../../Libraries/assimp/material.h"

#define TextureDirOffset(a, b) StringAppend("../Models/", a, b)

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
			// NOTE: aiScene is an object hierarchy so it might almost require GameObject creation here.
			processNode(scene->mRootNode, scene, meshes, materials);

#else
// separate model loading library
#pragma error "Define model loading library!"
#endif // AI_CONFIG_H_INC

			Model* model = new Model();
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
		}
	}
}