#ifndef _PhysicsWorld_H_
#define _PhysicsWorld_H_

#include "Libraries/Bullet3/LinearMath/btAlignedObjectArray.h"

class btDiscreteDynamicsWorld;
class btCollisionShape;
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;

// Should I make an abstract class that can be swapped
// when using Box2D/Bulet/PhysX depending on platform.
class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void CreateWorld();
	void Update(float deltatime);
	void Cleanup();

	btDiscreteDynamicsWorld* GetDynamicsWorld() { return m_pDynamicsWorld; }
	void AddShape(btCollisionShape* pShape) { m_CollisionShapes.push_back(pShape); }
	btCollisionShape* GetShape(int index) { if (index <= m_CollisionShapes.size()) return 0; return m_CollisionShapes[index]; }

protected:
	btBroadphaseInterface * m_pBroadphase;
	btDefaultCollisionConfiguration* m_pCollisionConfiguration;
	btCollisionDispatcher* m_pDispatcher;
	btSequentialImpulseConstraintSolver* m_pSolver;
	btDiscreteDynamicsWorld* m_pDynamicsWorld;

	// Keep track of the shapes, we release memory at exit.
	// Make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> m_CollisionShapes;
};

#endif // !_PhysicsWorld_H_
