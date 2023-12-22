#pragma once

#include "Scene.h"

namespace QwerkE {

    class PBR_Test1 : public Scene
    {
    public:
        PBR_Test1();
        virtual ~PBR_Test1();

        void Initialize();

    private:
        void p_Running(double TimePassed);
        std::vector<GameObject*> m_Subjects;
    };

}
