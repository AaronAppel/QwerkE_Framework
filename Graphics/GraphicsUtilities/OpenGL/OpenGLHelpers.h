#ifndef _OpenGLHelpers_H_
#define _OpenGLHelpers_H_

namespace QwerkE {

    void GLCheckforErrors();
    void GLCheckforErrors(const char* file, int line);

    GLuint LoadTextureDataToOpenGL(QImageFile& fileData);
    GLuint GLLoad2DTexture(const char* filePath, bool flipVertically = 0);
    GLuint GLLoadCubeMapTexture(const char* filePath);

}
#endif // !_OpenGLHelpers_H_
