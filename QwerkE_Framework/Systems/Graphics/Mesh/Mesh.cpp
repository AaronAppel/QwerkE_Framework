#include "Mesh.h"
#include "VertexData.h"
#include "../ShaderProgram/ShaderProgram.h"
#include "../GraphicsUtilities/GraphicsHelpers.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"

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
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Mesh::BufferMeshData(int numVerts, VertexData* vertices, int numIndices, unsigned int* indices)
{
	if (m_VertCount != 0) { assert(false); } // Mesh not empty
	// TODO:: If VBO has data in it then we need to handle
	// deletion and re-assignment of new data.

	m_VertCount = numVerts;
	m_IndexCount = numIndices;

	/* Set draw function */
	if (m_IndexCount > 0) { m_DrawFunc = &Mesh::DrawElements; }
	else { m_DrawFunc = &Mesh::DrawArrays; }

	/* Buffer mesh data into GPU RAM */
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * m_VertCount, vertices, GL_STATIC_DRAW); // (target, size, data, static/dynamic)

	if (m_IndexCount > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_IndexCount, indices, GL_STATIC_DRAW);
	}

	// unbind for safety
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CheckGraphicsErrors(__FILE__, __LINE__);
}

void Mesh::SetupShaderAttributes(ShaderProgram* shader)
{
	CheckGraphicsErrors(__FILE__, __LINE__);

	if (shader == nullptr) { return; } // null ShaderProgram*
	GLuint t_ShaderHandle = shader->GetProgram();

	/* Setup VAO */
	glBindVertexArray(m_VAO); // Bind
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	CheckGraphicsErrors(__FILE__, __LINE__);

	/* Assign ShaderProgram() attribute data */
	std::vector<std::string> attributes = shader->GetAttributeList();
	for (unsigned int i = 0; i < attributes.size(); i++)
	{
		if (StringCompare(attributes.at(i), "Position"))
		{
			GLuint aPos = glGetAttribLocation(t_ShaderHandle, DispStrCombine(Helper_GetAttributePrefix(), "Position").c_str());
			if (aPos != -1)
			{
				glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, position));
				glEnableVertexAttribArray(aPos); // size of vertexData
			}
		}
		if (StringCompare(attributes.at(i), "Color"))
		{
			GLuint aColor = glGetAttribLocation(t_ShaderHandle, DispStrCombine(Helper_GetAttributePrefix(), "Color").c_str());
			if (aColor != -1)
			{
				glVertexAttribPointer(aColor, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, color));
				glEnableVertexAttribArray(aColor);
			}
		}
		if (StringCompare(attributes.at(i), "UV"))
		{
			GLuint aUV = glGetAttribLocation(t_ShaderHandle, DispStrCombine(Helper_GetAttributePrefix(), "UV").c_str());
			if (aUV != -1)
			{
				glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, UV));
				glEnableVertexAttribArray(aUV);
			}
		}
		if (StringCompare(attributes.at(i), "Normal"))
		{
			GLuint aNormal = glGetAttribLocation(t_ShaderHandle, DispStrCombine(Helper_GetAttributePrefix(), "Normal").c_str());
			if (aNormal != -1)
			{
				glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid*)offsetof(VertexData, normal));
				glEnableVertexAttribArray(aNormal);
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
	// if read acces violation it is because SetupAttributes was not called
	glDrawElements(m_PrimitiveType, m_IndexCount, GL_UNSIGNED_INT, 0); // (drawMode, numIndices, EBOType, dataOffset)
	glBindVertexArray(0);
}

void Mesh::DrawArrays()
{
	glBindVertexArray(m_VAO); // Enable attribute arrays
	glDrawArrays(m_PrimitiveType, 0, m_VertCount); // (drawMode, firstIndex, numVerts)
	glBindVertexArray(0);
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
