#include "../../Graphics/Graphics_Header.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../Graphics/Shader/ShaderProgram.h"
#include "../../Graphics/Shader/ShaderComponent.h"
#include "../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"

ShaderProgram* ShaderFactory::CreateShader(eShaderTypes type)
{
	ShaderProgram* shader = new ShaderProgram();
	shader->GetVertShader()->SetStringData(CreateVertexShader(type));
	shader->GetFragShader()->SetStringData(CreateFragmentShader(type));
	shader->GetGeoShader()->SetStringData(CreateGeometryShader(type));

	if (BuildShaderProgram(shader))
		return shader;
	else
	{
		delete shader;
		return nullptr;
	}
}

ShaderProgram* ShaderFactory::CreateShader(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir)
{
	ShaderProgram* shader = new ShaderProgram();
	if(vertFileDir) CreateShaderComponent(GL_VERTEX_SHADER, vertFileDir);
	if (fragFileDir) CreateShaderComponent(GL_VERTEX_SHADER, fragFileDir);
	if (geoFileDir) CreateShaderComponent(GL_VERTEX_SHADER, geoFileDir);

	if(BuildShaderProgram(shader))
		return shader;
	else
	{
		delete shader;
		return nullptr;
	}
}
// Returns new shader handle is successful, else 0
ShaderComponent* ShaderFactory::CreateShaderComponent(GLenum shaderType, const char* shaderPath)
{
	GLuint shaderHandle = glCreateShader(shaderType); // fails if context is not current for GLFW

	const char* shaderString = LoadCompleteFile(shaderPath, 0);
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
		OutputPrint("\n%s: ShaderFactory: CreateShader(Glenum, const char*) %s compile error-> ", ShaderName, shaderTypeString);
		OutputPrint(infoLog); // OpenGL message

		// cleanup
		glDeleteShader(shaderHandle);
		shaderHandle = 0;
		delete[] shaderString;
		return nullptr;
	}
	else
	{
		ShaderComponent* comp = new ShaderComponent();
		comp->SetName(GetFileNameWithExt(shaderPath));
		comp->SetStringData(shaderString);
		comp->SetHandle(shaderHandle);
		comp->SetType(DeepCopyString(GetFileExtension(shaderPath).c_str()));
		return comp;
	}
}

GLuint ShaderFactory::CreateShaderProgram(GLuint vert, GLuint frag, GLuint geo)
{
	if (vert == 0 && frag == 0 && geo == 0) // no valid shaders
	{
		return 0;
	}
	return LinkShaders(vert, frag, geo);
}

bool ShaderFactory::BuildShaderProgram(ShaderProgram* shader)
{
	// TODO: Add in geometry shader supprt
    GLuint result = LinkShaders(shader->GetVertShader()->GetHandle(), shader->GetFragShader()->GetHandle(), NULL);
	shader->SetProgram(result);
	return result != 0;
}

GLuint ShaderFactory::CreateVertexShader(const char* vertPath)
{
	GLuint shaderHandle = glCreateShader(GL_VERTEX_SHADER); // fails if context is not current for GLFW

	const char* data = LoadCompleteFile(vertPath, 0);
	if (data)
	{
		glShaderSource(shaderHandle, 1, &data, NULL);
		glCompileShader(shaderHandle);

		GLint success = 0;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			// Error compiling shader
			GLchar infoLog[512];
			glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);

			char* next_token = 0;
			char* ShaderName = strtok_s((char*)data, "\n", &next_token);
			// TODO: error reads as garbage characters.
			OutputPrint("\n%s: ShaderFactory: CreateShader(Glenum, const char*) %s compile error-> ", ShaderName, "GL_VERTEX_SHADER");
			OutputPrint(infoLog); // OpenGL message

								  // cleanup
			glDeleteShader(shaderHandle);
			delete[] data;
			return 0;
		}
		else
		{
			delete[] data;
			return shaderHandle;
		}
	}
	else
	{
		return 0;
	}
}

GLuint ShaderFactory::CreateFragmentShader(const char* fragPath)
{
	GLuint shaderHandle = glCreateShader(GL_FRAGMENT_SHADER); // fails if context is not current for GLFW

	const char* data = LoadCompleteFile(fragPath, 0);
	if (data)
	{
		glShaderSource(shaderHandle, 1, &data, NULL);
		glCompileShader(shaderHandle);

		GLint success = 0;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			// Error compiling shader
			GLchar infoLog[512];
			glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);

			char* next_token = 0;
			char* ShaderName = strtok_s((char*)data, "\n", &next_token);
			// TODO: error reads as garbage characters.
			OutputPrint("\n%s: ShaderFactory: CreateShader(Glenum, const char*) %s compile error-> ", ShaderName, "GL_FRAGMENT_SHADER");
			OutputPrint(infoLog); // OpenGL message

								  // cleanup
			glDeleteShader(shaderHandle);
			delete[] data;
			return 0;
		}
		else
		{
			delete[] data;
			return shaderHandle;
		}
	}
	else
	{
		return 0;
	}
}

