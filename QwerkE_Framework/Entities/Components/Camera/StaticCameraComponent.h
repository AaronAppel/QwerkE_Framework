#ifndef __StaticCameraComponent_H_
#define __StaticCameraComponent_H_

class StaticCameraComponent : public CameraComponent
{
public:
	StaticCameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = g_YAW, float pitch = g_PITCH);
	~StaticCameraComponent();

	void ProcessKeyboard(eCamera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

private:

};

#endif //!__StaticCameraComponent_H_
