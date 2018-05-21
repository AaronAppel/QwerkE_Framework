#include "RenderComponent.h"
#include "../GameObject.h"
#include "../Routines/RenderRoutine.h"
#include "../../Systems/Graphics/Mesh/Model.h"
#include "../../Systems/Graphics/ShaderProgram/ShaderProgram.h"

RenderComponent::RenderComponent()
{
	m_Colour.Set(1.0f, 1.0f, 1.0f, 1.0f);
	m_pShader = nullptr;
	m_CurrentTexture = NULL;
	m_ComponentTag = Component_Render;
}

RenderComponent::~RenderComponent()
{
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

void RenderComponent::SetModel(Model* model)
{
	m_Model = model;
	m_Model->SetupMeshAttributes(m_pShader);
}