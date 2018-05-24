#ifndef _GraphicsHelpers_H_
#define _GraphicsHelpers_H_

//////////////////////////////
// GraphicsHelpers.h
// Defines an interface for graphics utility functions such as texture loading.
// The function bodies vary based on graphics libraries.
//////////////////////////////

#include "../FrameBufferObject.h"

// TODO: Can I just #macro the functions to avoid a stack frame?
void CheckAllGraphicsErrors();
void CheckGraphicsErrors();
void CheckGraphicsErrors(char* file, int line);
void CheckGraphicsErrors(const char* file, int line);

GLuint Load2DTexture(const char* filename, bool flipVertically = 0);
GLuint LoadCubeMapTexture(const char* filename);

// GLuint Duplicate2DTexture(GLuint handle, int w, int h, int x, int y);
GLuint CopyFBOToTexture(FrameBufferObject& handle, int w, int h, int x = 0, int y = 0);

class RenderComponent;
void SaveObjectSchematic(RenderComponent* rComp);
RenderComponent* LoadObjectSchematic(const char* schematicPath);

class MaterialData;
void SaveMaterialSchematic(MaterialData* material);
MaterialData* LoadMaterialSchematic(const char* schematicPath);

class Model;
void SaveMaterialSchematic(MaterialData* material);
MaterialData* LoadMaterialSchematic(const char* schematicPath);

class ShaderProgram;
void SaveShaderSchematic(ShaderProgram* shader);
ShaderProgram* LoadShaderSchematic(const char* schematicPath);

char* Helper_GetAttributePrefix(); // TODO: Move to a shader specific file like ShaderFactory.h
char* Helper_GetUniformPrefix();
char* Helper_GetTransferPrefix();

#endif // !_GraphicsHelpers_H_