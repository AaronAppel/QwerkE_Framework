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

		// compile
		if (m_Type == "vert")
		{
			m_ShaderHandle = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateVertexShader(shaderPath);
		}
		else if (m_Type == "frag")
		{
			m_ShaderHandle = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateFragmentShader(shaderPath);
		}
		else if (m_Type == "geo")
		{
			m_ShaderHandle = ((ShaderFactory*)QwerkE::ServiceLocator::GetService(eEngineServices::Factory_Shader))->CreateGeometryShader(shaderPath);
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