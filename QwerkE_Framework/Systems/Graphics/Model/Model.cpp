#include "Model.h"
#include "Mesh/Mesh.h"


Model::Model()
{
}

Model::~Model()
{
	for (unsigned int i = 0; i < m_HotMeshes.size(); i++)
	{
		delete m_HotMeshes.at(i);
	}
}

void Model::SetupMeshes(ShaderProgram* shader)
{
    for (unsigned int i = 0; i < m_HotMeshes.size(); i++)
    {
        m_HotMeshes.at(i)->SetupShaderAttributes(shader);
    }
}

void Model::Draw()
{
	for (unsigned int i = 0; i < m_HotMeshes.size(); i++)
	{
		m_HotMeshes.at(i)->Draw();
	}
}