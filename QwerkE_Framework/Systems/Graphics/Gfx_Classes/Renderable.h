#ifndef _Renderable_H_
#define _Renderable_H_

#include "../Mesh/Mesh.h"
#include "../ShaderProgram/ShaderProgram.h"

#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"

class Mesh;
class ShaderProgramData;
class MaterialData;

class Renderable
{
public:
	Renderable() {}
	Renderable(ShaderProgramData* shader, MaterialData* material, Mesh* mesh)
	{
		m_Shader = shader;
		m_Material = material;
		m_Mesh = mesh;
	}

	// Getters + Setters
	// Getters
	ShaderProgramData* GetShaderSchematic() { return m_Shader; }
	MaterialData* GetMaterialSchematic() { return m_Material; }
	Mesh* GetMesh() { return m_Mesh; }

	// Setters
	void SetShader(ShaderProgramData* shader)
	{
		if (shader)
		{
			m_Shader = shader;
			if (m_Mesh)
				m_Mesh->SetupShaderAttributes(m_Shader);
		}
	}

	void SetMaterial(MaterialData* material)
	{
		if (material)
			m_Material = material;
	}

	void SetMesh(Mesh* mesh)
	{
		if (mesh)
			m_Mesh = mesh;
	}

private:
	ShaderProgramData * m_Shader = nullptr;
	MaterialData* m_Material = nullptr;
	Mesh* m_Mesh = nullptr;
};

#endif // !_Renderable_H_
