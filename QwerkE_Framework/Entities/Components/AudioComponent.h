#ifndef _AudioComponent_H_
#define _AudioComponent_H_

#include "Component.h"

class AudioSource;

class AudioComponent : public Component // abstract
{
public:
	virtual ~AudioComponent();

	virtual int Play() = 0;

protected:
	AudioComponent();
};

#endif //!_AudioComponent_H_
