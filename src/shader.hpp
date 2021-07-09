/**
 * @file shader.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SHADER_HPP
#define SHADER_HPP

// std includes //
#include <string>

// Library includes //
#include <GL/gl.h>

using namespace std;

/*! Shader class */
class Shader {
    public:
        static bool Initialize();
        static void Update();
        static void Shutdown();

        static string ReadFile(string filename);
        static void LoadShader(string vertexPath, string fragmentPath);

        static GLuint GetProgram();
        static GLuint GetMatrixId();
    private:
        GLuint program;  //!< Program id for the engine
        GLuint matrixId; //!< MVP matrix id
};

#endif