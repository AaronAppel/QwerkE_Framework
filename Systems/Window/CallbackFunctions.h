#ifndef _CallBackFunctions_H_
#define _CallBackFunctions_H_

struct GLFWwindow;

namespace QwerkE {

    // setup
    // void SetCursor(); TODO:
    void SetupCallbacks(GLFWwindow* window);

    // window
    void window_position_callback(GLFWwindow* window, int x, int y);
    void window_resize_callback(GLFWwindow* window, int width, int height);
    void window_close_callback(GLFWwindow* window);
    void window_refresh_callback(GLFWwindow* window);
    void window_focus_callback(GLFWwindow* window, int isFocused);
    void window_iconify_callback(GLFWwindow* window, int isIconified);
    void framebuffer_resize_callback(GLFWwindow* window, int x, int y);

    // error
    void error_callback(int error, const char* description);

    // file
    void file_drop_callback(GLFWwindow* window, int count, const char** paths);

}
#endif // !_CallBackFunctions_H_
