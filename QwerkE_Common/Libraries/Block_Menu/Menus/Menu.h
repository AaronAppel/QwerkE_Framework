#ifndef _Menu_H_
#define _Menu_H_

#include "../../Math_Includes.h"
#include <vector>

class MenuWindow;

class Menu
{
public:
	Menu(vec2 resoultion);
	~Menu();

	void Update(vec2 mousePos);

	void Draw();

	void AddWindow(MenuWindow* window) { m_Windows.push_back(window); };

	void LeftClick(vec2 mousePos);
	void RightClick(vec2 mousePos) {};
	void MiddleClick(vec2 mousePos) {};

private:
	std::vector<MenuWindow*> m_Windows;
	vec2 m_Resolution = vec2(0,0);
	// menu state
	// menu identifier
	// menu interface for things like numWindows
	// menu types like overlay, tooltip, opaque etc
};

#endif // !_Menu_H_