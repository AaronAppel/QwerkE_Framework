#include "../../../Graphics/Graphics_Header.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../../QwerkE_Common/Utilities/ImageHelpers.h"
#include "../../../QwerkE_Common/Libraries/lodepng/lodepng.h"

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
		OutputPrint("Invalid value. Can't find value.", error);
	if (error == GL_INVALID_OPERATION)
		OutputPrint("Invalid operation.", error);
}

void GLCheckforErrors(const char* file, int line)
{
	GLenum error = glGetError();
	if (error != 0)
		OutputPrint("\nglGetError: Error caught in file %s(%i) -> Error %i ", file, line, error);
	if (error == GL_INVALID_VALUE)
		OutputPrint("Invalid value. Can't find value.", error);
	if (error == GL_INVALID_OPERATION)
		OutputPrint("Invalid operation.", error);
}

GLuint GLLoad2DTexture(const char* filePath, bool flipVertically)
{
	// TODO: If this fails should I return a null texture?
	// TODO: Flags for how to setup opengl settings for texture? Save that into the texture object?
	unsigned char* pngbuffer = 0;
	GLenum channels = GL_RGBA;

	// buffer file data
#define QwerkE_Image_Library 1
#if QwerkE_Image_Library == 0 // stb
		// stb has shown to be 20% faster than lodepng in 1 instance, however it is not reliable for loading all image. maybe use both?
		signed int width = 0, height = 0;
		int nrChannels = 0;
		pngbuffer = stbi_load(filePath, &width, &height, &nrChannels, 0); // can set 0 to desired comp (rgba == 4)
		if (pngbuffer == nullptr || pngbuffer == NULL || *pngbuffer == *"")
		{
			OutputPrint("GLLoad2DTexture(): Error loading image: %s\n", filePath);
			stbi_image_free(pngbuffer);
			return 0; // null handle
		}
		if (nrChannels == 3)
			channels = GL_RGB; // no alpha

#elif QwerkE_Image_Library == 1 // lodepng
		unsigned int width = 0, height = 0;
		long filesize;
		unsigned int result = -1;
		unsigned char* filebuffer = (unsigned char*)LoadCompleteFile(filePath, &filesize);
		if (filebuffer != NULL) // decode file data
		{
			result = lodepng_decode32(&pngbuffer, &width, &height, filebuffer, filesize);
		}

		if (result != 0) // error decoding image data
		{
			OutputPrint("GLLoad2DTexture(): Error loading image: %s\n", filePath);
			free(pngbuffer);
			delete[] filebuffer;
			return 0; // exit
		}
#elif QwerkE_Image_Library == 2 // SOIL
		// TODO:
#else
#pragma error "Define image loading library!"
#endif

	// flip image vertically?
	if (flipVertically)
	{
		Flip32BitImageVertically(pngbuffer, width, height);
	}

	// buffer data in GPU RAM
	GLuint texhandle = 0;
	glGenTextures(1, &texhandle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texhandle);
	// https://stackoverflow.com/questions/23150123/loading-png-with-stb-image-for-opengl-texture-gives-wrong-colors
	glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, channels, GL_UNSIGNED_BYTE, pngbuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // TODO: Handle texture parameters better
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// glGenerateMipmap(GL_TEXTURE_2D); // Create mipmap

	glBindTexture(GL_TEXTURE_2D, 0);

	CheckGraphicsErrors(__FILE__, __LINE__);

	// cleanup
#if QwerkE_Image_Library == 0 // stb
	stbi_image_free(pngbuffer);
#elif QwerkE_Image_Library == 1 // lodepng
	free(pngbuffer);
	delete[] filebuffer;
#elif QwerkE_Image_Library == 2 // SOIL
	// TODO:
#else
#pragma error "Define image loading library!"
#endif

	OutputPrint("GLLoad2DTexture(): Loaded %s\n", filePath);
	return texhandle;
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
