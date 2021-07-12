/**
 * @file camera.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

// std includes //
#include <utility>

// Library includes //
#include <vec3.hpp>

// Engine includes //w
#include "file_reader.hpp"

using namespace std;
using namespace glm;

/*! Camera class ?*/
class Camera {
    public:
        Camera(int width, int height);
        static bool Initialize(File_Reader& settings);
        static void Update();
        static void MouseUpdate(GLFWwindow*, double xpos, double ypos);
        static void Shutdown();


        static vec3& GetPosition();
        static vec3& GetFront();
        static vec3& GetUp();

        static float GetFov();
        static float GetNear();
        static float GetFar();

        static float GetYaw();
        static float GetPitch();

        static float& GetOriginalMoveSpeed();
        static float& GetOriginalSprintSpeed();
        static float& GetOriginalSensitivity();
    private:
        vec3 position;             //!< Position of camera
        vec3 front;                //!< Direction of camera
        vec3 up;                   //!< 90 degree upwards direction of camera
        float yaw;                 //!< x rotation
        float pitch;               //!< y rotation
        pair<float, float> last;   //!< Last position of mouse on screen
        float fov;                 //!< Field of view
        float speed;               //!< Move speed
        float nearV;               //!< Near view distance
        float farV;                //!< Far view distance
        float sensitivity;         //!< Mouse sensitivity
        float originalMoveSpeed;   //!< Initial move speed (speed gets change by delta time)
        float originalSprintSpeed; //!< Initial sprint speed
        float originalSensitivity; //!< Original mouse sensitivity 
        bool canMoveMouse;
};

#endif