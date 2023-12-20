#ifndef _ShaderUtilities_H_
#define _ShaderUtilities_H_

// This class requires access to OpenGL functions.
// https://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shader

#include <vector>
#include <string>

namespace QwerkE {

    class ShaderProgram;

    // TODO: Better name
    void FindShaderUniformsAndAttributesInComponentStrings(ShaderProgram* shader, std::vector<std::string>& attributes, std::vector<std::string>& uniforms);

}
#endif //!_ShaderUtilities_H_
