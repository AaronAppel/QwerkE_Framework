#include "RenderComponent.h"
#include "../../Systems/Resources/Resources.h"
#include "../../Systems/Services.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Shader/ShaderProgram.h"
#include "../../Entities/GameObject.h"
#include "../../Entities/Routines/RenderRoutine.h"
#include "../../Graphics/GraphicsUtilities/GraphicsHelpers.h"

namespace QwerkE {

    RenderComponent::RenderComponent()
    {
        m_ComponentTag = eComponentTags::Component_Render;
    }

    RenderComponent::RenderComponent(const char* objectRecipe)
    {
        m_ComponentTag = eComponentTags::Component_Render;

        if (m_pParent)
        {
            RenderRoutine* rRoutine = (RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render);
            if (rRoutine)
                rRoutine->ResetUniformList();
        }
    }

    RenderComponent::RenderComponent(const char* shaderName, const char* materialName, const char* meshName)
    {
        m_ComponentTag = eComponentTags::Component_Render;

        Renderable t_Renderable;
        t_Renderable.SetMaterial(Resources::GetMaterial(materialName));
        t_Renderable.SetMesh(Resources::GetMesh(meshName));
        t_Renderable.SetShader(Resources::GetShaderProgram(shaderName));

        t_Renderable.GetMesh()->SetupShaderAttributes(t_Renderable.GetShaderSchematic());

        m_RenderableList.push_back(t_Renderable);

        if (m_pParent)
        {
            RenderRoutine* rRoutine = (RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render);
            if (rRoutine)
                rRoutine->ResetUniformList();
        }
    }

    RenderComponent::~RenderComponent()
    {
    }

    void RenderComponent::GenerateSchematic()
    {
        // TODO: Test
        if (strcmp(m_SchematicName.c_str(), "None") == 0)
            if (m_pParent)
                m_SchematicName = m_pParent->GetName();
        SaveObjectSchematic(this);
    }

    void RenderComponent::Setup(const char* shaderName, const char* materialName, const char* meshName)
    {
        Renderable t_Renderable;

        t_Renderable.SetMaterial(Resources::GetMaterial(materialName));
        t_Renderable.SetMesh(Resources::GetMesh(meshName));
        t_Renderable.SetShader(Resources::GetShaderProgram(shaderName));

        t_Renderable.GetMesh()->SetupShaderAttributes(t_Renderable.GetShaderSchematic());

        m_RenderableList.push_back(t_Renderable);

        if (m_pParent)
            ((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
    }

    void RenderComponent::AppendEmptyRenderables(int count)
    {
        for (int i = 0; i < count; i++)
        {
            Renderable t_Renderable;

            t_Renderable.SetShader(Resources::GetShaderProgram(null_shader_schematic));
            t_Renderable.SetMaterial(Resources::GetMaterial(null_material));
            t_Renderable.SetMesh(Resources::GetMesh(null_mesh));

            m_RenderableList.push_back(t_Renderable);
        }
    }

    void RenderComponent::AddRenderable(Renderable renderable)
    {
        m_RenderableList.push_back(renderable);
    }

    void RenderComponent::SetNameAtIndex(int index, std::string name)
    {
        // TODO: More error handling
        if (index < m_RenderableList.size())
        {
            m_RenderableList[index].SetRenderableName(name);
        }
    }

    void RenderComponent::SetShaderAtIndex(int index, ShaderProgram* shader)
    {
        // TODO: More error handling
        if (index < m_RenderableList.size() && shader != nullptr)
        {
            m_RenderableList[index].SetShader(shader);

            if (m_RenderableList[index].GetMesh())
            {
                m_RenderableList[index].GetMesh()->SetupShaderAttributes(shader);

                if (m_pParent)
                    ((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
            }
        }
    }

    void RenderComponent::SetMaterialAtIndex(int index, Material* material)
    {
        // TODO: More error handling
        if (index < m_RenderableList.size() && material != nullptr)
            m_RenderableList[index].SetMaterial(material);
        // TODO: Changing material will need to reset render routine in the future
    }

    void RenderComponent::SetMeshAtIndex(int index, Mesh* mesh)
    {
        // TODO: More error handling
        if (index < m_RenderableList.size() && mesh != nullptr)
        {
            m_RenderableList[index].SetMesh(mesh);

            if (m_RenderableList[index].GetShaderSchematic())
            {
                m_RenderableList[index].GetMesh()->SetupShaderAttributes(m_RenderableList[index].GetShaderSchematic());

                if (m_pParent)
                    ((RenderRoutine*)m_pParent->GetFirstDrawRoutineOfType(eRoutineTypes::Routine_Render))->ResetUniformList();
            }
        }
    }

}
