#include "FileLoader.h"
#include "LoadWavFile.h"

namespace QwerkE
{
	namespace FileLoader
	{
		unsigned char* LoadSoundFile(const char* path, DWORD& bufferSize, unsigned short& channels, ALsizei& frequency)
		{
			// get extension

			if (true) // wav
			{
				return QwerkE_wav_loadSound(path, bufferSize, channels, frequency);
				// QwerkE_wav_loadSound(path);
			}
		}
	}
}