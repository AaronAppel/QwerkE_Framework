#include "../../../QwerkE_Defines.h"
#include "../../../QwerkE_Platform.h" // TODO: Need?
#include "../../Graphics/Graphics_Header.h"
#include "../../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../GraphicsUtilities/GraphicsHelpers.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <cstring>
#include <string> // TODO: 1 use at bottom could be avoided

ShaderProgram::ShaderProgram(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir)
{
	Init(vertFileDir, fragFileDir, geoFileDir);
}

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
	CleanUp();
}

bool ShaderProgram::Init(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir)
{
	// load strings
	if (m_VertString == 0 && vertFileDir != 0)
		m_VertString = LoadCompleteFile(vertFileDir, 0);
	if (m_FragString == 0 && fragFileDir != 0)
		m_FragString = LoadCompleteFile(fragFileDir, 0);
	if (m_GeoString == 0 && geoFileDir != 0)
		m_GeoString = LoadCompleteFile(geoFileDir, 0);
	// otherwise loaded by ShaderFactory

    return BuildShaderProgram();
}
// Returns new shader handle is successful, else 0
GLuint ShaderProgram::ReCompile1Shader(GLenum shaderType, const char* shaderString)
{
	// Note: Future code may try to re-use shaders. If that is the case then they
	// cannot be delete when a program is no longer using it. Maybe keep track of shaders
	// separately and use a reference counter to delete.

	// Note: Shaders are not unlinked before linking to a new program in case the linking
	// fails. OpenGL will throw an error message. Consider finding a better solution.
	// Maybe glDetachShader()

	// TODO: Can cleanup the 3 condition if statements everywhere with a GLuint*.

    GLuint handle = CompileShader(shaderType, shaderString); // create a new shader

	if (handle > 0) // compiled
	{
		// temp handles in case linking fails
		GLuint tempVert = m_VertShaderHandle;
		GLuint tempFrag = m_FragShaderHandle;
		GLuint tempGeo = m_GeoShaderHandle;

		// overwrite the 1 shader being recompiled
		if (shaderType == GL_VERTEX_SHADER) { tempVert = handle; }
		else if (shaderType == GL_FRAGMENT_SHADER) { tempFrag = handle; }
		else if (shaderType == GL_GEOMETRY_SHADER) { tempGeo = handle; }

		// create a new and linked program
        GLuint result = LinkShaders(tempVert, tempFrag, tempGeo);

		CheckGraphicsErrors(__FILE__, __LINE__); // Currently throws error because shaders are already linked

        if (result > 0) // linked
        {
			// delete old shader
			if (shaderType == GL_VERTEX_SHADER) { glDeleteShader(m_VertShaderHandle); }
			else if (shaderType == GL_FRAGMENT_SHADER) { glDeleteShader(m_FragShaderHandle); }
			else if (shaderType == GL_GEOMETRY_SHADER) { glDeleteShader(m_GeoShaderHandle); }

			// save new shader handle
			if (shaderType == GL_VERTEX_SHADER) { m_VertShaderHandle = handle; }
			else if (shaderType == GL_FRAGMENT_SHADER) { m_FragShaderHandle = handle; }
			else if (shaderType == GL_GEOMETRY_SHADER) { m_GeoShaderHandle = handle; }

			// save new string data
			if (shaderType == GL_VERTEX_SHADER)
			{
				delete[] m_VertString;
				m_VertString = shaderString;
			}
			else if (shaderType == GL_FRAGMENT_SHADER)
			{
				delete[] m_FragString;
				m_FragString = shaderString;
			}
			else if (shaderType == GL_GEOMETRY_SHADER)
			{
				delete[] m_GeoString;
				m_GeoString = shaderString;
			}

            glDeleteProgram(m_ProgramHandle);
            m_ProgramHandle = result; // update program handle
        }
        else
        {
            OutputPrint("\nRecompile1Shader(): Error linking shaders!");
			glDeleteProgram(result); // TODO: needed?
			glDeleteShader(handle);
        }
	}
	else
	{
        OutputPrint("ReCompileShader(): Error recompiling %s. No changes were made.\n");// TODO: Nice message with GetShaderName(shaderString));
		glDeleteShader(handle);
	}
	CheckGraphicsErrors(__FILE__, __LINE__);
	return handle;
}

bool ShaderProgram::ReCompileShader()
{
    // TODO: How to handle data deletion and re-initialization?

    return BuildShaderProgram(); // build using new string data
}

void ShaderProgram::SetShaderStringData(GLenum shaderType, const char* shaderString)
{
	if (shaderString != nullptr) // if nullptr do not alter

	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		delete[] m_VertString;
		m_VertString = shaderString;
		break;
	case GL_FRAGMENT_SHADER:
		delete[] m_FragString;
		m_FragString = shaderString;
		break;
	case GL_GEOMETRY_SHADER:
		delete[] m_GeoString;
		m_GeoString = shaderString;
		break;
	}
}

