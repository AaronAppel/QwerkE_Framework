#include "ShaderProgram.h"
#include "../../Systems/ShaderFactory/ShaderFactory.h"
#include "../../Systems/ServiceLocator.h"
#include "ShaderComponent.h"

void ShaderProgram::RecompileShaderType(GLenum type, const char* shaderData)
{
	ShaderComponent* result = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->GenerateShaderFromData(type, shaderData);

	if (result)
	{
		// TODO: Handle old shader value
		switch (type)
		{
		case GL_VERTEX_SHADER:
			result->SetName(m_VertShader->GetName());
			m_VertShader = result;
			break;
		case GL_FRAGMENT_SHADER:
			result->SetName(m_FragShader->GetName());
			m_FragShader = result;
			break;
		case GL_GEOMETRY_SHADER:
			result->SetName(m_GeoShader->GetName());
			m_GeoShader = result;
			break;
		}
		// link new shader and re
		((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->LinkCreatedShaderProgram(this);
	}
}

/* Attribute value assignment */
// void SetAttributeData() {} good idea?

/* Uniform value assignment */
// int
void ShaderProgram::SetUniformInt1(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value);
}
void ShaderProgram::SetUniformInt2(const char* name, int value1, int value2)
{
	glUniform2i(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2);
}
void ShaderProgram::SetUniformInt3(const char* name, int value1, int value2, int value3)
{
	glUniform3i(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2, value3);
}
void ShaderProgram::SetUniformInt4(const char* name, int value1, int value2, int value3, int value4)
{
	glUniform4i(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2, value3, value4);
}
// float
void ShaderProgram::SetUniformFloat1(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value);
}
void ShaderProgram::SetUniformFloat2(const char* name, float value1, float value2)
{
	glUniform2f(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2);
}
void ShaderProgram::SetUniformFloat3(const char* name, float value1, float value2, float value3)
{
	glUniform3f(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2, value3);
}
void ShaderProgram::SetUniformFloat4(const char* name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2, value3, value4);
}
// matrix
void ShaderProgram::SetUniformMat4(const char* name, const GLfloat* matrix)
{
	// TODO: Improve uniform prefixing
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), 1, GL_FALSE, matrix);
}