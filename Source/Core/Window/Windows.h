#pragma once

#include <vector>

namespace QwerkE {

    class Window;

    class Windows
    {
    public:
        static void AddWindow(Window* window);
        static Window* GetWindow(int windowID);
        static const Window* GetLastFocusedWindow();

        static void Initialize();
        static void Shutdown();

    private:
        Windows() {}
        ~Windows() {}

        static std::vector<Window*> m_Windows;
        static unsigned char m_lastFocusedWindowIndex;
    };

}
