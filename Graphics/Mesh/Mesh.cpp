#include "Mesh.h"
#include "MeshData.h"
#include "../Shader/ShaderProgram.h"
#include "../GraphicsUtilities/GraphicsHelpers.h"
#include "../Shader/ShaderProgram.h"
#include "../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <string>
#include <assert.h>
#include <vector>

Mesh::Mesh()
{
 	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);
}

Mesh::~Mesh()
{
	// Move code to a function to be used for unloading mesh data
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::BufferMeshData(MeshData* data)
{
	// TODO: Return true or false to communicate successful buffering?
	if (!data)
	{
		QwerkE::LogError(__FILE__, __LINE__, "MeshData is null!");
		assert(false);
	}

	// TODO: If VBO has data in it, handle deletion and re-assignment of new data
	if (m_BufferData.numPositions != 0) { // Empty mesh
		QwerkE::LogError(__FILE__, __LINE__, "Mesh already has vertex data!");
		assert(false);
	}

	// Save buffer info for later use
	m_BufferData = data->BufferInfo();

	if (m_BufferData.BufferSize() == 0)
	{
		QwerkE::LogError(__FILE__, __LINE__, "Error buffering mesh vertex data!");
		assert(false);
	}

	// Pack model data into a contiguous buffer
	char* buffer = PackModelData(data);

	// Buffer mesh data into GPU RAM
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_BufferData.BufferSize(), buffer, GL_STATIC_DRAW); // (target, size, data, static/dynamic)

	if (m_BufferData.numIndices > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_BufferData.numIndices, data->indices.data(), GL_STATIC_DRAW);
	}

	// unbind for safety
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CheckGraphicsErrors(__FILE__, __LINE__);

	delete[] buffer;
}

// TODO: Could create a reusable packer function. Maybe with variables arguments
char* Mesh::PackModelData(MeshData* data)
{
	char* buffer = new char[m_BufferData.BufferSize()];
	int currentIndex = 0;

	// Write raw data into a buffer, but only if it was loaded into MeshData
	memcpy(&buffer[currentIndex], data->positions.data(), data->positions.size() * sizeof(vec3));
	currentIndex += data->positions.size() * sizeof(vec3);
	memcpy(&buffer[currentIndex], data->colors.data(), data->colors.size() * sizeof(vec4));
	currentIndex += data->colors.size() * sizeof(vec4);
	memcpy(&buffer[currentIndex], data->UVs.data(), data->UVs.size() * sizeof(vec2));
	currentIndex += data->UVs.size() * sizeof(vec2);
	memcpy(&buffer[currentIndex], data->normals.data(), data->normals.size() * sizeof(vec3));
	currentIndex += data->normals.size() * sizeof(vec3);
	memcpy(&buffer[currentIndex], data->tangents.data(), data->tangents.size() * sizeof(vec3));
	currentIndex += data->tangents.size() * sizeof(vec3);
	memcpy(&buffer[currentIndex], data->bitangents.data(), data->bitangents.size() * sizeof(vec3));
	// currentIndex += data->bitangents.size() * sizeof(vec3);

	return buffer;
}

