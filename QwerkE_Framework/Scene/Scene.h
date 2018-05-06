#ifndef _Scene_H_
#define _Scene_H_

#include "../../QwerkE_Common/Custom_Classes/MyLinkedList.h"
#include "../../QwerkE_Common/Math_Includes.h"
#include "../QwerkE_Enums.h"

#include <map>

extern int g_WindowWidth, g_WindowHeight;

class GameCore;
class MyMatrix;
class SceneManager;
class GameObject;

class Scene; // forward declare for function* typedef
typedef void (Scene::*UpdateFunc)(double deltatime); // Scene pause

													 // TODO: Create derived classes for scenes like SplashScreen, GameScene, etc
class Scene // Abstract class
{
public:
	Scene();
	virtual ~Scene();

	virtual void OnWindowResize(unsigned int width, unsigned int height);
	virtual void Initialize();
	virtual void ResetScene();

	virtual void Update(double deltatime) { (this->*m_UpdateFunc)(deltatime); };
	virtual void Draw() = 0;

	// cameras
	virtual bool AddCamera(GameObject* camera);
	virtual void RemoveCamera(GameObject* camera);
	virtual void SetupCameras();

	// lights
	virtual bool AddLight(GameObject* light);
	virtual void RemoveLight(GameObject* light);
	virtual void SetupLights();

	virtual bool AddObjectToScene(GameObject* object);
	virtual void RemoveObjectFromScene(GameObject* object);

	virtual void RemoveAllObjectsFromScene(); // Possibly a scene reset

											  // Save/Load
	virtual void SaveScene();
	virtual void LoadScene();

	/* Getters + Setters */
	// getters
	GameObject* GetGameObject(const char* name);
	bool GetIsEnabled() { return m_IsEnabled; };
	SceneManager* GetSceneManager() { return m_pSceneManager; };
	Linear2LinkedList<GameObject*> GetCameraList() { return m_CameraList; };
	std::map<std::string, GameObject*> GetObjectList() { return m_pGameObjects; };
	int GetCurrentCamera() { return m_CurrentCamera; };
	Linear2LinkedList<GameObject*> GetLightList() { return m_LightList; };
	bool GetIsPaused() { return m_IsPaused; };
	eSceneTypes GetSceneID() { return m_ID; }

	// setters
	void SetIsEnabled(bool isEnabled) { m_IsEnabled = isEnabled; };
	void SetCurrentCamera(int camera) { m_CurrentCamera = camera; }; // TODO:: Better way for ImGUI to change camera
	void SetIsPaused(bool isPaused);

protected:
	virtual void p_Update(double deltatime);
	virtual void p_Paused(double deltatime) {}; // Currently empty
	UpdateFunc m_UpdateFunc = &Scene::p_Update;

	bool m_IsPaused = false;
	bool m_IsEnabled = false;
	const char* m_LevelFileDir = "Uninitialized";
	void Draw(GameObject* camera);
	SceneManager* m_pSceneManager = nullptr;
	MyMatrix* m_pViewMatrix = nullptr; // TODO:: create cameras with different view matrices

	std::map<std::string, GameObject*> m_pGameObjects;
	eSceneTypes m_ID = Scene_Null;

	int m_CurrentCamera = 0;
	Linear2LinkedList<GameObject*> m_CameraList;

	Linear2LinkedList<GameObject*> m_LightList;

	Linear2LinkedList<GameObject*> m_SceneDrawList; // sorted by render order

													//MenuManager* m_pMenuManager = nullptr;

													// TODO:: Store window size in cameras?
	vec3 m_ViewWindowPosition = 0; // world pos 3D
	vec2 m_ViewWindowSize = vec2(g_WindowWidth, g_WindowHeight); // screen size
};

#endif //!_Scene_H_
