#ifndef _OpenGLHelpers_H_
#define _OpenGLHelpers_H_

void GLCheckforErrors();
void GLCheckforErrors(char* file, int line);
void GLCheckforErrors(const char* file, int line);

GLuint GLLoad2DTexture(const char* filename, bool flipVertically = 0);
GLuint GLLoadCubeMapTexture(const char* filename);

#endif // !_OpenGLHelpers_H_