/**
 * @file graphics.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

// std includes //
#include <utility>

// Library includes //
#include <GL/gl.h>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

// Engine includes //
#include "file_reader.hpp"

/*! Graphics class */
class Graphics {
    public:
        Graphics(int width, int height);
        static bool Initialize(File_Reader& settings);
        static bool Initialize();
        static bool InitializeGL();
        static void Update();
        static void Render();
        static void Shutdown();

        static bool ErrorCheck(GLenum error);
        static void ErrorCallback(int error, const char* description);
        static std::pair<int, int> GetWindowSize();
        static GLFWwindow* GetWindow();
    private:
        std::pair<int, int> windowSize; //!< Size of the window
        GLFWwindow* window;        //!< Window for application
        GLuint vertexArrayId;      //!< Id of the VAO
};

#endif
