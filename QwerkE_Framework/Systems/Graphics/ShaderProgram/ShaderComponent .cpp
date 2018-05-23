#include "ShaderComponent.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "ShaderFactory.h"
#include "../../ServiceLocator.h"

ShaderComponent::ShaderComponent()
{
}

ShaderComponent::ShaderComponent(const char* shaderPath)
{
	// read and compile file data
	if (FileExists)
	{
		m_Name = GetFileNameWithExt(shaderPath);
		m_Type = GetFileExtension(shaderPath);
		m_ShaderString = LoadCompleteFile(shaderPath, 0);

		// compile
		if (m_Type == "vert")
		{
			m_ShaderHandle = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateShaderComponent(
				GL_VERTEX_SHADER, m_ShaderString);
		}
		else if (m_Type == "frag")
		{
			m_ShaderHandle = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateShaderComponent(
				GL_FRAGMENT_SHADER, m_ShaderString);
		}
		else if (m_Type == "geo")
		{
			m_ShaderHandle = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateShaderComponent(
				GL_GEOMETRY_SHADER, m_ShaderString);
		}
		else
		{
			m_ShaderHandle = 0;
			delete m_ShaderString; // clean up
			m_ShaderString = nullptr;
		}
	}
	if (m_ShaderHandle)
	{
		m_Name = "Error";
		m_Type = "Error";
		OutputPrint("\nError compiling Shader Component: %s\n", shaderPath);
	}
}

ShaderComponent::~ShaderComponent()
{
	// delete shader and shader string data
	glDeleteShader(m_ShaderHandle);
	delete[] m_ShaderString;
}