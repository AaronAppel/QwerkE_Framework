#ifndef _TestScene_H_
#define _TestScene_H_

#include "Scene.h"

class TestScene: public Scene
{
public:
	TestScene();
    virtual ~TestScene();

    void Initialize();
    void Draw();

private:
	void p_Running(double TimePassed);
};

#endif // !_TestScene_H_
