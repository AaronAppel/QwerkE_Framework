#ifndef _Routine_H_
#define _Routine_H_

#include "../../QwerkE_Enums.h"

class GameObject;

class Routine
{
public:
	virtual ~Routine();

	virtual void Update(double a_Deltatime) {};

	virtual void Draw(GameObject* a_Camera) {};

	virtual void Initialize() = 0;

	/* CleanUp */
	// used to prevent deletion errors.
	// routines are to be deleted by their creators exclusively
	// CleanUp() is used to detach routines
	virtual void CleanUp() {};

	/* Getters + Setters */
	int GetPriority() { return m_Priority; };
	eRoutineTypes GetRoutineType() { return m_Type; };
	GameObject* GetParent() { return m_pParent; };

	void SetPriority(int priority) { m_Priority = priority; };
	void SetParent(GameObject* a_Parent) { m_pParent = a_Parent; };
	void SetRoutineType(eRoutineTypes type) { m_Type = type; };

protected:
	Routine();
	int m_Priority = 0; // render order / update order
	GameObject* m_pParent = nullptr;
	eRoutineTypes m_Type = eRoutineTypes::Routine_NULL;
};

#endif //!_Routine_H_
