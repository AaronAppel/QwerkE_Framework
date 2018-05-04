#ifndef _AudioManager_H_
#define _AudioManager_H_

// TODO: Remove unecessary includes
#include "../../Shared_Generic/Libraries/OpenAL/include/al.h"
#include "../../Shared_Generic/Libraries/OpenAL/include/alc.h"
#include "../../Shared_Generic/Libraries/OpenAL/include/efx.h"
#include "../../Shared_Generic/Libraries/OpenAL/include/efx-creative.h"
#include "../../Shared_Generic/Libraries/OpenAL/include/EFX-Util.h"
#include "../../Shared_Generic/Libraries/OpenAL/include/xram.h"

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
