#include "../../Graphics_Header.h"
#include "../Systems/Log/Log.h"
#include "../../Systems/FileSystem/FileIO/FileUtilities.h"
#include "../../Systems/FileSystem/ImageHelpers.h"
#include "../../Systems/Misc/StringHelpers.h"
#include "../../../Libraries/lodepng/lodepng.h"
#include "../../../Systems/FileSystem/FileSystem.h"

// TODO: Find a better spot for stb_image init
#pragma warning( disable : 28182 )
#pragma warning( disable : 6001 )
#pragma warning( disable : 6262 )
#define STB_IMAGE_IMPLEMENTATION
#include "../../../Libraries/stb_image.h"
#pragma warning( enable : 28182 )
#pragma warning( enable : 6001 )
#pragma warning( enable : 6262 )

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

namespace QwerkE {

#ifdef _QDebug
    void GLCheckforErrors()
    {
        GLenum error = glGetError();
        if (error != 0)
            LOG_ERROR("glGetError: {0}-> ", error);
        if (error == GL_INVALID_VALUE)
            LOG_ERROR("Invalid value used.", error);
        if (error == GL_INVALID_OPERATION)
            LOG_ERROR("Invalid operation.", error);
    }

    void GLCheckforErrors(const char* file, int line)
    {
        GLenum error = glGetError();
        if (error != 0)
            LOG_ERROR("glGetError: Error caught in file {0}({1}) -> Error {2} ", file, line, error);
        if (error == GL_INVALID_VALUE)
            LOG_ERROR("glGetError: Can't find value in file {0}({1}) -> Error {2} ", file, line, error);
        if (error == GL_INVALID_OPERATION)
            LOG_ERROR("glGetError: Invalid operation caught in file {0}({1}) -> Error {2} ", file, line, error);
    }
#else
    void GLCheckforErrors() {}
    void GLCheckforErrors(const char* file, int line) {}
#endif // _QDebug

    GLuint LoadTextureDataToOpenGL(QImageFile& fileData)
    {
        // buffer data in GPU RAM
        GLuint texhandle = 0;
        glGenTextures(1, &texhandle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texhandle);
        CheckGraphicsErrors(__FILE__, __LINE__);
        // https://stackoverflow.com/questions/23150123/loading-png-with-stb-image-for-opengl-texture-gives-wrong-colors
        glTexImage2D(GL_TEXTURE_2D, 0, fileData.s_Channels, fileData.s_Width, fileData.s_Height, 0, fileData.s_Channels, GL_UNSIGNED_BYTE, fileData.s_Data);

        CheckGraphicsErrors(__FILE__, __LINE__);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // TODO: Handle texture parameters better
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // glGenerateMipmap(GL_TEXTURE_2D); // Create mipmap

        glBindTexture(GL_TEXTURE_2D, 0);

        CheckGraphicsErrors(__FILE__, __LINE__);

        // TODO: need to free() allocations from lodepng
        // delete[] imageData; // clean up

        return texhandle;
    }

    GLuint GLLoad2DTexture(const char* filePath, bool flipVertically)
    {
        // TODO: If this fails should I return a null texture?
        // TODO: Flags for how to setup opengl settings for texture? Save that into the texture object?

        GLenum channels = 4;
        unsigned int width = 0, height = 0;
        unsigned char* imageData = FileSystem::LoadImageFileData(filePath, &width, &height, channels, flipVertically);

        if (!imageData)
        {
            LOG_ERROR("GLLoad2DTexture(): Failed to load: \"{0}\"", filePath);
            return 0;
        }
        else
        {
            // buffer data in GPU RAM
            GLuint texhandle = 0;
            glGenTextures(1, &texhandle);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texhandle);
            CheckGraphicsErrors(__FILE__, __LINE__);
            // https://stackoverflow.com/questions/23150123/loading-png-with-stb-image-for-opengl-texture-gives-wrong-colors
            channels = GL_RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, channels, GL_UNSIGNED_BYTE, imageData); // GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data)

            CheckGraphicsErrors(__FILE__, __LINE__);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // TODO: Handle texture parameters better
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            // glGenerateMipmap(GL_TEXTURE_2D); // Create mipmap

            glBindTexture(GL_TEXTURE_2D, 0);

            CheckGraphicsErrors(__FILE__, __LINE__);

            // TODO: need to free() allocations from lodepng
            delete[] imageData; // clean up

            return texhandle;
        }
    }

    GLuint GLLoadCubeMapTexture(const char* filename)
    {
        unsigned char* pngbuffer = 0;
        unsigned int width, height;
        long filesize;
        unsigned int result = -1;

        // buffer file data
        unsigned char* filebuffer = (unsigned char*)LoadCompleteFile(filename, &filesize);

        if (filebuffer != NULL) // decode file data
        {
            result = lodepng_decode32(&pngbuffer, &width, &height, filebuffer, filesize);
        }
        if (0) // TODO: Evaluate when to flip image vertically
        {
            Flip32BitImageVertically(pngbuffer, width, height);
        }

        if (result != 0) // error decoding image data
        {
            LOG_ERROR("LoadTexture(): Error loading image: {0}", filename);
            free(pngbuffer);
            delete[] filebuffer;
            return 0; // exit
        }

        GLuint texhandle = 0;
        glGenTextures(1, &texhandle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texhandle);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngbuffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);

        // cleanup
        free(pngbuffer);
        delete[] filebuffer;
        return texhandle;
    }

}
