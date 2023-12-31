#pragma once

#include <vector>

#include "Scene.h"

namespace QwerkE {

    class PBR_Test1 : public Scene
    {
    public:
        PBR_Test1();
        ~PBR_Test1() = default;

        void Update(float deltatime) override;

        void Initialize() override;

    private:
        std::vector<GameObject*> m_Subjects;
    };

}
