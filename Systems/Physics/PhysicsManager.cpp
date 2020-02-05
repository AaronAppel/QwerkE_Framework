#include "PhysicsManager.h"
#include "../../QwerkE_Common/Libraries/Bullet3/BulletCollision/BroadphaseCollision/btAxisSweep3.h"
#include "../../QwerkE_Common/Libraries/Bullet3/BulletDynamics/Character/btCharacterControllerInterface.h"
#include "../../QwerkE_Common/Libraries/Bullet3/LinearMath/btAabbUtil2.h"

namespace QwerkE {

    PhysicsManager::PhysicsManager()
    {
        ConsolePrint("\nPhysicsManager loaded successfully\n\n");
    }

    PhysicsManager::~PhysicsManager()
    {
    }

}
