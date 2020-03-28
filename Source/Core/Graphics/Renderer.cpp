#include "Renderer.h"
#include "FontRendering/FontTest.h"
#include "Shader/ShaderProgram.h"

namespace QwerkE {

    Renderer::Renderer()
    {
        LoadFonts();
    }

    Renderer::~Renderer()
    {
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
