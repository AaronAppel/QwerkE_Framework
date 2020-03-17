#include "Physics.h"
#include "Systems/Resources/Resources.h"

namespace QwerkE {

    void Physics::Initialize()
    {
        ConfigData config = ConfigHelper::GetConfigData();
        
        if (config.systems.PhysicsEnabled)
        {
            LibraryInitialize();

            // Request shapes from Resources
            Resources::GetMesh("Cube_UVd.obj");
        }
        else
        {
            Log::Info("Physics is currently disabled.");
        }
    }
}