GLuint ShaderFactory::CreateGeometryShader(const char* geoPath)
{
	GLuint shaderHandle = glCreateShader(GL_GEOMETRY_SHADER); // fails if context is not current for GLFW

	const char* data = LoadCompleteFile(geoPath, 0);
	if (data)
	{
		glShaderSource(shaderHandle, 1, &data, NULL);
		glCompileShader(shaderHandle);

		GLint success = 0;
		glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			// Error compiling shader
			GLchar infoLog[512];
			glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);

			char* next_token = 0;
			char* ShaderName = strtok_s((char*)data, "\n", &next_token);
			// TODO: error reads as garbage characters.
			OutputPrint("\n%s: ShaderFactory: CreateShader(Glenum, const char*) %s compile error-> ", ShaderName, "GL_GEOMETRY_SHADER");
			OutputPrint(infoLog); // OpenGL message

								  // cleanup
			glDeleteShader(shaderHandle);
			delete[] data;
			return 0;
		}
		else
		{
			delete[] data;
			return shaderHandle;
		}
	}
	else
	{
		return 0;
	}
}

const char* ShaderFactory::CreateVertexShader(eShaderTypes shaderType)
{
	std::string vertString;

	SetVertName(shaderType, vertString);
	SetVersion(vertString);

	switch (shaderType)
	{
	case eShader_Basic2D:
		vertString = Basic2DShaderVert(vertString);
		break;
	case eShader_Basic3D:
		vertString = Basic3DShaderVert(vertString);
		break;
	case eShader_LitMaterial:
		vertString = LitMaterialVert(vertString);
		break;
	}

	const char* returnString = DeepCopyString(vertString.c_str());

	return returnString;
}

const char* ShaderFactory::CreateFragmentShader(eShaderTypes shaderType)
{
	std::string fragString;

	SetFragName(shaderType, fragString);
	SetVersion(fragString);

	switch (shaderType)
	{
	case eShader_Basic2D:
		fragString = Basic2DShaderFrag(fragString);
		break;
	case eShader_Basic3D:
		fragString = Basic3DShaderFrag(fragString);
		break;
	case eShader_LitMaterial:
		fragString = LitMaterialFrag(fragString);
		break;
	}

	const char* returnString = DeepCopyString(fragString.c_str());
	return returnString;
}

const char* ShaderFactory::CreateGeometryShader(eShaderTypes shaderType)
{
	return 0; // TODO: Build geometry shader support
}

void ShaderFactory::SetVertName(eShaderTypes shaderType, std::string &shaderString)
{
	// TODO: Should have a generic "// " + Name + "." + extension functions
	switch (shaderType) // shader name comment for easier debugging
	{
	case eShader_Basic3D:
		shaderString.append("// Basic3D.vert");
		break;
	case eShader_LitMaterial:
		shaderString.append("// LitMaterial.vert");
		break;
	}
}

void ShaderFactory::SetFragName(eShaderTypes shaderType, std::string &shaderString)
{
	switch (shaderType) // shader name comment for easier debugging
	{
	case eShader_Basic3D:
		shaderString.append("// Basic3D.frag");
		break;
	case eShader_LitMaterial:
		shaderString.append("// LitMaterial.frag");
		break;
	}
}

void ShaderFactory::SetGeoName(eShaderTypes shaderType, std::string &shaderString)
{
	switch (shaderType) // shader name comment for easier debugging
	{
	case eShader_Basic3D:
		shaderString.append("// Basic3D.geo");
		break;
	case eShader_LitMaterial:
		shaderString.append("// LitMaterial.geo");
		break;
	}
}

void ShaderFactory::SetVersion(std::string &shaderString)
{
	// TODO:: Get and store the openGL version for reference
	int _OpenGLVersion = 330;
	std::string _OpenGLprofile = "core";
	shaderString.append("\n#version " + std::to_string(_OpenGLVersion) + " " + _OpenGLprofile);
}

void ShaderFactory::OpenMain(std::string &shaderString)
{
	shaderString.append("\nvoid main()\n{");
}

