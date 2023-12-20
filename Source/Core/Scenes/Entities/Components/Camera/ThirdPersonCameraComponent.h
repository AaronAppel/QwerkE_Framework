#ifndef _ThirdPersonCameraComponent_H_
#define _ThirdPersonCameraComponent_H_

#include "CameraComponent.h"

namespace QwerkE {

    class ThirdPersonCameraComponent : public CameraComponent
    {
    public:
        ThirdPersonCameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = gc_YAW, float pitch = gc_PITCH);
        ~ThirdPersonCameraComponent();

        void ProcessKeyboard(eCamera_Movement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        void ProcessMouseScroll(float yoffset);
    };

}
#endif //!_ThirdPersonCameraComponent_H_
