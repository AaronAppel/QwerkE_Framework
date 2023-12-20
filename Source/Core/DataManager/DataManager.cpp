#include "DataManager.h"

#include "../../Libraries/cJSON_Interface/cJSONInterface.h"

#include "../../Headers/QwerkE_File_Defines.h"

#include "../../Debug/Log/Log.h"
#include "../Factory/Factory.h"
#include "../Scenes/Entities/GameObject.h"
#include "../Scenes/Entities/Components/Camera/CameraComponent.h"
#include "../Scenes/Entities/Components/Camera/FreeCameraComponent.h"
#include "../Scenes/Entities/Components/Camera/FirstPersonCameraComponent.h"
#include "../Scenes/Entities/Components/Camera/StaticCameraComponent.h"
#include "../Scenes/Entities/Components/Camera/ThirdPersonCameraComponent.h"
#include "../Scenes/Entities/Components/LightComponent.h"
#include "../Scenes/Entities/Routines/Routine.h"
#include "../Scenes/Entities/Routines/RenderRoutine.h"
#include "../Scenes/Entities/Routines/TransformRoutine.h"
#include "../Scenes/Scene.h"

#include "../Resources/Resources.h"

// RenderComponent
#include "../Scenes/Entities/Components/RenderComponent.h"
#include "../Graphics/DataTypes/Renderable.h"
#include "../Graphics/DataTypes/Material.h"
#include "../Graphics/Shader/ShaderComponent.h"
#include "../Graphics/Shader/ShaderProgram.h"

namespace QwerkE {

    void DataManager::SaveScene(Scene* scene, const char* fileDir)
    {
        // TODO: Error checking
        cJSON* root = CreateObject();

        // Scene settings
        cJSON* t_Settings = CreateArray("Settings");
        AddItemToArray(t_Settings, CreateNumber("State", (int)scene->GetState()));
        AddItemToArray(t_Settings, CreateNumber("Enabled", scene->GetIsEnabled()));

        // Scene entities
        std::map<std::string, GameObject*> t_GameObjectList = scene->GetObjectList(); // GameObjects, Lights (Not cameras)

        cJSON* t_ObjectList = CreateArray("ObjectList");
        AddItemToRoot(root, t_ObjectList);
        std::map<std::string, GameObject*>::iterator it;
        for (it = t_GameObjectList.begin(); it != t_GameObjectList.end(); it++)
        {
            AddItemToArray(t_ObjectList, ConvertGameObjectToJSON(it->second));
        }

        // ADD CAMERAS
        std::vector<GameObject*> t_CameraObjectList = scene->GetCameraList(); // Cameras only

        cJSON* t_CameraList = CreateArray("CameraList");
        AddItemToObject(root, t_CameraList);
        for (unsigned int i = 0; i < t_CameraObjectList.size(); i++)
        {
            AddItemToArray(t_CameraList, ConvertGameObjectToJSON(t_CameraObjectList.at(i)));
        }

        // ADD LIGHTS
        std::vector<GameObject*> t_LightObjectList = scene->GetLightList(); // Cameras only

        cJSON* t_LightList = CreateArray("LightList");
        AddItemToObject(root, t_LightList);
        for (unsigned int i = 0; i < t_LightObjectList.size(); i++)
        {
            AddItemToArray(t_LightList, ConvertGameObjectToJSON(t_LightObjectList.at(i)));
        }

        // WRITE TO FILE
        PrintRootObjectToFile(fileDir, root);
        LOG_INFO("DataManager: Scene file {0} saved", fileDir);
        ClosecJSONStream(root);
    }

