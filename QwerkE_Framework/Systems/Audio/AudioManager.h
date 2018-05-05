#ifndef _AudioManager_H_
#define _AudioManager_H_

// TODO: Remove unecessary includes
#include "../QwerkE_Common/Libraries/OpenAL/include/al.h"
#include "../QwerkE_Common/Libraries/OpenAL/include/alc.h"
#include "../QwerkE_Common/Libraries/OpenAL/include/efx.h"
#include "../QwerkE_Common/Libraries/OpenAL/include/efx-creative.h"
#include "../QwerkE_Common/Libraries/OpenAL/include/EFX-Util.h"
#include "../QwerkE_Common/Libraries/OpenAL/include/xram.h"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void PlaySound();
	// music, effect, dialogue

private:
    ALCdevice* Device;
    ALCcontext* Context;
    ALboolean g_bEAX;
    ALsizei NUM_BUFFERS;
    ALuint* g_Buffers;
};

#endif // !_AudioManager_H_
