#ifndef _Null_Audio_Manager_H_
#define _Null_Audio_Manager_H_

#include "AudioManager.h"

class NullAudioManager : public AudioManager
{
public:
    NullAudioManager()
    {
        ConsolePrint("\nNullAudioManager loaded successfully\n\n");
    }

    ~NullAudioManager() {};

    void PlaySound(const char* name)
    {
        ConsolePrint("\nNullAudioManager.PlaySound()\n");
    }

    void SetListenerOrientation(vec3 position, vec3 velocity)
    {
        ConsolePrint("\SetListenerOrientation.PlaySound()\n");
    }
};

#endif // _Null_Audio_Manager_H_
