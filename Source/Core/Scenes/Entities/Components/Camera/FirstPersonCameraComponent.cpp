#include "../Component.h"
#include "CameraComponent.h"
#include "FirstPersonCameraComponent.h"
#include "../../../../../Headers/QwerkE_Enums.h"
#include "../../GameObject.h"
#include "../../../../../../Libraries/glew/GL/glew.h"

namespace QwerkE {

    FirstPersonCameraComponent::FirstPersonCameraComponent(vec3 position, vec3 up, float yaw, float pitch) :
        CameraComponent(position, up, yaw, pitch)
    {

    }

    FirstPersonCameraComponent::~FirstPersonCameraComponent()
    {

    }

    void FirstPersonCameraComponent::UpdateCameraVectors()
    {
        m_ViewMatrix->CreateLookAtView(m_Position, m_CamUp, m_Forward); // view

        m_ProjMatrix->CreatePerspectiveHFoV(m_Zoom * 0.5f, m_ViewportSize.x / m_ViewportSize.y, m_CAMNEAR, m_CAMFAR); // projection
    }

    void FirstPersonCameraComponent::ProcessKeyboard(eCamera_Movement direction, float deltaTime)
    {
        // this->GetParent()->GetPosition();

        float velocity = m_MovementSpeed * deltaTime;
        if (direction == FORWARD)
            m_Position += m_Forward * velocity;
        if (direction == BACKWARD)
            m_Position -= m_Forward * velocity;
        if (direction == LEFT)
            m_Position -= m_Right * velocity;
        if (direction == RIGHT)
            m_Position += m_Right * velocity;
        if (direction == UP)
            m_Position += m_CamUp * velocity;
        if (direction == DOWN)
            m_Position -= m_CamUp * velocity;
        if (direction == RROTATE)
        {
            // calculate distance from target and use that as radius
            vec3 distance = m_Position - m_TargetPosition;

            // rotate around object on x/z axis


            m_Position -= m_CamUp * velocity;
        }
        if (direction == LROTATE)
        {
            // m_Position -= m_CamUp * velocity;
        }

        // Update m_Forward, m_Right and Up Vectors using the updated Eular angles
        FirstPersonCameraComponent::UpdateCameraVectors();
        CameraComponent::UpdateParentPosition(m_Position);
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

        FirstPersonCameraComponent::UpdateCameraVectors();
    }

    void FirstPersonCameraComponent::ProcessMouseScroll(float yoffset)
    {
        CameraComponent::ProcessMouseScroll(yoffset);
    }

}
