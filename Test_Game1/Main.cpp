#include "Framework.h"
#include "Scene/SceneManager.h"

#define _QEasy // QwerkE_API

#ifdef _QEasy // Beginner API
int main()
{
	if (QwerkE::Framework::Startup() == eEngineMessage::_QFail)
	{
		OutputPrint("\nMain(): Error loading services!\n");
		assert(false);
		return 0;
	}

	SceneManager* sceneManager = (SceneManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Scene_Manager);
	sceneManager->Initialize(); // Setup test scene
	sceneManager->GetCurrentScene()->SetIsEnabled(true);

	QwerkE::Framework::Run();

	QwerkE::Framework::TearDown();
}

#elif defined(_QMedium) // Simple control
int main()
{

}

#elif defined(_QHard) // Mixed control
int main()
{

}

#else
// _QUltra // Full control
int main()
{

}

#endif // QwerkE_API