    void DataManager::LoadScene(Scene* scene, const char* fileDir)
    {
        if (scene == nullptr) { return; } // TODO: Load a null scene
        if (FileExists(fileDir) == false)
        {
            LOG_ERROR("DataManager: LoadScene() could not open file for reading.");
            return;
        }

        // Read scene json file
        cJSON* root = OpencJSONStream(fileDir);
        if (root == nullptr) // Compile error
        {
            LOG_ERROR("DataManager: LoadScene() null root object.");
            return;
        }

        scene->RemoveAllObjectsFromScene(); // Empty scene of objects

        // TODO: Improve below loops. A lot of copied code

        // Scene settings
        cJSON* t_Settings = GetItemFromRootByKey(root, "Settings");

        if (t_Settings != nullptr)
        {
            scene->SetState((eSceneState)((int)(GetItemFromArrayByKey(t_Settings, "State")->valuedouble)));
            scene->SetIsEnabled((bool)GetItemFromArrayByKey(t_Settings, "Enabled")->valuedouble);
        }

        // CREATE OBJECTS
        {
            cJSON* t_JSONObjectList = GetItemFromObjectByKey(root, "ObjectList");
            std::vector<cJSON*> t_GameObjects = GetAllItemsFromArray(t_JSONObjectList);

            for (unsigned int i = 0; i < t_GameObjects.size(); i++)
            {
                GameObject* t_TempObject = ConvertJSONToGameObject(t_GameObjects.at(i), scene);
                scene->AddObjectToScene(t_TempObject);
            }
        }

        // CREATE CAMERAS
        {
            cJSON* t_JSONCameraList = GetItemFromObjectByKey(root, "CameraList");
            std::vector<cJSON*> t_CameraObjects = GetAllItemsFromArray(t_JSONCameraList);

            for (unsigned int i = 0; i < t_CameraObjects.size(); i++)
            {
                GameObject* t_TempObject = ConvertJSONToGameObject(t_CameraObjects.at(i), scene);
                scene->AddCamera(t_TempObject);
            }
        }

        // CREATE LIGHTS
        {
            cJSON* t_JSONLightList = GetItemFromObjectByKey(root, "LightList");
            std::vector<cJSON*> t_LightObjects = GetAllItemsFromArray(t_JSONLightList);

            for (unsigned int i = 0; i < t_LightObjects.size(); i++)
            {
                GameObject* t_TempObject = ConvertJSONToGameObject(t_LightObjects.at(i), scene);
                scene->AddLight(t_TempObject);
            }
        }

        // END
        ClosecJSONStream(root);
        LOG_INFO("DataManager: Scene file {0} loaded", fileDir);
    }

    // Utility
    void DataManager::AddVec3ToItem(cJSON* item, const char* arrayName, const char* name1, float value1, const char* name2, float value2, const char* name3, float value3)
    {
        cJSON* vec3Array = CreateObject();
        vec3Array->string = DeepCopyString(arrayName);
        AddItemToArray(vec3Array, CreateNumber(name1, value1));
        AddItemToArray(vec3Array, CreateNumber(name2, value2));
        AddItemToArray(vec3Array, CreateNumber(name3, value3));

        AddItemToArray(item, vec3Array);
    }

    cJSON* DataManager::ConvertGameObjectToJSON(GameObject* object)
    {
        if (object == nullptr) { nullptr; }

        cJSON* t_ReturnJSON = CreateArray(object->GetName().c_str());

        // Transform
        AddPositionTocJSONItem(t_ReturnJSON, object); // Can put this in a SaveTransform() function
        AddRotationTocJSONItem(t_ReturnJSON, object);
        AddScaleTocJSONItem(t_ReturnJSON, object);

        AddItemToArray(t_ReturnJSON, CreateNumber((char*)"ObjectTag", (int)object->GetTag()));

        // Components
        AddComponentsTocJSONItem(t_ReturnJSON, object);

        // Routines
        AddRoutinesTocJSONItem(t_ReturnJSON, object);

        // Handle special cases for certain components
        switch (object->GetTag())
        {
        case GO_Tag_Player:
            break;
            // Cameras
        case GO_Tag_Camera:
            break;
            // Lights
        case GO_Tag_Light:
            break;
            // Shapes
        case GO_Tag_Cube:
            break;
        case GO_Tag_Plane:
            break;
            // Scenery
        case GO_Tag_SkyBox:
            break;
            // Test
        case GO_Tag_TestModel:
            break;
        }

        return t_ReturnJSON;
    }

