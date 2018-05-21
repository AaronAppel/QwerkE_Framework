#include "OpenAL_Component.h"
#include "../../../Systems/ServiceLocator.h"
#include "../../../Systems/ResourceManager/ResourceManager.h"

OpenAL_AudioComponent::OpenAL_AudioComponent()
{
	m_Buffer = ((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetSound("bounce.wav");
}

OpenAL_AudioComponent::~OpenAL_AudioComponent()
{
}

int OpenAL_AudioComponent::Play()
{
	alSourcePlay(m_Buffer);
	return 1;
}