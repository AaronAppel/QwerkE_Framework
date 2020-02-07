#include "Scene.h"
#include "../Entities/GameObject.h"
#include "../Entities/Components/Component.h"
#include "../Entities/Components/Camera/CameraComponent.h"
#include "../Systems/Input/Input.h"
#include "../Systems/DataManager/DataManager.h"
#include "../Systems/Services.h"
#include "../../QwerkE_Common/Utilities/StringHelpers.h"

#include <algorithm>

extern int g_WindowWidth;
extern int g_WindowHeight;

namespace QwerkE {

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
        int size = m_LightList.size();
        for (int i = size - 1; i > -1; i--)
        {
            delete m_LightList.at(i);
        }
        m_LightList.clear();

        size = m_CameraList.size();
        for (int i = size - 1; i > -1; i--)
        {
            delete m_CameraList.at(i);
        }
        m_CameraList.clear();

        for (auto object : m_pGameObjects)
        {
            delete object.second;
        }
        m_pGameObjects.clear();
    }

    void Scene::Initialize()
    {
        //m_pViewMatrix->CreateLookAtViewLeftHanded(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 0, 0));
    }

    void Scene::OnWindowResize(unsigned int width, unsigned int height)
    {
        // update camera view and projection matrices
        for (int i = 0; i < m_CameraList.size(); i++)
        {
            // ((CameraComponent*)m_CameraList.At(i)->GetComponent(Component_Camera))->Setup();
            ((CameraComponent*)m_CameraList.at(i)->GetComponent(Component_Camera))->SetViewportSize(vec2((float)width, (float)height));
        }
    }

    void Scene::ResetScene()
    {
    }

    void Scene::p_Running(double deltatime)
    {
        Input* input = (Input*)Services::GetService(eEngineServices::Input_Manager);

        CameraComponent* t_activecamera = ((CameraComponent*)m_CameraList.at(m_CurrentCamera)->GetComponent(Component_Camera));
        // temporary active camera control
        // mouse
        {
            //vec2 t_mousedelta = t_controller->getmouseposdelta();
            //t_activecamera->processmousemovement(t_mousedelta.x, t_mousedelta.y);
            //// m_zoom
            //t_activecamera->processmousescroll(t_controller->getmousescrolldelta());
        }

        // keyboard
        CameraInput(deltatime);

        // update all of the Scene objects in the list.
        for (auto object : m_pGameObjects)
        {
            object.second->Update(deltatime);
        }
    }

    void Scene::p_Frozen(double deltatime)
    {
        CameraInput(deltatime);
    }

    void Scene::p_SlowMotion(double deltatime)
    {
        p_Running(deltatime * 0.10);

        // TODO: Create animation functionality
        // for (auto object : m_pGameObjects)
        {
            // AnimationComponent* aComp (()object.second->GetComponent(Component_Animation));
            // if (aComp)
            // aComp->Animate();
        }
    }

    void Scene::p_Animating(double deltatime)
    {
        CameraInput(deltatime);

        // TODO: Create animation functionality
        // for (auto object : m_pGameObjects)
        {
            // AnimationComponent* aComp (()object.second->GetComponent(Component_Animation));
            // if (aComp)
                // aComp->Animate();
        }
    }

    void Scene::CameraInput(double deltatime) // camera control
    {
        Input* input = (Input*)Services::GetService(eEngineServices::Input_Manager);
        CameraComponent* t_activecamera = ((CameraComponent*)m_CameraList.at(m_CurrentCamera)->GetComponent(Component_Camera));

        if (input->GetIsKeyDown(eKeys::eKeys_W))
        {
            t_activecamera->ProcessKeyboard(eCamera_Movement::FORWARD, (float)deltatime);
        }
        if (input->GetIsKeyDown(eKeys::eKeys_S))
        {
            t_activecamera->ProcessKeyboard(eCamera_Movement::BACKWARD, (float)deltatime);
        }
        if (input->GetIsKeyDown(eKeys::eKeys_A))
        {
            t_activecamera->ProcessKeyboard(eCamera_Movement::LEFT, (float)deltatime);
        }
        if (input->GetIsKeyDown(eKeys::eKeys_D))
        {
            t_activecamera->ProcessKeyboard(eCamera_Movement::RIGHT, (float)deltatime);
        }
        if (input->GetIsKeyDown(eKeys::eKeys_Q))
        {
            t_activecamera->ProcessKeyboard(eCamera_Movement::DOWN, (float)deltatime);
        }
        if (input->GetIsKeyDown(eKeys::eKeys_E))
        {
            t_activecamera->ProcessKeyboard(eCamera_Movement::UP, (float)deltatime);
        }
        if (input->GetIsKeyDown(eKeys::eKeys_T))
        {
            t_activecamera->ProcessKeyboard(eCamera_Movement::RROTATE, (float)deltatime);
        }
        if (input->GetIsKeyDown(eKeys::eKeys_R))
        {
            t_activecamera->ProcessKeyboard(eCamera_Movement::LROTATE, (float)deltatime);
        }
    }

    void Scene::Draw()
    {
        // TODO:: Define draw behaviour (Highest first vs lowest first)
        GameObject* camera = m_CameraList.at(m_CurrentCamera);
        for (int i = m_SceneDrawList.size() - 1; i >= 0; i--)
        {
            m_SceneDrawList.at(i)->Draw(camera); // TODO:: Control render order
        }
    }

    bool Scene::AddCamera(GameObject* camera)
    {
        if (camera) // TODO: What conditions would prevent camera insertion?
        {
            m_CameraList.push_back(camera);
            return true;
        }
        return false;
    }

    void Scene::RemoveCamera(GameObject* camera)
    {
        if (m_CameraList.size() < 2) { return; } // Need 1 camera
        for (int i = 0; i < m_CameraList.size(); i++)
        {
            if (m_CameraList.at(i) == camera) // Pointer comparison
            {
                m_CameraList.erase(m_CameraList.begin() + i);
                // Delete
                return;
            }
        }
    }

    void Scene::SetupCameras()
    {
        for (int i = 0; i < m_CameraList.size(); i++)
        {
            ((CameraComponent*)m_CameraList.at(i)->GetComponent(Component_Camera))->Setup();
            ((CameraComponent*)m_CameraList.at(i)->GetComponent(Component_Camera))->SetTargetPosition(vec3(0, 0, 0)); // Give initial target location
        }
    }

    bool Scene::AddLight(GameObject* light)
    {
        if (true) // TODO: What conditions would prevent light insertion?
        {
            m_LightList.push_back(light);
            m_SceneDrawList.push_back(light);
            return true;
        }
        return false;
    }
    void Scene::RemoveLight(GameObject* light)
    {
        if (m_LightList.size() < 2) { return; }
        for (int i = 0; i < m_LightList.size(); i++)
        {
            if (m_LightList.at(i) == light) // Pointer comparison
            {
                m_LightList.erase(m_LightList.begin() + i);
                m_SceneDrawList.erase(m_SceneDrawList.begin() + i); // Lights are drawn
                // TODO: Deallocate memory
                return;
            }
        }
    }

    void Scene::SetupLights()
    {
        for (int i = 0; i < m_LightList.size(); i++)
        {
            // TODO:
        }
    }

    bool Scene::AddObjectToScene(GameObject* object)
    {
        if (object)
            if (m_pGameObjects.find(object->GetName()) == m_pGameObjects.end())
            {
                m_pGameObjects[object->GetName()] = object;
                // TODO: Sort by draw order
                m_SceneDrawList.push_back(object);
                return true; // Success
            }
        return false; // Failure
    }

    void Scene::RemoveObjectFromScene(GameObject* object)
    {
        // TODO: Fix implementation
        // Check object tag
        if (m_pGameObjects.find(object->GetName().c_str()) != m_pGameObjects.end())
        {
            // exists?
            if (object->GetTag() == eGameObjectTags::GO_Tag_Player)
            {
                // Player specific
            }

            std::vector<GameObject*>::iterator it = m_SceneDrawList.begin();
            m_SceneDrawList.erase(std::remove(m_SceneDrawList.begin(), m_SceneDrawList.end(), object), m_SceneDrawList.end());

            m_pGameObjects.erase(object->GetName());
            // TODO: Push object into a pool to be deleted at an appropriate time.
            // Object may be owned externally and should not always be deleted by the scene.
            delete object; // TODO:: Should deletion be handled differently?
        }
    }

    void Scene::RemoveAllObjectsFromScene()
    {
        m_LightList.clear();
        m_CameraList.clear();
        m_pGameObjects.clear();
    }

    // Setters
    void Scene::SetState(eSceneState newState)
    {
        switch (newState)
        {
        case eSceneState::SceneState_Running:
            m_UpdateFunc = &Scene::p_Running;
            m_State = eSceneState::SceneState_Running;
            break;
        case eSceneState::SceneState_Frozen:
            m_UpdateFunc = &Scene::p_Frozen;
            m_State = eSceneState::SceneState_Frozen;
            break;
        case eSceneState::SceneState_Paused:
            m_UpdateFunc = &Scene::p_Paused;
            m_State = eSceneState::SceneState_Paused;
            break;
        case eSceneState::SceneState_SlowMo:
            m_UpdateFunc = &Scene::p_SlowMotion;
            m_State = eSceneState::SceneState_SlowMo;
            break;
        case eSceneState::SceneState_Animating:
            m_UpdateFunc = &Scene::p_Animating;
            m_State = eSceneState::SceneState_Animating;
            break;
        }
    }

    void Scene::SaveScene()
    {
        if (m_LevelFileName == gc_DefaultCharPtrValue)
        {
            QwerkE::LogError(__FILE__, __LINE__, "Unable to Save scene! m_LevelFileName is \"%s\"", gc_DefaultCharPtrValue);
            return;
        }

        DataManager* t_pDataManager = (DataManager*)QwerkE::Services::GetService(eEngineServices::Data_Manager);
        t_pDataManager->SaveScene(this, SceneFolderPath(m_LevelFileName.c_str()));
    }

    void Scene::LoadScene(const char* sceneFileName)
    {
        if (sceneFileName == gc_DefaultCharPtrValue)
        {
            QwerkE::LogError(__FILE__, __LINE__, "Unable to Save scene! sceneFileName is \"%s\"", gc_DefaultCharPtrValue);
            return;
        }
        m_LevelFileName = sceneFileName;

        DataManager* t_pDataManager = (DataManager*)QwerkE::Services::GetService(eEngineServices::Data_Manager);
        t_pDataManager->LoadScene(this, SceneFolderPath(m_LevelFileName.c_str()));
        SetupCameras();
    }

    void Scene::ReloadScene()
    {
        if (m_LevelFileName == gc_DefaultCharPtrValue)
        {
            QwerkE::LogError(__FILE__, __LINE__, "Unable to Save scene! m_LevelFileName is \"%s\"", gc_DefaultCharPtrValue);
            return;
        }

        DataManager* t_pDataManager = (DataManager*)QwerkE::Services::GetService(eEngineServices::Data_Manager);
        t_pDataManager->LoadScene(this, SceneFolderPath(m_LevelFileName.c_str()));
        SetupCameras();
    }

    GameObject* Scene::GetGameObject(const char* name)
    {
        if (m_pGameObjects.find(name) != m_pGameObjects.end())
            return m_pGameObjects[name];

        return nullptr;
    }

}
