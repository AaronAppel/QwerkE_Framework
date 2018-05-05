#include "MenuItem.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Model/Mesh/Mesh.h"
#include "../../../Math_Includes.h"
#include "../../glew/GL/glew.h"
#include "../../../QwerkE_Framework/Systems/Graphics/ShaderProgram/ShaderProgram.h"
#include "../glfw/GLFW/glfw3.h"
#include "../Windows/MenuWindow.h"

MenuItem::MenuItem(Mesh* mesh)
{
	m_Mesh = mesh;
}

MenuItem::~MenuItem()
{
}

void MenuItem::Update(vec2 mousePos)
{
	// TODO:: change color better
	vec4 t = vec4(sin((float)(m_OriginalColor.x * glfwGetTime())), cos((float)(m_OriginalColor.y * glfwGetTime())), sin((float)(m_OriginalColor.z * glfwGetTime())), 1.0f);
	m_Color = t;
	DrawOverlays();
}

void MenuItem::Draw()
{
	m_Shader->Use();
	m_Shader->SetUniformMat4("Transform", &m_Transform.m11);
	m_Shader->SetUniformFloat4("Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	m_Mesh->Draw();
}

void MenuItem::SetParentWindow(MenuWindow* window)
{
	m_ParentWindow = window;
	UpdateTransform();
}

void MenuItem::SetPosition(vec2 position)
{
	m_Position = position;
}

void MenuItem::SetRotation(float rotation)
{
	m_Rotation = rotation;
}

void MenuItem::SetSize(vec2 size)
{
	m_Size = size;
}

void MenuItem::UpdateTransform()
{
	mat4 temp;

	vec2 parentPosition = m_ParentWindow->GetPosition(); // return screen pos in pixels (bottom left->top right)
	vec2 parentSize = m_ParentWindow->GetSize(); // return pixel size of window

	// rotation
	// temp = glm::rotate(temp, glm::radians(m_Rotation), vec3(0, 0, 1));

	// translate
	vec3 finalPos = vec3((m_ParentWindow->GetPosition().x - parentSize.x * 0.5 + parentSize.x * m_Position.x) / m_Resolution.x * 2 - 1,
		(m_ParentWindow->GetPosition().y - parentSize.y * 0.5 + parentSize.y * m_Position.y) / m_Resolution.y * 2 - 1,
		0);

	// temp = glm::translate(temp, vec3(finalPos));
	// temp = glm::translate(temp, vec3(0, 0, 0));

	// scale1
	vec3 finalSize = vec3(parentSize.x * m_Size.x * 2.0f / m_Resolution.x, parentSize.y * m_Size.y * 2.0f / m_Resolution.y, 1);

	// temp = glm::scale(temp, vec3(finalSize));
	// m_Transform = temp;
}
/* Functionality */
void MenuItem::LeftClick()
{
	// OutputMessage("\nMenuItem:: LeftClick() Works!");
	// std::cout >> "\\nMenuItem:: LeftClick() Works!" >> std::endl;
}
/* Overlay buttons */
void MenuItem::DrawOverlays() // private
{
	if (m_IsHighlighted)
	for (int i = 0; i < m_OverLayButtons.Size(); i++)
	{
		m_OverLayButtons.At(i)->Draw();
	}
}