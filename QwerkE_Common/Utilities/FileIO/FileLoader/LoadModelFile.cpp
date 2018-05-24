#include "FileLoader.h"
#include "../../../../QwerkE_Framework/Systems/ServiceLocator.h"
#include "../../../../QwerkE_Framework/Systems/ResourceManager/ResourceManager.h"
#include "../../../../QwerkE_Framework/Graphics/Mesh/Mesh.h"
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
		Mesh* LoadMeshInModelByName(const char* modelFilePath, const char* meshName)
		{
			if (false == ((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->MeshExists(meshName))
			{
				// TODO: remain assimp agnostic
				Assimp::Importer importer;
				const aiScene *scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);

				if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
				{
					std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
					return nullptr; // failure
				}
				Mesh* mesh = nullptr;
				QwerkE_assimp_loadMeshByName(scene->mRootNode, scene, mesh, modelFilePath, meshName);
				((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->AddMesh(meshName, mesh);
				return mesh;
			}
			else
			{
				return ((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetMesh(meshName);
			}
		}

		// TODO: API should only ask for fileName, then prepend directory
		bool LoadModelFileToMeshes(const char* path)
		{
			// check if a model with the same name already exists
			ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

			// TODO: Prevent the same model from being loaded

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
				return false; // failure
			}

			// NOTE: aiScene is an object hierarchy so it might almost require GameObject creation here.
			QwerkE_assimp_loadSceneNodeData(scene->mRootNode, scene, meshes, path, matNames);

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
				// TODO: Do something with the .mtl file loaded material names?
				// resMan->GetTexture(DispStrCombine(directory.c_str(), matNames[i].c_str()).c_str());
			}

			return true; // success
		}
	}
}