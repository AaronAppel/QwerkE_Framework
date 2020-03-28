#include "OpenGLManager.h"
#include "../Graphics/Graphics_Header.h"

namespace QwerkE {

    OpenGLManager::OpenGLManager()
    {
    }

    OpenGLManager::~OpenGLManager()
    {
    }

    void OpenGLManager::Init()
    {
        ResetGLState();
    }

    void OpenGLManager::ResetGLState()
    {
        // TODO: Improve
        return;

        // turn on depth buffer testing
        if (m_DepthTestingOn)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS); // GL_LEQUAL, GL_ALWAYS
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
        // depth cull for efficiency
        if (m_BackfaceCullingOn)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }
        // turn on alpha blending
        if (m_BlendingOn) // https://learnopengl.com/#!Advanced-OpenGL/Blending
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else
        {
            glDisable(GL_BLEND);
        }
    }

    void OpenGLManager::ViewPortSize(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLManager::ClearScreen()
    {
        // CheckforGLErrors(__FILE__, __LINE__);
        glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w); // TODO: Don't reset every frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen to color
    }

    void OpenGLManager::SetZBufferLock(bool lock)
    {
        if (lock)
        {
            glDepthMask(GL_TRUE);
        }
        else
        {
            glDepthMask(GL_FALSE); // disable Z buffer writing
        }
    };

}
