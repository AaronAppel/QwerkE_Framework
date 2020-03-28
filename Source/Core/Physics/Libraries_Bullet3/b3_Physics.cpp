#include "../Physics.h"
#include "b3_PhysicsFactory.h"

#ifdef qw_BULLET3
#include "../../../Debug/Profiler/Profiler.h"

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

// NOTE : Following example code copied from Ciro Santilli : https://stackoverflow.com/questions/11175694/bullet-physics-simplest-collision-example
#define PRINTF_FLOAT "%7.3f"

namespace QwerkE {

    void TickCallback(btDynamicsWorld* dynamicsWorld, btScalar timeStep);

    void Loop();

    std::vector<btVector3> g_Collisions;

    const float g_Gravity = -10.0f;
    const float g_InitialY = 10.0f;
    const float g_TimeStep = 1.0f / 144.0f;
    // TODO some combinations of coefficients smaller than 1.0
    // make the ball go up higher / not lose height. Why?
    const float g_GroundRestitution = 0.9f;
    const float g_SphereRestitution = 0.9f;
    const int g_MaxNPoints = 500;

    btDefaultCollisionConfiguration* g_CollisionConfiguration = nullptr;
    btCollisionDispatcher* g_Dispatcher = nullptr;
    btBroadphaseInterface* g_OverlappingPairCache = nullptr; // NOTE: Quad tree structure stroing object positions
    btSequentialImpulseConstraintSolver* g_Solver = nullptr;
    // btConstraintSolver
    btDiscreteDynamicsWorld* g_DynamicsWorld = nullptr; // TODO: Support multiple physics worls for many active scenes
    btAlignedObjectArray<btCollisionShape*> g_CollisionShapes;

    void Physics::LibraryInitialize()
    {
        // TODO: Safe ? : TearDown();
        g_CollisionConfiguration = new btDefaultCollisionConfiguration();
        g_Dispatcher = new btCollisionDispatcher(g_CollisionConfiguration);
        g_OverlappingPairCache = new btDbvtBroadphase();
        g_Solver = new btSequentialImpulseConstraintSolver;
        g_DynamicsWorld = new btDiscreteDynamicsWorld(g_Dispatcher, g_OverlappingPairCache, g_Solver, g_CollisionConfiguration);

        g_DynamicsWorld->setGravity(btVector3(0, g_Gravity, 0));
        g_DynamicsWorld->setInternalTickCallback(TickCallback);

        // TESTING
        btRigidBody* body = PhysicsFactory::CreateRigidPlane(btVector3(0, 0, 0), 100.0f, 100.0f, 0.0f);
        body->setRestitution(g_GroundRestitution);
        RegisterObject(body);
        //

        // RegisterObject(CreateRigidSphere(btVector3(0, g_InitialY, 0), 1.0f, STATIC_MASS));

        LOG_INFO("Physics system initialized successfully");
    }

    void Physics::TearDown()
    {
        const btCollisionObjectArray& objArray = g_DynamicsWorld->getCollisionObjectArray();
        int numObjects = g_DynamicsWorld->getNumCollisionObjects();

        for (int i = numObjects - 1; i >= 0; --i)
        {   
            btRigidBody* body = btRigidBody::upcast(objArray[i]);
            g_DynamicsWorld->removeCollisionObject(body);

            if (body != nullptr)
            {
                if (body->getCollisionShape()) {
                    delete body->getCollisionShape();
                }

                if (body->getMotionState()) {
                    delete body->getMotionState();
                }
            }

            delete body;
        }

        delete g_Dispatcher;
        delete g_Solver;
        delete g_CollisionConfiguration;
        delete g_OverlappingPairCache;
        delete g_DynamicsWorld;
        g_CollisionShapes.clear();
    }

    void Physics::Tick()
    {
        PROFILE_SCOPE("Physics Step");
        g_DynamicsWorld->stepSimulation(g_TimeStep);
    }

    void Physics::RegisterObject(btRigidBody* rigidBody)
    {
        // TODO: Error handling
        g_CollisionShapes.push_back(rigidBody->getCollisionShape());
        g_DynamicsWorld->addRigidBody(rigidBody);
    }

    void Physics::UnregisterObject(btRigidBody* rigidBody)
    {
        // TODO: Error handling
        g_CollisionShapes.remove(rigidBody->getCollisionShape());
        g_DynamicsWorld->removeRigidBody(rigidBody);
    }

    float Physics::GetDefaultRestitution()
    {
        return g_GroundRestitution;
    }

    float Physics::GetSphereRestitution()
    {
        return g_SphereRestitution;
    }

    void TickCallback(btDynamicsWorld* dynamicsWorld, btScalar timeStep)
    {
        g_Collisions.clear();

        int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();

        for (int i = 0; i < numManifolds; i++) {
            btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
            // TODO those are unused. What can be done with them?
            // I think they are the same objects as those in the main loop
            // dynamicsWorld->getCollisionObjectArray() and we could compare
            // the pointers to see which object collided with which.
            {
                const btCollisionObject* objA = contactManifold->getBody0();
                const btCollisionObject* objB = contactManifold->getBody1();
            }

            int numContacts = contactManifold->getNumContacts();

            for (int j = 0; j < numContacts; j++) {
                btManifoldPoint& pt = contactManifold->getContactPoint(j);
                const btVector3& ptA = pt.getPositionWorldOnA();
                const btVector3& ptB = pt.getPositionWorldOnB();
                const btVector3& normalOnB = pt.m_normalWorldOnB;
                g_Collisions.push_back(ptA);
                g_Collisions.push_back(ptB);
                g_Collisions.push_back(normalOnB);
            }
        }
    }

    bool CollisionCallBack(btManifoldPoint& cp, const btCollisionObject* obj1, int id1, int index1, const btCollisionObject* obj2, int id2, int index2)
    {

        return false;
    }

    void Loop()
    {
        // Main loop.
        std::printf("step body x y z collision a b normal\n");

        for (int i = 0; i < g_MaxNPoints; ++i) {
            g_DynamicsWorld->stepSimulation(g_TimeStep);

            for (int j = g_DynamicsWorld->getNumCollisionObjects() - 1; j >= 0; --j) {

                btCollisionObject* obj = g_DynamicsWorld->getCollisionObjectArray()[j];
                btRigidBody* body = btRigidBody::upcast(obj);
                btTransform trans;

                if (body && body->getMotionState()) {
                    body->getMotionState()->getWorldTransform(trans);
                }
                else {
                    trans = obj->getWorldTransform();
                }

                btVector3 origin = trans.getOrigin();
                std::printf("%d %d " PRINTF_FLOAT " " PRINTF_FLOAT " " PRINTF_FLOAT " ",
                    i,
                    j,
                    float(origin.getX()),
                    float(origin.getY()),
                    float(origin.getZ()));

                if (g_Collisions.empty()) {
                    std::printf("0 ");
                }
                else {
                    std::printf("1 ");
                    // Yes, this is getting reprinted for all bodies when collisions happen.
                    // It's just a quick and dirty way to visualize it, should be outside
                    // of this loop normally.
                    for (auto& v : g_Collisions) {
                        std::printf(
                            PRINTF_FLOAT " " PRINTF_FLOAT " " PRINTF_FLOAT " ",
                            v.getX(), v.getY(), v.getZ());
                    }
                }

                puts("");
            }
        }
    }

}
#endif // qw_BULLET3