#include "../../Entities/Components/PhysicsComponent.h"
#include "../../Headers/QwerkE_Enums.h"
#include "../../Entities/Components/Component.h"
#include "../../Entities/Components/Bullet3Component.h"

namespace QwerkE {

	Bullet3Component::Bullet3Component()
	{
		m_ComponentTag = Component_Physics;
	}

	Bullet3Component::~Bullet3Component()
	{
	}

	void Bullet3Component::getWorldTransform(btTransform& worldTrans) const
	{
		m_pParent->GetPosition();
	}

	//Bullet only calls the update of worldtransform for active objects
	void Bullet3Component::setWorldTransform(const btTransform& worldTrans)
	{
		/*worldTrans.getRotation().x;
		worldTrans.getRotation().y;
		worldTrans.getRotation().z;*/
		m_pParent->SetPosition(vec3(0, 0, 0));
	}

}
