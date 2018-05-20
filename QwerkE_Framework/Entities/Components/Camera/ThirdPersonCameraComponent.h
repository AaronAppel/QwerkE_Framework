#ifndef __ThirdPersonCameraComponent_H_
#define __ThirdPersonCameraComponent_H_

class ThirdPersonCameraComponent : public CameraComponent
{
public:
	ThirdPersonCameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = g_YAW, float pitch = g_PITCH);
	~ThirdPersonCameraComponent();

	void ProcessKeyboard(eCamera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

private:

};

#endif //!__ThirdPersonCameraComponent_H_
