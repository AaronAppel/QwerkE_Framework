#include "RenderRoutine.h"

#include <string>
#include <vector>
#include <map>

#include "../GameObject.h"
#include "../../Entities/Components/Component.h"
#include "../../Entities/Components/Camera/CameraComponent.h"
#include "../../Entities/Components/RenderComponent.h"
#include "../../Entities/Components/LightComponent.h"
#include "../../../Graphics/Shader/ShaderProgram.h"
#include "../../../Graphics/DataTypes/Material.h"
#include "../../../Graphics/DataTypes/Texture.h"
#include "../../../Graphics/Shader/ShaderVariable_Defines.h"
#include "../../../Graphics/DataTypes/Renderable.h"
#include "../../../Scenes/Scene.h"
#include "../../../../Headers/QwerkE_Enums.h"
#include "../../../Math/Vector.h"

namespace QwerkE {

    // Private functions
    /* Vertex uniform value assignment */
    void RenderRoutine::Setup3DTransform(CameraComponent* camera, Renderable* renderable)
    {
        ShaderProgram* t_pShader = renderable->GetShaderSchematic();
        // world
        mat4 worldMat;
        worldMat.CreateSRT(m_pParent->GetScale(), m_pParent->GetRotation(), m_pParent->GetPosition());
        t_pShader->SetUniformMat4(worldMatrix, &worldMat.m11);
        // view
        t_pShader->SetUniformMat4(viewMatrix, &camera->GetViewMatrix()->m11); // get from camera
        // projection
        t_pShader->SetUniformMat4(projectionMatrix, &camera->GetProjectionMatrix()->m11); // get from camera
    }
    void RenderRoutine::Setup2DTransform(CameraComponent* camera, Renderable* renderable)
    {
        ShaderProgram* t_pShader = renderable->GetShaderSchematic();
        mat4 worldMat;

        worldMat.CreateSRT(m_pParent->GetScale(), m_pParent->GetRotation(), m_pParent->GetPosition());

        t_pShader->SetUniformMat4(transform2D, &worldMat.m11); // TODO: Review 2DTransform setup
    }
    /* Fragment uniform value assignment */
    void RenderRoutine::SetupColorUniforms(CameraComponent* cameraObject, Renderable* renderable)
    {
        ShaderProgram* t_pShader = renderable->GetShaderSchematic();
        vec4 t_Colour = vec4(0, 1, 0, 1); // m_pRenderComp->GetColour();

        t_pShader->SetUniformFloat4(objectColor, t_Colour.x, t_Colour.y, t_Colour.z, t_Colour.w);
    }
    // Materials
    void RenderRoutine::SetupMaterialUniforms(CameraComponent* a_Camera, Renderable* renderable)
    {
        Material* material = renderable->GetMaterialSchematic();
        const std::map<eMaterialMaps, Texture*>* materialList = material->SeeMaterials();
        ShaderProgram* shader = renderable->GetShaderSchematic();
        // TODO: Check uniforms from : const std::vector<std::string>* uniforms = shader->SeeUniforms();

        /* Assign material texture values */
        int counter = 0;
        for (auto p : *materialList)
        {
            // TODO: Do not assign values the material does not use
            // if (p.second == nullptr)
            // 	continue;

            glActiveTexture(GL_TEXTURE0 + counter);
            glBindTexture(GL_TEXTURE_2D, p.second->s_Handle);

            // TODO: Stop activating textures the shader does not use
            // if (shader->SeeUniforms().contains(counter) == true)
            switch (p.first)
            {
            case eMaterialMaps::MatMap_Ambient:
                shader->SetUniformInt1(AmbientName, counter);
                break;
            case eMaterialMaps::MatMap_Diffuse:
                shader->SetUniformInt1(DiffuseName, counter);
                break;
            case eMaterialMaps::MatMap_Specular:
                shader->SetUniformInt1(SpecularName, counter);
                break;
            case eMaterialMaps::MatMap_Emissive:
                shader->SetUniformInt1(EmissiveName, counter);
                break;
            case eMaterialMaps::MatMap_Height:
                shader->SetUniformInt1(HeightName, counter);
                break;
            case eMaterialMaps::MatMap_Normals:
                shader->SetUniformInt1(NormalsName, counter);
                break;
            case eMaterialMaps::MatMap_Shininess:
                shader->SetUniformInt1(ShininessName, counter);
                break;
            case eMaterialMaps::MatMap_Opacity:
                shader->SetUniformInt1(OpacityName, counter);
                break;
            case eMaterialMaps::MatMap_Displacement:
                shader->SetUniformInt1(DisplacementName, counter);
                break;
            case eMaterialMaps::MatMap_LightMap:
                shader->SetUniformInt1(LightMapName, counter);
                break;
            case eMaterialMaps::MatMap_Reflection:
                shader->SetUniformInt1(ReflectionName, counter);
                break;
            case eMaterialMaps::MatMap_Albedo:
                shader->SetUniformInt1(AlbedoName, counter);
                break;
            case eMaterialMaps::MatMap_Metallic:
                shader->SetUniformInt1(MetallicName, counter);
                break;
            case eMaterialMaps::MatMap_AmbientOcclusion:
                shader->SetUniformInt1(AmbientOcclusionName, counter);
                break;
            case eMaterialMaps::MatMap_Roughness:
                shader->SetUniformInt1(RougnessName, counter);
                break;
            }
            counter++;
        }

        /* Assign other values */
        shader->SetUniformFloat1("Shine", 0.5f); // TODO: Improve

    }
    // Lighting
    void RenderRoutine::SetupLightingUniforms(CameraComponent* a_Camera, Renderable* renderable)
    {
        ShaderProgram* t_pShader = renderable->GetShaderSchematic();
        // TODO: Get light data better
        GameObject* t_Light = m_pRenderComp->GetParent()->GetScene()->GetLightList().at(0); // TODO: Stop hard coding index. Handle multiple lights
        LightComponent* t_LightComp = (LightComponent*)t_Light->GetComponent(Component_Light);

        vec3 lightColour = t_LightComp->GetColour();

        vec3 t_LightPos = t_Light->GetPosition();
        t_pShader->SetUniformFloat3(lightPosition, t_LightPos.x, t_LightPos.y, t_LightPos.z);

        t_pShader->SetUniformFloat3(lightColor, lightColour.x, lightColour.y, lightColour.z);
    }
    // Camera
    void RenderRoutine::SetupCameraUniforms(CameraComponent* a_Camera, Renderable* renderable)
    {
        ShaderProgram* t_pShader = renderable->GetShaderSchematic();

        vec3 t_CamPos = a_Camera->GetParent()->GetPosition();
        t_pShader->SetUniformFloat3(cameraPosition, t_CamPos.x, t_CamPos.y, t_CamPos.z);
    }
    // Textures
    void RenderRoutine::SetupTextureUniforms(GLuint textures[], int size, ShaderProgram* shader)
    {
        // Handle multiple textures
        for (int i = 0; i < size; i++)
        {
            std::string id = TexturePrefix;
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            shader->SetUniformInt1(id.append(std::to_string(i)).c_str(), i);
        }
    }

}
