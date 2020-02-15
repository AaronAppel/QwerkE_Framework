#ifndef _ShaderProgram_H_
#define _ShaderProgram_H_

#include "../../Systems/Misc/StringHelpers.h"
#include "../GraphicsUtilities/GraphicsHelpers.h"
#include "../Shader/ShaderUtilities.h"
#include "../../Headers/QwerkE_Global_Constants.h"

#include <string>
#include <vector>

namespace QwerkE {

    class ShaderComponent;

    class ShaderProgram
    {
    public:
        ShaderProgram() {}
        ~ShaderProgram() {}

        void Use() { glUseProgram(m_ProgramHandle); }
        GLuint GetProgram() const { return m_ProgramHandle; }
        void SetProgram(GLuint handle) { m_ProgramHandle = handle; }

        void FindAttributesAndUniforms() { FindShaderUniformsAndAttributesInComponentStrings(this, m_Attributes, m_Uniforms); };

        // TODO: void RecompileShaderType(GLenum type);
        void RecompileShaderType(GLenum type, const char* shaderData);

        // Const getters
        const std::vector<std::string>* SeeAttributes() const { return &m_Attributes; }
        const std::vector<std::string>* SeeUniforms() const { return &m_Uniforms; }

        // Getters
        std::string GetName() const { return m_Name; }
        std::string GetVertName() const { return m_VertName; }
        std::string GetFragName() const { return m_FragName; }
        std::string GetGeoName() const { return m_GeoName; }

        ShaderComponent* GetVertShader() { return m_VertShader; }
        ShaderComponent* GetFragShader() { return m_FragShader; }
        ShaderComponent* GetGeoShader() { return m_GeoShader; }

        // Setters
        void SetName(std::string name) { m_Name = name; }
        void SetVertName(std::string name) { m_VertName = name; }
        void SetFragName(std::string name) { m_FragName = name; }
        void SetGeoName(std::string name) { m_GeoName = name; }

        void SetVertShader(ShaderComponent* shader) { m_VertShader = shader; }
        void SetFragShader(ShaderComponent* shader) { m_FragShader = shader; }
        void SetGeoShader(ShaderComponent* shader) { m_GeoShader = shader; }

        // Attribute value assignment
        // void SetAttributeData() {} good idea?

        /* Uniform value assignment */
        // int
        void SetUniformInt1(const char* name, int value);
        void SetUniformInt2(const char* name, int value1, int value2);
        void SetUniformInt3(const char* name, int value1, int value2, int value3);
        void SetUniformInt4(const char* name, int value1, int value2, int value3, int value4);
        // float
        void SetUniformFloat1(const char* name, float value);
        void SetUniformFloat2(const char* name, float value1, float value2);
        void SetUniformFloat3(const char* name, float value1, float value2, float value3);
        void SetUniformFloat4(const char* name, float value1, float value2, float value3, float value4);
        // matrix
        void SetUniformMat4(const char* name, const GLfloat* matrix);

    private:
        std::string m_Name = gc_DefaultStringValue;

        std::string m_VertName = gc_DefaultStringValue; // TODO: Remove these names and use the component member variables m_Name
        std::string m_FragName = gc_DefaultStringValue;
        std::string m_GeoName = gc_DefaultStringValue;

        GLuint m_ProgramHandle = 0;

        ShaderComponent* m_VertShader = nullptr;
        ShaderComponent* m_FragShader = nullptr;
        ShaderComponent* m_GeoShader = nullptr;

        std::vector<std::string> m_Attributes;
        std::vector<std::string> m_Uniforms;
    };

}
#endif // !_ShaderProgram_H_
