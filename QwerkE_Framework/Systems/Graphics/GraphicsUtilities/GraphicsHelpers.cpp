void CheckAllGraphicsErrors()
{
	// TODO: Handle all sorts of graphics system errors?
}

#ifdef OpenGL
#include "OpenGL/OpenGLHelpers.h"
void CheckGraphicsErrors()
{
	GLCheckforErrors();
}

void CheckGraphicsErrors(char* file, int line)
{
	GLCheckforErrors(file, line);
}

void CheckGraphicsErrors(const char* file, int line)
{
	GLCheckforErrors(file, line);
}

GLuint Load2DTexture(const char* filename, bool flipVertically)
{
	return GLLoad2DTexture(filename, flipVertically);
}

GLuint LoadCubeMapTexture(const char* filename)
{
	return GLLoadCubeMapTexture(filename);
}

#elif defined(Vulcan)
#include "OpenGL/VulcanHelpers.h"

#elif defined(Direct3D)
#include "OpenGL/Direct3DHelpers.h"

#else
#pragma error "Define graphics library!"

#endif // OpenGL



char* Helper_GetAttributePrefix()
{
	return (char*)"a_"; // for attributes or i_ for inputs
}

char* Helper_GetUniformPrefix()
{
	return (char*)"u_"; // uniforms
}

char* Helper_GetTransferPrefix()
{
	return (char*)"t_"; // for transfers or v_ for varyings
}