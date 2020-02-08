#include "Physics.h"
#include "../../QwerkE_Common/Libraries/Bullet3/BulletCollision/BroadphaseCollision/btAxisSweep3.h"
#include "../../QwerkE_Common/Libraries/Bullet3/BulletDynamics/Character/btCharacterControllerInterface.h"
#include "../../QwerkE_Common/Libraries/Bullet3/LinearMath/btAabbUtil2.h"

namespace QwerkE {

    Physics::Physics()
    {
        ConsolePrint("\nPhysics loaded successfully\n\n");
    }

    Physics::~Physics()
    {
    }

}
