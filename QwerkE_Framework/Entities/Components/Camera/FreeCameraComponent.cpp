#include "../Component.h"
#include "FreeCameraComponent.h"
#include "../../../../QwerkE_Common/Math_Includes.h"
#include "CameraComponent.h"
#include "../../../QwerkE_Enums.h"
#include "../../GameObject.h"

// https://msdn.microsoft.com/en-us/library/bb203907(v=xnagamestudio.10).aspx

FreeCameraComponent::FreeCameraComponent(vec3 position, vec3 up, float yaw, float pitch) :
	CameraComponent(position, up, yaw, pitch)
{
}

FreeCameraComponent::~FreeCameraComponent()
{
}

void FreeCameraComponent::ProcessKeyboard(eCamera_Movement direction, float deltaTime)
{
	// https://learnopengl.com/Getting-started/Camera
	float velocity = m_MovementSpeed * deltaTime;
	float forwardVel = m_MovementSpeed * deltaTime;
	float angularVel = 0.35f * deltaTime;

	if (direction == eCamera_Movement::FORWARD)
	{
		m_Position += m_Forward * forwardVel;
	}
	else if(direction == eCamera_Movement::BACKWARD)
	{
		m_Position -= m_Forward * forwardVel;
	}
	else if (direction == eCamera_Movement::RIGHT)
	{
		m_Position += m_Right * velocity;
	}
	else if (direction == eCamera_Movement::LEFT)
	{
		m_Position -= m_Right * velocity;
	}
	else if (direction == eCamera_Movement::UP)
	{
		m_Position += m_CamUp * velocity;
	}
	else if (direction == eCamera_Movement::DOWN)
	{
		m_Position -= m_CamUp * velocity;
	}
	else if (direction == eCamera_Movement::RROTATE)
	{
		m_Forward += vec3(angularVel, 0, angularVel);
		m_Forward.Normalize();
		m_Right = g_WORLDUP.Cross(m_Forward).GetNormalized() * m_MovementSpeed;
		m_Right.Normalize();
	}
	else if (direction == eCamera_Movement::LROTATE)
	{
		m_Forward -= vec3(angularVel, 0, angularVel);
		m_Forward.Normalize();
		m_Right = g_WORLDUP.Cross(m_Forward).GetNormalized() * m_MovementSpeed;
		m_Right.Normalize();
	}

	// update parent position
	UpdateParentPosition(m_Position);
	// TODO: Update parent rotation

	m_ViewMatrix->CreateLookAtView(m_Position, m_CamUp, m_Position - m_Forward); // view
	m_ProjMatrix->CreatePerspectiveHFoV(m_Zoom * 0.5f, m_ViewportSize.x / m_ViewportSize.y, m_CAMNEAR, m_CAMFAR); // projection
}

void FreeCameraComponent::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	// Update m_Forward, m_Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void FreeCameraComponent::ProcessMouseScroll(float yoffset)
{
	CameraComponent::ProcessMouseScroll(yoffset);
}