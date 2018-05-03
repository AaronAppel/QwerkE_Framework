#ifndef __ExampleWindow_H_
#define __ExampleWindow_H_

#include "MenuWindow.h"

class ExampleWindow : public MenuWindow
{
public:
	ExampleWindow(vec2 resolution);
	~ExampleWindow();

	void Init();

private:

};

#endif // __ExampleWindow_H_