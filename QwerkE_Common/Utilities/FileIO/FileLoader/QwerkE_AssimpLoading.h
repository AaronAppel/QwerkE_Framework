#ifndef _QwerkE_AssimpLoading_H_
#define _QwerkE_AssimpLoading_H_

// Assimp specific loading function definitions and helpers

#include "../../Libraries/assimp/Importer.hpp"
#include "../../Libraries/assimp/scene.h"
#include "../../Libraries/assimp/postprocess.h"
#include "../../Libraries/assimp/config.h"
#include "../../Libraries/assimp/material.h"

#include <iostream>
#include <vector>
#include <string>

struct Texture // TODO: take out of here or delete
{
	std::string name;
	// std::string directory;
	GLuint handle;
};

class Model;

void ProcessNode() {}
std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, std::vector<Texture>& textures);

#endif // !_QwerkE_AssimpLoading_H_
