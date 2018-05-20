#ifndef _OpenAL_Component_H_
#define _OpenAL_Component_H_

#include "../AudioComponent.h"

class AudioSource;

class OpenAL_AudioComponent : public AudioComponent
{
public:
	OpenAL_AudioComponent();
	~OpenAL_AudioComponent();

	AudioSource* GetSource() { return m_Source; }

private:
	AudioSource* m_Source;
};

#endif //!_OpenAL_Component_H_
