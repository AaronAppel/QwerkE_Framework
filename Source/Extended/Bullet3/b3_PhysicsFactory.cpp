#include "b3_PhysicsFactory.h"
#include "../../Core/Physics/Physics.h"

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

    btRigidBody* PhysicsFactory::CreateRigidSphere(btVector3 origin, float radius, float mass)
    {
        btCollisionShape* shape = new btSphereShape(btScalar(radius));
        return CreateRigidBody(origin, shape, mass);
    }

    btRigidBody* PhysicsFactory::CreateRigidPlane(btVector3 origin, float width, float length, float mass)
    {
        // TODO: Where is the plane width/height set?
        btCollisionShape* shape = new btStaticPlaneShape(btVector3(0, 1, 0), 0); // TODO: Hard coded default value
        return CreateRigidBody(origin, shape, mass);
    }

    btRigidBody* PhysicsFactory::CreateRigidCube(btVector3 origin, float width, float height, float depth, float mass)
    {
        btCollisionShape* shape = new btBoxShape(btVector3(width / 2.0, height / 2.0, depth / 2.0));
        return CreateRigidBody(origin, shape, mass);
    }

    btRigidBody* PhysicsFactory::CreateRigidCylinder(btVector3 origin, float radius, float height, float mass)
    {
        btCollisionShape* shape = new btCylinderShape(btVector3(radius / 2.0, height / 2.0, radius / 2.0));
        return CreateRigidBody(origin, shape, mass);
    }

    btRigidBody* PhysicsFactory::PhysicsFactory::CreateRigidCone(btVector3 origin, float radius, float height, float mass)
    {
        btCollisionShape* shape = new btConeShape(radius, height);
        return CreateRigidBody(origin, shape, mass);
    }

    btRigidBody* PhysicsFactory::CreateRigidBody(btVector3 origin, btCollisionShape* shape, float mass)
    {
        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(origin);

        btVector3 localInertia(0, 0, 0); // TODO: Currently a hard coded default value
        btScalar massScalar(mass);

        btDefaultMotionState* motionState = new btDefaultMotionState(startTransform); // TODO: Use btMotionState?
        if (massScalar != STATIC_MASS)
            shape->calculateLocalInertia(massScalar, localInertia);

        btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(massScalar, motionState, shape, localInertia);

        return new btRigidBody(info);
    }

}