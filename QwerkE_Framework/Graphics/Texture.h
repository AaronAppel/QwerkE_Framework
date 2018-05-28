#ifndef _Texture_H_
#define _Texture_H_

#include "../../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <string>

struct Texture
{
#ifdef OpenGL
	GLuint s_Handle = 0;
#else
	unsigned int handle = 0;
#endif // OpenGL

	std::string s_Name = "Uninitialized";

	Texture() {}
	~Texture() {}
};

#endif // !_Texture_H_