void ShaderProgram::CleanUp()
{
	if (m_VertString)
		delete[] m_VertString;
	if (m_FragString)
		delete[] m_FragString;
	if (m_GeoString)
		delete[] m_GeoString;

	if (m_VertShaderHandle) // destroy shaders
	{
		glDetachShader(m_ProgramHandle, m_VertShaderHandle);
		glDeleteShader(m_VertShaderHandle);
	}
	if (m_FragShaderHandle)
	{
		glDetachShader(m_ProgramHandle, m_FragShaderHandle);
		glDeleteShader(m_FragShaderHandle);
	}
	if (m_GeoShaderHandle)
	{
		glDetachShader(m_ProgramHandle, m_GeoShaderHandle);
		glDeleteShader(m_GeoShaderHandle);
	}
	if (m_ProgramHandle)
		glDeleteProgram(m_ProgramHandle);

	m_VertString = 0; // reset strings
	m_FragString = 0;
	m_GeoString = 0;

	m_VertShaderHandle = 0;	// reset handles
	m_FragShaderHandle = 0;
	m_GeoShaderHandle = 0;
	m_ProgramHandle = 0;
}

void ShaderProgram::SetShaderName()
{
	// TODO: Improve logic
	if (m_VertString)
	{
		std::string test = m_VertString;
		test = test.substr(3, test.find_first_of('.') - 1 - 2);
		m_Name = test;
	}
	else if (m_FragString) m_FragShaderHandle = CompileShader(GL_FRAGMENT_SHADER, m_FragString);
	else if (m_GeoString) m_GeoShaderHandle = CompileShader(GL_GEOMETRY_SHADER, m_GeoString);
	else
		m_Name = "Null";
}

