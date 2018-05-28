#ifndef _LoadWavFile_H_
#define _LoadWavFile_H_

#include "../../Libraries/OpenAL/include/al.h"
#include "../../Libraries/OpenAL/include/alc.h"

unsigned char* QwerkE_wav_loadSound(const char* filePath, DWORD& bufferSize, unsigned short& channels, ALsizei& frequency);

#endif // !_LoadWavFile_H_
