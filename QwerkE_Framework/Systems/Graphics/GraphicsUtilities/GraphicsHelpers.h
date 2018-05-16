#ifndef _GraphicsHelpers_H_
#define _GraphicsHelpers_H_

//////////////////////////////
// GraphicsHelpers.h
// Defines an interface for graphics utility functions such as texture loading.
// The function bodies vary based on graphics libraries.
//////////////////////////////

// TODO: Can I just #macro the functions to avoid a stack frame?
void CheckAllGraphicsErrors();
void CheckGraphicsErrors();
void CheckGraphicsErrors(char* file, int line);
void CheckGraphicsErrors(const char* file, int line);

GLuint Load2DTexture(const char* filename, bool flipVertically = 0);
GLuint LoadCubeMapTexture(const char* filename);

char* Helper_GetAttributePrefix(); // TODO: Move to a shader specific file like ShaderFactory.h
char* Helper_GetUniformPrefix();
char* Helper_GetTransferPrefix();

#endif // !_GraphicsHelpers_H_