void Mesh::SetupShaderAttributes(ShaderProgram* shader)
{
	// Tell the shader where to look for the mesh data.
	// This needs to be called on shader changes but does not
	// affect the mesh at all.

	CheckGraphicsErrors(__FILE__, __LINE__);

	if (shader == nullptr) { return; } // null ShaderProgram*

	// Set draw function
	if (m_BufferData.numIndices > 0) { m_DrawFunc = &Mesh::DrawElements; } // draw using elements
	else if (m_BufferData.numPositions > 0) { m_DrawFunc = &Mesh::DrawArrays; } // no IBOs
	else { // not initialized
		QwerkE::LogWarning(__FILE__, __LINE__, "Mesh assigned null draw method");
		m_DrawFunc = &Mesh::NullDraw;
	}

	// Setup VAO
	glBindVertexArray(m_VAO); // Bind
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	CheckGraphicsErrors(__FILE__, __LINE__);

	// Assign ShaderProgram() attribute data
	const std::vector<std::string>* attributes = shader->SeeAttributes();
	int vertexDataStride = 0; // m_DataSizes.Stride();

	for (unsigned int i = 0; i < attributes->size(); i++)
	{
		if (StringCompare(attributes->at(i), "Position"))
		{
			GLuint aPos = glGetAttribLocation(shader->GetProgram(), DispStrCombine(Helper_GetAttributePrefix(), "Position").c_str());
			if (aPos != -1)
			{
				glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, vertexDataStride, (GLvoid*)m_BufferData.PositionOff()); // GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
				glEnableVertexAttribArray(aPos);
			}
		}
		else if (StringCompare(attributes->at(i), "Color"))
		{
			GLuint aColor = glGetAttribLocation(shader->GetProgram(), DispStrCombine(Helper_GetAttributePrefix(), "Color").c_str());
			if (aColor != -1)
			{
				glVertexAttribPointer(aColor, 4, GL_FLOAT, GL_FALSE, vertexDataStride, (GLvoid*)m_BufferData.ColorOff());
				glEnableVertexAttribArray(aColor);
			}
		}
		else if (StringCompare(attributes->at(i), "UV"))
		{
			GLuint aUV = glGetAttribLocation(shader->GetProgram(), DispStrCombine(Helper_GetAttributePrefix(), "UV").c_str());
			if (aUV != -1)
			{
				glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, vertexDataStride, (GLvoid*)m_BufferData.UVOff());
				glEnableVertexAttribArray(aUV);
			}
		}
		else if (StringCompare(attributes->at(i), "Normal"))
		{
			GLuint aNormal = glGetAttribLocation(shader->GetProgram(), DispStrCombine(Helper_GetAttributePrefix(), "Normal").c_str());
			if (aNormal != -1)
			{
				glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, vertexDataStride, (GLvoid*)m_BufferData.NormalOff());
				glEnableVertexAttribArray(aNormal);
			}
		}
		else if (StringCompare(attributes->at(i), "Tangent"))
		{
			GLuint aTangent = glGetAttribLocation(shader->GetProgram(), DispStrCombine(Helper_GetAttributePrefix(), "Tangent").c_str());
			if (aTangent != -1)
			{
				glVertexAttribPointer(aTangent, 3, GL_FLOAT, GL_FALSE, vertexDataStride, (GLvoid*)m_BufferData.TangentsOff());
				glEnableVertexAttribArray(aTangent);
			}
		}
		else if (StringCompare(attributes->at(i), "Bitangent"))
		{
			GLuint aBitangent = glGetAttribLocation(shader->GetProgram(), DispStrCombine(Helper_GetAttributePrefix(), "Bitangent").c_str());
			if (aBitangent != -1)
			{
				glVertexAttribPointer(aBitangent, 3, GL_FLOAT, GL_FALSE, vertexDataStride, (GLvoid*)m_BufferData.BitangentsOff());
				glEnableVertexAttribArray(aBitangent);
			}
		}
	}
	// TODO: Check if vertex arrays should to be disabled after drawing
	glBindVertexArray(0); // Unbind
	CheckGraphicsErrors(__FILE__, __LINE__);
}

void Mesh::DrawElements()
{
	glBindVertexArray(m_VAO); // Enable attribute arrays
	// if read access violation it is because SetupAttributes was not called
	glDrawElements(m_PrimitiveType, m_BufferData.numIndices, GL_UNSIGNED_INT, 0); // (drawMode, numIndices, EBOType, dataOffset)
	glBindVertexArray(0); // unbind
}

void Mesh::DrawArrays()
{
	glBindVertexArray(m_VAO); // Enable attribute arrays
	glDrawArrays(m_PrimitiveType, 0, m_BufferData.numPositions); // (drawMode, firstIndex, numVerts)
	glBindVertexArray(0); // unbind
}

void Mesh::NullDraw()
{
	// TODO:
	// SetupShaderAttributes();
	// if (m_IndexCount > 0) { DrawElements(); }
	// else if (m_VertCount > 0) { DrawArrays(); }
}

void Mesh::ToggleWireframe()
{
	if (m_PrimitiveType == GL_TRIANGLES) // TEMP: hacked in for now
	{
		m_PrimitiveType = GL_POINTS;
	}
	else
	{
		m_PrimitiveType = GL_TRIANGLES;
	}
}

void Mesh::DestroyMesh()
{
	// TODO:: Find a good way to allow for mesh data re-assignment
}
