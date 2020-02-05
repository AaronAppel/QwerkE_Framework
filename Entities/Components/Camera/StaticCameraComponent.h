#ifndef _StaticCameraComponent_H_
#define _StaticCameraComponent_H_

namespace QwerkE {

    class StaticCameraComponent : public CameraComponent
    {
    public:
        StaticCameraComponent(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = g_WORLDUP, float yaw = gc_YAW, float pitch = gc_PITCH);
        ~StaticCameraComponent();

        void ProcessKeyboard(eCamera_Movement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        void ProcessMouseScroll(float yoffset);

    private:

    };

}
#endif //!_StaticCameraComponent_H_
