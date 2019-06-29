#ifndef _Config_Helper_H_
#define _Config_Helper_H_

struct Framework
{
    bool QuickLoad = true;
    int MaxConcurrentThreadCount = 10;
};

struct Libraries
{
    std::string Rendering = "OpenGL";
    std::string Audio = "OpenAL";
    std::string Physics = "Bullet3D";
    std::string Networking = "RakNet";
    std::string Window = "GLFW3";
};

struct Scenes
{
    std::vector<std::string> fileNames;
};

struct SceneSettings
{
    int MaxEnabledScenes = 1;
};

struct Systems
{
    bool AudioEnabled = true;
    bool PhysicsEnabled = true;
    bool NetworkingEnabled = true;
    bool DebuggingEnabled = true;
    bool LoggingEnabled = true;
};

// TODO: Hide the data for safety. Find a better API for ConfigData
struct ConfigData
{
    // ConfigData() {};
    // ConfigData(Libraries l, Scenes sc, SceneSettings ss, Systems sy)
    // {
    //     libraries = l;
    //     scenes = sc;
    //     sceneSettings = ss;
    //     systems = sy;
    // }

    Framework framework;
    Libraries libraries;
    Scenes scenes;
    SceneSettings sceneSettings;
    Systems systems;
};

static class ConfigHelper
{
public:
    static void LoadConfigData();
    static void SaveConfigData();
    static void SaveConfigData(ConfigData config);

    static ConfigData GetConfigData() { return m_ConfigData; }
    static void SetConfigData(ConfigData config) { m_ConfigData = config; }

private:
    static ConfigData m_ConfigData;

    ConfigHelper() {}
    ~ConfigHelper() {};
};

#endif //!_Config_Helper_H_