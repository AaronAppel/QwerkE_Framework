#pragma once

#include "Scene.h"

namespace QwerkE {

    class TestScene : public Scene
    {
    public:
        TestScene();
        virtual ~TestScene();

        void Update(float deltaTime);

        void Initialize();
    };

}
