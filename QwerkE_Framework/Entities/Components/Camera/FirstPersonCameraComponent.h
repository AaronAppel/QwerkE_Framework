#ifndef __FirstPersonCameraComponent_H_
#define __FirstPersonCameraComponent_H_

class FirstPersonCameraComponent : public CameraComponent
{
public:
	FirstPersonCameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = g_YAW, float pitch = g_PITCH);
	~FirstPersonCameraComponent();

	void ProcessKeyboard(eCamera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

private:

};

#endif //!__FirstPersonCameraComponent_H_
