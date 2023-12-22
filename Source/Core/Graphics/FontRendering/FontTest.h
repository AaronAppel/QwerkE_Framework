#pragma once

#include <string>

typedef float GLfloat;
#include "../../Libraries/glm/glm/glm.hpp"

namespace QwerkE {

    class ShaderProgram;

    void LoadFonts();
    void RenderText(ShaderProgram* shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

}
