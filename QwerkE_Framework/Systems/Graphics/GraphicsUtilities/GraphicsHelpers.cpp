#include "GraphicsHelpers.h"

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

// TODO: Return a valid handle and try to avoid a stack frame if not necessary
GLuint Load2DTexture(const char* filename, bool flipVertically)
{
	return GLLoad2DTexture(filename, flipVertically);
}

GLuint LoadCubeMapTexture(const char* filename)
{
	return GLLoadCubeMapTexture(filename);
}

GLuint CopyFBOToTexture(FrameBufferObject& fbo, int w, int h, int x, int y)
{
	// TODO: abstract from library specific implementation
	// Note: You can specify what region of the framebuffer to take which
	// means you can easily capture a specified square from the scene.

	// bind framebuffer
	fbo.Bind();
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, w, h, 0);

	// create return texture
	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);

	// copy data
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, w, h, 1);
	CheckGraphicsErrors(__FILE__, __LINE__);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // , , GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// return handle to newly created texture
	fbo.UnBind();
	glBindTexture(GL_TEXTURE_2D, 0); // unbind
	return result;
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