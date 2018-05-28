#ifndef _QwerkE_AssimpLoading_H_
#define _QwerkE_AssimpLoading_H_

// Assimp specific loading function definitions and helpers

#include "../../../Libraries/assimp/Importer.hpp"
#include "../../../Libraries/assimp/scene.h"
#include "../../../Libraries/assimp/postprocess.h"
#include "../../../Libraries/assimp/config.h"
#include "../../../Libraries/assimp/material.h"

#include <iostream>
#include <vector>
#include <string>

class aiNode;
class aiScene;
class Mesh;

// TODO: Load model as 1 mesh
void QwerkE_assimp_loadSceneNodeData(aiNode *node, const aiScene *scene, std::vector<Mesh*>& meshes, const std::string& filePath, std::vector<std::string>& matNames);
void QwerkE_assimp_loadMeshByName(aiNode *node, const aiScene *scene, Mesh*& mesh, const char* modelFilePath, const char* meshName);
void QwerkE_assimp_loadModelAs1Mesh(aiNode *node, const aiScene *scene, Mesh*& mesh, const char* modelFilePath);

#endif // !_QwerkE_AssimpLoading_H_
