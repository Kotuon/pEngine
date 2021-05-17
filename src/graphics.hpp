
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <utility>

#define GLUT_DISABLE_ATEXIT_HACK
#include <glut.h>

#include <SDL.h>
#include <SDL_opengl.h>

using namespace std;

class Graphics {
    public:
        Graphics(int width, int height);
        static void Initialize(int argc, char** argv);
        static bool InitializeGL();
        static void Update();
        static void Render();
        static void Shutdown();

        static void SwapWindow();
        static void Reshape(GLsizei width, GLsizei height);
        static void Timer(int time);
    private:
        pair<int, int> screenSize;
        SDL_Window* window;
        SDL_GLContext context;
        GLfloat angleCube;
};

#endif
