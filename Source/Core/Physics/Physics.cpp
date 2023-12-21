#include "Physics.h"
#include "../Resources/Resources.h"

#include "../DataManager/ConfigHelper.h"
#include "../../Debug/Log/Log.h"

namespace QwerkE {

    void Physics::Initialize()
    {
        const ConfigData config = ConfigHelper::GetConfigData();

        if (config.systems.PhysicsEnabled)
        {
            LibraryInitialize();

            // #TODO Review GetMesh() call
            // Request shapes from Resources
            // Resources::GetMesh("Cube_UVd.obj");
        }
        else
        {
            Log::Safe("Physics is currently disabled.");
        }
    }
}
