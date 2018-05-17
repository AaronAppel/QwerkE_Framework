#ifndef _ShaderProgram_H_
#define _ShaderProgram_H_

// This class requires access to OpenGL functions.
// https ://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade

#include "../../../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include <vector>

// TODO: Remember to specify floating point precision

class ShaderProgram
{
public:
	ShaderProgram(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir);
	ShaderProgram();
	~ShaderProgram();

	/* Setup */
	bool Init(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir);

    // TODO: GLuint ReCompile1Shader(GLenum shaderType); // uses m_????String that might have been changed
    // TODO: GLuint ReCompile1Shader(GLenum shaderType, const char* shaderFileDir); // recompile 1 shader file
	GLuint ReCompile1Shader(GLenum shaderType, const char* shaderString); // recompile 1 shader by type (vert, frag, geo)
    bool ReCompileShader(); // recompile shader

	/* Utility */
	void SetShaderStringData(GLenum shaderType, const char* shaderString);
	void Use() { glUseProgram(m_ProgramHandle); };
	void CleanUp();

	/* Getters + Setters */
	// Getters
	// TODO: GLuint GetShaderName() {}
	GLuint GetProgram() { return m_ProgramHandle; };
    const char* GetVertString() { return m_VertString; };
    const char* GetFragString() { return m_FragString; };
    const char* GetGeoString() { return m_GeoString; };

	/* Texture setup */
	void SetupTextures(GLuint textures[], int numTextures);

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
	// matrices
	void SetUniformMat4(const char* name, const GLfloat* matrix);

	// uniform list
	std::vector<std::string> GetAttributeList() { return m_AttributeList; };
	std::vector<std::string> GetUniformList() { return m_UniformList; };
	void SetUniformList(std::vector<std::string> list) { m_UniformList = list; };

private:
	/* Variables */
	const char* m_VertString = 0;
	const char* m_FragString = 0;
	const char* m_GeoString = 0;

	GLuint m_VertShaderHandle = 0;
	GLuint m_FragShaderHandle = 0;
	GLuint m_GeoShaderHandle = 0;
	GLuint m_ProgramHandle = 0;

	/* Functionality */
    bool BuildShaderProgram(); // return BuildSucceeded == true
	GLuint CompileShader(GLenum shaderType, const char* shaderString);
	GLuint LinkShaders(GLuint vert, GLuint frag, GLuint geo);

	void SetupAttributeList(); // TODO:: Parse m_VertString and m_FragString for all attributes and store them in m_AttributesList
	void SetupUniformList(); // TODO:: Parse shaderstrings and m_FragString for all uniforms and store them in m_UniformList
	std::vector<std::string> m_AttributeList; // Shader->SetupAttributes() sets up values. Mesh->SetupShaderAttributes() uses the list to enable vertex array data.
	std::vector<std::string> m_UniformList; // GameObject->RenderRoutine->Draw() sets values
};

#endif //_ShaderProgram_H_
