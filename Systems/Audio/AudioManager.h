#ifndef _AudioManager_H_
#define _AudioManager_H_

class AudioManager
{
public:
    virtual ~AudioManager() {};

	virtual void PlaySound(const char* name) = 0; // music, effects, dialogue

	virtual void SetListenerOrientation(vec3 position, vec3 velocity) = 0;
};

#endif // !_AudioManager_H_
