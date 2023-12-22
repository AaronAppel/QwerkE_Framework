#pragma once

#include "../../Libraries/Bullet3/LinearMath/btMotionState.h"
#include "../../Libraries/Bullet3/LinearMath/btTransform.h"

#include "../../Components/Component.h"
#include "../../Components/PhysicsComponent.h"
#include "../../GameObject.h"

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
