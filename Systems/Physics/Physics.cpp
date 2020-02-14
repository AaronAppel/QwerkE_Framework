#include "Physics.h"
#pragma warning( disable : 26495 )
#pragma warning( disable : 4099 )
#include "../../Libraries/Bullet3/BulletCollision/BroadphaseCollision/btAxisSweep3.h"
#include "../../Libraries/Bullet3/BulletDynamics/Character/btCharacterControllerInterface.h"
#include "../../Libraries/Bullet3/LinearMath/btAabbUtil2.h"
#pragma warning( enable : 26495 )
#pragma warning( enable : 4099 )

namespace QwerkE {

    Physics::Physics()
    {
        ConsolePrint("\nPhysics loaded successfully");
    }

    Physics::~Physics()
    {
    }

}
