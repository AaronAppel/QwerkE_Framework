#pragma once

#include "../../Libraries/Bullet3/LinearMath/btVector3.h"
#include "../../Libraries/Bullet3/LinearMath/btAlignedObjectArray.h"

#include "../../Headers/QwerkE_Defines.h"

#ifdef qw_BULLET3
#elif qw_HAVOC
#elif qw_PHYSX
#else
#pragma error "No physics library specified!"
#endif

// TODO: Find a better spot
#define STATIC_MASS 0.0f

class btRigidBody;

namespace QwerkE {

    // TODO: Abstract from Bullet3 library
    class Physics
    {
    public:
        static void Initialize();
        static void TearDown();

        static void Tick();

        static void RegisterObject(btRigidBody* rigidBody);
        static void UnregisterObject(btRigidBody* rigidBody);

        static float GetDefaultRestitution();
        static float GetSphereRestitution();

    protected:
        Physics() {}
        ~Physics() {}

        static void LibraryInitialize();
    };

}
