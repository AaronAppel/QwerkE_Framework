#ifndef __CubeMap_H__
#define __CubeMap_H__

#include <vector>
#include <string>

struct CubeMapData
{
	const char* m_PosX = 0; // GL_TEXTURE_CUBE_MAP_POSITIVE_X
	const char* m_NegX = 0;
	const char* m_PosY = 0;
	const char* m_NegY = 0;
	const char* m_PosZ = 0;
	const char* m_NegZ = 0;
};

class CubeMap
{
public:
	CubeMap();
	~CubeMap();

	void Init();
	GLuint loadCubemap(std::vector<std::string> faces);
private:
	GLuint m_TextureHandle = -1;
};

#endif //__FrameBufferObject_H__
