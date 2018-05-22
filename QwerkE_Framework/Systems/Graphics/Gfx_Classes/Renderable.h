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
	ShaderProgram* s_Shader = nullptr;
	MaterialData* s_Material = 0;
	Mesh* s_Mesh = nullptr;

	Renderable() {}
	Renderable(ShaderProgram* shader, MaterialData* material, Mesh* mesh)
	{
		s_Shader = shader;
		s_Material = material;
		s_Mesh = mesh;
	}
};

#endif // !_Renderable_H_
