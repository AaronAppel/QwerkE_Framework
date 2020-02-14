#ifndef _Mesh_H_
#define _Mesh_H_

#include "../Headers/QwerkE_Global_Constants.h"
#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <string>

namespace QwerkE {

    struct VertexData;
    class ShaderProgram;
    class Mesh;
    struct MeshData;

    typedef void (QwerkE::Mesh::* MeshFunction)(); // Draw function

    // TODO: Use macro functions to replace OpenGL specific functions.
    // The idea is to abstract library functionality without losing performance.
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        // Setup
        void BufferMeshData(MeshData* data);
        void SetupShaderAttributes(ShaderProgram* shader);

        // Drawing
        void Draw() { (this->*m_DrawFunc)(); }; // Call appropriate Draw() function

        // Getters
        std::string GetName() const { return m_Name; };
        std::string GetFileName() const { return m_FileName; };

        // Setters
        void SetName(std::string name) { m_Name = name; }
        void SetFileName(std::string file) { m_FileName = file; }
        void SetPrimitiveType(GLenum type) { m_PrimitiveType = type; };
        void ToggleWireframe(); // TODO: Improve

        // Cleanup
        // TODO: Maybe EmptyMesh() instead of DestroyMesh()
        void DestroyMesh(); // Used for assigning new data to an already initialize mesh

    private:
        // Handles
        GLuint m_VBO = 0;
        GLuint m_EBO = 0;
        GLuint m_VAO = 0; // TODO: Do meshes need a shader list to support VAOs for many shaders

        // Variables
        GLenum m_PrimitiveType = GL_TRIANGLES;
        std::string m_Name = gc_DefaultStringValue;
        std::string m_FileName = gc_DefaultStringValue;

        MeshBufferInfo m_BufferData;
        char* PackModelData(MeshData* data);

        /* Draw functionality */
        MeshFunction m_DrawFunc = &Mesh::NullDraw;

        void DrawElements(); // Use IBO
        void DrawArrays(); // Draw raw vertex data
        void NullDraw(); // Not setup or invalid data
    };

}
#endif //!_Mesh_H_
