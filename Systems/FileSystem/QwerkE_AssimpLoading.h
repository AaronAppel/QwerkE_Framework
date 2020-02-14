#ifndef _QwerkE_AssimpLoading_H_
#define _QwerkE_AssimpLoading_H_

#include <iostream>
#include <vector>
#include <string>

// Assimp types
struct aiNode;
struct aiScene;
class Mesh;

namespace QwerkE {

    // TODO: Load model as 1 mesh
    void QwerkE_assimp_loadSceneNodeData(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes, const std::string& filePath, std::vector<std::string>& matNames);
    void QwerkE_assimp_loadMeshByName(aiNode* node, const aiScene* scene, Mesh*& mesh, const char* modelFilePath, const char* meshName);
    void QwerkE_assimp_loadModelAs1Mesh(aiNode* node, const aiScene* scene, Mesh*& mesh, const char* modelFilePath);

}
#endif // _QwerkE_AssimpLoading_H_
