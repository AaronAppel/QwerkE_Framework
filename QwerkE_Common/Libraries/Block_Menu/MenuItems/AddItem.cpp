#include "AddItem.h"
#include "../Windows/MenuWindow.h"
#include "../../../QwerkE_Framework/Systems/Graphics/ShaderProgram/ShaderProgram.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Model/Mesh/Mesh.h"

AddButton::AddButton(Mesh* mesh) : MenuItem(mesh)
{
}

AddButton::~AddButton()
{
	MenuItem* item = new MenuItem(vec2(1,1));
	item->SetMesh(m_Mesh);
	item->SetParentWindow(m_ParentWindow);

	m_ParentWindow->SetDimensions(5, 5);
	m_ParentWindow->AddItem(item);
	m_ParentWindow->UpdateItems();
	// set image as + symbol
}

void AddButton::Draw()
{
	m_Shader->Use();
	m_Shader->SetUniformMat4("Transform", &m_Transform.m11);
	m_Shader->SetUniformFloat4("Color", m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	m_Mesh->Draw();
}

void AddButton::LeftClick()
{
	// TODO:: check menu item list size
	MenuItem* item = new MenuItem(vec2(1,1));
	item->SetMesh(m_Mesh);
	item->SetParentWindow(m_ParentWindow);

	m_ParentWindow->AddItem(item);
	m_ParentWindow->UpdateItems();
	// TODO:: Update menu item list dimensions
}