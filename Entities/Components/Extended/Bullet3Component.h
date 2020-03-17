#ifndef _Bullet3Component_H_
#define _Bullet3Component_H_

#include "../../Entities/Components/Component.h"
#include "../../Entities/Components/PhysicsComponent.h"
#include "../../Entities/GameObject.h"
#include "../../Libraries/Bullet3/LinearMath/btMotionState.h"
#include "../../Libraries/Bullet3/LinearMath/btTransform.h"

class btRigidBody;

namespace QwerkE {

    class Bullet3Component : public PhysicsComponent, public btMotionState
    {
    public:
        Bullet3Component(btRigidBody* rigidBody);
        ~Bullet3Component();

        void ApplyForce(vec3 force);
        void ApplyTorque(vec3 force);
        
        /* Getters + Setters */
        // getters
        void getWorldTransform(btTransform& worldTrans) const;
        vec3 GetBodyPosition();
        vec3 GetBodyRotation();

        // setters
        void setWorldTransform(const btTransform& worldTrans);

    private:
        btRigidBody* m_Body;
    };

}
#endif // _Bullet3Component_H_