void ShaderFactory::CloseMain(std::string &shaderString)
{
	shaderString.append("\n}");
}
/* Getters + Setters */
// Getters
// Setters
void ShaderFactory::SetPrefixes(const char* attr, const char* unif, const char* trans)
{
	m_AttributePrefix = DeepCopyString(attr);
	m_UniformPrefix = DeepCopyString(unif);
	m_TransferPrefix = DeepCopyString(trans);
}
// private functions
// Returns new program handle if successful, else 0
GLuint ShaderFactory::LinkShaders(GLuint vert, GLuint frag, GLuint geo)
{
	GLuint result = 0;
	result = glCreateProgram(); // create new program

	// TODO: Handle error when attaching linked shaders. May want to de-link before attaching?
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
		OutputPrint("\nShaderProgram: LinkShaders() linking error-> %s", infoLog);
		return 0;
	}

	CheckGraphicsErrors(__FILE__, __LINE__);
	return result;
}
/* Utility */
// structs
void ShaderFactory::AddMaterialStruct(std::string &string)
{
	// TODO: Update material struct
	const char* material_struct =
		"\nstruct Material {"
		"\nvec3 ambient;"
		"\nvec3 diffuse;"
		"\nvec3 specular;"
		"\nfloat shininess;"
		"\n};\n";
	string.append(material_struct);
}
// TODO: Would a light struct help?
void ShaderFactory::AddLightStruct(std::string &string)
{
	const char* light_struct =
		"\nstruct Light {"
		"\nvec3 colour;"
		"\n};\n";
	string.append(light_struct);
}
// attributes
void ShaderFactory::AddAttributeInt(const char* name, std::string &string)
{
	const char* line = "\nin int ";
	string.append(line);
	string.append(m_AttributePrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddAttributeFloat(const char* name, std::string &string)
{
	const char* line = "\nin float ";
	string.append(line);
	string.append(m_AttributePrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddAttributeVec2(const char* name, std::string &string)
{
	const char* line = "\nin vec2 ";
	string.append(line);
	string.append(m_AttributePrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddAttributeVec3(const char* name, std::string &string)
{
	const char* line = "\nin vec3 ";
	string.append(line);
	string.append(m_AttributePrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddAttributeVec4(const char* name, std::string &string)
{
	const char* line = "\nin vec4 ";
	string.append(line);
	string.append(m_AttributePrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddAttributeMat2(const char* name, std::string &string)
{
	const char* line = "\nin mat2 ";
	string.append(line);
	string.append(m_AttributePrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddAttributeMat3(const char* name, std::string &string)
{
	const char* line = "\nin mat3 ";
	string.append(line);
	string.append(m_AttributePrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddAttributeMat4(const char* name, std::string &string)
{
	const char* line = "\nin mat4 ";
	string.append(line);
	string.append(m_AttributePrefix);
	string.append(name);
	string.append(";");
}
// uniforms
void ShaderFactory::AddUniformMaterialStruct(const char* name, std::string &string)
{
	const char* line = "\nuniform Material ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformInt(const char* name, std::string &string)
{
	const char* line = "\nuniform int ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformFloat(const char* name, std::string &string)
{
	const char* line = "\nuniform float ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformVec2(const char* name, std::string &string)
{
	const char* line = "\nuniform vec2 ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformVec3(const char* name, std::string &string)
{
	const char* line = "\nuniform vec3 ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformVec4(const char* name, std::string &string)
{
	const char* line = "\nuniform vec4 ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformMat2(const char* name, std::string &string)
{
	const char* line = "\nuniform mat2 ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformMat3(const char* name, std::string &string)
{
	const char* line = "\nuniform mat3 ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformMat4(const char* name, std::string &string)
{
	const char* line = "\nuniform mat4 ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformSampler2D(const char* name, std::string string)
{
	const char* line = "\nuniform sampler2D ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddUniformTexture(int* count, std::string string)
{
	const char* line = "\nuniform sampler2D ";
	string.append(line);
	string.append(m_UniformPrefix);
	string.append("Texture");
	string.append(std::to_string(*count));
	*count++; // increment
	string.append(";");
}
// input
void ShaderFactory::AddInputInt(const char* name, std::string &string)
{
	const char* line = "\nin int ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddInputFloat(const char* name, std::string &string)
{
	const char* line = "\nin float ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddInputVec2(const char* name, std::string &string)
{
	const char* line = "\nin vec2 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddInputVec3(const char* name, std::string &string)
{
	const char* line = "\nin vec3 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddInputVec4(const char* name, std::string &string)
{
	const char* line = "\nin vec4 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddInputMat2(const char* name, std::string &string)
{
	const char* line = "\nin mat2 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddInputMat3(const char* name, std::string &string)
{
	const char* line = "\nin mat3 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddInputMat4(const char* name, std::string &string)
{
	const char* line = "\nin mat4 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}
// output
void ShaderFactory::AddOutputInt(const char* name, std::string &string)
{
	const char* line = "\nout int ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddOutputFloat(const char* name, std::string &string)
{
	const char* line = "\nout float ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddOutputVec2(const char* name, std::string &string)
{
	const char* line = "\nout vec2 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddOutputVec3(const char* name, std::string &string)
{
	const char* line = "\nout vec3 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddOutputVec4(const char* name, std::string &string)
{
	const char* line = "\nout vec4 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddOutputMat2(const char* name, std::string &string)
{
	const char* line = "\nout mat2 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddOutputMat3(const char* name, std::string &string)
{
	const char* line = "\nout mat3 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}

void ShaderFactory::AddOutputMat4(const char* name, std::string &string)
{
	const char* line = "\nout mat4 ";
	string.append(line);
	string.append(m_TransferPrefix);
	string.append(name);
	string.append(";");
}