#ifndef _AddItem_H_
#define _AddItem_H_

#include "MenuItem.h"

class Mesh;

class AddButton : public MenuItem
{
public:
	AddButton(Mesh* mesh);
	~AddButton();

	void Draw();
	void LeftClick();

private:

};

#endif // _AddItem_H_