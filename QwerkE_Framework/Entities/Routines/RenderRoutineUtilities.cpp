#include "RenderRoutine.h"
#include "../GameObject.h"
#include "../../Entities/Components/Component.h"
#include "../../Entities/Components/Camera/CameraComponent.h"
#include "../../Entities/Components/RenderComponent.h"
#include "../../Entities/Components/LightComponent.h"
#include "../../Graphics/Shader/ShaderProgram.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Texture.h"
#include "../../Graphics/Shader/ShaderVariable_Defines.h"
#include "../../Graphics/Renderable.h"
#include "../../Scenes/Scene.h"
#include "../../../QwerkE_Common/Math_Includes.h"
#include "../../../QwerkE_Framework/QwerkE_Enums.h"

#include <string>
#include <vector>
#include <map>

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

	t_pShader->SetUniformMat4(transform2D, &worldMat.m11); // TODO: Set 2DTransform
}
/* Fragment uniform value assignment */
void RenderRoutine::SetupColorUniforms(CameraComponent* cameraObject, Renderable* renderable)
{
	ShaderProgram* t_pShader = renderable->GetShaderSchematic();
	// TODO: Still using colour?
	vec4 t_Colour = vec4(0,1,0,1); // m_pRenderComp->GetColour();

	t_pShader->SetUniformFloat4(objectColor, t_Colour.x, t_Colour.y, t_Colour.z, t_Colour.w);
}
// Materials
void RenderRoutine::SetupMaterialUniforms(CameraComponent* a_Camera, Renderable* renderable)
{
	Material* material = renderable->GetMaterialSchematic();
	const std::map<eMaterialMaps, Texture*>* materialList = material->SeeMaterials();

	/* Assign material texture values */
	int counter = 0;
	for (auto p : *materialList)
	{
		glActiveTexture(GL_TEXTURE0 + counter);
		glBindTexture(GL_TEXTURE_2D, p.second->s_Handle);

		switch (p.first)
		{
		case eMaterialMaps::MatMap_Ambient:
			renderable->GetShaderSchematic()->SetUniformInt1(AmbientName, counter);
			break;
		case eMaterialMaps::MatMap_Diffuse:
			renderable->GetShaderSchematic()->SetUniformInt1(DiffuseName, counter);
			break;
		case eMaterialMaps::MatMap_Specular:
			renderable->GetShaderSchematic()->SetUniformInt1(SpecularName, counter);
			break;
		}
		counter++;
	}

	/* Assign other values */
	renderable->GetShaderSchematic()->SetUniformFloat1("Shine", 0.5f); // TODO: Improve

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