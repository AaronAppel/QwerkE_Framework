#ifndef _AudioComponent_H_
#define _AudioComponent_H_

#include "Component.h"

class AudioSource;

class AudioComponent : public Component
{
public:
	virtual ~AudioComponent();

	AudioSource* GetSource() { return m_Source; }

protected:
	AudioComponent();
	AudioSource* m_Source;
};

#endif //!_AudioComponent_H_
