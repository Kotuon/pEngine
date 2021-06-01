
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <utility>

#include <vec3.hpp>

using namespace std;
using namespace glm;

class Camera {
    public:
        Camera(int width, int height);
        static void Initialize(int width, int height);
        static void Update();
        static void MouseUpdate(GLFWwindow* window, double xpos, double ypos);
        static void Shutdown();


        static vec3& GetPosition();
        static vec3& GetFront();
        static vec3& GetUp();

        static float GetFov();
        static float GetNear();
        static float GetFar();

        static float GetYaw();
        static float GetPitch();
    private:
        vec3 position;
        vec3 front;
        vec3 up;
        float yaw;
        float pitch;
        pair<float, float> last;
        float fov;
        float speed;
        float nearV;
        float farV;
        float sensitivity;
};

#endif