#include "../../Core/Input/Input.h"

#ifdef dearimgui
#include "../../Libraries/imgui/imgui.h"
// #include "../../Libraries/imgui/imgui_impl_glfw_gl3.h"
#endif // dearimgui

#include "../../Headers/QwerkE_Global_Constants.h"

#include "../../Core/Input/Mouse.h"
#include "../../Core/Input/Keyboard.h"
#include "../../Core/Graphics/Renderer.h"

namespace QwerkE {

#ifdef GLFW3

    void Input::SetupCallbacks(GLFWwindow* window)
    {
        glfwSetKeyCallback(window, key_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetCharCallback(window, char_callback);
        glfwSetCharModsCallback(window, char_mods_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetJoystickCallback(joystick_callback);
    }

    void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        if (action == GLFW_PRESS)
        {
            ProcessKeyEvent(GLFWToQwerkEKey(key),
                eKeyState::eKeyState_Press);
        }
        else if (action == GLFW_RELEASE)
        {
            ProcessKeyEvent(GLFWToQwerkEKey(key),
                eKeyState::eKeyState_Release);
        }

#ifdef dearimgui // TODO: Checkout how to call imgui properly
        ImGuiIO& io = ImGui::GetIO();
        if (action == GLFW_PRESS)
            io.KeysDown[key] = true;
        if (action == GLFW_RELEASE)
            io.KeysDown[key] = false;

        //(void)mods; // Modifiers are not reliable across systems
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif // dearimgui
    }

    void Input::char_callback(GLFWwindow* window, unsigned int codePoint)
    {
        // l_Input->ProcessKeyEvent(l_Input->GLFWToQwerkEKey(key), eKeyState::eKeyState_Down);
        int bp = 1;

#ifdef dearimgui // TODO: Checkout how to call imgui properly
        ImGuiIO& io = ImGui::GetIO();
        if (codePoint > 0 && codePoint < 0x10000)
            io.AddInputCharacter((unsigned short)codePoint);
#endif // dearimgui
    }

    void Input::char_mods_callback(GLFWwindow* window, unsigned int codepoint, int mods)
    {
        // TODO:
    }

    void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        ProcessMouseMove((float)xpos, (float)-ypos);

        ypos = (double)Renderer::g_WindowHeight - ypos; // invert y
    }

    void Input::cursor_enter_callback(GLFWwindow* window, int entered)
    {
        // ProcessMouse();
        if (entered == GLFW_TRUE)
        {
            // mouse entered window rectangle
        }
        else
        {
            // mouse left window rectangle
        }
    }

    void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            ProcessMouseClick(GLFWToQwerkEKey(button), eKeyState::eKeyState_Press);
        }
        else if (action == GLFW_RELEASE)
        {
            ProcessMouseClick(GLFWToQwerkEKey(button), eKeyState::eKeyState_Release);
        }

        // imgui
        // io.MouseDown[i] = ;
    }

    void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        // ProcessMouse();

#ifdef dearimgui
    // ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += (float)xoffset;
        io.MouseWheel += (float)yoffset;

#endif // dearimgui
    }

    void Input::joystick_callback(int joy, int event)
    {
        // ProcessGamePad/Joystick();
        // joystick button pressed
        // http://www.glfw.org/docs/latest/input_guide.html#joystick
        int bp = 1;
    }

}
#endif // GLFW3
