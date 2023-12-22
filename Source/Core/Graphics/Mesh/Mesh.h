#pragma once

#include <string>

#include "../../../../Libraries/glew/GL/glew.h"

#include "../../../Headers/QwerkE_Global_Constants.h"

#include "MeshData.h"

namespace QwerkE {

    class Mesh;
    struct MeshData;
    class ShaderProgram;
    struct VertexData;

    typedef void (QwerkE::Mesh::* MeshFunction)();

    // #TODO Use macro functions to replace OpenGL specific functions.
    // The idea is to abstract library functionality without losing performance.
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        void BufferMeshData(MeshData* data);
        void SetupShaderAttributes(ShaderProgram* shader);

        void Draw() { (this->*m_DrawFunc)(); };

        std::string GetName() const { return m_Name; };
        std::string GetFileName() const { return m_FileName; };

        void SetName(std::string name) { m_Name = name; }
        void SetFileName(std::string file) { m_FileName = file; }
        void SetPrimitiveType(GLenum type) { m_PrimitiveType = type; };
        void ToggleWireframe();

    private:
        // Handles
        GLuint m_VBO = 0;
        GLuint m_EBO = 0;
        GLuint m_VAO = 0; // #TODO Do meshes need a shader list to support VAOs for many shaders

        // Variables
        GLenum m_PrimitiveType = GL_TRIANGLES;
        std::string m_Name = gc_DefaultStringValue;
        std::string m_FileName = gc_DefaultStringValue;

        MeshBufferInfo m_BufferData;
        char* PackModelData(MeshData* data);

        void DrawElements(); // Use IBO
        void DrawArrays(); // Draw raw vertex data
        void NullDraw(); // For invalid or uninitialized data

        MeshFunction m_DrawFunc = &Mesh::NullDraw;
    };

}
