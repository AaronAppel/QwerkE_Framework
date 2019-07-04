#include "GameObject.h"
#include "../Scenes/Scene.h"
#include "Routines/Routine.h"
#include "Components/Component.h"
#include "../Headers/QwerkE_Enums.h"


GameObject::GameObject(Scene* scene)
{
	m_pScene = scene;
	for (int i = 0; i < m_BaseUpdateListSize; i++)
	{
		m_UpdateList.push_back(nullptr); // fill for runtime
	}
	for (int i = 0; i < m_BaseDrawListSize; i++)
	{
		m_DrawList.push_back(nullptr); // fill for runtime
	}
}

GameObject::GameObject(Scene* scene, vec3 position)
{
	m_Transform.s_Position = position;
	m_pScene = scene;
	for (int i = 0; i < m_BaseUpdateListSize; i++)
	{
		m_UpdateList.push_back(nullptr); // fill for runtime
	}
	for (int i = 0; i < m_BaseDrawListSize; i++)
	{
		m_DrawList.push_back(nullptr); // fill for runtime
	}
}

GameObject::~GameObject()
{
	for (auto l_LoopVar : m_Components)
	{
		delete l_LoopVar.second;
	}
	m_Components.clear();
	for (unsigned int i = 0; i < m_UpdateList.size(); i++)
	{
		if (m_UpdateList.at(i) != nullptr)
		{
			m_UpdateList.at(i)->CleanUp(); // detach foreign routines
		}
	}
	for (unsigned int i = 0; i < m_UpdateList.size(); i++)
	{
		delete m_UpdateList.at(i); // TODO: Delete or nullptr?
	}
	m_UpdateList.clear();
	for (unsigned int i = 0; i < m_DrawList.size(); i++)
	{
		delete m_DrawList.at(i);
	}
	m_DrawList.clear();
}

void GameObject::Update(double deltatime)
{
	for (unsigned int i = 0; i < m_UpdateList.size(); i++)
	{
		if (m_UpdateList.at(i) != nullptr)
		{
			m_UpdateList.at(i)->Update(deltatime);
		}
	}
	Component* tempComp = nullptr;
}

void GameObject::Draw(GameObject* camera)
{
	for (unsigned int i = 0; i < m_DrawList.size(); i++)
	{
		if (m_DrawList.at(i) != nullptr)
		{
			m_DrawList.at(i)->Draw(camera);
		}
	}
}

void GameObject::AddComponent(Component* component)
{
	if (m_Components.find(component->GetTag()) == m_Components.end())
	{
		m_Components[component->GetTag()] = component;
		component->SetParent(this);
	}
};

void GameObject::AddRoutine(Routine* routine)
{
	routine->SetParent(this);
	routine->Initialize();
}

void GameObject::AddUpdateRoutine(Routine* routine)
{
    if (!routine) { return; }

	for (unsigned int i = 0; i < m_UpdateList.size(); i++)
	{
		if (m_UpdateList.at(i) == nullptr)
		{
			m_UpdateList.at(i) = routine;
			return;
		}
	}
	m_UpdateList.push_back(routine);
}

void GameObject::AddDrawRoutine(Routine* routine)
{
    if (!routine) { return; }

	for (unsigned int i = 0; i < m_DrawList.size(); i++)
	{
		if (m_DrawList.at(i) == nullptr)
		{
			m_DrawList.at(i) = routine;
			return;
		}
	}
	m_DrawList.push_back(routine);
}

void GameObject::RemoveRoutine(Routine* routine) // TODO:: handle removing routines
{
	for (unsigned int i = 0; i < m_UpdateList.size(); i++)
	{
		if (m_UpdateList.at(i) == routine) // pointer comparison
		{
			m_UpdateList.at(i) = nullptr; // routine needs to be delete by creator
		}
	}
	for (unsigned int i = 0; i < m_DrawList.size(); i++)
	{
		if (m_DrawList.at(i) == routine) // pointer comparison
		{
			m_DrawList.at(i) = nullptr; // routine needs to be delete by creator
		}
	}
}

Component* GameObject::GetComponent(eComponentTags tag)
{
	if (m_Components.find(tag) != m_Components.end())
	{
		return m_Components[tag];
	}
		return nullptr;
}

void GameObject::Reset()
{
	for (auto l_LoopVar : m_Components)
	{
		l_LoopVar.second->Reset();
	}
}

void GameObject::Activate()
{
	for (auto l_LoopVar : m_Components)
	{
		l_LoopVar.second->Activate();
	}
}

void GameObject::Deactivate()
{
	for (auto l_LoopVar : m_Components)
	{
		l_LoopVar.second->Deactivate();
	}
}

Routine* GameObject::GetFirstUpdateRoutineOfType(eRoutineTypes type)
{
	Routine* t_ReturnRoutine = nullptr;
	for (unsigned int i = 0; i < m_UpdateList.size(); i++)
	{
		if (m_UpdateList.at(i)->GetRoutineType() == type)
		{
			return m_UpdateList.at(i);
		}
	}
	return t_ReturnRoutine;
}

Routine* GameObject::GetFirstDrawRoutineOfType(eRoutineTypes type)
{
	Routine* rRoutine = nullptr;
	for (unsigned int i = 0; i < m_DrawList.size(); i++)
	{
		if (m_DrawList.at(i)->GetRoutineType() == type)
		{
			rRoutine = m_DrawList.at(i);
			break;
		}
	}
	return rRoutine;
}

void GameObject::SetPosition(vec3 position)
{
	m_Transform.s_Position = position;
	// TODO: Update direction vectors
	if (m_Components.find(Component_Physics) != m_Components.end())
	{
		// TODO: Update children or components. Could use listeners or callbacks.
		//((PhysicsComponent*)m_Components[Component_Physics])->SetTransform(vec2(m_Position.x, m_Position.z), m_Rotation.y);
	}
}

void GameObject::SetRotation(vec3 rotation)
{
	m_Transform.s_Rotation = rotation; // TODO: Cap rotation degrees to 360
	// TODO: Update direction vectors
}