    GameObject* DataManager::ConvertJSONToGameObject(cJSON* item, Scene* scene)
    {
        if (item == nullptr || scene == nullptr) { nullptr; }

        GameObject* object = new GameObject(scene);

        // Misc
        object->SetName(item->string);
        object->SetTag((eGameObjectTags)GetItemFromArrayByKey(item, "ObjectTag")->valueint);

        // Transform
        cJSON* tempObject = GetItemFromArrayByKey(item, "Position");
        vec3 position = GetPositionFromcJSONItem(tempObject);
        object->SetPosition(position);
        tempObject = GetItemFromArrayByKey(item, "Rotation");
        vec3 rotation = GetRotationFromcJSONItem(tempObject);
        object->SetRotation(rotation);
        tempObject = GetItemFromArrayByKey(item, "Scale");
        vec3 scale = GetScaleFromcJSONItem(tempObject);
        object->SetScale(scale);

        // Components
        AddComponentsToGameObject(object, item);

        // Routines
        AddRoutinesToGameObject(object, item);

        return object; // TODO: Finish
    }

    void DataManager::UpdateJSONArrayInFile(cJSON* array, const char* fileDir)
    {
        // Open file stream
        // find object and overwrite it
        // save new cJSON string to file
    }
    // Getters
    vec3 DataManager::GetPositionFromcJSONItem(cJSON* item)
    {
        vec3 Position;
        Position.x = (float)GetItemFromArrayByKey(item, "PositionX")->valuedouble;
        Position.y = (float)GetItemFromArrayByKey(item, "PositionY")->valuedouble;
        Position.z = (float)GetItemFromArrayByKey(item, "PositionZ")->valuedouble;
        return Position;
    }
    vec3 DataManager::GetRotationFromcJSONItem(cJSON* item)
    {
        vec3 Rotation;
        Rotation.x = (float)GetItemFromArrayByKey(item, "RotationX")->valuedouble;
        Rotation.y = (float)GetItemFromArrayByKey(item, "RotationY")->valuedouble;
        Rotation.z = (float)GetItemFromArrayByKey(item, "RotationZ")->valuedouble;
        return Rotation;
    }
    vec3 DataManager::GetScaleFromcJSONItem(cJSON* item)
    {
        vec3 Scale;
        Scale.x = (float)GetItemFromArrayByKey(item, "ScaleX")->valuedouble;
        Scale.y = (float)GetItemFromArrayByKey(item, "ScaleY")->valuedouble;
        Scale.z = (float)GetItemFromArrayByKey(item, "ScaleZ")->valuedouble;
        return Scale;
    }
    // TODO: Getters for data types: float vec3, etc. Not specific to names, but just per type

