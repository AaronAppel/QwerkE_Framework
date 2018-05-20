#include "../GameObject.h"
#include "../Routines/Routine.h"
#include "../Components/RenderComponent.h"
#include "RenderRoutine.h"
#include "../../QwerkE_Enums.h"
#include "../../Systems/Graphics/Mesh/Mesh.h"
#include "../../Systems/Graphics/Graphics_Header.h"
#include "../../Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../Systems/Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../Entities/Components/Camera/CameraComponent.h"

#include <assert.h>

void RenderRoutine::Initialize()
{
	m_pParent->AddDrawRoutine(this);
	m_pRender = (RenderComponent*)m_pParent->GetComponent(Component_Render);
	SetDrawFunctions();
	m_Type = eRoutineTypes::Routine_Render;
}
//// Private functions
void RenderRoutine::Draw(GameObject* a_Camera)
{
	if (!m_pRender) return;

	/* Variables */
	CameraComponent* t_pCamera = (CameraComponent*)a_Camera->GetComponent(Component_Camera);
	ShaderProgram* t_pShader = m_pRender->GetShader();
	Model* t_pModel = m_pRender->GetModel();

	/* Use Program */
	t_pShader->Use();

	// TODO:
	for (int i = 0; i < t_pModel->m_Meshes.size(); i++)
	for (unsigned int j = 0; j < m_UniformSetupList.size(); j++)
	{
		(this->*m_UniformSetupList[i].at(j))(t_pCamera); // Call setup function
	}

	// TODO: Setup model uniform setup functions
	for (size_t i = 0; i < t_pModel->m_Meshes.size(); i++)
	{
		// setup uniforms
		GLuint ambHandle = t_pModel->m_Materials[i]->ambientHandle;
		GLuint diffHandle = t_pModel->m_Materials[i]->diffuseHandle;
		GLuint specHandle = t_pModel->m_Materials[i]->specularHandle;

		if (diffHandle == 0)
			diffHandle = 1;

		if (specHandle == 0)
			specHandle = 1;

		float shine = t_pModel->m_Materials[i]->shine;

		// activate textures/material
		GLuint textures[] = { ambHandle, diffHandle , specHandle };
		int size = 3;

		t_pShader->SetUniformFloat1("Shine", shine);

		SetupTextureUniforms(textures, size);

		// draw mesh
		t_pModel->m_Meshes[i]->Draw();
	}
}

void RenderRoutine::SetDrawFunctions()
{
	ShaderProgram* t_pShader = m_pRender->GetShader();
	Model* t_pModel = m_pRender->GetModel();
	m_UniformSetupList.clear(); // reset list when changing shaders

	// TODO:: Improve conditions for assignments.
	/* Variables*/
	GLuint t_Texture = m_pRender->GetCurrentTexture(); // TODO: Handle more than 1 texture

	/* Uniforms */
	std::vector<std::string> t_Uniforms = t_pShader->GetUniformList();

	for (size_t i = 0; i < t_pModel->m_Meshes.size(); i++)
	{
		std::vector<SetupUniformFunction> temp;
		m_UniformSetupList.push_back(temp);
	}

	for (size_t i = 0; i < m_UniformSetupList.size(); i++)
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
		// Texture
		else if (SearchForString(t_Uniforms.at(j), "Texture")) // TODO: deprecate
		{
			m_UniformSetupList[i].push_back(&RenderRoutine::SetupTextureUniforms);
		}
		// Material
		else if (t_pModel->m_Materials[i] != nullptr)
		{
			m_UniformSetupList[i].push_back(&RenderRoutine::SetupMaterialUniforms);
		}
		// Lighting
		else if (t_pModel->m_Materials[i] != nullptr) // TODO: Improve logic
		{
			m_UniformSetupList[i].push_back(&RenderRoutine::SetupLightingUniforms);
		}
	}

	CheckGraphicsErrors(__FILE__, __LINE__); // DEBUG:
}