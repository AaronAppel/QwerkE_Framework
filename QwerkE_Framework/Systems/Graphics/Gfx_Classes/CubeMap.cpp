#include "../../Graphics/Graphics_Header.h"
#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"

CubeMap::CubeMap()
{
	glGenTextures(1, &m_TextureHandle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureHandle);
}

CubeMap::~CubeMap()
{
	glDeleteTextures(1, &m_TextureHandle);
}

void CubeMap::Init()
{
	std::vector<std::string> t_Faces;
	// m_TextureHandle = loadCubemap(t_Faces);

	/*int width, height, nrChannels;
	unsigned char *data;
	for (GLuint i = 0; i < textures_faces.size(); i++)
	{
		data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);
	}*/
}

GLuint CubeMap::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID = -1;
	/*
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (uint i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	*/
	return textureID;
}