#pragma once

#include "../../Core/Math/Vector.h"

namespace QwerkE {

    // TODO: Rip these functions out and put them in a new opengl_window class that extends the Window class
    class OpenGLManager
    {
    public:
        OpenGLManager();
        ~OpenGLManager();

        void Init();
        void ResetGLState();
        void ViewPortSize(int x, int y, int width, int height);
        void ClearScreen();
        void SetZBufferLock(bool lock);

        void SetVSynchON(bool VSyncIsON) { m_VSyncOn = VSyncIsON; };  // TODO: Handle VSync Toggling
        bool GetVSynchON() { return m_VSyncOn; };  // TODO: Handle VSync Toggling

        void SetClearColor(vec4 color) { m_ClearColor = color; };

    private:
        vec4 m_ClearColor = vec4(0.2f, 0.3f, 0.4f, 1.0f);

        bool m_DepthTestingOn = true;
        bool m_BackfaceCullingOn = true;
        bool m_BlendingOn = true;
        bool m_VSyncOn = true; // TODO: Handle VSync Toggling
    };

}
