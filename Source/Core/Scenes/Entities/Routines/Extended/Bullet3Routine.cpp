#include "Bullet3Routine.h"
#include "../../Components/Extended/Bullet3Component.h"

#pragma warning( disable : 26495 )
#pragma warning( disable : 4099 )
#include "../../Libraries/Bullet3/BulletCollision/BroadphaseCollision/btAxisSweep3.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"

#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btCollisionShape.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btSphereShape.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btBoxShape.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btCylinderShape.h"
#include "../../Libraries/Bullet3/BulletCollision/CollisionShapes/btConeShape.h"

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
    
    Bullet3Routine::Bullet3Routine() :
        m_bulletComponent(nullptr)
    {
        m_Type = eRoutineTypes::Routine_Render;
    }

    Bullet3Routine::~Bullet3Routine()
    {
    }

    void Bullet3Routine::Initialize()
    {
        m_pParent->AddUpdateRoutine(this);
        m_bulletComponent = (Bullet3Component*)m_pParent->GetComponent(eComponentTags::Component_Physics);
    }

    void Bullet3Routine::Update(double a_Deltatime)
    {
        m_pParent->SetPosition(m_bulletComponent->GetBodyPosition());
        m_pParent->SetRotation(m_bulletComponent->GetBodyRotation());
    }

}
