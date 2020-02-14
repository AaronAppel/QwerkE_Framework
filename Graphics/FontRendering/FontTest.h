#ifndef _FontTest_H_
#define _FontTest_H_

#include <string>

class ShaderProgram;
typedef float GLfloat;
#include "../../Libraries/glm/glm/glm.hpp"

namespace QwerkE {

    void LoadFonts();
    void RenderText(ShaderProgram* shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

}
#endif // !_FontTest_H_
