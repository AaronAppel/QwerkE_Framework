#include <stdio.h>
#include <cstring>

// ImageHelpers.cpp
void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height)
{
	// flip the image in buffer.  Assumes RGBA 32 bit.

	{
		// temp allocation big enough for one line
		unsigned int* temp;
		temp = new unsigned int[width];
		int linesize = width * sizeof(unsigned int);

		unsigned int* buffer32 = (unsigned int*)buffer;
		for (unsigned int y = 0; y<height / 2; y++)
		{
			int LineOffsetY = y*width;
			int LineOffsetHminusY = (height - 1 - y)*width;

			memcpy(temp, &buffer32[LineOffsetY], linesize);
			memcpy(&buffer32[LineOffsetY], &buffer32[LineOffsetHminusY], linesize);
			memcpy(&buffer32[LineOffsetHminusY], temp, linesize);
		}

		delete[] temp;
	}
}
