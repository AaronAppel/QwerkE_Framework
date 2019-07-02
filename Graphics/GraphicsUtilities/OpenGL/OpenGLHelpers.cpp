#include "../../Graphics_Header.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../../QwerkE_Common/Utilities/ImageHelpers.h"
#include "../../../QwerkE_Common/Libraries/lodepng/lodepng.h"
#include "../../../Systems/FileSystem/FileSystem.h"
#include "../../../Systems/ServiceLocator.h"

// TODO: Find a better spot for st_image init
#define STB_IMAGE_IMPLEMENTATION
#include "../../../QwerkE_Common/Libraries/stb_image.h"

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

// OpenGLHelpers.cpp
void GLCheckforErrors()
{
	GLenum error = glGetError();
	if (error != 0)
		OutputPrint("\nglGetError: %i-> ", error);
	if (error == GL_INVALID_VALUE)
		OutputPrint("Invalid value used.", error);
	if (error == GL_INVALID_OPERATION)
		OutputPrint("Invalid operation.", error);
}

void GLCheckforErrors(char* file, int line)
{
	GLenum error = glGetError();
	if (error != 0)
		OutputPrint("\nglGetError: Error caught in file %s(%i) -> Error %i ", file, line, error);
	if (error == GL_INVALID_VALUE)
		OutputPrint("Invalid value. Can't find value.");
	if (error == GL_INVALID_OPERATION)
		OutputPrint("Invalid operation.");
}

void GLCheckforErrors(const char* file, int line)
{
	GLenum error = glGetError();
	if (error != 0)
		OutputPrint("\nglGetError: Error caught in file %s(%i) -> Error %i ", file, line, error);
	if (error == GL_INVALID_VALUE)
		OutputPrint("Invalid value. Can't find value.");
	if (error == GL_INVALID_OPERATION)
		OutputPrint("Invalid operation.");
}

GLuint GLLoad2DTexture(const char* filePath, bool flipVertically)
{
	// TODO: If this fails should I return a null texture?
	// TODO: Flags for how to setup opengl settings for texture? Save that into the texture object?

	GLenum channels = 4;
	unsigned int width = 0, height = 0;
	unsigned char* imageData = ((FileSystem*)QwerkE::ServiceLocator::GetService(eEngineServices::FileSystem))->LoadImageFileData(filePath, &width, &height, channels, flipVertically);

	if (!imageData)
	{
		OutputPrint("GLLoad2DTexture(): Failed to load: \"%s\"\n", filePath);
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
		OutputPrint("LoadTexture(): Error loading image: %s\n", filename);
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
