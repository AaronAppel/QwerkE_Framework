#pragma once

#include "Scene.h"

namespace QwerkE {

    class ViewerScene : public Scene
    {
    public:
        ViewerScene();
        ~ViewerScene();

        void Initialize();

    private:
        void p_Update(double TimePassed);
    };

}
