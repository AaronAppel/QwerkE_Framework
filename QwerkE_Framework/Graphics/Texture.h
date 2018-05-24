#ifndef _Texture_H_
#define _Texture_H_

#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <string>

struct Texture
{
#ifdef OpenGL
	GLuint handle = 0;
#else
	unsigned int handle = 0;
#endif // OpenGL

	std::string name = "Uninitialized";
	std::string path = "Uninitialized"; // TODO: Useful?

	Texture();
	~Texture();
};

#endif // !_Texture_H_