bool ShaderProgram::BuildShaderProgram()
{
    // shader strings should have been loaded by Init(), ShaderFactory, or SetStringData()
    // compile shaders
    if (m_VertString) m_VertShaderHandle = CompileShader(GL_VERTEX_SHADER, m_VertString);
    if (m_FragString) m_FragShaderHandle = CompileShader(GL_FRAGMENT_SHADER, m_FragString);
    if (m_GeoString) m_GeoShaderHandle = CompileShader(GL_GEOMETRY_SHADER, m_GeoString);

    if (m_VertShaderHandle == 0 && m_FragShaderHandle == 0 && m_GeoShaderHandle == 0) // no valid program
    {
        CleanUp(); // deallocate memory
        assert(0); // DEBUG: Error compiling ShaderProgram().
        return false;
    }

    // link shaders
    // TODO: Can you even make a vert or frag only shader? Do I need asserts for that?
    m_ProgramHandle = LinkShaders(m_VertShaderHandle, m_FragShaderHandle, m_GeoShaderHandle);
    if (m_ProgramHandle == 0) { return false; } // check if null program

	SetupAttributeList();
	SetupUniformList();
	SetShaderName();
    return true; // shader built properly
}
// Returns new shader handle is successful, else 0
GLuint ShaderProgram::CompileShader(GLenum shaderType, const char* shaderString)
{
	GLuint shaderHandle = glCreateShader(shaderType); // fails if context is not current for GLFW
	glShaderSource(shaderHandle, 1, &shaderString, NULL);
	glCompileShader(shaderHandle);

	GLint success = 0;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// Error compiling shader
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);

		const char* shaderTypeString = nullptr;
		if (shaderType == GL_VERTEX_SHADER)
			shaderTypeString = "GL_VERTEX_SHADER";
		else if (shaderType == GL_FRAGMENT_SHADER)
			shaderTypeString = "GL_FRAGMENT_SHADER";
		else if (shaderType == GL_GEOMETRY_SHADER)
			shaderTypeString = "GL_GEOMETRY_SHADER";

		char* next_token = 0;
		char* ShaderName = strtok_s((char*)shaderString, "\n", &next_token);
		// TODO: error reads as garbage characters.
		OutputPrint("\n%s: ShaderProgram: CompileShader() %s compile error-> ", ShaderName, shaderTypeString);
		OutputPrint(infoLog); // OpenGL message

		// cleanup
		glDeleteShader(shaderHandle);
		shaderHandle = 0;
	}

	return shaderHandle;
}
// Returns new program handle if successful, else 0
GLuint ShaderProgram::LinkShaders(GLuint vert, GLuint frag, GLuint geo)
{
	GLuint result = 0;
	result = glCreateProgram(); // create new program

	// TODO: Handle NULL handles
    // TODO: Handle error when attaching linked shaders. May want to de-link before attaching
	if (vert) glAttachShader(result, vert); // link vertex shader
	if (frag) glAttachShader(result, frag); // link fragment shader
	if (geo) glAttachShader(result, geo); // link geometry shader

	glLinkProgram(result);
	CheckGraphicsErrors(__FILE__, __LINE__);
	// GL_INVALID_VALUE is generated if program is not a value generated by OpenGL.
	// GL_INVALID_OPERATION is generated if program is not a program object.
	// GL_INVALID_OPERATION is generated if program is the currently active program object and transform feedback mode is active.

	GLint success;
	glGetProgramiv(result, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(result, 512, NULL, infoLog);
		// OutputMessage("\nShaderProgram: LinkShaders() linking error-> ");
		// OutputMessage(infoLog); // OpenGL message

		CleanUp(); // deallocate memory
		return false;
	}

	glDeleteShader(vert); // no longer needed
	glDeleteShader(frag);
	glDeleteShader(geo);

    CheckGraphicsErrors(__FILE__, __LINE__);
	return result;
}
/* Texture setup */
void ShaderProgram::SetupTextures(GLuint textures[], int numTextures)
{
	for (int i = 0; i < numTextures; i++)
	{
		std::string id = "Texture";
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		id.append(std::to_string(i));
		this->SetUniformInt1(id.c_str(), i);
	}
}
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
// private uniform and attribute setup
void ShaderProgram::SetupAttributeList()
{
	// TODO: Handle "in" and "attribute"
	if (m_VertString == 0)
	{
		return;
	}
	// store string in temp buffer
	char* buffer = (char*)DeepCopyString(m_VertString); // Delete buffer when done

	// store lines in std::vector
	char* next_token = 0;
	char* line = strtok_s(buffer, "\n", &next_token);

	std::vector<std::string> vertStringList;

	while (line)
	{
		//OutputMessage("%s\n", line);
		vertStringList.push_back(line);
		line = strtok_s(0, "\n", &next_token);
	}
	delete[] buffer; // cleanup

	/* Populate .vert attributes */
	// vert
	for (unsigned int i = 0; i < vertStringList.size(); i++) // stringList.size() = number of lines in file
	{
		std::string loopString = vertStringList.at(i);
		if (loopString.at(0) == 'i' && loopString.find("in") != loopString.npos) // starts with 'i' and has "in" in line
		{
            unsigned int size = 20;
			std::string t_Variable;
			sscanf_s((char*)loopString.c_str(), "%*s %*s %s", (char*)t_Variable.c_str(), size);
			strtok_s((char*)t_Variable.c_str(), ";", &next_token); // remove ';' from end

			std::string loopString;
			int counter = 2; // remove 'u_' from beginning
			while (t_Variable[counter] != '\0')
			{
				loopString.push_back(t_Variable[counter]);
				counter++;
			}

			m_AttributeList.push_back(loopString);
		}
		// duplicates caught in .vert by compiler
	}
}
void ShaderProgram::SetupUniformList()
{
	if (m_VertString == 0 || m_FragString == 0)
	{
		return;
	}
	// vert
	// store string in temp buffer
	char* buffer = (char*)DeepCopyString(m_VertString);

	// store lines in std::vector
	char* next_token = 0;
	char* line = strtok_s(buffer, "\n", &next_token);

	std::vector<std::string> vertStringList;
	std::vector<std::string> fragStringList;
	// TODO: Geo shader uniforms

	while (line)
	{
		//OutputMessage("%s\n", line);
		vertStringList.push_back(line);
		line = strtok_s(0, "\n", &next_token);
	}
	delete[] buffer; // cleanup

					 // frag
	buffer = (char*)DeepCopyString(m_FragString);
	line = strtok_s(buffer, "\n", &next_token);

	while (line)
	{
		//OutputMessage("%s\n", line);
		fragStringList.push_back(line);
		line = strtok_s(0, "\n", &next_token);
	}
	delete[] buffer; // cleanup

	/* Populate .vert uniforms */
	for (unsigned int i = 0; i < vertStringList.size(); i++) // stringList.size() = number of lines in file
	{
		std::string loopString = vertStringList.at(i);
		if (loopString.at(0) == 'u' && loopString.find("uniform") != loopString.npos) // starts with 'u' and has uniform in line
		{
            unsigned int size = 20;
			std::string t_Variable;
			sscanf_s((char*)loopString.c_str(), "%*s %*s %s", (char*)t_Variable.c_str(), size);
			strtok_s((char*)t_Variable.c_str(), ";", &next_token); // remove ';' from end

			std::string loopString;
			int counter = 2; // remove 'u_' from beginning
			while (t_Variable[counter] != '\0')
			{
				loopString.push_back(t_Variable[counter]);
				counter++;
			}
			// TODO: Check for duplicates? Caught by compiler?
			m_UniformList.push_back(loopString);
		}
	}
	/* Populate .frag uniforms */
	for (unsigned int i = 0; i < fragStringList.size(); i++) // stringList.size() = number of lines in file
	{
		std::string loopString = fragStringList.at(i);
		if (loopString.at(0) == 'u' && loopString.find("uniform") != loopString.npos)
		{
            unsigned int size = 20;
			std::string t_Variable;
			sscanf_s((char*)loopString.c_str(), "%*s %*s %s", (char*)t_Variable.c_str(), size);
			strtok_s((char*)t_Variable.c_str(), ";", &next_token); // remove ';' from end

			std::string loopString;
			int counter = 2; // remove 'u_' from beginning
			while (t_Variable[counter] != '\0')
			{
				loopString.push_back(t_Variable[counter]);
				counter++;
			}
			// TODO: Check for duplicates? Caught by compiler?
			m_UniformList.push_back(loopString);
		}
	}
}