    // Transform
    void DataManager::AddPositionTocJSONItem(cJSON* item, GameObject* object)
    {
        cJSON* t_Position = CreateArray("Position");
        AddItemToArray(t_Position, CreateNumber((char*)"PositionX", object->GetPosition().x));
        AddItemToArray(t_Position, CreateNumber((char*)"PositionY", object->GetPosition().y));
        AddItemToArray(t_Position, CreateNumber((char*)"PositionZ", object->GetPosition().z));
        AddItemToArray(item, t_Position);
    }
    void DataManager::AddRotationTocJSONItem(cJSON* item, GameObject* object)
    {
        cJSON* t_Rotation = CreateArray("Rotation");
        AddItemToArray(t_Rotation, CreateNumber((char*)"RotationX", object->GetRotation().x));
        AddItemToArray(t_Rotation, CreateNumber((char*)"RotationY", object->GetRotation().y));
        AddItemToArray(t_Rotation, CreateNumber((char*)"RotationZ", object->GetRotation().z));
        AddItemToArray(item, t_Rotation);
    }
    void DataManager::AddScaleTocJSONItem(cJSON* item, GameObject* object)
    {
        cJSON* t_Scale = CreateArray("Scale");
        AddItemToArray(t_Scale, CreateNumber((char*)"ScaleX", object->GetScale().x));
        AddItemToArray(t_Scale, CreateNumber((char*)"ScaleY", object->GetScale().y));
        AddItemToArray(t_Scale, CreateNumber((char*)"ScaleZ", object->GetScale().z));
        AddItemToArray(item, t_Scale);
    }
    /* Components */
    void DataManager::AddComponentTocJSONItem(cJSON* componentList, const Component* component)
    {
        if (!component) return;

        cJSON* t_Component = CreateArray(std::to_string(component->GetTag()).c_str());

        switch (component->GetTag())
        {
        case Component_Camera:
        {
            AddItemToArray(t_Component, CreateString("ComponentName", "Camera"));
            eCamType camType = ((CameraComponent*)component)->GetType();
            AddItemToArray(t_Component, CreateNumber("CamType", (int)camType));
        }
        break;
        case Component_Physics:
            break;
        case Component_Light:
        {
            AddItemToArray(t_Component, CreateString("ComponentName", "Light"));
            switch (((LightComponent*)component)->GetType())
            {
            case LightType_Point:
                // AddItemToArray(t_Component, CreateNumber("LightType", (int)LightType_Point));
                // AddVec3ToItem(t_Component, "LightColour",
                //     "Red", ((LightComponent*)component)->GetColour().x,
                //     "Green", ((LightComponent*)component)->GetColour().y,
                // 	   "Blue", ((LightComponent*)component)->GetColour().z);
                break;
            case LightType_Area: // TODO: Implement other light types.
                break;
            case LightType_Spot: // TODO: Implement other light types.
                break;
            }
        }
        break;
        case Component_Controller:
            break;
        case Component_Render:
        {
            AddItemToArray(t_Component, CreateString("ComponentName", "Render"));
            AddItemToArray(t_Component, CreateString("SchematicName", ((RenderComponent*)component)->GetSchematicName().c_str()));

            cJSON* t_Renderables = CreateArray("Renderables");

            std::vector<Renderable>* renderablesList = (std::vector<Renderable>*) ((RenderComponent*)component)->LookAtRenderableList();

            for (size_t i = 0; i < renderablesList->size(); i++)
            {
                // TODO: Set the renderable names
                cJSON* renderable = CreateArray(renderablesList->at(i).GetRenderableName().c_str());

                AddItemToArray(renderable, CreateString("Shader", renderablesList->at(i).GetShaderSchematic()->GetName().c_str()));
                AddItemToArray(renderable, CreateString("Material", renderablesList->at(i).GetMaterialSchematic()->GetMaterialName().c_str()));

                if (strcmp(renderablesList->at(i).GetMesh()->GetFileName().c_str(), gc_DefaultCharPtrValue) != 0)
                    AddItemToArray(renderable, CreateString("MeshFile", renderablesList->at(i).GetMesh()->GetFileName().c_str()));
                else
                    AddItemToArray(renderable, CreateString("MeshFile", no_file));

                AddItemToArray(renderable, CreateString("MeshName", renderablesList->at(i).GetMesh()->GetName().c_str()));

                AddItemToArray(t_Renderables, renderable);
            }

            AddItemToArray(t_Component, t_Renderables);
        }
        break;
        case Component_Print:
            break;
        case Component_SkyBox:
            break;
        }
        AddItemToArray(componentList, t_Component);
    }

    void DataManager::AddComponentsTocJSONItem(cJSON* item, GameObject* object)
    {
        const std::map<eComponentTags, Component*>* t_ComponentList = object->SeeComponents();

        cJSON* t_Components = CreateArray("ComponentList");

        for (auto p : *t_ComponentList)
        {
            AddComponentTocJSONItem(t_Components, p.second);
        }
        AddItemToArray(item, t_Components);
    }

