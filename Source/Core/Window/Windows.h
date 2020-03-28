#ifndef _Windows_H_
#define _Windows_H_

#include <vector>

namespace QwerkE {

    class Window;

    class Windows
    {
    public:
        static void AddWindow(Window* window);
        static Window* GetWindow(int windowID);

        static void Initialize();
        static void Shutdown();

    private:
        Windows() {}
        ~Windows() {}

        static std::vector<Window*> m_Windows;
    };

}
#endif // !_Windows_H_
