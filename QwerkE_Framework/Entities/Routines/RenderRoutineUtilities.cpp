#include "RenderRoutine.h"
#include "../GameObject.h"
#include "../../Entities/Components/Component.h"
#include "../../Entities/Components/Camera/CameraComponent.h"
#include "../../Entities/Components/RenderComponent.h"
#include "../../Entities/Components/LightComponent.h"
#include "../../Systems/Graphics/Gfx_Classes/ShaderProgramData.h"
#include "../../Systems/Graphics/Gfx_Classes/MaterialData.h"
#include "../../Systems/Graphics/Gfx_Classes/Renderable.h"
#include "../../Scenes/Scene.h"
#include "../../../QwerkE_Common/Math_Includes.h"

#include <string>

// Private functions
/* Vertex uniform value assignment */
void RenderRoutine::Setup3DTransform(CameraComponent* camera, Renderable* renderable)
{
	ShaderProgramData* t_pShader = renderable->s_Shader;
	// world
	mat4 worldMat;
	worldMat.CreateSRT(m_pParent->GetScale(), m_pParent->GetRotation(), m_pParent->GetPosition());
	t_pShader->SetUniformMat4("WorldMat", &worldMat.m11);
	// view
	t_pShader->SetUniformMat4("ViewMat", &camera->GetViewMatrix()->m11); // get from camera
	// projection
	t_pShader->SetUniformMat4("ProjMat", &camera->GetProjectionMatrix()->m11); // get from camera
}
void RenderRoutine::Setup2DTransform(CameraComponent* camera, Renderable* renderable)
{
	ShaderProgramData* t_pShader = renderable->s_Shader;
	mat4 worldMat;

	worldMat.CreateSRT(m_pParent->GetScale(), m_pParent->GetRotation(), m_pParent->GetPosition());

	t_pShader->SetUniformMat4("2DTransform", &worldMat.m11); // TODO: Set 2DTransform
}
/* Fragment uniform value assignment */
void RenderRoutine::SetupColorUniforms(CameraComponent* cameraObject, Renderable* renderable)
{
	ShaderProgramData* t_pShader = renderable->s_Shader;
	// TODO: Still using colour?
	vec4 t_Colour = vec4(0,1,0,1); // m_pModel->GetColour();

	t_pShader->SetUniformFloat4("ObjectColor", t_Colour.x, t_Colour.y, t_Colour.z, t_Colour.w);
}
// Materials
void RenderRoutine::SetupMaterialUniforms(CameraComponent* a_Camera, Renderable* renderable)
{
	GLuint ambHandle = renderable->s_Material->s_AmbientHandle;
	GLuint diffHandle = renderable->s_Material->s_DiffuseHandle;
	GLuint specHandle = renderable->s_Material->s_SpecularHandle;
	float shine = renderable->s_Material->s_Shine;

	/* Assign values */
	renderable->s_Shader->SetUniformFloat1("Shine", shine);

	// activate textures
	GLuint textures[] = { ambHandle , diffHandle , specHandle};
	int size = 3; // TODO: Support all material handles

	SetupTextureUniforms(textures, size, renderable->s_Shader);
}
// Lighting
void RenderRoutine::SetupLightingUniforms(CameraComponent* a_Camera, Renderable* renderable)
{
	ShaderProgramData* t_pShader = renderable->s_Shader;
	// TODO: Get light data better
	GameObject* t_Light = m_pModel->GetParent()->GetScene()->GetLightList().At(0); // TODO: Stop hard coding index. Handle multiple lights
	LightComponent* t_LightComp = (LightComponent*)t_Light->GetComponent(Component_Light);

	vec3 lightColour = t_LightComp->GetColour();

	vec3 t_LightPos = t_Light->GetPosition();
	t_pShader->SetUniformFloat3("LightPos", t_LightPos.x, t_LightPos.y, t_LightPos.z);

	t_pShader->SetUniformFloat3("LightColour", lightColour.x, lightColour.y, lightColour.z);
}
// Camera
void RenderRoutine::SetupCameraUniforms(CameraComponent* a_Camera, Renderable* renderable)
{
	ShaderProgramData* t_pShader = renderable->s_Shader;

	vec3 t_CamPos = a_Camera->GetParent()->GetPosition();
	t_pShader->SetUniformFloat3("CamPos", t_CamPos.x, t_CamPos.y, t_CamPos.z);
}
// Textures
void RenderRoutine::SetupTextureUniforms(GLuint textures[], int size, ShaderProgramData* shader)
{
	// Handle multiple textures
	for (int i = 0; i < size; i++)
	{
		std::string id = "Texture";
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		shader->SetUniformInt1(id.append(std::to_string(i)).c_str(), i);
	}
}