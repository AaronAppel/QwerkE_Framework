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
#include "../../Entities/Components/CameraComponent.h"

#include <assert.h>

void RenderRoutine::Initialize()
{
	m_pParent->AddDrawRoutine(this);
	m_pRender = (RenderComponent*)m_pParent->GetComponent(Component_Render);
	SetDrawFunctions();
	m_Type = eRoutineTypes::Routine_Render;
}
//// Private functions
void RenderRoutine::DrawMesh(GameObject* a_Camera)
{
	assert(m_pRender != nullptr); // safety check

	/* Variables */
	CameraComponent* t_pCamera = (CameraComponent*)a_Camera->GetComponent(Component_Camera);
	Mesh* t_pMesh = m_pRender->GetMesh();
	ShaderProgram* t_pShader = m_pRender->GetShader();

	/* Safety check */
	if (t_pShader == nullptr) { return; } // nullptr*?
	if (t_pMesh == nullptr) { return; } // nullptr*?

	/* Use Program */
	t_pShader->Use();

	for (unsigned int i = 0; i < m_UniformSetupList.size(); i++)
	{
		(this->*m_UniformSetupList.at(i))(t_pCamera); // Call setup function
	}

	/* Draw */
	t_pMesh->Draw();
}

void RenderRoutine::DrawModel(GameObject* a_Camera)
{
	assert(m_pRender != nullptr); // safety check

	/* Variables */
	CameraComponent* t_pCamera = (CameraComponent*)a_Camera->GetComponent(Component_Camera);
	Mesh* t_pMesh = m_pRender->GetMesh();
	ShaderProgram* t_pShader = m_pRender->GetShader();

	/* Use Program */
	t_pShader->Use();

	for (unsigned int i = 0; i < m_UniformSetupList.size(); i++)
	{
		(this->*m_UniformSetupList.at(i))(t_pCamera); // Call setup function
	}

	Model* t_Model = m_pRender->GetModel();

	for (size_t i = 0; i < t_Model->m_Meshes.size(); i++)
	{
		// setup uniforms
		GLuint ambHandle = t_Model->m_Materials[i]->ambientHandle;
		GLuint diffHandle = t_Model->m_Materials[i]->diffuseHandle;
		GLuint specHandle = t_Model->m_Materials[i]->specularHandle;
		float shine = t_Model->m_Materials[i]->shine;

		// activate textures/material
		GLuint textures[] = { ambHandle , diffHandle , specHandle };
		int size = 3;

		t_pShader->SetUniformFloat1("Shine", shine);
		SetupTextureUniforms(textures, size);

		// draw mesh
		t_Model->m_Meshes[i]->Draw();
	}

	//	// setup uniforms
	//if (t_Model->GetName() == "nanosuit/nanosuit.obj")
	//{
	//	int index = 6;
	//	GLuint ambHandle = t_Model->m_Materials[index]->ambientHandle;
	//	GLuint diffHandle = t_Model->m_Materials[index]->diffuseHandle;
	//	GLuint specHandle = t_Model->m_Materials[index]->specularHandle;
	//	float shine = t_Model->m_Materials[index]->shine;

	//	// activate textures/material
	//	GLuint textures[] = { ambHandle , diffHandle , specHandle };
	//	int size = 3;

	//	t_pShader->SetUniformFloat1("Shine", shine);
	//	SetupTextureUniforms(textures, size);

	//	// draw mesh
	//	t_Model->m_Meshes[index]->Draw();
	//}
}

void RenderRoutine::SetDrawFunctions() // Setup routine to render Model/Mesh
{
	Mesh* t_pMesh = m_pRender->GetMesh();
	ShaderProgram* t_pShader = m_pRender->GetShader();

	/* Safety check */
	// TODO: Setup NULL Meshes and Shaders for debugging
	if (t_pShader == nullptr) { return; } // nullptr*?
	m_UniformSetupList.clear(); // reset list when changing shaders

	if (t_pMesh == nullptr)
	{
		Model* t_Model = m_pRender->GetModel();
		if (t_Model)
		{
			SetModelDrawFunctions();
		}
		else
		{
			return; // no meshes to draw
		}
	}
	else
	{
		/* Setup Shader() and Mesh() */
		SetMeshDrawFunctions(t_pShader);
	}
}

void RenderRoutine::SetMeshDrawFunctions(ShaderProgram* shader)
{
	m_UniformSetupList.clear(); // reset list when changing shaders

	// TODO:: Improve conditions for assignments.
	/* Variables*/
	GLuint t_Texture = m_pRender->GetCurrentTexture(); // TODO: Handle more than 1 texture
	MaterialData* t_Material = m_pRender->GetMaterial();

	/* Uniforms */
	std::vector<std::string> t_Uniforms = shader->GetUniformList();
	for (size_t i = 0; i < t_Uniforms.size(); i++) // Setup uniforms
	{
		// Color
		if (t_Uniforms.at(i) == "ObjectColor")
		{
			m_UniformSetupList.push_back(&RenderRoutine::SetupColorUniforms);
		}
		else if (t_Uniforms.at(i) == "WorldMat")
		{
			m_UniformSetupList.push_back(&RenderRoutine::Setup3DTransform);
		}
		else if (t_Uniforms.at(i) == "2DTransform")
		{
			m_UniformSetupList.push_back(&RenderRoutine::Setup2DTransform);
		}
		// Texture
		else if (SearchForString(t_Uniforms.at(i), "Texture"))
		{
			m_UniformSetupList.push_back(&RenderRoutine::SetupTextureUniforms);
		}
		// Material
		else if (t_Material != nullptr)
		{
			m_UniformSetupList.push_back(&RenderRoutine::SetupMaterialUniforms);
			m_UniformSetupList.push_back(&RenderRoutine::SetupLightingUniforms);
		}
		// Lighting
		else if (false)
		{
			// TODO: m_UniformSetupList.push_back(&RenderRoutine::SetupLightingUniforms);
		}
	}

	CheckGraphicsErrors(__FILE__, __LINE__); // DEBUG:
}

void RenderRoutine::SetModelDrawFunctions()
{
	Model* t_Model = m_pRender->GetModel();
	ShaderProgram* t_pShader = m_pRender->GetShader();

	t_Model->SetupMeshes(t_pShader);
	m_DrawFunc = &RenderRoutine::DrawModel;

	// TODO:
	for (unsigned int i = 0; i < t_Model->m_Meshes.size(); i++)
	{
		SetMeshDrawFunctions(t_pShader); // TODO: Change component data per mesh
	}
}
