#pragma once

#include "../../Entities/Components/Component.h"

class btRigidBody;

namespace QwerkE {

    // TODO: Change/move to b3_PhysicsComponent
    class PhysicsComponent : public Component
    {
    public:
        PhysicsComponent();
        ~PhysicsComponent();

    protected:
    };

}
