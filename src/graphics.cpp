
#include <string>
#include <vector>
#include <cmath>

#include <vec3.hpp>
#include <vec2.hpp>
#include <mat4x4.hpp>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

#include "graphics.hpp"
#include "trace.hpp"
#include "model.hpp"
#include "object_manager.hpp"
#include "transform.hpp"
#include "engine.hpp"
#include "camera.hpp"

using namespace glm;

static Graphics* graphics = nullptr;

Graphics::Graphics(int width, int height) {
    screenSize.first = width;
    screenSize.second = height;
}

bool Graphics::Initialize(File_Reader& settings) {
    graphics = new Graphics(settings.Read_Int("windowWidth"), settings.Read_Int("windowHeight"));
    if (!graphics) {
        Trace::Message("Graphics was not initialized.");
        return false;
    }

    glfwSetErrorCallback(ErrorCallback);
    
    if (!glfwInit()) {
        Trace::Message("Could not initialize GLFW.\n");
        return false;
    }

    graphics->window = glfwCreateWindow(graphics->screenSize.first, graphics->screenSize.second, 
        "pEngine", nullptr, nullptr);
    
    if (!graphics->window) {
        Trace::Message("Error creating window.\n");
        return false;
    }

    glfwSetCursorPosCallback(graphics->window, Camera::MouseUpdate);
    glfwSetWindowSizeCallback(graphics->window, Reshape);
    glfwMakeContextCurrent(graphics->window);
    glfwSwapInterval(1);
    InitializeGL();
    Reshape(nullptr, graphics->screenSize.first, graphics->screenSize.second);

    glfwSetInputMode(graphics->window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(graphics->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
}

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

void Graphics::Update() {
    while(!glfwWindowShouldClose(graphics->window)) {
        Engine::Update();
        Render();

        glfwPollEvents();
    }
}

void Graphics::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    mat4 view = lookAt(
        Camera::GetPosition(), 
        Camera::GetPosition() + Camera::GetFront(), 
        Camera::GetUp());

    glLoadMatrixf(&view[0][0]);

    for (unsigned i = 0; i < Object_Manager::GetSize(); ++i) {

        Object* object = Object_Manager::FindObject(i);

        Model* model = object->GetComponent<Model>();

        glPushMatrix();
        model->Draw();
        glPopMatrix();
    }

    glfwSwapBuffers(graphics->window);
}

void Graphics::Shutdown() {
    if (!graphics) return;

    glfwDestroyWindow(graphics->window);
    glfwTerminate();
    delete graphics;
}

void Graphics::Reshape(GLFWwindow*, GLsizei width, GLsizei height) {
    if (height == 0) height = 1;

    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);

    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    fH = tan( Camera::GetFov() / 180 * pi ) * Camera::GetNear();
    fW = fH * aspect;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -fW, fW, -fH, fH, Camera::GetNear(), Camera::GetFar());
}

void Graphics::ErrorCallback(int error, const char* description) {
    Trace::Message("Error: " + string(description) + "\n");
}

bool Graphics::ErrorCheck(GLenum error) {
    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error initializing OpenGl. \n");
        return false;
    }

    return true;
}

pair<int, int> Graphics::GetScreenSize() {
    return graphics->screenSize;
}

GLFWwindow* Graphics::GetWindow() {
    return graphics->window;
}