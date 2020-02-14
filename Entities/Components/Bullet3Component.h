#ifndef _Bullet3Component_H_
#define _Bullet3Component_H_

#include "../../Entities/Components/Component.h"
#include "../../Entities/Components/PhysicsComponent.h"
#include "../../Entities/GameObject.h"
#include "../../Libraries/Bullet3/LinearMath/btMotionState.h"

namespace QwerkE {

    class Bullet3Component : public PhysicsComponent, public btMotionState
    {
    public:
        Bullet3Component();
        ~Bullet3Component();

        // btMotionState interface
        void getWorldTransform(btTransform& worldTrans) const;

        //Bullet only calls the update of worldtransform for active objects
        void setWorldTransform(const btTransform& worldTrans);

        /* Getters + Setters */
        // getters

        // setters

    private:
    };

}
#endif //!_Bullet3Component_H_
