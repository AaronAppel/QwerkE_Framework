#include "../Graphics_Header.h"
#include "../../../Shared_Generic/Utilities/PrintFunctions.h"
#include "../../../Shared_Generic/Utilities/FileIO/FileUtilities.h"
#include "../../../Shared_Generic/Utilities/ImageHelpers.h"
#include "../../../Shared_Generic/Libraries/lodepng/lodepng.h"

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

// OpenGLHelpers.cpp
void CheckforGLErrors()
{
	GLenum error = glGetError();
	if (error != 0)
		OutputPrint("\nglGetError: %i-> ", error);
	if (error == GL_INVALID_VALUE)
		OutputPrint("Invalid value used.", error);
	if (error == GL_INVALID_OPERATION)
		OutputPrint("Invalid operation.", error);
}

void CheckforGLErrors(char* file, int line)
{
	GLenum error = glGetError();
	if (error != 0)
		OutputPrint("\nglGetError: Error caught in file %s(%i) -> Error %i ", file, line, error);
	if (error == GL_INVALID_VALUE)
		OutputPrint("Invalid value. Can't find value.", error);
	if (error == GL_INVALID_OPERATION)
		OutputPrint("Invalid operation.", error);
}

void CheckforGLErrors(const char* file, int line)
{
	GLenum error = glGetError();
	if (error != 0)
		OutputPrint("\nglGetError: Error caught in file %s(%i) -> Error %i ", file, line, error);
	if (error == GL_INVALID_VALUE)
		OutputPrint("Invalid value. Can't find value.", error);
	if (error == GL_INVALID_OPERATION)
		OutputPrint("Invalid operation.", error);
}

GLuint Load2DTexture(const char* filename, bool flipVertically)
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

	if (flipVertically)
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// glGenerateMipmap(GL_TEXTURE_2D); // Create mipmap

	glBindTexture(GL_TEXTURE_2D, 0);

	// cleanup
	free(pngbuffer);
	delete[] filebuffer;
	return texhandle;
}

GLuint LoadCubeMapTexture(const char* filename)
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