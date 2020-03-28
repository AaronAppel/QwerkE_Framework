#include "../../../../Headers/QwerkE_Enums.h"
#include "../../Entities/Components/LightComponent.h"
#include "../../Entities/Components/Component.h"

namespace QwerkE {

    LightComponent::LightComponent()
    {
        m_ComponentTag = Component_Light;
    }

    LightComponent::~LightComponent()
    {
    }

}
