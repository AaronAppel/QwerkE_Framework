#ifndef _OBJLoader_H_
#define _OBJLoader_H_

#include "../../Math_Includes.h"

class Model;

Model* ImportOBJModel(const char* fileDirectory, vec3 objScale = 1.0f, vec2 UVScale = 1.0f, bool invertFaces = false);

#endif //!_OBJLoader_H_
