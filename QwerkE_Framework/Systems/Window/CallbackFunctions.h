#ifndef _CallBackFunctions_H_
#define _CallBackFunctions_H_

struct GLFWwindow;

// setup
// void SetCursor(); TODO:
void SetupCallbacks(GLFWwindow* window);
// input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void char_callback(GLFWwindow* window, unsigned int codePoint);
void char_mods_callback(GLFWwindow* window, unsigned int codepoint, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void cursor_enter_callback(GLFWwindow* window, int entered);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void joystick_callback(int joy, int event);
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
#endif // !_CallBackFunctions_H_