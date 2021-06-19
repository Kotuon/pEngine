/**
 * @file graphics.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <string>
#include <vector>
#include <cmath>

// Library includes //
#include <vec3.hpp>
#include <vec2.hpp>
#include <mat4x4.hpp>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

// Engine includes //
  // System //
#include "engine.hpp"
#include "graphics.hpp"
  // Object //
#include "object_manager.hpp"
  // Component //
#include "model.hpp"
#include "transform.hpp"
  // Misc //
#include "camera.hpp"
#include "trace.hpp"
#include "shader.hpp"

using namespace glm;

static Graphics* graphics = nullptr; //!< Graphics object

/**
 * @brief Creates Graphics object with given window size
 * 
 * @param width 
 * @param height 
 */
Graphics::Graphics(int width, int height) {
    windowSize.first = width;
    windowSize.second = height;
}

/**
 * @brief Initializes the Graphics system using the settings in the given data
 * 
 * @param settings Settings information
 * @return true 
 * @return false 
 */
bool Graphics::Initialize(File_Reader& settings) {
      // Initializing graphics
    graphics = new Graphics(settings.Read_Int("windowWidth"), settings.Read_Int("windowHeight"));
    if (!graphics) {
        Trace::Message("Graphics was not initialized.");
        return false;
    }

      // Setting up error recording with graphics
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) {
        Trace::Message("Could not initialize GLFW.\n");
        return false;
    }

      // Setting up the graphics window
    graphics->window = glfwCreateWindow(graphics->windowSize.first, graphics->windowSize.second, 
        "pEngine", nullptr, nullptr);
    if (!graphics->window) {
        Trace::Message("Error creating window.\n");
        return false;
    }

      // Setting up callback functions
    glfwSetCursorPosCallback(graphics->window, Camera::MouseUpdate);
    glfwSetWindowSizeCallback(graphics->window, Reshape);

    glfwMakeContextCurrent(graphics->window);
    glfwSwapInterval(1);
    InitializeGL();
    Reshape(nullptr, graphics->windowSize.first, graphics->windowSize.second);

      // Setting up input for keyboard and mouse using glfw library
    glfwSetInputMode(graphics->window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(graphics->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

/**
 * @brief Initializes the settings of the graphics system
 * 
 * @return true 
 * @return false 
 */
bool Graphics::InitializeGL() {
    GLenum error = GL_NO_ERROR;

    glClearColor(0.f, 0.f, 0.f, 1.f);
    if (!Graphics::ErrorCheck(error)) return false;

    glClearDepth(1.f);
    if (!Graphics::ErrorCheck(error)) return false;

    glEnable(GL_DEPTH_TEST);
    if (!Graphics::ErrorCheck(error)) return false;

    glDepthFunc(GL_LEQUAL);
    if (!Graphics::ErrorCheck(error)) return false;

    glShadeModel(GL_SMOOTH);
    if (!Graphics::ErrorCheck(error)) return false;

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    if (!Graphics::ErrorCheck(error)) return false;

    glEnable(GL_CULL_FACE);
    if (!Graphics::ErrorCheck(error)) return false;

    return true;
}

/**
 * @brief Graphics update loop. Calls other update functions for the engine,
 *        input, and rendering. This is the main update function for the engine
 * 
 * @return void
 */ 
void Graphics::Update() {
    while(!glfwWindowShouldClose(graphics->window)) {
          // Run updates
        Engine::Update();
        Render();
        glfwPollEvents();

          // Check for restart
        if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_R) == GLFW_PRESS) {
            if (glfwGetKey(Graphics::GetWindow(), GLFW_KEY_R) == GLFW_RELEASE) {
                Engine::Restart();
            }
        }
    }
}

/**
 * @brief Renders all of the objects in the object_manager
 * 
 * @return void
 */
void Graphics::Render() {
      // Setting up graphics system for rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

      // Getting the view matrix of the camera
    mat4 view = lookAt(
        Camera::GetPosition(), 
        Camera::GetPosition() + Camera::GetFront(), 
        Camera::GetUp());

      // Updating the view matrix of the camera in the graphics system
    glLoadMatrixf(&view[0][0]);

      // Rendering all of the objects
    for (unsigned i = 0; i < Object_Manager::GetSize(); ++i) {
        Object* object = Object_Manager::FindObject(i);

        Model* model = object->GetComponent<Model>();

        glPushMatrix();
        model->Draw();
        glPopMatrix();
    }

    glfwSwapBuffers(graphics->window);
}

/**
 * @brief Shutdown the graphics system
 * 
 * @return void
 */
void Graphics::Shutdown() {
    if (!graphics) return;

      // Shutting down opengl
    glfwDestroyWindow(graphics->window);
    glfwTerminate();
      // Deleting graphics object
    delete graphics;
    graphics = nullptr;
}

/**
 * @brief Reshape callback for if the window changes size
 * 
 * @param width Width of the window
 * @param height Height of the window
 * @return void
 */
void Graphics::Reshape(GLFWwindow*, GLsizei width, GLsizei height) {
    if (height == 0) height = 1;

      // Updating viewport
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);

    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

      // Updating camera
    fH = tan( Camera::GetFov() / 180 * pi ) * Camera::GetNear();
    fW = fH * aspect;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -fW, fW, -fH, fH, Camera::GetNear(), Camera::GetFar());
}

/**
 * @brief Error callback for when the graphics system has an issue
 * 
 * @param error Error that occurred
 * @param description Description of error
 * @return void
 */
void Graphics::ErrorCallback(int error, const char* description) {
    Trace::Message("Error: " + string(description) + "\n");
}

/**
 * @brief Checking for error in given enum
 * 
 * @param error Possible error
 * @return true 
 * @return false 
 */
bool Graphics::ErrorCheck(GLenum error) {
    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error initializing OpenGl. \n");
        return false;
    }

    return true;
}

/**
 * @brief Returns window size
 * 
 * @return pair<int, int> 
 */
pair<int, int> Graphics::GetWindowSize() {
    return graphics->windowSize;
}

/**
 * @brief Return the graphics window
 * 
 * @return GLFWwindow* 
 */
GLFWwindow* Graphics::GetWindow() {
    return graphics->window;
}