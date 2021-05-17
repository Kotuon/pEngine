
#include <string>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <vec3.hpp>
#include <vec2.hpp>

#include "graphics.hpp"
#include "trace.hpp"
#include "model.hpp"

Graphics* graphics;

static Model* model;

Graphics::Graphics(int width, int height) {
    screenSize.first = width;
    screenSize.second = height;
    angleCube = 0.f;
}

void Graphics::Initialize(int argc, char** argv) {
    graphics = new Graphics(800, 600);

    model = new Model(GL_QUADS);
    model->Load("data/cube.obj");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(graphics->screenSize.first, graphics->screenSize.second);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("pEngine");
    glutDisplayFunc(Render);
    glutReshapeFunc(Reshape);
    
    InitializeGL();
    glutTimerFunc(0, Timer, 0);
}

bool Graphics::InitializeGL() {
    GLenum error = GL_NO_ERROR;

    glClearColor(0.f, 0.f, 0.f, 1.f);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGL. \n");
        return false;
    }

    glClearDepth(1.f);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    
    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }

    glDepthFunc(GL_LEQUAL);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }

    glShadeModel(GL_SMOOTH);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }


    return true;
}

void Graphics::Update() {
    glutMainLoop();
}

void Graphics::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.f, 0.f, -7.f);
    glRotatef(graphics->angleCube, 1.f, 1.f, 1.f);

    model->Draw();

   glutSwapBuffers();

   graphics->angleCube += .3f;
}

void Graphics::Shutdown() {
    SDL_DestroyWindow(graphics->window);
    SDL_Quit();
    
    delete graphics;
}

void Graphics::SwapWindow() {
    SDL_GL_SwapWindow(graphics->window);
}

void Graphics::Reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;

    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f, aspect, 0.1f, 100.f);
}

void Graphics::Timer(int time) {
    glutPostRedisplay();
    glutTimerFunc(15, Timer, 0);
}