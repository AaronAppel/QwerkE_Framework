#include "RenderComponent.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Systems/ServiceLocator.h"
#include "../../Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../Systems/Graphics/Gfx_Classes/ShaderProgramData.h"
#include "../../Entities/GameObject.h"
#include "../../Entities/Routines/RenderRoutine.h"

RenderComponent::RenderComponent()
{
	m_ComponentTag = eComponentTags::Component_Model;
}

RenderComponent::~RenderComponent()
{
}

RenderComponent::RenderComponent(const char* shaderName, const char* materialName, const char* meshName)
{
	Renderable t_Renderable;
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	t_Renderable.SetMaterial(resMan->GetMaterial(materialName));
	t_Renderable.SetMesh(resMan->GetMesh(meshName));
	t_Renderable.SetShader(resMan->GetShaderProgramData(shaderName));

	t_Renderable.GetMesh()->SetupShaderAttributes(t_Renderable.GetShaderSchematic());

	m_RenderableList.push_back(t_Renderable);

	if (m_pParent)
		((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
}

void RenderComponent::GenerateRecipe()
{
	// TODO: Define recipes
}

void RenderComponent::Setup(const char* shaderName, const char* materialName, const char* meshName)
{
	Renderable t_Renderable;
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	t_Renderable.SetMaterial(resMan->GetMaterial(materialName));
	t_Renderable.SetMesh(resMan->GetMesh(meshName));
	t_Renderable.SetShader(resMan->GetShaderProgramData(shaderName));

	t_Renderable.GetMesh()->SetupShaderAttributes(t_Renderable.GetShaderSchematic());

	m_RenderableList.push_back(t_Renderable);

	if (m_pParent)
		((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
}

void RenderComponent::AppendEmptyRenderables(int count)
{
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
	for (int i = 0; i < count; i++)
	{
		Renderable t_Renderable;

		t_Renderable.SetShader(resMan->GetShaderProgramData(null_shader_schematic));
		t_Renderable.SetMaterial(resMan->GetMaterial(null_material));
		t_Renderable.SetMesh(resMan->GetMesh(null_mesh));

		m_RenderableList.push_back(t_Renderable);
	}
}

void RenderComponent::AddRenderable(Renderable renderable)
{
	m_RenderableList.push_back(renderable);
}

void RenderComponent::SetShaderAtIndex(int index, ShaderProgramData* shader)
{
	// TODO: More error handling
	if (index < m_RenderableList.size())
	{
		m_RenderableList[index].SetShader(shader);
		m_RenderableList[index].GetMesh()->SetupShaderAttributes(shader);

		if (m_pParent)
			((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
	}
}

void RenderComponent::SetMaterialAtIndex(int index, MaterialData* material)
{
	// TODO: More error handling
	if (index < m_RenderableList.size())
		m_RenderableList[index].SetMaterial(material);
	// TODO: Changing material will need to reset render routine in the future
}

void RenderComponent::SetMeshAtIndex(int index, Mesh* mesh)
{
	// TODO: More error handling
	if (index < m_RenderableList.size())
	{
		m_RenderableList[index].SetMesh(mesh);
		m_RenderableList[index].GetMesh()->SetupShaderAttributes(m_RenderableList[index].GetShaderSchematic());
	}
}