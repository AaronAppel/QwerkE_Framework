#ifndef _LightComponent_H_
#define _LightComponent_H_

#include "../../Entities/Components/Component.h"
#include "../../../../Headers/QwerkE_Enums.h"

#pragma warning( disable : 26495 )
class MyMatrix;
#pragma warning( default : 26495 )

namespace QwerkE {

    class LightComponent : public Component
    {
    public:
        LightComponent();
        ~LightComponent();

        /* Getters + Setters */
        // getters
        eLightType GetType() { return m_Type; }
        vec3 GetColour() { return m_Colour; };
        bool GetIsON() { return m_IsOn; };

        // setters
        void SetType(eLightType type) { m_Type = type; }
        void SetColour(vec3 ambient) { m_Colour = ambient; };
        void SetIsOn(bool isOn) { m_IsOn = isOn; }

    private:
        bool m_IsOn = true; // TODO: Communicate light state visually. Could turn mesh colour black (would have to save previous colour)
        vec3 m_Colour = vec3(1, 1, 1);
        float m_Attenuation = 1.0f; // Brightness over distance // Currently unused
        float m_AttenuationDecay = 100.0f; // Distance for attenuation to decay to x value

        eLightType m_Type = LightType_NULL;
    };

}
#endif //!_LightComponent_H_
