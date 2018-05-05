#include "MenuManager.h"
#include "Menus/Menu.h"
// TODO: Remove dependency and transition into a library
#include "../../../QwerkE_Framework/QwerkE_Enums.h"

MenuManager::MenuManager()
{
}

MenuManager::~MenuManager()
{
	for (unsigned int i = 0; i < m_Menus.size(); i++)
	{
		delete m_Menus.at(i);
	}
	m_Menus.clear();
}

void MenuManager::Update(vec2 mousePos)
{
	for (unsigned int i = 0; i < m_Menus.size(); i++)
	{
		m_Menus.at(i)->Update(vec2(mousePos.x, mousePos.y));
	}
}

void MenuManager::Draw()
{
	for (unsigned int i = 0; i < m_Menus.size(); i++)
	{
		m_Menus.at(i)->Draw();
	}
}

void MenuManager::Click(vec2 mousePos, int button)
{
	if (button == Button_MouseLeft) // 0
	{
		for (unsigned int i = 0; i < m_Menus.size(); i++)
		{
			m_Menus.at(i)->LeftClick(vec2(mousePos.x, mousePos.y));
		}
	}
	else if (button == Button_MouseRight)
	{

	}
	else if (button == Button_MouseMiddle)
	{

	}
}