#ifndef _ShaderProgramData_H_
#define _ShaderProgramData_H_

#include <string>
#include <vector>

struct ShaderProgramData
{
	std::string s_Name = "Uninitialized";

	std::string s_vertName = "Uninitialized";
	std::string s_fragName = "Uninitialized";
	std::string s_geoName = "Uninitialized";

	GLuint s_programHandle = 0;

	GLuint s_vertHandle = 0;
	GLuint s_fragHandle = 0;
	GLuint s_geoHandle = 0;

	std::vector<std::string> s_Attributes;
	std::vector<std::string> s_Uniforms;

	ShaderProgramData() {}
	~ShaderProgramData() {}
};

#endif // !_ShaderProgramData_H_
