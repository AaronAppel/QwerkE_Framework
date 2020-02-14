#ifndef _FreeCameraComponent_H_
#define _FreeCameraComponent_H_

#include "../../../Libraries/glew/GL/glew.h"
#include "../Component.h"
#include "CameraComponent.h"
#include "../../../Headers/QwerkE_Global_Constants.h"

namespace QwerkE {

    class FreeCameraComponent : public CameraComponent
    {
    public:
        FreeCameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = gc_YAW, float pitch = gc_PITCH);
        ~FreeCameraComponent();

        void ProcessKeyboard(eCamera_Movement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
        void ProcessMouseScroll(float yoffset);

    private:

    };

}
#endif //!_FreeCameraComponent_H_
