#ifndef _Transform_Routine_H_
#define _Transform_Routine_H_

#include "Routine.h"

class TransformRoutine : Routine
{
public:
	TransformRoutine() {};
	~TransformRoutine() {};

	void Initialize();

	void Update(double a_Deltatime);

	// Setters
	float GetSpeed() { return m_Speed; }
	vec3 GetPositionOff() { return m_PositionOffset; }
	vec3 GetRotationOff() { return m_RotationOffset; }
	vec3 GetScaleOff() { return m_ScaleOffset; }

	// Gettters
	void SetSpeed(float speed) { m_Speed = speed; }
	void SetPositionOff(vec3 pos) { m_PositionOffset = pos; }
	void SetRotationOff(vec3 rot) { m_RotationOffset = rot; }
	void SetScaleOff(vec3 scale) { m_ScaleOffset = scale; }

private:
	float m_Speed = 1.0f;

	vec3 m_PositionOffset = vec3(0, 0, 0);
	vec3 m_RotationOffset = vec3(0, 0, 0);
	vec3 m_ScaleOffset = vec3(0, 0, 0);
};

#endif //!_Transform_Routine_H_
