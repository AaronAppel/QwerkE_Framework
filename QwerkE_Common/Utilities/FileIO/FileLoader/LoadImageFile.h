#ifndef _LoadImageFile_H_
#define _LoadImageFile_H_

unsigned char* QwerkE_stb_image_loadImage(const char* path, unsigned int* imageWidth, unsigned int* imageHeight, GLenum& channels, bool flipVertically = 0);
unsigned char* QwerkE_lodepng_loadImage(const char* path, unsigned int* imageWidth, unsigned int* imageHeight, GLenum& channels, bool flipVertically = 0);
// void QwerkE_soil_loadImage();

#endif // !_LoadImageFile_H_
