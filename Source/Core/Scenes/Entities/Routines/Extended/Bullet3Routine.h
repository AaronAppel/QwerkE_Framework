#pragma once

#include "../../Routines/Routine.h"

namespace QwerkE {

	class Bullet3Component;

	class Bullet3Routine : public Routine
	{
	public:
		Bullet3Routine();
        ~Bullet3Routine();

        void Initialize();

        void Update(double a_Deltatime);

	private:
		Bullet3Component* m_bulletComponent;
	};

}
