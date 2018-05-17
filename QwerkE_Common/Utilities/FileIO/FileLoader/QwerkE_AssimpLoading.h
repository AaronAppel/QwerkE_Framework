#ifndef _QwerkE_AssimpLoading_H_
#define _QwerkE_AssimpLoading_H_

// Assimp specific loading function definitions and helpers

#include "../../../Libraries/assimp/Importer.hpp"
#include "../../../Libraries/assimp/scene.h"
#include "../../../Libraries/assimp/postprocess.h"
#include "../../../Libraries/assimp/config.h"
#include "../../../Libraries/assimp/material.h"
#include "../../../../QwerkE_Framework/Systems/Graphics/Gfx_Classes/MaterialData.h"

#include <iostream>
#include <vector>
#include <string>

class aiNode;
class aiScene;

void QwerkE_assimp_loadSceneNodeData(aiNode *node, const aiScene *scene, std::vector<Mesh*>& meshes, std::string directory, std::vector<std::string>& matNames);

#endif // !_QwerkE_AssimpLoading_H_
