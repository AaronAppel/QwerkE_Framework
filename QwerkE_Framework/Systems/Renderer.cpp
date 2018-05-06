#include "Renderer.h"
#include "Graphics/FontRendering/FontTest.h"
#include "ServiceLocator.h"
#include "../QwerkE_Enums.h"

Renderer::Renderer()
{
	LoadFonts();
}

Renderer::~Renderer()
{
}

void Renderer::DrawFont(const char* text)
{
    // TODO: Improve font rendering
	ResourceManager* resourceManager = (ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager);
	RenderText(resourceManager->GetShader("text"),
		std::string(text),
		100, 100, // x, y
		1.0f, // scale
		glm::vec3(0,0,0));
}