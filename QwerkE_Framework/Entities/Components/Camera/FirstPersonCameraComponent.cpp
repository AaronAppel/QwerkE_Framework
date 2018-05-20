#include "../Component.h"
#include "CameraComponent.h"
#include "FirstPersonCameraComponent.h"
#include "../../../QwerkE_Common/Math_Includes.h"
#include "../../../QwerkE_Enums.h"
#include "../../GameObject.h"
#include "../../../../QwerkE_Common/Libraries/glew/GL/glew.h"

FirstPersonCameraComponent::FirstPersonCameraComponent(vec3 position, vec3 up, float yaw, float pitch) :
	CameraComponent(position, up, yaw, pitch)
{

}

FirstPersonCameraComponent::~FirstPersonCameraComponent()
{

}

void FirstPersonCameraComponent::ProcessKeyboard(eCamera_Movement direction, float deltaTime)
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

void FirstPersonCameraComponent::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
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

	UpdateCameraVectors();
}

void FirstPersonCameraComponent::ProcessMouseScroll(float yoffset)
{
	CameraComponent::ProcessMouseScroll(yoffset);
}