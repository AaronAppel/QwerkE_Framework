#ifndef _MenuManager_H_
#define _MenuManager_H_

#include "../../Math_Includes.h"
#include <vector>

class Menu;

class MenuManager
{
public:
	MenuManager();
	~MenuManager();

	void Update(vec2 mousePos);

	void Draw();

	void AddMenu(Menu* menu) { m_Menus.push_back(menu); };

	void Click(vec2 mousePos, int button);

private:
	std::vector<Menu*> m_Menus;

};

#endif // !_MenuManager_H_