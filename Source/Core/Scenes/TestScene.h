#ifndef _TestScene_H_
#define _TestScene_H_

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
#endif // !_TestScene_H_
