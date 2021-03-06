#include "PBR_Test1.h"
#include "../../Headers/QwerkE_Enums.h"
#include "../DataManager/DataManager.h"
#include "../Scenes/Entities/GameObject.h"
#include "../Factory/Factory.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Mesh/MeshFactory.h"
#include "../Graphics/Shader/ShaderProgram.h"
#include "../Resources/Resources.h"

namespace QwerkE {

    PBR_Test1::PBR_Test1()
    {
        m_ID = (eSceneTypes::Scene_PBR_Test1);
        m_LevelFileName = "PBR_Test1.qscene";
    }

    PBR_Test1::~PBR_Test1()
    {
    }

    void PBR_Test1::Initialize()
    {
        // load shaders to make them available at launch
        Resources::GetShaderProgram("PBR1.ssch");
        // t_pResources->GetShaderProgram("test_normal.ssch");

        // Create cameras
        Factory::CreateFreeCamera(this, vec3(2, 0, -15))->SetRotation(vec3(0, 45, 0));
        Scene::SetupCameras();
        
        // Create objects
        for (int i = 0; i < 10; i++)
        {
            Factory::CreateCube(this, vec3(i - 5, i - 5, i));
            Factory::CreateSphere(this, vec3(i - 5, i - 5, i));
        }

        GameObject* plane = Factory::CreatePlane(this, vec3(0, 0, 20));
        plane->SetScale(vec3(10, 10, 10));
        plane->SetRotation(vec3(90, 0, 0));

        m_Subjects.push_back(Factory::CreateCube(this, vec3(0, 0, -5)));
        Factory::CreatePlane(this, vec3(2, 0, -5))->SetRotation(vec3(90, 0, 0));
        m_Subjects.push_back(Factory::CreateSphere(this, vec3(-2, 0, -5)));

        // Create lights
        Factory::CreateLight(this, vec3(10, 5, -10));
    }

    void PBR_Test1::p_Running(double deltatime)
    {
        for (size_t i = 0; i < m_Subjects.size(); i++)
        {
            m_Subjects[i]->SetRotation(vec3(m_Subjects[i]->GetRotation().x,
                (float)m_Subjects[i]->GetRotation().y + 45.0 * deltatime,
                m_Subjects[i]->GetRotation().z));

            if (m_Subjects[i]->GetRotation().y >= 360.0f)
                m_Subjects[i]->SetRotation(vec3(m_Subjects[i]->GetRotation().x, m_Subjects[i]->GetRotation().y - 360.0f, m_Subjects[i]->GetRotation().z));

        }
        Scene::p_Running(deltatime);
    }

}
