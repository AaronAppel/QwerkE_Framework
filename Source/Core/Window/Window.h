#pragma once

#include "../Math/Vector.h"

namespace QwerkE {

    class Window
    {
    public:
        Window(int windowWidth, int windowHeight, const char* windowTitle);
        virtual ~Window() = default;

        void SetResolution(vec2 resolution);
        const vec2& GetResolution() const { return m_Resolution; }
        const vec2& GetAspectRatio() const { return m_AspectRatio; }

        virtual void* GetContext() = 0;

        virtual void SwapBuffers() = 0;

        void SetClosing(bool closing) { m_IsClosing = closing; };
        bool IsClosing() { return m_IsClosing; };

    protected:
        vec2 m_Resolution = vec2(1600.f, 900.f);
        vec2 m_AspectRatio = vec2(16.f, 9.f);

        bool m_IsFocused = false;
        bool m_IsClosing = false;

        const char* m_WindowTitle = "null";
    };

}
