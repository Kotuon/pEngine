
#include <string>

#include <glut.h>

#include "graphics.hpp"
#include "trace.hpp"

Graphics* graphics;

Graphics::Graphics(int width, int height) {
    screenSize.first = width;
    screenSize.second = height;
}

bool Graphics::Initialize() {
    graphics = new Graphics(800, 600);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Trace::Message("Error initializing SDL: " + string(SDL_GetError()) + "\n");
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    graphics->window = SDL_CreateWindow("pEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        graphics->screenSize.first, graphics->screenSize.second, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!graphics->window) {
        Trace::Message("Window could not be created: k,ml p0" + string(SDL_GetError()) + "\n");
        return false;
    }

    graphics->context = SDL_GL_CreateContext(graphics->window);

    if (!graphics->context) {
        Trace::Message("OpenGL context could not be created: " + string(SDL_GetError()) + "\n");
        return false;
    }

    if (SDL_GL_SetSwapInterval(1) < 0) {
        Trace::Message("Unable to set VSync: " + string(SDL_GetError()) + "\0");
    }

    if (!InitializeGL()) {
        Trace::Message("Unable to intialize OpenGL.\n");
        return false;
    }

    return true;
}

bool Graphics::InitializeGL() {
    GLenum error = GL_NO_ERROR;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGL. \n");
        return false;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }

    glClearColor(0.f, 0.f, 0.f, 1.f);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        Trace::Message("Error intializing OpenGl. \n");
        return false;
    }

    return true;
}

void Graphics::Update() {

}

void Graphics::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
    glEnd();
}

void Graphics::Shutdown() {
    SDL_DestroyWindow(graphics->window);
    SDL_Quit();
    
    delete graphics;
}

void Graphics::SwapWindow() {
    SDL_GL_SwapWindow(graphics->window);
}