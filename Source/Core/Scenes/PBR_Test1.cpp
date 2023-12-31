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

    void PBR_Test1::Initialize()
    {
        // Load assets into Resources
        Resources::GetShaderProgram("PBR1.ssch");
        // Resources::GetShaderProgram("test_normal.ssch");

        Factory::CreateFreeCamera(this, vec3(2, 0, -15))->SetRotation(vec3(0, 45, 0));
        Scene::SetupCameras();

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

        Factory::CreateLight(this, vec3(10, 5, -10));
    }

    void PBR_Test1::Update(float deltatime)
    {
        for (size_t i = 0; i < m_Subjects.size(); i++)
        {
            const vec3 rotation = vec3(m_Subjects[i]->GetRotation().x, (float)m_Subjects[i]->GetRotation().y + 45.0f * (float)deltatime, m_Subjects[i]->GetRotation().z);
            m_Subjects[i]->SetRotation(rotation);

            if (m_Subjects[i]->GetRotation().y >= 360.0f) // #TODO What about < 0?
            {
                // #TODO Improve logic and variable naming
                const vec3 rotation2 = vec3(vec3(m_Subjects[i]->GetRotation().x, m_Subjects[i]->GetRotation().y - 360.0f, m_Subjects[i]->GetRotation().z));
                m_Subjects[i]->SetRotation(rotation2);
            }

        }
    }

}
