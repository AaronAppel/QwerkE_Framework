#ifndef _ShaderComponent_H_
#define _ShaderComponent_H_

#include <string>

class ShaderComponent
{
public:
	ShaderComponent();
	ShaderComponent(const char* shaderPath);
	~ShaderComponent();

private:
	std::string m_Name = "Uninitialized";
	std::string m_Type = "Uninitialized";

	const char* m_ShaderString = nullptr;
	GLuint m_ShaderHandle = 0;
};

#endif // !_ShaderComponent_H_