    void DataManager::AddComponentToGameObject(GameObject* object, cJSON* item)
    {
        if (!item) { return; }

        eComponentTags value = (eComponentTags)std::stoi(item->string); // eComponentTags::Component_Render; // GetItemFromArrayByKey(item, "");
        // Reference : https://www.techiedelight.com/convert-string-to-int-cpp/

        switch (value)
        {
        case Component_Camera:
        {
            CameraComponent* t_pCamComp = nullptr;
            eCamType camType = eCamType::CamType_FreeCam; // TODO: Get dynamically
            switch (camType)
            {
            case CamType_FreeCam:
                t_pCamComp = new FreeCameraComponent();
                break;
            case CamType_FirstPerson:
                t_pCamComp = new FirstPersonCameraComponent();
                break;
            case CamType_ThirdPerson:
                t_pCamComp = new ThirdPersonCameraComponent();
                break;
            case CamType_Static:
                t_pCamComp = new StaticCameraComponent();
                break;
            }
            t_pCamComp->SetType(camType); // TODO: Set in component constructor.
            object->AddComponent(t_pCamComp);
        }
        break;
        case Component_Physics:
            break;
        case Component_Light:
        {
            LightComponent* t_pLightComp = new LightComponent();
            t_pLightComp->SetColour(vec3(1.0f, 1.0f, 1.0f));

            // fact->AddModelComponentFromSchematic(t_pLight, "light.osch");
            object->AddComponent(t_pLightComp);
        }
        break;
        case Component_Controller:
            break;
        case Component_Render:
        {
            RenderComponent* rComp = new RenderComponent();
            cJSON* renderables = GetItemFromArrayByKey(item, "Renderables");

            for (size_t i = 0; i < GetArraySize(renderables); i++)
            {
                cJSON* renderableArray = GetItemFromArrayByIndex(renderables, i); // renderables->child->child;

                Renderable renderable;
                renderable.SetRenderableName(renderableArray->string);

                cJSON* shader = GetItemFromArrayByKey(renderableArray, "Shader");
                cJSON* material = GetItemFromArrayByKey(renderableArray, "Material");
                cJSON* meshFile = GetItemFromArrayByKey(renderableArray, "MeshFile");
                cJSON* meshName = GetItemFromArrayByKey(renderableArray, "MeshName");

                renderable.SetShader(Resources::GetShaderProgram(shader->valuestring));
                renderable.SetMaterial(Resources::GetMaterial(material->valuestring));

                // Load Mesh
                if (strcmp(meshFile->valuestring, no_file) == 0)
                    renderable.SetMesh(Resources::GetMesh(meshName->valuestring));
                else
                    renderable.SetMesh(Resources::GetMeshFromFile(meshFile->valuestring, meshName->valuestring));

                rComp->AddRenderable(renderable);
            }

            object->AddComponent(rComp);
        }
        break;
        case Component_Print:
            break;
        case Component_SkyBox:
            break;
        case Component_SoundPlayer:
            break;
        case Component_SoundListener:
            break;
        case Component_Max:
            break;
        case Component_Null:
            break;
        default:
            break;
        }
    }

    void DataManager::AddComponentsToGameObject(GameObject* object, cJSON* item)
    {
        cJSON* t_ComponentsList = GetItemFromArrayByKey(item, "ComponentList");
        std::vector<cJSON*> t_Components = GetAllItemsFromArray(t_ComponentsList);

        for (size_t i = 0; i < t_Components.size(); i++)
        {
            AddComponentToGameObject(object, t_Components[i]);
        }
    }

    // Routines
    void DataManager::AddRoutineTocJSONItem(cJSON* routineList, Routine* routine)
    {
        if (!routine) return;

        cJSON* t_Routine = CreateArray(std::to_string(routine->GetRoutineType()).c_str());

        switch (routine->GetRoutineType())
        {
        case eRoutineTypes::Routine_Render:
            AddItemToArray(t_Routine, CreateString("RoutineName", "Render"));
            break;
        case eRoutineTypes::Routine_Print:
            AddItemToArray(t_Routine, CreateString("RoutineName", "Print"));
            break;
        case eRoutineTypes::Routine_Transform:
            AddItemToArray(t_Routine, CreateString("RoutineName", "Transform"));

            TransformRoutine* tRoutine = (TransformRoutine*)routine;
            AddItemToArray(t_Routine, CreateNumber("Speed", tRoutine->GetSpeed()));

            cJSON* transform = CreateArray("TransformValues");

            vec3 pos = tRoutine->GetPositionOff();
            cJSON* position = CreateArray("Position");
            AddItemToArray(position, CreateNumber("PositionX", pos.x));
            AddItemToArray(position, CreateNumber("PositionY", pos.y));
            AddItemToArray(position, CreateNumber("PositionZ", pos.z));

            AddItemToArray(transform, position);

            vec3 rot = tRoutine->GetRotationOff();
            cJSON* rotation = CreateArray("Rotation");
            AddItemToArray(rotation, CreateNumber("RotationX", rot.x));
            AddItemToArray(rotation, CreateNumber("RotationY", rot.y));
            AddItemToArray(rotation, CreateNumber("RotationZ", rot.z));

            AddItemToArray(transform, rotation);

            vec3 sca = tRoutine->GetScaleOff();
            cJSON* scale = CreateArray("Scale");
            AddItemToArray(scale, CreateNumber("ScaleX", sca.x));
            AddItemToArray(scale, CreateNumber("ScaleY", sca.y));
            AddItemToArray(scale, CreateNumber("ScaleZ", sca.z));

            AddItemToArray(transform, scale);

            // TODO: Save routine values... or create a component

            AddItemToArray(t_Routine, transform);
            break;
        }
        AddItemToArray(routineList, t_Routine);
    }

