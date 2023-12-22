#include "Renderer.h"

#include "../Resources/Resources.h"

#include "Renderer.h"
#include "FontRendering/FontTest.h"
#include "Shader/ShaderProgram.h"
#include "Graphics_Header.h"

namespace QwerkE {

    int Renderer::g_WindowWidth = 1600;
    int Renderer::g_WindowHeight = 900;

    // TODO: Move OpenGL code to proper files
    void Renderer::Initialize()
    {
        LoadFonts();

        // TODO: GL state init should be in a Window() or OpenGLManager()
        //     class or some type of ::Graphics() system.
        glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // turn on depth buffer testing
        glEnable(GL_DEPTH_TEST);
        glPointSize(10);
        glLineWidth(10);

        // depth cull for efficiency
        // TODO: This is also in the framework
        // glEnable(GL_CULL_FACE);
        // glDisable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        if (Wind_CCW) glFrontFace(GL_CCW);
        else glFrontFace(GL_CW);

        // turn on alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glViewport(0, 0, Renderer::g_WindowWidth, Renderer::g_WindowHeight);
    }

    void Renderer::NewFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::DrawFont(const char* text)
    {
        // TODO: Improve font rendering
        RenderText(Resources::GetShaderProgram("font_shader.ssch"),
            std::string(text),
            100, 100, // x, y
            1.0f, // scale
            glm::vec3(0, 0, 0));
    }

}
