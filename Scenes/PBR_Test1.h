#ifndef _PBR_Test1_H_
#define _PBR_Test1_H_

#include "Scene.h"

class PBR_Test1: public Scene
{
public:
	PBR_Test1();
    virtual ~PBR_Test1();

    void Initialize();

private:
	void p_Running(double TimePassed);
	std::vector<GameObject*> m_Subjects;
};

#endif // !_PBR_Test1_H_
