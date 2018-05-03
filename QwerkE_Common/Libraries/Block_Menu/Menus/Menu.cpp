#include "Menu.h"
#include "../Windows/MenuWindow.h"

Menu::Menu(vec2 resoultion)
{
	m_Resolution = m_Resolution;
}

Menu::~Menu()
{
	for (unsigned int i = 0; i < m_Windows.size(); i++)
	{
		delete m_Windows.at(i);
	}
	m_Windows.clear();
}

void Menu::Update(vec2 mousePos)
{
	for (unsigned int i = 0; i < m_Windows.size(); i++)
	{
		MenuWindow* tempWindow = m_Windows.at(i); // position is screen space coords
		vec2 windowPos = tempWindow->GetPosition();
		vec2 windowSize = tempWindow->GetSize();

		if (PointInBox(vec2(mousePos.x, mousePos.y), vec2(windowPos.x, windowPos.y), windowSize.x, windowSize.y) ||
			tempWindow->GetIsInteracting()) // Mouse interacting with Gizmos
		{
			m_Windows.at(i)->Update(mousePos);
		}
	}
}

void Menu::Draw()
{
	for (unsigned int i = 0; i < m_Windows.size(); i++)
	{
		m_Windows.at(i)->Draw();
	}
}

void Menu::LeftClick(vec2 mousePos)
{
	for (unsigned int i = 0; i < m_Windows.size(); i++)
	{
		m_Windows.at(i)->LeftClick(mousePos);
	}
}
