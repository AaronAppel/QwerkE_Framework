#ifndef _FirstPersonCameraComponent_H_
#define _FirstPersonCameraComponent_H_

namespace QwerkE {

    class FirstPersonCameraComponent : public CameraComponent
    {
    public:
        FirstPersonCameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = gc_YAW, float pitch = gc_PITCH);
        ~FirstPersonCameraComponent();

        virtual void UpdateCameraVectors();

        void ProcessKeyboard(eCamera_Movement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        void ProcessMouseScroll(float yoffset);

    private:

    };

}
#endif //!_FirstPersonCameraComponent_H_
