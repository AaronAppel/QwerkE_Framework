#pragma once

#include "Scene.h"

namespace QwerkE {

    class TestScene : public Scene
    {
    public:
        TestScene();
        virtual ~TestScene();

        void Initialize();

    private:
        void p_Running(double TimePassed);
    };

}
