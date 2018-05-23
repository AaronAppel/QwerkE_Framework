#ifndef _ShaderProgramData_H_
#define _ShaderProgramData_H_

#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../GraphicsUtilities/GraphicsHelpers.h"

#include <string>
#include <vector>

class ShaderComponent;

struct ShaderProgramData
{
	ShaderProgramData() {}
	~ShaderProgramData() {}

	std::string s_Name = "Uninitialized";

	std::string s_vertName = "Uninitialized";
	std::string s_fragName = "Uninitialized";
	std::string s_geoName = "Uninitialized";

	GLuint s_programHandle = 0;

	ShaderComponent* s_vertShader = nullptr;
	ShaderComponent* s_fragShader = nullptr;
	ShaderComponent* s_geoShader = nullptr;

	std::vector<std::string> s_Attributes;
	std::vector<std::string> s_Uniforms;

	void Use() { glUseProgram(s_programHandle); }

	/* Uniform value assignment */
	// void SetAttributeData() {} good idea?

	/* Uniform value assignment */
	// int
	void SetUniformInt1(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value);
	}
	void SetUniformInt2(const char* name, int value1, int value2)
	{
		glUniform2i(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2);
	}
	void SetUniformInt3(const char* name, int value1, int value2, int value3)
	{
		glUniform3i(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2, value3);
	}
	void SetUniformInt4(const char* name, int value1, int value2, int value3, int value4)
	{
		glUniform4i(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2, value3, value4);
	}
	// float
	void SetUniformFloat1(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value);
	}
	void SetUniformFloat2(const char* name, float value1, float value2)
	{
		glUniform2f(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2);
	}
	void SetUniformFloat3(const char* name, float value1, float value2, float value3)
	{
		glUniform3f(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2, value3);
	}
	void SetUniformFloat4(const char* name, float value1, float value2, float value3, float value4)
	{
		glUniform4f(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), value1, value2, value3, value4);
	}
	// matrix
	void SetUniformMat4(const char* name, const GLfloat* matrix)
	{
		// TODO: Improve uniform prefixing
		glUniformMatrix4fv(glGetUniformLocation(s_programHandle, DispStrCombine(Helper_GetUniformPrefix(), name).c_str()), 1, GL_FALSE, matrix);
	}
};

#endif // !_ShaderProgramData_H_
