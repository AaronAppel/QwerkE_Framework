#include "LoadWavFile.h"

#include <iostream>

// load wav file
// https://stackoverflow.com/questions/38022123/openal-not-playing-sound/50429578#50429578
unsigned char* QwerkE_wav_loadSound(const char* filePath, DWORD& bufferSize)
{
	FILE* f;
	fopen_s(&f, filePath, "rb"); // "rb" instead of "r"

	assert(f);

	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, byteRate;
	short blockAlign, bitsPerSample;

	char subChunk1ID[4], subChunk2ID[4];

	DWORD subChunk1Size, subChunk2Size;

	// read first chunk
	fread(type, sizeof(char), 4, f); // ChunkID "RIFF"
	if (!strcmp(type, "RIFF"))
	{
		std::cout << "Not RIFF!" << std::endl;
		return nullptr;
	}

	fread(&chunkSize, sizeof(DWORD), 1, f); // ChunkSize == "fmt "(4) + (8 + SubChunk1Size) + (8 + SubChunk2Size)

	fread(type, sizeof(char), 4, f);
	if (!strcmp(type, "WAVE"))
	{
		std::cout << "Not WAVE!" << std::endl;
		return nullptr;
	}

	// read "fmt " chunk
	fread(&subChunk1ID, sizeof(char), 4, f); // "fmt "
	if (!strcmp(type, "fmt "))
	{
		std::cout << "Not fmt!" << std::endl;
		return nullptr;
	}

	fread(&subChunk1Size, sizeof(DWORD), 1, f);

	fread(&formatType, sizeof(short), 1, f); // not 1 == compression
	fread(&channels, sizeof(short), 1, f);
	fread(&sampleRate, sizeof(DWORD), 1, f);
	fread(&byteRate, sizeof(DWORD), 1, f);
	fread(&blockAlign, sizeof(short), 1, f);
	fread(&bitsPerSample, sizeof(short), 1, f);

	// read "data" chunk
	fread(type, sizeof(char), 4, f);
	if (!strcmp(type, "data"))
	{
		std::cout << "Missing data" << std::endl;
		return nullptr;
	}

	fread(&bufferSize, sizeof(DWORD), 1, f);

	unsigned char* buffer = new unsigned char[bufferSize];

	int result = fread(buffer, 1, bufferSize, f);

	if (result != bufferSize || ferror(f) != 0)
	{
		std::cout << "Error reading data!" << std::endl;
		return nullptr;
	}

	fclose(f);

	return buffer;
}