
#include <string>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
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

void Graphics::Initialize(int argc, char** argv) {
    graphics = new Graphics(800, 600);

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
    glutMainLoop();
}

void Graphics::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    //glTranslatef(0.f, 0.f, -7.f);
    //glRotatef(graphics->angleCube, 1.f, 1.f, 1.f);

    for (unsigned i = 0; i < Object_Manager::GetSize(); ++i) {
        Object* object = Object_Manager::FindObject(i);

        Model* model = object->GetComponent<Model>(CType::CModel);
        model->Draw();
    }

   glutSwapBuffers();

   graphics->angleCube += .3f;
}

void Graphics::Shutdown() {
    delete graphics;
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

bool Graphics::ErrorCheck(GLenum error) {
    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }

    return true;
}