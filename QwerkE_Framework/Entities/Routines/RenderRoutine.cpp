#include "../GameObject.h"
#include "../Routines/Routine.h"
#include "RenderRoutine.h"
#include "../../QwerkE_Enums.h"
#include "../../Systems/Graphics/Mesh/Mesh.h"
#include "../../Systems/Graphics/Graphics_Header.h"
#include "../../Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../Systems/Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../Entities/Components/Camera/CameraComponent.h"
#include "../../Entities/Components/ModelComponent.h"
#include "../../Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../Systems/Graphics/Gfx_Classes/Renderable.h"

#include <assert.h>

void RenderRoutine::Initialize()
{
	m_pParent->AddDrawRoutine(this);
	m_pModel = (ModelComponent*)m_pParent->GetComponent(eComponentTags::Component_Model);
	m_Type = eRoutineTypes::Routine_Render;
	SetDrawFunctions();
}
//// Private functions
void RenderRoutine::DrawMeshData(GameObject* a_Camera)
{
	if (!m_pModel) m_DrawFunc = &RenderRoutine::NullDraw;

	/* Variables */
	CameraComponent* t_pCamera = (CameraComponent*)a_Camera->GetComponent(Component_Camera);

	std::vector<Renderable> t_Renderables = *m_pModel->LookAtRenderableList();

	for (size_t i = 0; i < t_Renderables.size(); i++)
	{
		t_Renderables[i].s_Shader->Use();

		for (int j = 0; j < m_UniformSetupList[j].size(); j++)
		{
			(this->*m_UniformSetupList[i][j])(t_pCamera, &t_Renderables[i]);
		}

		t_Renderables[i].s_Mesh->Draw();
	}
}

void RenderRoutine::NullDraw(GameObject* a_Camera)
{
	// look for valid models/materials
	if (m_pModel)
	{
		// TODO: Do I need to check that other data is valid?
		SetDrawFunctions();
		m_DrawFunc = &RenderRoutine::DrawMeshData;
		DrawMeshData(a_Camera); // draw current frame
	}
}

void RenderRoutine::SetDrawFunctions()
{
	if (!m_pModel) m_DrawFunc = &RenderRoutine::NullDraw;

	m_UniformSetupList.clear(); // reset uniform func list

	const std::vector<Renderable>* t_Renderables = m_pModel->LookAtRenderableList();

	// TODO:: Improve conditions for assignments.
	// append empty vectors to fill
	for (size_t i = 0; i < t_Renderables->size(); i++)
	{
		std::vector<SetupUniformFunction> temp;
		m_UniformSetupList.push_back(temp);
	}

	for (int i = 0; i < t_Renderables->size(); i++)
	{
		std::vector<std::string> t_Uniforms = t_Renderables->at(i).s_Shader->GetUniformList(); // get shader
		MaterialData* t_Material = t_Renderables->at(i).s_Material;

		/* Add functions to setup shader uniforms */
		for (size_t j = 0; j < t_Uniforms.size(); j++) // Setup uniforms
		{
			// Color
			if (t_Uniforms.at(j) == "ObjectColor")
			{
				m_UniformSetupList[i].push_back(&RenderRoutine::SetupColorUniforms);
			}
			else if (t_Uniforms.at(j) == "WorldMat")
			{
				m_UniformSetupList[i].push_back(&RenderRoutine::Setup3DTransform);
			}
			else if (t_Uniforms.at(j) == "2DTransform")
			{
				m_UniformSetupList[i].push_back(&RenderRoutine::Setup2DTransform);
			}
		}
		/* More complex uniforms */
		// Material
		if (t_Material)
		{
			m_UniformSetupList[i].push_back(&RenderRoutine::SetupMaterialUniforms);
		}
		// Lighting
		if (t_Material) // TODO: Improve logic
		{
			m_UniformSetupList[i].push_back(&RenderRoutine::SetupLightingUniforms);
		}
	}

	CheckGraphicsErrors(__FILE__, __LINE__); // DEBUG:
}