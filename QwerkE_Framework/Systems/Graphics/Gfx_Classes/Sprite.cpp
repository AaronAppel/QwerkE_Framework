#include "Sprite.h"
#include "../ShaderProgram/ShaderProgram.h"
#include "../Mesh/Mesh.h"
#include "../../Math_Includes.h"

Sprite2D::Sprite2D()
{
	m_Transform = new mat4();
	UpdateTransform();
}

Sprite2D::~Sprite2D()
{
	delete m_Transform;
}

void Sprite2D::UpdateTransform()
{
	m_Transform->CreateSRT(m_Scale, vec3(0, 0, m_Angle), m_Position);
}

void Sprite2D::Draw()
{
	if (m_Mesh) // nullptr*?
	{
		/* Use Program */
		m_Shader->Use();

		/* Setup Uniforms */
		m_Shader->SetUniformMat4("Transform", &m_Transform->m11);
		m_Shader->SetupTextures(&m_TextureID, 1);

		/* Draw */
		m_Mesh->Draw();
	}
}