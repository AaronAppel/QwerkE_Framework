#include "WindowManager.h"

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
	int size = m_Windows.size();
	for (int i = 0; i < size; i++)
	{
		delete m_Windows.at(i);
	}
}

void WindowManager::AddWindow(Window* window)
{
	m_Windows.push_back(window);
}

Window* WindowManager::GetWindow(int windowID)
{
	return m_Windows.at(windowID);
}