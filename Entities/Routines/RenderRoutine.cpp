#include "RenderRoutine.h"
#include "../GameObject.h"
#include "../Routines/Routine.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Renderable.h"
#include "../../Graphics/Shader/ShaderProgram.h"
#include "../../Graphics/Mesh/Mesh.h"
#include "../../Graphics/Graphics_Header.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../Entities/Components/Camera/CameraComponent.h"
#include "../../Entities/Components/RenderComponent.h"

#include "../../Headers/QwerkE_Enums.h"

#include <assert.h>

void RenderRoutine::Initialize()
{
	m_pParent->AddDrawRoutine(this);
	m_pRenderComp = (RenderComponent*)m_pParent->GetComponent(eComponentTags::Component_Render);
	m_Type = eRoutineTypes::Routine_Render;
	SetDrawFunctions();

    if (m_pRenderComp)
    {
        // Setup mesh, shader, material render time values for each renderable
        std::vector<Renderable>* renderables = m_pRenderComp->GetRenderableList();

        for (int i = 0; i < renderables->size(); i++)
        {
            if (renderables->at(i).GetShaderSchematic())
            {
				// TODO: Handle null mesh, material, shader
                renderables->at(i).GetMesh()->SetupShaderAttributes(renderables->at(i).GetShaderSchematic());
            }
        }

        if (m_pParent)
            ((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
    }
    else
        QwerkE::LogWarning(__FILE__, __LINE__, "m_pRenderComp is nullptr for object %s!", m_pParent->GetName().c_str());
}
//// Private functions
void RenderRoutine::DrawMeshData(GameObject* a_Camera)
{
	if (!m_pRenderComp)
    {
        QwerkE::LogWarning(__FILE__, __LINE__, "m_pRenderComp is nullptr for object %s!", m_pParent->GetName().c_str());
        m_DrawFunc = &RenderRoutine::NullDraw;
		return;
	}

	/* Variables */
	CameraComponent* t_pCamera = (CameraComponent*)a_Camera->GetComponent(Component_Camera);

	std::vector<Renderable> t_Renderables = *m_pRenderComp->LookAtRenderableList();

	for (size_t i = 0; i < t_Renderables.size(); i++)
	{
		t_Renderables[i].GetShaderSchematic()->Use();

		for (int j = 0; j < m_UniformSetupList[i].size(); j++)
		{
			(this->*m_UniformSetupList[i][j])(t_pCamera, &t_Renderables[i]);
		}

		t_Renderables[i].GetMesh()->Draw();
	}
}

void RenderRoutine::NullDraw(GameObject* a_Camera)
{
	// look for valid models/materials
	if (m_pRenderComp)
	{
		// TODO: Do I need to check that other data is valid?
		m_DrawFunc = &RenderRoutine::DrawMeshData;
		SetDrawFunctions();
		if(m_DrawFunc == &RenderRoutine::DrawMeshData)
			DrawMeshData(a_Camera); // draw current frame
	}
}

void RenderRoutine::SetDrawFunctions()
{
	if (!m_pRenderComp)
    {
        QwerkE::LogWarning(__FILE__, __LINE__, "m_pRenderComp is nullptr for object %s!", m_pParent->GetName().c_str());
		m_DrawFunc = &RenderRoutine::NullDraw;
		return;
	}

	m_UniformSetupList.clear(); // reset uniform func list

	std::vector<Renderable>* t_Renderables = (std::vector<Renderable>*)m_pRenderComp->LookAtRenderableList();

	// TODO:: Improve conditions for assignments.
	// append empty vectors to fill
	for (size_t i = 0; i < t_Renderables->size(); i++)
	{
		std::vector<SetupUniformFunction> temp;
		m_UniformSetupList.push_back(temp);
	}

	for (int i = 0; i < t_Renderables->size(); i++) // for each renderable
	{
		if (t_Renderables->at(i).GetShaderSchematic()->SeeUniforms()->size() == 0) t_Renderables->at(i).GetShaderSchematic()->FindAttributesAndUniforms();
		const std::vector<std::string>* t_Uniforms = t_Renderables->at(i).GetShaderSchematic()->SeeUniforms(); // get shader
		Material* t_Material = t_Renderables->at(i).GetMaterialSchematic();

		/* Add functions to setup shader uniforms */
		for (size_t j = 0; j < t_Uniforms->size(); j++) // Setup uniforms
		{
			// Color
			if (t_Uniforms->at(j) == "ObjectColor")
			{
				m_UniformSetupList[i].push_back(&RenderRoutine::SetupColorUniforms);
			}
			else if (t_Uniforms->at(j) == "WorldMat")
			{
				m_UniformSetupList[i].push_back(&RenderRoutine::Setup3DTransform);
			}
			else if (t_Uniforms->at(j) == "2DTransform")
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