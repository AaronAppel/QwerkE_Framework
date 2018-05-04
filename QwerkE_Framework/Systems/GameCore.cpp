#include "GameCore.h"
#include "ResourceManager.h"
#include "Graphics/OpenGLManager.h"
#include "Graphics/FBO/FrameBufferObject.h"
#include "../../../Shared_Generic/Math_Includes.h"
#include "../Systems/Factory/Factory.h"
#include "../Systems/Factory/LevelLoader.h"
#include "../Scene/SceneManager.h"

GameCore::GameCore()
{
	m_pProjectionMatrix = new MyMatrix();
	m_pProjectionMatrix->SetIdentity();
	m_pResourceManager = new ResourceManager();
	//m_pAudioManager = new AudioManager();
	m_pFactory = new Factory();
	m_pSceneManager = new SceneManager();
	m_pGLManager = new OpenGLManager();
	m_pDataManager = new LevelLoader(m_pFactory);

	m_FBO = new FrameBufferObject();
	// m_FBO->Init();
}

GameCore::~GameCore()
{
    delete m_pProjectionMatrix;
	//delete m_pAudioManager;
	delete m_pFactory;
	delete m_pResourceManager;
	delete m_pDataManager;
	delete m_pSceneManager;
	delete m_pGLManager;
	delete m_FBO;

	m_pProjectionMatrix = 0; // Null pointers
	//m_pAudioManager = 0;
	m_pFactory = 0;
	m_pResourceManager = 0;
	m_pDataManager = 0;
	m_pSceneManager = 0;
	m_pGLManager = 0;
	m_FBO = 0;
}

void GameCore::OnWindowResize(unsigned int width, unsigned int height)
{
	// TODO:: Add support for multiple windows
    glViewport( 0, 0, width, height );

    m_WindowWidth = width;
    m_WindowHeight = height;

	// TODO: Tell scene to resize camera view ports
	// TODO:: resize scene viewWindow size
}

void GameCore::Initialize() // TODO:: Is this a reset or should that be a separate function?
{
	m_pGLManager->ResetGLState();

	// m_pFactory->LoadScene(eSceneTypes::Scene_TestScene); // load assets for this scene
	m_pSceneManager->Initialize();
	m_pSceneManager->DisableAll();
}

GLuint GameCore::RenderSceneToTexture(eSceneTypes scene)
{
	m_FBO->Bind();

	m_pGLManager->ClearScreen();

	m_pSceneManager->DrawScene(scene);

	m_FBO->UnBind();

	return m_FBO->GetTextureID();
}
