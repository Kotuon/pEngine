/**
 * @file camera.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Library includes
#include <glfw3.h>
#include <glm.hpp>

// Engine includes
  // System
#include "editor.hpp"
#include "engine.hpp"
#include "graphics.hpp"
  // Misc
#include "camera.hpp"
#include "trace.hpp"

static Camera* camera = nullptr; //!< Camera object

/**
 * @brief Creates a new camera with default values
 * 
 * @param width  Width of screen
 * @param height Height of screen
 */
Camera::Camera(int width, int height) : position(0.f, 0.f, 0.f), front(0.f, 0.f, -1.f),
    up(0.f, 1.f, 0.f), yaw(-90.f), pitch(0.f), last({ width / 2.f, height / 2.f }), 
    fov(45.f), speed(1), nearV(0.1f), farV(10000.f), sensitivity(1), canMoveMouse(true) {}

/**
 * @brief Initializes the camera
 * 
 * @param settings File that contains settings for the camera 
 * @return true 
 * @return false 
 */
bool Camera::Initialize(File_Reader& settings) {
      // Initializing the camera
    camera = new Camera(settings.Read_Int("windowWidth"), settings.Read_Int("windowHeight"));
    if (!camera) {
        Trace::Message("Camera was not initialized.");
        return false;
    }

      // Getting data from settings file
    camera->originalMoveSpeed = settings.Read_Float("moveSpeed");
    camera->originalSprintSpeed = settings.Read_Float("sprintSpeed");
    camera->originalSensitivity = settings.Read_Float("sensitivity");

    return true;
}

/**
 * @brief Moves the camera and checks for some other inputs
 * 
 * @return void
 */
void Camera::Update() {
      // Checking if the engine should be closed
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS && Editor::GetTakeKeyboardInput()) {
        if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            glfwSetWindowShouldClose(Graphics::GetWindow(), true);
        }
    }
    
      // Checking if sprint is being used
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera->speed = camera->originalSprintSpeed * Engine::GetDeltaTime();
    }
    else {
        camera->speed = camera->originalMoveSpeed * Engine::GetDeltaTime();
    }

      // Checking for movement using W, A, S, D, SPACE, and CTRL
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        camera->position += camera->speed * camera->front;
    }
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        camera->position -= camera->speed * camera->front;
    }
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        camera->position -= normalize(cross(camera->front, camera->up)) * camera->speed;
    }
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        camera->position += normalize(cross(camera->front, camera->up)) * camera->speed;
    }
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera->position += camera->speed * camera->up;
    }
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera->position -= camera->speed * camera->up;
    }

    if (glfwGetMouseButton(Graphics::GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && Editor::GetTakeKeyboardInput()) {
        camera->canMoveMouse = true;
    }
    if (glfwGetMouseButton(Graphics::GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        camera->canMoveMouse = false;
    }
}

/**
 * @brief Moves the camera using the mouse
 * 
 * @param xpos x position of the mouse
 * @param ypos y position of the mouse
 * @return void
 */
void Camera::MouseUpdate(GLFWwindow*, double xpos, double ypos) {
    if (!camera->canMoveMouse) {
        camera->last = { xpos, ypos };
        return;
    }
      // Setting up variables
    static bool firstMouse = true;
    std::pair<double, double> mousePos = { xpos, ypos };

      // Setting the camera sens using delta time
    camera->sensitivity = camera->originalSensitivity * Engine::GetDeltaTime();

      // Checking if this is the first time the function was called
    if (firstMouse) {
        camera->last = { mousePos.first, mousePos.second };
        firstMouse = false;
    }

      // Finding how far the mouse is from its last position
    std::pair<float, float> offset = { 
        mousePos.first - camera->last.first, 
        camera->last.second - mousePos.second
    };
      // Setting new last position
    camera->last = { mousePos.first, mousePos.second };

      // Updating offsets to use the sensitivity of the camera
    offset.first *= camera->sensitivity;
    offset.second *= camera->sensitivity;

      // Applying the offset to the camera's direction
    camera->yaw += offset.first;
    camera->pitch += offset.second;

      // Stops the camera from circling completely in the y direction
    if (camera->pitch > 89.f) camera->pitch = 89.f;
    if (camera->pitch < -89.f) camera->pitch = -89.f;

      // Finding the direction of the camera
    glm::vec3 tempFront = {
        std::cos(glm::radians(camera->yaw)) * std::cos(glm::radians(camera->pitch)),
        std::sin(glm::radians(camera->pitch)),
        std::sin(glm::radians(camera->yaw)) * std::cos(glm::radians(camera->pitch))
    };
    camera->front = glm::normalize(tempFront);

      // Finding the upward direction of the camera
    glm::vec3 tempUp = { 0.f, 1.f, 0.f };
    glm::vec3 right = glm::normalize(glm::cross(tempUp, camera->front));
    glm::vec3 up = glm::cross(camera->front, right);
    camera->up = up;
}

/**
 * @brief Deletes the camera object if it exists
 * 
 * @return void
 */
void Camera::Shutdown() {
    if (camera) {
        delete camera;
        camera = nullptr;
    }
}

/**
 * @brief Returns the position of the camera
 * 
 * @return vec3& 
 */
glm::vec3& Camera::GetPosition() { return camera->position; }

/**
 * @brief Returns the direction of the camera
 * 
 * @return vec3& 
 */
glm::vec3& Camera::GetFront() { return camera->front; }

/**
 * @brief Returns the upward direction of the camera
 * 
 * @return vec3& 
 */
glm::vec3& Camera::GetUp() { return camera->up; }

/**
 * @brief Returns the field of view of the camera
 * 
 * @return float 
 */
float Camera::GetFov() { return camera->fov; }

/**
 * @brief Returns the near view distance of the camera
 * 
 * @return float 
 */
float Camera::GetNear() { return camera->nearV; }

/**
 * @brief Returns the far view distance of the camera
 * 
 * @return float 
 */
float Camera::GetFar() { return camera->farV; }

/**
 * @brief Returns the x rotation of the camera
 * 
 * @return float 
 */
float Camera::GetYaw() { return camera->yaw; }

/**
 * @brief Returns the y rotation of the camera
 * 
 * @return float 
 */
float Camera::GetPitch() { return camera->pitch; }

/**
 * @brief Returns reference to originalMoveSpeed
 * 
 * @return float& 
 */
float& Camera::GetOriginalMoveSpeed() { return camera->originalMoveSpeed; }

/**
 * @brief Returns reference to originalSprintSpeed
 * 
 * @return float& 
 */
float& Camera::GetOriginalSprintSpeed() { return camera->originalSprintSpeed; }

/**
 * @brief Returns reference to originalSensitivity
 * 
 * @return float& 
 */
float& Camera::GetOriginalSensitivity() { return camera->originalSensitivity; }