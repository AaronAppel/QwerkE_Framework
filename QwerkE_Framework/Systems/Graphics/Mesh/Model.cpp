#include "Model.h"
#include "Mesh.h"

Model::Model()
{
}

Model::~Model()
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		delete m_Meshes.at(i);
	}
}

void Model::SetupMeshes(ShaderProgram* shader)
{
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes.at(i)->SetupShaderAttributes(shader);
    }
}

void Model::Draw()
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes.at(i)->Draw();
	}
}