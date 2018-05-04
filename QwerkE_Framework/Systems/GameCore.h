#ifndef __GameCore_H__
#define __GameCore_H__

#include "../../Shared_Generic/Math_Includes.h"
#include "../Engine_Enums.h"
#include "../../Shared_Generic/Libraries/glew/GL/glew.h"

class SceneManager;
class ResourceManager;
class Factory;
class DataManager;
class AudioManager;
class MyMatrix;
class FrameBufferObject;
class OpenGLManager;

class GameCore
{
public:
    GameCore();
    virtual ~GameCore();

    void OnWindowResize(unsigned int width, unsigned int height);
    void Initialize();

	/* Getters + Setters */
	// getters
	SceneManager* GetSceneManager() { return m_pSceneManager; };
	ResourceManager* GetResourceManager() { return m_pResourceManager; };
	Factory* GetFactory() { return m_pFactory; };
	DataManager* GetDataManager() { return m_pDataManager; };
	AudioManager* GetAudioManager() { return m_pAudioManager; };
	OpenGLManager* GetGLManager() { return m_pGLManager; };

	MyMatrix* GetProjectionMatrix() { return m_pProjectionMatrix; };
	vec2 GetScreenSize() { return vec2((int)m_WindowWidth, (int)m_WindowHeight); };
	bool DebugDrawEnabled() { return m_DebugDrawEnabled; };

	// Setters
	void SetScreenSize(vec2 screensize) { m_WindowWidth = (unsigned int)screensize.x, m_WindowHeight = (unsigned int)screensize.y; };
	void SetClearColor(vec4 color) { m_ClearColor = color; };

	// Utility
	GLuint RenderSceneToTexture(eSceneTypes scene);

protected:
	SceneManager* m_pSceneManager = nullptr;
	ResourceManager* m_pResourceManager = nullptr;
	Factory* m_pFactory = nullptr;
	DataManager* m_pDataManager = nullptr;
	AudioManager* m_pAudioManager = nullptr;
	OpenGLManager* m_pGLManager = nullptr;

	FrameBufferObject* m_FBO;
	MyMatrix* m_pProjectionMatrix = nullptr;

    unsigned int m_WindowWidth = 0;
    unsigned int m_WindowHeight = 0;

	bool m_DebugDrawEnabled = false; // Box2D

	bool m_IsFullScreen = false; // TODO:: add fullscreen support
	vec4 m_ClearColor = vec4(0.2f, 0.3f, 0.4f, 1.0f);
};

#endif //__GameCore_H__
