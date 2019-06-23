#ifndef _Texture_H_
#define _Texture_H_

#include "../QwerkE_Common/Libraries/glew/GL/glew.h"

#include <string>

struct Texture
{
#ifdef OpenGL
	GLuint s_Handle = 0;
#else
	unsigned int s_Handle = 0;
#endif

	std::string s_Name = gc_DefaultStringValue;

	Texture() {}
	~Texture() {}
};

#endif // !_Texture_H_
