#ifndef _Mesh_H_
#define _Mesh_H_

#include "../QwerkE_Common/Libraries/glew/GL/glew.h"
#include <string>

struct VertexData;
struct ShaderProgram;
class Mesh;

typedef void (Mesh::*MeshFunction)(); // Draw function

// TODO: Use macro functions to replace OpenGL specific functions.
// The idea is to abstract library functionality without losing speed.
class Mesh
{
public:
	Mesh();
	~Mesh();

	/* Setup */
	void BufferMeshData(int numVerts, VertexData* verts, int numIndices, unsigned int* indices);
	void SetupShaderAttributes(ShaderProgram* shader);

	/* Draw */
	void Draw() { (this->*m_DrawFunc)(); }; // Call appropriate Draw() function

	/* Getters + Setters */
	// Getters
	std::string GetName() const { return m_Name; };
	std::string GetFileName() const { return m_FileName; };

	// Setters
	void SetName(std::string name) { m_Name = name; }
	void SetFileName(std::string file) { m_FileName = file; }
	void SetPrimitiveType(GLenum type) { m_PrimitiveType = type; };
	void ToggleWireframe(); // TODO: Improve

	/* Cleanup */
	void DestroyMesh(); // Used for assigning new data to an already initialize mesh

private:
	/* Handles */
	GLuint m_VBO = 0;
	GLuint m_EBO = 0;
	GLuint m_VAO = 0;

	/* Variables */
	GLuint m_VertCount = 0; // TODO: Is storing this necessary?
	GLuint m_IndexCount = 0;
	GLenum m_PrimitiveType = GL_TRIANGLES;
	std::string m_Name = "Uninitialized";
	std::string m_FileName = "Uninitialized";

	/* Draw functionality */
	MeshFunction m_DrawFunc = &Mesh::NullDraw;

	void DrawElements(); // Use IBO
	void DrawArrays(); // Draw raw vertex data
	void NullDraw(); // Not setup
};

#endif //!_Mesh_H_
