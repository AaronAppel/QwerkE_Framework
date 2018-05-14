#ifndef _LoadWavFile_H_
#define _LoadWavFile_H_

#include "../../Libraries/OpenAL/include/al.h"
#include "../../Libraries/OpenAL/include/alc.h"

bool LoadWavFile(const char* filename, ALuint& data);

#endif // !_LoadWavFile_H_
