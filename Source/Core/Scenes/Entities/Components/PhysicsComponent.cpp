#include "../../../../Headers/QwerkE_Enums.h"
#include "../../Entities/Components/PhysicsComponent.h"
#include "../../Entities/Components/Component.h"

#pragma warning( disable : 26495 )
#pragma warning( disable : 4099 )
#include "../../Libraries/Bullet3/BulletCollision/BroadphaseCollision/btAxisSweep3.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btCollisionShape.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btSphereShape.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btBox2dShape.h"

#include "../../Libraries/Bullet3/BulletDynamics/Character/btCharacterControllerInterface.h"
#include "../../Libraries/Bullet3/BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "../../Libraries/Bullet3/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "../../Libraries/Bullet3/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"

#include "../../Libraries/Bullet3/LinearMath/btAabbUtil2.h"
#include "../../Libraries/Bullet3/LinearMath/btScalar.h"
#include "../../Libraries/Bullet3/LinearMath/btVector3.h"
#include "../../Libraries/Bullet3/LinearMath/btDefaultMotionState.h"
#pragma warning( default : 26495 )
#pragma warning( default : 4099 )

namespace QwerkE {

    PhysicsComponent::PhysicsComponent()
    {
        m_ComponentTag = Component_Physics;
    }

    PhysicsComponent::~PhysicsComponent()
    {
    }

}