    void DataManager::AddRoutinesTocJSONItem(cJSON* item, GameObject* object)
    {
        const std::vector<Routine*>* t_UpdateList = object->SeeUpdateRoutines();
        const std::vector<Routine*>* t_DrawList = object->SeeDrawRoutines();

        cJSON* t_Routines = CreateArray("RoutineList");

        cJSON* t_UpdateRoutines = CreateArray("UpdateRoutines");
        for (Routine* p : *t_UpdateList)
        {
            AddRoutineTocJSONItem(t_UpdateRoutines, p);
        }
        AddItemToArray(t_Routines, t_UpdateRoutines);

        cJSON* t_DrawRoutines = CreateArray("DrawRoutines");
        for (Routine* p : *t_DrawList)
        {
            AddRoutineTocJSONItem(t_DrawRoutines, p);
        }
        AddItemToArray(t_Routines, t_DrawRoutines);

        AddItemToArray(item, t_Routines);
    }

    void DataManager::AddRoutineToGameObject(GameObject* object, cJSON* item)
    {
        if (!item) { return; }

        eRoutineTypes type = (eRoutineTypes)std::stoi(item->string);

        switch (type)
        {
        case eRoutineTypes::Routine_Render:
            object->AddRoutine((Routine*)new RenderRoutine());
        case eRoutineTypes::Routine_Print:
            // object->AddDrawRoutine((Routine*)new PrintRoutine());
            break;
        case eRoutineTypes::Routine_Transform:
            cJSON* transformValues = GetItemFromArrayByKey(item, "TransformValues");
            cJSON* pos = GetItemFromArrayByKey(transformValues, "Position");
            vec3 position = vec3((float)GetItemFromArrayByIndex(pos, 0)->valuedouble,
                (float)GetItemFromArrayByIndex(pos, 1)->valuedouble,
                (float)GetItemFromArrayByIndex(pos, 2)->valuedouble);
            cJSON* rot = GetItemFromArrayByKey(transformValues, "Rotation");
            vec3 rotation = vec3((float)GetItemFromArrayByIndex(rot, 0)->valuedouble,
                (float)GetItemFromArrayByIndex(rot, 1)->valuedouble,
                (float)GetItemFromArrayByIndex(rot, 2)->valuedouble);
            cJSON* sca = GetItemFromArrayByKey(transformValues, "Scale");
            vec3 scale = vec3((float)GetItemFromArrayByIndex(sca, 0)->valuedouble,
                (float)GetItemFromArrayByIndex(sca, 1)->valuedouble,
                (float)GetItemFromArrayByIndex(sca, 2)->valuedouble);

            TransformRoutine* transform = new TransformRoutine();
            transform->SetSpeed((float)GetItemFromArrayByKey(item, "Speed")->valuedouble);
            transform->SetPositionOff(position);
            transform->SetRotationOff(rotation);
            transform->SetScaleOff(scale);

            object->AddRoutine((Routine*)transform);
            break;
        }
    }

    void DataManager::AddRoutinesToGameObject(GameObject* object, cJSON* item)
    {
        cJSON* t_RoutineList = GetItemFromArrayByKey(item, "RoutineList");

        cJSON* t_UpdateRoutines = GetItemFromArrayByKey(t_RoutineList, "UpdateRoutines");
        std::vector<cJSON*> t_Routines = GetAllItemsFromArray(t_UpdateRoutines);
        for (size_t i = 0; i < t_Routines.size(); i++)
        {
            AddRoutineToGameObject(object, t_Routines[i]);
        }

        cJSON* t_DrawRoutines = GetItemFromArrayByKey(t_RoutineList, "DrawRoutines");
        t_Routines = GetAllItemsFromArray(t_DrawRoutines);
        for (size_t i = 0; i < t_Routines.size(); i++)
        {
            AddRoutineToGameObject(object, t_Routines[i]);
        }
    }

}
