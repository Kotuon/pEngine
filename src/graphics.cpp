
#include <string>
#include <vector>
#include <cmath>

#include <vec3.hpp>
#include <vec2.hpp>

#include "graphics.hpp"
#include "trace.hpp"
#include "model.hpp"
#include "object_manager.hpp"
#include "transform.hpp"
#include "engine.hpp"

Graphics* graphics;

Graphics::Graphics(int width, int height) {
    screenSize.first = width;
    screenSize.second = height;
}

bool Graphics::Initialize() {
    graphics = new Graphics(800, 600);
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

    glfwSetWindowSizeCallback(graphics->window, Reshape);
    glfwMakeContextCurrent(graphics->window);
    glfwSwapInterval(1);
    InitializeGL();
    Reshape(nullptr, graphics->screenSize.first, graphics->screenSize.second);

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


    return true;
}

void Graphics::Update() {
    while(!glfwWindowShouldClose(graphics->window)) {
        Engine::Update(0.f);
        Render();

        glfwSwapBuffers(graphics->window);
        glfwPollEvents();
    }
}

void Graphics::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (unsigned i = 0; i < Object_Manager::GetSize(); ++i) {
        Object* object = Object_Manager::FindObject(i);

        Model* model = object->GetComponent<Model>(CType::CModel);
        model->Draw();
    }
}

void Graphics::Shutdown() {
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

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( 45.f / 360 * pi ) * 0.1f;
    fW = fH * aspect;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -fW, fW, -fH, fH, 0.1f, 100.f);
}

void Graphics::ErrorCallback(int error, const char* description) {
    Trace::Message("Error: " + string(description) + "\n");
}

bool Graphics::ErrorCheck(GLenum error) {
    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }

    return true;
}