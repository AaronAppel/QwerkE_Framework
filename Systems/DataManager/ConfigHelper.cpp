#include "ConfigHelper.h"
#include "QwerkE_Common/Utilities/ReflectionMacros.h"

#include <iostream>
#include <limits.h>
#include <stdlib.h>

namespace QwerkE {

    ConfigData ConfigHelper::m_ConfigData = ConfigData();

    void ConfigHelper::LoadConfigData()
    {
        std::string configFilePath = ConfigsFolderPath("preferences.qpref"); // TODO: How to handle file names?
        LoadConfigData(configFilePath);
    }

    void ConfigHelper::LoadConfigData(std::string configFilePath)
    {
        cJSON* root = OpencJSONStream(configFilePath.c_str());
        if (root == nullptr)
        {
            LOG_ERROR("Unable to load json for file {0}", configFilePath);
            return;
        }

        // Framework
        cJSON* framework = GetItemFromRootByKey(root, "Framework");
        m_ConfigData.framework.QuickLoad = (bool)GetItemFromArrayByKey(framework, "QuickLoad")->valueint;
        m_ConfigData.framework.MaxConcurrentThreadCount = GetItemFromArrayByKey(framework, "MaxConcurrentThreadCount")->valueint;

        // Libraries
        cJSON* libraries = GetItemFromRootByKey(root, "Libraries");
        m_ConfigData.libraries.Audio = GetItemFromArrayByKey(libraries, "Audio")->valuestring;
        m_ConfigData.libraries.Networking = GetItemFromArrayByKey(libraries, "Networking")->valuestring;
        m_ConfigData.libraries.Physics = GetItemFromArrayByKey(libraries, "Physics")->valuestring;
        m_ConfigData.libraries.Rendering = GetItemFromArrayByKey(libraries, "Rendering")->valuestring;
        m_ConfigData.libraries.Window = GetItemFromArrayByKey(libraries, "Window")->valuestring;

        // Scenes // TODO: Put scenes inside SceneSettings
        cJSON* scenes = GetItemFromRootByKey(root, "Scenes");
        std::vector<cJSON*> sceneList = GetAllItemsFromArray(scenes);

        for (unsigned int i = 0; i < sceneList.size(); i++)
        {
            m_ConfigData.scenes.fileNames.push_back(sceneList.at(i)->valuestring);
        }

        // SceneSettings
        cJSON* sceneSettings = GetItemFromRootByKey(root, "SceneSettings");
        m_ConfigData.sceneSettings.MaxEnabledScenes = GetItemFromArrayByKey(sceneSettings, "MaxEnabledScenes")->valueint;

        // Systems
        cJSON* systems = GetItemFromRootByKey(root, "Systems");
        m_ConfigData.systems.AudioEnabled = (bool)GetItemFromArrayByKey(systems, "AudioEnabled")->valueint;
        m_ConfigData.systems.DebuggingEnabled = (bool)GetItemFromArrayByKey(systems, "DebuggingEnabled")->valuestring;
        m_ConfigData.systems.LoggingEnabled = (bool)GetItemFromArrayByKey(systems, "LoggingEnabled")->valuestring;
        m_ConfigData.systems.NetworkingEnabled = (bool)GetItemFromArrayByKey(systems, "NetworkingEnabled")->valuestring;
        m_ConfigData.systems.PhysicsEnabled = (bool)GetItemFromArrayByKey(systems, "PhysicsEnabled")->valuestring;

        ClosecJSONStream(root);
    }

    void ConfigHelper::SaveConfigData(ConfigData config)
    {
        m_ConfigData = config;
        SaveConfigData();
    }

    void ConfigHelper::SaveConfigData()
    {
        cJSON* root = CreateObject();

        // Framework
        cJSON* framework = CreateArray("Framework");
        AddItemToArray(framework, CreateNumber("QuickLoad", (int)m_ConfigData.framework.QuickLoad));
        AddItemToArray(framework, CreateNumber("MaxConcurrentThreadCount", m_ConfigData.framework.MaxConcurrentThreadCount));

        // Libraries
        cJSON* libraries = CreateArray("Libraries");

        AddItemToArray(libraries, CreateString("Audio", m_ConfigData.libraries.Audio.c_str()));
        AddItemToArray(libraries, CreateString("Networking", m_ConfigData.libraries.Networking.c_str()));
        AddItemToArray(libraries, CreateString("Physics", m_ConfigData.libraries.Physics.c_str()));
        AddItemToArray(libraries, CreateString("Rendering", m_ConfigData.libraries.Rendering.c_str()));
        AddItemToArray(libraries, CreateString("Window", m_ConfigData.libraries.Window.c_str()));

        AddItemToRoot(root, libraries);

        // Scenes // TODO: Put scenes inside SceneSettings
        cJSON* scenes = CreateArray("Scenes");

        for (unsigned int i = 0; i < m_ConfigData.scenes.fileNames.size(); i++)
        {
            AddItemToArray(scenes, CreateString(std::to_string(i).c_str(), m_ConfigData.scenes.fileNames[i].c_str()));
        }

        AddItemToRoot(root, scenes);

        // SceneSettings
        cJSON* sceneSettings = CreateArray("SceneSettings");

        AddItemToArray(sceneSettings, CreateNumber("MaxEnabledScenes", m_ConfigData.sceneSettings.MaxEnabledScenes));

        AddItemToRoot(root, sceneSettings);

        // Systems
        cJSON* systems = CreateArray("Systems");

        AddItemToArray(systems, CreateNumber("AudioEnabled", (int)m_ConfigData.systems.AudioEnabled));
        AddItemToArray(systems, CreateNumber("DebuggingEnabled", (int)m_ConfigData.systems.DebuggingEnabled));
        AddItemToArray(systems, CreateNumber("LoggingEnabled", (int)m_ConfigData.systems.LoggingEnabled));
        AddItemToArray(systems, CreateNumber("NetworkingEnabled", (int)m_ConfigData.systems.NetworkingEnabled));
        AddItemToArray(systems, CreateNumber("PhysicsEnabled", (int)m_ConfigData.systems.PhysicsEnabled));

        AddItemToRoot(root, systems);

        std::string path = ConfigsFolderPath("preferences.qpref"); // TODO: How to handle file names?
        PrintRootObjectToFile(path.c_str(), root);
    }

}
