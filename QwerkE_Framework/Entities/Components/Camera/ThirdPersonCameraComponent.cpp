#include "CameraComponent.h"
#include "ThirdPersonCameraComponent.h"
#include "../../GameObject.h"
#include "../../../Global_Constants.h"
#include "../Component.h"

ThirdPersonCameraComponent::ThirdPersonCameraComponent(vec3 position, vec3 up, float yaw, float pitch) :
	CameraComponent(position, up, yaw, pitch)
{
}

ThirdPersonCameraComponent::~ThirdPersonCameraComponent()
{
}

void ThirdPersonCameraComponent::ProcessKeyboard(eCamera_Movement direction, float deltaTime)
{
	this->GetParent()->GetPosition();

	float velocity = m_MovementSpeed * deltaTime;
	if (direction == FORWARD)
		m_Position += m_Front * velocity;
	if (direction == BACKWARD)
		m_Position -= m_Front * velocity;
	if (direction == LEFT)
		m_Position -= m_Right * velocity;
	if (direction == RIGHT)
		m_Position += m_Right * velocity;
	if (direction == UP)
		m_Position += m_CamUp * velocity;
	if (direction == DOWN)
		m_Position -= m_CamUp * velocity;

	// Update m_Front, m_Right and Up Vectors using the updated Eular angles
	UpdateCameraVectors();
	UpdateParentPosition(m_Position);
}

void ThirdPersonCameraComponent::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	this->GetParent()->GetPosition();
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

	// Update m_Front, m_Right and Up Vectors using the updated Eular angles
	UpdateCameraVectors();
}

void ThirdPersonCameraComponent::ProcessMouseScroll(float yoffset)
{
	CameraComponent::ProcessMouseScroll(yoffset);
}