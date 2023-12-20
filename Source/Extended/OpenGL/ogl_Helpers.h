#ifndef _ogl_Helpers_H_
#define _ogl_Helpers_H_

#include "../../../Libraries/glew/GL/glew.h"

#include "../../FileSystem/FileSystem.h"

namespace QwerkE {

    void GLCheckforErrors();
    void GLCheckforErrors(const char* file, int line);

    GLuint LoadTextureDataToOpenGL(QImageFile& fileData);
    GLuint GLLoad2DTexture(const char* filePath, bool flipVertically = 0);
    GLuint GLLoadCubeMapTexture(const char* filePath);

}
#endif // _ogl_Helpers_H_
