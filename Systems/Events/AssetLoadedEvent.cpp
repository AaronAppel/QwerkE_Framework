#include "AssetLoadedEvent.h"
#include "../ResourceManager/ResourceManager.h"
#include "../ServiceLocator.h"
#include "../../Graphics/GraphicsUtilities/OpenGL/OpenGLHelpers.h"

AssetLoadedEvent::AssetLoadedEvent(QImageFile asset) :
	m_Asset(asset)
{
	m_EventType = eEventTypes::eEvent_AssetLoaded;
}

AssetLoadedEvent::~AssetLoadedEvent()
{
}

void AssetLoadedEvent::Process()
{
	if (m_Asset.s_Data != nullptr)
	{
		// take loaded char* data and feed it to OpenGL for a handle
		Texture* texture = new Texture();
		texture->s_Name = m_Asset.s_Name;
		texture->s_Handle = LoadTextureDataToOpenGL(m_Asset); // TODO: Remove OpenGL dependency

		if (texture->s_Handle > 0)
		{
			// add texture to resource manager
			((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->AddTexture(texture->s_Name.c_str(), texture);
		}
		else
		{
			delete texture; // failed
		}
	}
}