#ifndef _Renderable_H_
#define _Renderable_H_

#include "../Mesh/Mesh.h"
#include "../ShaderProgram/ShaderProgram.h"

#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"

class Mesh;
class ShaderProgram;
class MaterialData;

struct Renderable
{
	Mesh* s_Mesh = nullptr;
	MaterialData* s_Material = 0;
	ShaderProgram* s_Shader = nullptr;
};

#endif // !_Renderable_H_
