#ifndef _OpenAL_Component_H_
#define _OpenAL_Component_H_

#include "../AudioComponent.h"

#include "../../../QwerkE_Common/Libraries/OpenAL/include/al.h"

namespace QwerkE {

    class OpenAL_AudioComponent : public AudioComponent
    {
    public:
        OpenAL_AudioComponent();
        ~OpenAL_AudioComponent();

        int Play();

    private:
        ALuint m_Buffer = 0;
    };

}
#endif //!_OpenAL_Component_H_
