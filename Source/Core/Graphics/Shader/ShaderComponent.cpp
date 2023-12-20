#include "ShaderComponent.h"

#include "../../../FileSystem/FileIO/FileUtilities.h"
#include "../../../Debug/Log/Log.h"

#include "../ShaderFactory/ShaderFactory.h"

namespace QwerkE {

    ShaderComponent::ShaderComponent()
    {
    }

    ShaderComponent::ShaderComponent(const char* shaderPath)
    {
        // read and compile file data
        if (FileExists(shaderPath))
        {
            m_Name = GetFileNameWithExt(shaderPath);
            m_Type = GetFileExtension(shaderPath);

            // compile
            if (m_Type == "vert") // TODO: Make an enum for this type
            {
                m_ShaderHandle = ShaderFactory::CreateVertexShader(shaderPath);
            }
            else if (m_Type == "frag")
            {
                m_ShaderHandle = ShaderFactory::CreateFragmentShader(shaderPath);
            }
            else if (m_Type == "geo")
            {
                m_ShaderHandle = ShaderFactory::CreateGeometryShader(shaderPath);
            }
            else
            {
                m_ShaderHandle = 0;
            }
        }
        if (!m_ShaderHandle)
        {
            m_Name = "Error";
            m_Type = "Error";
            LOG_ERROR("Error compiling Shader Component: {0}", shaderPath);
        }
    }

    ShaderComponent::~ShaderComponent()
    {
        // delete shader and shader string data
        glDeleteShader(m_ShaderHandle);
        delete[] m_ShaderData;
    }

}
