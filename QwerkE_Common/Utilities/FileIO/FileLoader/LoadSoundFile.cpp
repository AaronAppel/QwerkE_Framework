#include "FileLoader.h"
#include "LoadWavFile.h"

namespace QwerkE
{
	namespace FileLoader
	{
		unsigned char* LoadSoundFile(const char* path, DWORD& bufferSize)
		{
			// get extension

			if (true) // wav
			{
				return QwerkE_wav_loadSound(path, bufferSize);
				// QwerkE_wav_loadSound(path);
			}
		}
	}
}