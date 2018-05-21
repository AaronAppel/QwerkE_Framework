#include "FileLoader.h"
#include "../../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../../QwerkE_Framework/Systems/ResourceManager/ResourceManager.h"
#include "../../../../QwerkE_Framework/Systems/Graphics/Mesh/Mesh.h"
#include "../../StringHelpers.h"

#include <iostream>
#include <vector>
#include <string>

// define generic functions for model loading but
// use library specific prototype and body defines
#ifdef AI_CONFIG_H_INC // assimp
#include "QwerkE_AssimpLoading.h"
#define TextureDirOffset(a, b) StringAppend("../Models/", a, b)
#else
#pragma error "Define model loading library!"
#endif

namespace QwerkE
{
	namespace FileLoader
	{
		Model* LoadModelFileToMeshes(const char* path)
		{
			// check if a model with the same name already exists
			ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
			std::string fileName = path;
			fileName = fileName.substr(fileName.find_last_of('/') + 1, fileName.size()); // get name + ext

			// TODO: Prevent the same model from being loaded

			std::string directory = path;
			directory = directory.substr(0, directory.find_last_of('/') + 1); // folder absolute path

			// create temporary mesh and material buffers to load.
			// external library only cares about copying the data, not initializing it.
			std::vector<Mesh*> meshes;
			std::vector<std::string> matNames;

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

			// NOTE: aiScene is an object hierarchy so it might almost require GameObject creation here.
			QwerkE_assimp_loadSceneNodeData(scene->mRootNode, scene, meshes, directory, matNames);

			// TODO: De-allocate RAM created by assimp
#else
// separate model loading library
#pragma error "Define model loading library!"
#endif // AI_CONFIG_H_INC

			// take copied data from external library and init it for QwerkE systems use.
			for (size_t i = 0; i < meshes.size(); i++)
			{
				resMan->AddMesh(meshes[i]->GetName().c_str(), meshes[i]);
			}
			for (size_t i = 0; i < matNames.size(); i++)
			{
				resMan->GetTexture(DispStrCombine(directory.c_str(), matNames[i].c_str()).c_str());
			}
		}
	}
}