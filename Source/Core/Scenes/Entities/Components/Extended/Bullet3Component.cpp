#include "Bullet3Component.h"

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

#include "../../../../../Headers/QwerkE_Enums.h"
#include "../../../Entities/Components/PhysicsComponent.h"
#include "../../../Entities/Components/Component.h"
#include "../../../../Math/Vector.h"
#include "../../../Entities/GameObject.h"

namespace QwerkE {

	Bullet3Component::Bullet3Component(btRigidBody* rigidBody) :
		m_Body(rigidBody)
	{
		m_ComponentTag = Component_Physics;

		// Get Physics world
		// Add object to world
	}

	Bullet3Component::~Bullet3Component()
	{
	}

	void Bullet3Component::getWorldTransform(btTransform& worldTrans) const
	{
        vec3 parentPosition = m_pParent->GetPosition();
        worldTrans.setOrigin( btVector3( parentPosition.x, parentPosition.y, parentPosition.z ) );
	}

	void Bullet3Component::setWorldTransform(const btTransform& worldTrans)
    {
		m_pParent->SetPosition( { worldTrans.getRotation().getX() , worldTrans.getRotation().getY() , worldTrans.getRotation().getZ() } );
	}

	vec3 Bullet3Component::GetBodyPosition()
    {
		vec3 position;
		btTransform transform;
		m_Body->getMotionState()->getWorldTransform(transform);
		btVector3 origin = transform.getOrigin();
        position.x = origin.x();
        position.y = origin.y();
        position.z = origin.z();
        return position;
    }

    vec3 Bullet3Component::GetBodyRotation()
    {
        vec3 rotation;
        btTransform transform;
        m_Body->getMotionState()->getWorldTransform(transform);
        btVector3 origin = transform.getOrigin();
		btQuaternion quaternion = transform.getRotation();
		rotation.x = quaternion.x();
		rotation.y = quaternion.y();
		rotation.z = quaternion.z();
        return rotation;
    }

    void Bullet3Component::ApplyForce(vec3 force)
    {
        if (!m_Body->isActive())
        {
            m_Body->setActivationState(1);
        }

        btTransform transform;
		m_Body->getMotionState()->getWorldTransform(transform);

        m_Body->applyForce(btVector3(force.x, force.y, force.z), transform.getOrigin());
    }

    void Bullet3Component::ApplyTorque(vec3 force)
    {
        if (!m_Body->isActive())
        {
            m_Body->setActivationState(1);
        }

        m_Body->applyTorque(btVector3(force.x, force.y, force.z));
    }

}
