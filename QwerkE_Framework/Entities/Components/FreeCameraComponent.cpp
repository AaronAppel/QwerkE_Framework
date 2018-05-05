#include "Component.h"
#include "FreeCameraComponent.h"
#include "../../../QwerkE_Common/Math_Includes.h"
#include "CameraComponent.h"
#include "../../QwerkE_Enums.h"
#include "../GameObject.h"

FreeCameraComponent::FreeCameraComponent(vec3 position, vec3 up, float yaw, float pitch) :
	CameraComponent(position, up, yaw, pitch)
{

}

FreeCameraComponent::~FreeCameraComponent()
{

}

void FreeCameraComponent::ProcessKeyboard(eCamera_Movement direction, float deltaTime)
{
	this->GetParent()->GetPosition(); // Parent GameObject().position

	if (m_LookAt)
	{
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
	}
	else
	{
		float velocity = m_MovementSpeed * deltaTime;
		if (direction == FORWARD)
		{
			m_TargetPosition += m_Front * velocity;
			m_Position += m_Front * velocity;
		}
		if (direction == BACKWARD)
		{
			m_TargetPosition -= m_Front * velocity;
			m_Position -= m_Front * velocity;
		}
		if (direction == LEFT)
		{
			m_TargetPosition -= m_Right * velocity; // Strafe
			m_Position -= m_Right * velocity;

			/*
			mat4 temp;
			temp.CreateSRT(vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 90.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));
			m_Right = m_Right * glm::vec3(temp.GetAt().x, temp.GetAt().y, temp.GetAt().z);
			m_TargetPosition -=  m_Right * velocity;
			*/
		}
		if (direction == RIGHT)
		{
			m_TargetPosition += m_Right * velocity; // Strafe
			m_Position += m_Right * velocity;

			/*
			mat4 temp; // Rotate
			temp.CreateSRT(vec3(1.0f, 1.0f, 1.0f), vec3(0.0f, 90.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));
			glm::vec3 pos = glm::vec3(temp.GetAt().x, temp.GetAt().y, temp.GetAt().z);
			m_TargetPosition += pos * m_Right * velocity;
			*/
		}
		if (direction == UP)
		{
			m_TargetPosition += m_CamUp * velocity;
			m_Position += m_CamUp * velocity;
		}
		if (direction == DOWN)
		{
			m_TargetPosition -= m_CamUp * velocity;
			m_Position -= m_CamUp * velocity;
		}
	}
	// update parent position
	UpdateParentPosition(m_Position);
	UpdateCameraVectors();
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

	// Update m_Front, m_Right and Up Vectors using the updated Eular angles
	UpdateCameraVectors();
}

void FreeCameraComponent::ProcessMouseScroll(float yoffset)
{
	CameraComponent::ProcessMouseScroll(yoffset);
}