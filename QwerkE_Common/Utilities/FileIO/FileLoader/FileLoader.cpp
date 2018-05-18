#include "FileLoader.h"
#include "LoadImageFile.h"
#include "../Utilities/PrintFunctions.h"

#define QwerkE_Image_Library 1

#include <string>

namespace QwerkE
{
	namespace FileLoader
	{
		void LoadSound() // TODO:
		{
			// OpenAL?
		}

		// determine image type and use proper library
		// lodepng, stb_image, SOIL, etc
		unsigned char* LoadImageFile(const char* path, unsigned int* imageWidth, unsigned int* imageHeight, GLenum& channels, bool flipVertically)
		{
			unsigned char* returnBuffer = nullptr;

			// TODO: Determine which tool/library to use depending on image type and format
			// png, jpg, 8bit vs 32bit, etc

#if QwerkE_Image_Library == 1 // stb
			// stb has shown to be faster than lodepng, however it is not reliable for loading all image formats.
			// use both for now...
			//returnBuffer = QwerkE_stb_image_loadImage(path, imageWidth, imageHeight, channels, flipVertically);

// #elif QwerkE_Image_Library == 2 // lodepng
			// if (returnBuffer == nullptr || strcmp((const char*)returnBuffer, "") == 0)
			if(!returnBuffer)
				returnBuffer = QwerkE_lodepng_loadImage(path, imageWidth, imageHeight, channels, flipVertically);
			else
#elif QwerkE_Image_Library == 3 // SOIL
			// TODO:
			returnBuffer = QwerkE_soil_loadImage(path);
#else
#pragma error "Define image loading library!"
#endif

			if (!returnBuffer)// (returnBuffer == nullptr || strcmp((const char*)returnBuffer, "") == 0)
			{
				OutputPrint("LoadImageFile(): Failed to load image: %s\n", path);
				return nullptr; // failed
			}

			OutputPrint("LoadImageFile(): Loaded: %s\n", path);
			return returnBuffer;
		}

		//Material* GetMaterialFromMatFile(const char* path)
		//{
		//	// TODO:
		//}
	}
}