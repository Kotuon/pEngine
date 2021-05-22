
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <utility>

#include <GL/gl.h>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

using namespace std;

class Graphics {
    public:
        Graphics(int width, int height);
        static bool Initialize();
        static bool InitializeGL();
        static void Update();
        static void Render();
        static void Shutdown();

        static void Reshape(GLFWwindow* window_, GLsizei width, GLsizei height);

        static bool ErrorCheck(GLenum error);
        static void ErrorCallback(int error, const char* description);
        static pair<int, int> GetScreenSize();
        static GLFWwindow* GetWindow();
    private:
        pair<int, int> screenSize;
        GLFWwindow* window;
};

#endif
