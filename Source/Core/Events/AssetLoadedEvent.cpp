#include "AssetLoadedEvent.h"
#include "../Resources/Resources.h"
#include "../Graphics/GraphicsUtilities/OpenGL/OpenGLHelpers.h"

namespace QwerkE {

    AssetLoadedEvent::AssetLoadedEvent(QImageFile asset) :
        m_Asset(asset)
    {
        // TODO: Init list
        m_EventType = eEventTypes::eEvent_AssetLoaded;
    }

    AssetLoadedEvent::~AssetLoadedEvent()
    {
    }

    void AssetLoadedEvent::Process()
    {
        if (m_Asset.s_Data != nullptr)
        {
            // Take loaded char* data and feed it to OpenGL for a handle
            // Texture* texture = new Texture();
            // texture->s_Name = m_Asset.s_Name;
            // texture->s_Handle = LoadTextureDataToOpenGL(m_Asset); // TODO: Remove OpenGL dependency

            int handle = LoadTextureDataToOpenGL(m_Asset);

            if (handle > 0) // if (texture->s_Handle > 0)
            {
                // Update texture data in resource manager
                Resources::UpdateTexture(m_Asset.s_Name.c_str(), handle);
            }
            else
            {
                // delete texture; // failed
            }
        }
    }

}
