
#include <glfw3.h>
#include <glm.hpp>

#include "camera.hpp"
#include "graphics.hpp"
#include "engine.hpp"

Camera* camera;

Camera::Camera(int width, int height) : position(0.f, 0.f, 0.f), front(0.f, 0.f, -1.f),
    up(0.f, 1.f, 0.f), yaw(-90.f), pitch(0.f), last({ width / 2.f, height / 2.f }), 
    fov(45.f), speed(1), nearV(0.1f), farV(100.f), sensitivity(1) {}

void Camera::Initialize(int width, int height) {
    camera = new Camera(width, height);
}

void Camera::Update() {
    if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(Graphics::GetWindow(), true);
    }
    
    camera->speed = .00000005f * Engine::GetDeltaTime();

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
}

void Camera::MouseUpdate(GLFWwindow*, double xpos, double ypos) {
    static bool firstMouse = true;
    pair<double, double> mousePos = { xpos, ypos };

    camera->sensitivity = 0.0000000075f * Engine::GetDeltaTime();

    if (firstMouse) {
        camera->last = { mousePos.first, mousePos.second };
        firstMouse = false;
    }

    pair<float, float> offset = { 
        mousePos.first - camera->last.first, 
        camera->last.second - mousePos.second
    };

    camera->last = { mousePos.first, mousePos.second };

    offset.first *= camera->sensitivity;
    offset.second *= camera->sensitivity;

    camera->yaw += offset.first;
    camera->pitch += offset.second;

    if (camera->pitch > 89.f) camera->pitch = 89.f;
    if (camera->pitch < -89.f) camera->pitch = -89.f;

    vec3 tempFront = {
        cos(radians(camera->yaw)) * cos(radians(camera->pitch)),
        sin(radians(camera->pitch)),
        sin(radians(camera->yaw)) * cos(radians(camera->pitch))
    };

    camera->front = normalize(tempFront);

    vec3 tempUp = { 0.f, 1.f, 0.f };
    vec3 right = normalize(cross(tempUp, camera->front));

    vec3 up = cross(camera->front, right);

    camera->up = up;
}

void Camera::Shutdown() {
    delete camera;
}

vec3& Camera::GetPosition() {
    return camera->position;
}

vec3& Camera::GetFront() {
    return camera->front;
}

vec3& Camera::GetUp() {
    return camera->up;
}

float Camera::GetFov() {
    return camera->fov;
}

float Camera::GetNear() {
    return camera->nearV;
}

float Camera::GetFar() {
    return camera->farV;
}

float Camera::GetYaw() {
    return camera->yaw;
}

float Camera::GetPitch() {
    return camera->pitch;
}
