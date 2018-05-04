#include "RenderRoutine.h"
#include "../../Systems/Graphics/ShaderProgram/ShaderProgram.h"
#include "../GameObject.h"
#include "../../GameObject/Components/Component.h"
#include "../../GameObject/Components/CameraComponent.h"
#include "../../GameObject/Components/RenderComponent.h"
#include "../../GameObject/Components/LightComponent.h"
#include "../../Systems/Graphics/MaterialData.h"
#include "../../Scene/Scene.h"
#include "../../../Shared_Generic/Math_Includes.h"

#include <string>

// Private functions
/* Vertex uniform value assignment */
void RenderRoutine::Setup3DTransform(CameraComponent* camera)
{
	ShaderProgram* t_pShader = m_pRender->GetShader();
	// world
	mat4 worldMat;
	worldMat.CreateSRT(m_pParent->GetScale(), m_pParent->GetRotation(), m_pParent->GetPosition());
	t_pShader->SetUniformMat4("WorldMat", &worldMat.m11);
	// view
	t_pShader->SetUniformMat4("ViewMat", &camera->GetViewMatrix()->m11); // get from camera
	// projection
	t_pShader->SetUniformMat4("ProjMat", &camera->GetProjectionMatrix()->m11); // get from camera
}
void RenderRoutine::Setup2DTransform(CameraComponent* camera)
{
	ShaderProgram* t_pShader = m_pRender->GetShader();
	mat4 worldMat;

	worldMat.CreateSRT(m_pParent->GetScale(), m_pParent->GetRotation(), m_pParent->GetPosition());

	t_pShader->SetUniformMat4("2DTransform", &worldMat.m11); // TODO: Set 2DTransform
}
/* Fragment uniform value assignment */
void RenderRoutine::SetupColorUniforms(CameraComponent* cameraObject)
{
	ShaderProgram* t_pShader = m_pRender->GetShader();
	vec4 t_Colour = m_pRender->GetColour();

	t_pShader->SetUniformFloat4("ObjectColor", t_Colour.x, t_Colour.y, t_Colour.z, t_Colour.w);
}
// Materials
void RenderRoutine::SetupMaterialUniforms(CameraComponent* a_Camera)
{
	/* Variables */
	MaterialData* t_Material = m_pRender->GetMaterial();
	ShaderProgram* t_pShader = m_pRender->GetShader();

	// TODO: Handle Null image handles
	GLuint ambHandle = t_Material->ambientHandle;
	GLuint diffHandle = t_Material->diffuseHandle;
	GLuint specHandle = t_Material->specularHandle;
	float shine = t_Material->shine;

	/* Assign values */
	t_pShader->SetUniformFloat1("Shine", shine);

	SetupCameraUniforms(a_Camera);
	SetupLightingUniforms(a_Camera);

	// activate textures
	GLuint textures[] = { ambHandle , diffHandle , specHandle};
	int size = 3;

	SetupTextureUniforms(textures, size);
}
// Lighting
void RenderRoutine::SetupLightingUniforms(CameraComponent* a_Camera)
{
	ShaderProgram* t_pShader = m_pRender->GetShader();
	GameObject* t_Light = m_pRender->GetParent()->GetScene()->GetLightList().At(0); // TODO: Stop hard coding index. Handle multiple lights
	LightComponent* t_LightComp = (LightComponent*)t_Light->GetComponent(Component_Light);

	vec3 lightColour = t_LightComp->GetColour();

	vec3 t_LightPos = t_Light->GetPosition();
	t_pShader->SetUniformFloat3("LightPos", t_LightPos.x, t_LightPos.y, t_LightPos.z);

	t_pShader->SetUniformFloat3("LightColour", lightColour.x, lightColour.y, lightColour.z);
}
// Camera
void RenderRoutine::SetupCameraUniforms(CameraComponent* a_Camera)
{
	ShaderProgram* t_pShader = m_pRender->GetShader();

	vec3 t_CamPos = a_Camera->GetParent()->GetPosition();
	t_pShader->SetUniformFloat3("CamPos", t_CamPos.x, t_CamPos.y, t_CamPos.z);
}
// Textures
void RenderRoutine::SetupTextureUniforms(CameraComponent* camera)
{
	// TODO: Improve texture count handling
	GLuint textures[] = { m_pRender->GetCurrentTexture() };
	SetupTextureUniforms(textures, 1);
}

void RenderRoutine::SetupTextureUniforms(GLuint textures[], int size)
{
	ShaderProgram* t_pShader = m_pRender->GetShader();

	// Handle multiple textures
	for (int i = 0; i < size; i++)
	{
		std::string id = "Texture";
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		t_pShader->SetUniformInt1(id.append(std::to_string(i)).c_str(), i);
	}
}