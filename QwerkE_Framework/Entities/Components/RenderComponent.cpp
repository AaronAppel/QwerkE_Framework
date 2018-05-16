#include "RenderComponent.h"
#include "../GameObject.h"
#include "../Routines/RenderRoutine.h"
#include "../../Systems/Graphics/Mesh/Mesh.h"

RenderComponent::RenderComponent()
{
	m_Colour.Set(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMesh = nullptr;
	m_pShader = nullptr;
	m_CurrentTexture = NULL;
	m_ComponentTag = Component_Render;
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::SetMesh(Mesh* mesh)
{
	m_pMesh = mesh;
	m_pMesh->SetupShaderAttributes(m_pShader);
}
void RenderComponent::SetShader(ShaderProgram* shader)
{
	m_pShader = shader;
	if (m_pParent)
	{
		RenderRoutine* rRoutine = (RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render);
		if (rRoutine != nullptr)
		{
			rRoutine->ResetUniformList();
		}
	}
}