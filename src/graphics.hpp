
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <utility>

#include <SDL.h>
#include <SDL_opengl.h>

using namespace std;

class Graphics {
    public:
        Graphics(int width, int height);
        static bool Initialize();
        static bool InitializeGL();
        static void Update();
        static void Render();
        static void Shutdown();

        static void SwapWindow();
    private:
        pair<int, int> screenSize;
        SDL_Window* window;
        SDL_GLContext context;
};

#endif
