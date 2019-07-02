#include "FileSystem.h"
#include "LoadImageFile.h"
#include "../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../QwerkE_Common/Libraries/assimp/Importer.hpp"
#include "../../QwerkE_Common/Libraries/assimp/scene.h"
#include "../../QwerkE_Common/Libraries/assimp/postprocess.h"
#include "../../QwerkE_Common/Libraries/assimp/config.h"
#include "../../QwerkE_Common/Libraries/assimp/material.h"
#include "../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../ResourceManager/ResourceManager.h"
#include "QwerkE_AssimpLoading.h"
#include "../ServiceLocator.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../Audio/OpenAL_Helpers.h"

#define QwerkE_Image_Library_stb 1
#define QwerkE_Image_Library_lodepng 1
#define QwerkE_Image_Library_soil 0

#include <string>
#include <iostream>
#include <vector>

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

void FileSystem::LoadSoundFileData(const char* filePath, QSoundFile& soundFile)
{
	// this function is meant to abstract file type from external code

	soundFile.s_Name = GetFileNameWithExt(filePath);
	soundFile.s_Type = GetFileExtension(filePath);

	// read file data
	if (strcmp(soundFile.s_Type.c_str(), "wav") == 0)
	{
		soundFile.s_Data = (char*)LoadWaveFileData(filePath, soundFile.s_Size, soundFile.s_Channels, soundFile.s_Frequency, soundFile.s_BitsPerSample);
	}
	else if (strcmp(soundFile.s_Type.c_str(), "mp3") == 0)
	{
		// soundFile.s_Type = "mp3";
		// TODO: soundFile.s_Data = LoadMP3FileData(...);
	}

	if (soundFile.s_Data == nullptr)
		ConsolePrint("\nOpenAL error buffering sound data!\n");
}


// determine image type and use proper library
// lodepng, stb_image, SOIL, etc
unsigned char* FileSystem::LoadImageFileData(const char* path, unsigned int* imageWidth, unsigned int* imageHeight, GLenum& channels, bool flipVertically)
{
	unsigned char* returnBuffer = nullptr;

	// TODO: Determine which tool/library to use depending on image type and format
	// png, jpg, 8bit vs 32bit, etc

	std::string extention = GetFileExtension(path);

	if (strcmp(extention.c_str(), "jpg") == 0)
	{
		// returnBuffer = QwerkE_stb_image_loadImage(path, imageWidth, imageHeight, channels, flipVertically);
		OutputPrint("LoadImageFile(): .jpg image not loaded. No working jpg load function currently: %s\n", path);
	}
	else if (strcmp(extention.c_str(), "png") == 0)
	{
#if QwerkE_Image_Library_stb == 1 // stb
		// stb has shown to be faster than lodepng, however it is not reliable for loading all image formats.
		// use both for now... // TODO: Fix stb_image
		// returnBuffer = QwerkE_stb_image_loadImage(path, imageWidth, imageHeight, channels, flipVertically);
#endif
#if QwerkE_Image_Library_lodepng == 1 // lodepng
		// if (returnBuffer == nullptr || strcmp((const char*)returnBuffer, "") == 0)
		if (!returnBuffer)
			returnBuffer = QwerkE_lodepng_loadImage(path, imageWidth, imageHeight, channels, flipVertically);
#endif
#if QwerkE_Image_Library_soil == 1 // SOIL
		returnBuffer = QwerkE_soil_loadImage(path); // TODO:
#endif

#if !QwerkE_Image_Library_stb && !QwerkE_Image_Library_lodepng && !QwerkE_Image_Library_soil
#pragma error "Define image loading library!"
#endif
	}
	else
	{
		OutputPrint("LoadImageFile(): Image type unsupported for file: %s\n", path);
	}

	if (!returnBuffer)// (returnBuffer == nullptr || strcmp((const char*)returnBuffer, "") == 0)
	{
		OutputPrint("LoadImageFile(): Failed to load image: %s\n", path);
		return nullptr; // failed
	}

	OutputPrint("LoadImageFile(): Loaded: %s\n", path);
	return returnBuffer;
}

ALuint FileSystem::LoadSound(const char* soundPath)
{
	// this function is meant to abstract audio libraries from external code

    // TODO: Load sounds from libraries dynamically using preference.qpref. No #defines

	ALuint retValue = 0;

	// get sound data
	QSoundFile soundFile;
	LoadSoundFileData(soundPath, soundFile);

	// create sound file
#ifdef OpenAL
	retValue = OpenAL_LoadSound(soundFile);
#elif defined(XAudio)
	retValue = 0;
#else
#pragma error "Define audio library!"
#endif // AudioLibrary

	return retValue;
}

Mesh* FileSystem::LoadModelFileTo1Mesh(const char* modelFilePath)
{
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
	if (false == resMan->MeshExists(GetFileNameNoExt(modelFilePath).c_str()))
	{
		Mesh* mesh = nullptr;

#ifdef AI_CONFIG_H_INC // assimp
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            QwerkE::LogWarning(__FILE__, __LINE__, "ERROR::ASSIMP::%s", importer.GetErrorString());
			return nullptr; // failure
		}
		QwerkE_assimp_loadModelAs1Mesh(scene->mRootNode, scene, mesh, modelFilePath);
#else
		// separate model loading library
#pragma error "Define model loading library!"
#endif // AI_CONFIG_H_INC

		if (mesh)
		{
			resMan->AddMesh(GetFileNameNoExt(modelFilePath).c_str(), mesh);
			return resMan->GetMesh(GetFileNameNoExt(modelFilePath).c_str());
		}
		else
		{
			return resMan->GetMesh(null_mesh);
		}
	}
	else
	{
		return resMan->GetMesh(GetFileNameNoExt(modelFilePath).c_str());
	}
}

//Material* GetMaterialFromMatFile(const char* path)
//{
//	// TODO:
//}
Mesh* FileSystem::LoadMeshInModelByName(const char* modelFilePath, const char* meshName)
{
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
	if (false == resMan->MeshExists(meshName))
	{
		Mesh* mesh = nullptr;
#ifdef AI_CONFIG_H_INC // assimp
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            QwerkE::LogWarning(__FILE__, __LINE__, "ERROR::ASSIMP::%s", importer.GetErrorString());
			return nullptr; // failure
		}
		QwerkE_assimp_loadMeshByName(scene->mRootNode, scene, mesh, modelFilePath, meshName);
#else
		// separate model loading library
#pragma error "Define model loading library!"
#endif // AI_CONFIG_H_INC
		resMan->AddMesh(meshName, mesh);
		return resMan->GetMesh(meshName);
	}
	else
	{
		return resMan->GetMesh(meshName);
	}
}

bool FileSystem::LoadModelFileToMeshes(const char* path)
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
        QwerkE::LogWarning(__FILE__, __LINE__, "ERROR::ASSIMP::%s", importer.GetErrorString());
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