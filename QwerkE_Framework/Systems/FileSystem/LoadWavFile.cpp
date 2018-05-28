#include "LoadWavFile.h"
#include "../../QwerkE_Common/Utilities/PrintFunctions.h"

#include <iostream>

// load wav file
// https://stackoverflow.com/questions/38022123/openal-not-playing-sound/50429578#50429578
unsigned char* QwerkE_wav_loadSound(const char* filePath, DWORD& bufferSize, unsigned short& channels, ALsizei& frequency)
{
	// TODO: Cleaner error handling

	FILE* f;
	fopen_s(&f, filePath, "rb"); // "rb" instead of "r"

	if (!f)
	{
		OutputPrint("QwerkE_wav_loadSound: Error opening file: %s", filePath);
		return nullptr;
	}

	char type[4];
	DWORD size, chunkSize;
	short formatType;
	DWORD sampleRate, byteRate;
	short blockAlign, bitsPerSample;

	char subChunk1ID[4], subChunk2ID[4];

	DWORD subChunk1Size, subChunk2Size;

	// read first chunk
	fread(type, sizeof(char), 4, f); // ChunkID "RIFF"
	if (!strcmp(type, "RIFF"))
	{
		OutputPrint("QwerkE_wav_loadSound: Not a \"RIFF\" file: %s", filePath);
		fclose(f);
		return nullptr;
	}

	fread(&chunkSize, sizeof(DWORD), 1, f); // ChunkSize == "fmt "(4) + (8 + SubChunk1Size) + (8 + SubChunk2Size)

	fread(type, sizeof(char), 4, f);
	if (!strcmp(type, "WAVE"))
	{
		OutputPrint("QwerkE_wav_loadSound: Not a \"WAVE\" file: %s", filePath);
		fclose(f);
		return nullptr;
	}

	// read "fmt " chunk
	fread(&subChunk1ID, sizeof(char), 4, f); // "fmt "
	if (!strcmp(type, "fmt "))
	{
		OutputPrint("QwerkE_wav_loadSound: No format found in file: %s", filePath);
		fclose(f);
		return nullptr;
	}

	fread(&subChunk1Size, sizeof(DWORD), 1, f);

	fread(&formatType, sizeof(short), 1, f); // not 1 == compression
	fread(&channels, sizeof(short), 1, f);
	fread(&sampleRate, sizeof(DWORD), 1, f);
	fread(&byteRate, sizeof(DWORD), 1, f);
	fread(&blockAlign, sizeof(short), 1, f);
	fread(&bitsPerSample, sizeof(short), 1, f);

	frequency = sampleRate;

	// read "data" chunk
	fread(type, sizeof(char), 4, f);
	if (!strcmp(type, "data"))
	{
		OutputPrint("QwerkE_wav_loadSound: No data in file: %s", filePath);
		fclose(f);
		return nullptr;
	}

	fread(&bufferSize, sizeof(DWORD), 1, f);

	unsigned char* buffer = new unsigned char[bufferSize]; //RAM: new

	int result = fread(buffer, 1, bufferSize, f);

	if (result != bufferSize || ferror(f) != 0)
	{
		OutputPrint("QwerkE_wav_loadSound: Error reading data in file: %s", filePath);
		fclose(f);
		return nullptr;
	}

	fclose(f);

	return buffer;
}