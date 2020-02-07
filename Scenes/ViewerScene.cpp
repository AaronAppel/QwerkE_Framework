#include "ViewerScene.h"
#include "../Systems/Services.h"
#include "../Systems/Resources/Resources.h"
#include "../Systems/Factory/Factory.h"

namespace QwerkE {

    ViewerScene::ViewerScene()
    {
        m_ID = eSceneTypes::Scene_ViewerScene;
        m_LevelFileName = "ViewerScene.qscene";
    }

    ViewerScene::~ViewerScene()
    {
    }

    void ViewerScene::Initialize()
    {
        // Cameras
        Factory::CreateFreeCamera(this, vec3(0, 0, 5));
        Scene::SetupCameras();

        // Lights
        Factory::CreateLight(this, vec3(0, 5, -10));

        // Actors
        // none. Add one and use it to take thumbnail pictures for assets
    }

    void ViewerScene::p_Update(double TimePassed)
    {
        Scene::p_Running(TimePassed);
    }

}
