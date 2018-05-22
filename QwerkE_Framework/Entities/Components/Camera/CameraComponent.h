#ifndef _CameraComponent_H_
#define _CameraComponent_H_

#include "../../../QwerkE_Global_Constants.h"
#include "../../Math_Includes.h"
#include "../../../QwerkE_Common/Libraries/glew/GL/glew.h"
#include "../../../QwerkE_Enums.h"
#include "../../Components/Component.h"

const vec3 g_WORLDUP = vec3(0, -1, 0); // TODO: Fix inverted world Y-axis

class CameraComponent : public Component
{
public:
	CameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = g_YAW, float pitch = g_PITCH);
	CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~CameraComponent();

	void Setup();

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	virtual mat4* GetViewMatrix();
	virtual mat4* GetProjectionMatrix();

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	virtual void ProcessKeyboard(eCamera_Movement direction, float deltaTime) = 0;

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	virtual void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) = 0;
	void Rotate() {};

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	virtual void ProcessMouseScroll(float yoffset);
	void ZoomCamera(float yOffset) { ProcessMouseScroll(yOffset); };

	// Calculates the front vector from the Camera's (updated) Eular Angles
	void UpdateCameraVectors();

	/* Getters + Setters*/
	// Getters
	eCamType GetType() { return m_Type; };

	// Setters
	void SetType(eCamType type) { m_Type = type; };
	void SetTargetPosition(vec3 position);
	void SetViewportSize(vec2 size) { m_ViewportSize = size; UpdateCameraVectors(); };

protected:
	// Camera Attributes
	eCamType m_Type = CamType_NULL;

	vec3 m_Position = vec3(0, 0, 0);
	vec3 m_Front = vec3(0.0f, 0.0f, 1.0f);
	vec3 m_WorldUp = g_WORLDUP;
	vec3 m_CamUp = m_WorldUp;
	vec3 m_Right = vec3(1, 0, 0);

	float m_CAMNEAR = 0.01f; // Near and far frustum values
	float m_CAMFAR = 1000.0f;

	// Eular Angles
	float m_Yaw = g_YAW;
	float m_Pitch = g_PITCH;
	// Camera options
	float m_MovementSpeed = g_SPEED;
	float m_MouseSensitivity = g_SENSITIVTY;
	float m_Zoom = g_ZOOM;

	vec3 m_TargetPosition = m_Position + m_Front * 1.5f;

	// Camera Control Behaviour
	bool m_LookAt = false;

	vec2 m_ViewportSize = vec2(1280, 720);

	// matrices
	mat4* m_ViewMatrix = new mat4();
	mat4* m_ProjMatrix = new mat4();

	void UpdateParentPosition(vec3 m_Position);
};

#endif //!_CameraComponent_H_
