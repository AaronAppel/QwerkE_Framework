#include "ViewerScene.h"

#include "../Resources/Resources.h"
#include "../Factory/Factory.h"

namespace QwerkE {

    ViewerScene::ViewerScene()
    {
        m_ID = eSceneTypes::Scene_ViewerScene;
        m_LevelFileName = "ViewerScene.qscene";
    }

    void ViewerScene::Initialize()
    {
        Factory::CreateFreeCamera(this, vec3(0, 0, 5));
        Scene::SetupCameras();

        Factory::CreateLight(this, vec3(0, 5, -10));
    }

}
