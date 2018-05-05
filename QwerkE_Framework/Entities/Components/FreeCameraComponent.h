#ifndef _FreeCameraComponent_H_
#define _FreeCameraComponent_H_

#include "../../QwerkE_Enums.h"
#include "../../../QwerkE_Common/Math_Includes.h"
#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "Component.h"
#include "CameraComponent.h"
#include "../../Global_Constants.h"

class FreeCameraComponent : public CameraComponent
{
public:
	FreeCameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = g_YAW, float pitch = g_PITCH);
	~FreeCameraComponent();

	void ProcessKeyboard(eCamera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
	void ProcessMouseScroll(float yoffset);

private:

};

#endif //!_FreeCameraComponent_H_
