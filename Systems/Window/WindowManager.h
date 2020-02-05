#ifndef _WindowManager_H_
#define _WindowManager_H_

#include <vector>

class Window;

namespace QwerkE {

    class WindowManager
    {
    public:
        WindowManager();
        ~WindowManager();

        void AddWindow(Window* window);
        Window* GetWindow(int windowID);

    private:
        std::vector<Window*> m_Windows;
    };

}
#endif // !_WindowManager_H_
