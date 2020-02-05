#include "../../Entities/Components/PhysicsComponent.h"
#include "../../Headers/QwerkE_Enums.h"
#include "../../Entities/Components/Component.h"

namespace QwerkE {

    PhysicsComponent::PhysicsComponent()
    {
        m_ComponentTag = Component_Physics;
    }

    PhysicsComponent::~PhysicsComponent()
    {
    }

}
