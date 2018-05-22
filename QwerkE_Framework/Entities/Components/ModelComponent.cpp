#include "ModelComponent.h"
#include "../../Systems/ResourceManager/ResourceManager.h"
#include "../../Systems/ServiceLocator.h"
#include "../../Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../Entities/GameObject.h"
#include "../../Entities/Routines/RenderRoutine.h"

ModelComponent::ModelComponent()
{
	m_ComponentTag = eComponentTags::Component_Model;
}

ModelComponent::~ModelComponent()
{
}

ModelComponent::ModelComponent(const char* shaderName, const char* materialName, const char* meshName)
{
	Renderable t_Renderable;
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	t_Renderable.s_Material = resMan->GetMaterial(materialName);
	t_Renderable.s_Mesh = resMan->GetMesh(meshName);
	t_Renderable.s_Shader = resMan->GetShader(shaderName);

	t_Renderable.s_Mesh->SetupShaderAttributes(t_Renderable.s_Shader);

	m_RenderableList.push_back(t_Renderable);

	if (m_pParent)
		((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
}

void ModelComponent::GenerateRecipe()
{
	// TODO: Define recipes
}

void ModelComponent::Setup(const char* shaderName, const char* materialName, const char* meshName)
{
	Renderable t_Renderable;
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);

	t_Renderable.s_Material = resMan->GetMaterial(materialName);
	t_Renderable.s_Mesh = resMan->GetMesh(meshName);
	t_Renderable.s_Shader = resMan->GetShader(shaderName);

	t_Renderable.s_Mesh->SetupShaderAttributes(t_Renderable.s_Shader);

	m_RenderableList.push_back(t_Renderable);

	if (m_pParent)
		((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
}

void ModelComponent::AppendEmptyRenderables(int count)
{
	ResourceManager* resMan = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
	for (int i = 0; i < count; i++)
	{
		Renderable t_Renderable;

		t_Renderable.s_Shader = resMan->GetShader(null_shader);
		t_Renderable.s_Material = resMan->GetMaterial(null_material);
		t_Renderable.s_Mesh = resMan->GetMesh(null_mesh);

		m_RenderableList.push_back(t_Renderable);
	}
}

void ModelComponent::AddRenderable(Renderable renderable)
{
	m_RenderableList.push_back(renderable);
}

void ModelComponent::SetShaderAtIndex(int index, ShaderProgram* shader)
{
	// TODO: More error handling
	if (index < m_RenderableList.size())
	{
		m_RenderableList[index].s_Shader = shader;
		m_RenderableList[index].s_Mesh->SetupShaderAttributes(shader);

		if (m_pParent)
			((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
	}
}

void ModelComponent::SetMaterialAtIndex(int index, MaterialData* material)
{
	// TODO: More error handling
	if (index < m_RenderableList.size())
		m_RenderableList[index].s_Material = material;
	// TODO: Changing material will need to reset render routine in the future
}

void ModelComponent::SetMeshAtIndex(int index, Mesh* mesh)
{
	// TODO: More error handling
	if (index < m_RenderableList.size())
	{
		m_RenderableList[index].s_Mesh = mesh;
		m_RenderableList[index].s_Mesh->SetupShaderAttributes(m_RenderableList[index].s_Shader);
	}
}