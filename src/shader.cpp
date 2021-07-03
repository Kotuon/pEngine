/**
 * @file shader.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <fstream>
#include <vector>

// Library includes //
#include <glew.h>

// Engine includes //
#include "shader.hpp"
#include "trace.hpp"

static Shader* shader = nullptr; //!< Shader object

/**
 * @brief Initializes the shader object
 * 
 * @return true 
 * @return false 
 */
bool Shader::Initialize() {
    shader = new Shader;
    if (!shader) {
        Trace::Message("Shader failed to initialize.\n");
        return false;
    }

    LoadShader("src/shaders/transform.vert", "src/shaders/white.frag");
    return true;
}

/**
 * @brief Tells program to use shader
 * 
 * @return void
 */
void Shader::Update() {
    //LoadShader("src/shaders/transform.vert", "src/shaders/white.frag");
    glUseProgram(shader->program);
}

/**
 * @brief Shutdown shader
 * 
 * @return void
 */
void Shader::Shutdown() {
    if (!shader) return;

    delete shader;
    shader = nullptr;
}

/**
 * @brief Reads shader file into string
 * 
 * @param filepath Shader file
 * @return string 
 */
string Shader::ReadFile(string filepath) {
    string content;

      // Opening the shader file
    ifstream file(filepath.c_str(), ios::in);
    if (!file.is_open()) {
        Trace::Message("Failed to read file: " + filepath + "\n");
        return "";
    }

      // Saving shader file into string
    string line = "";
    while (!file.eof()) {
        getline(file, line);
        content.append(line + "\n");
    }

      // Closing file and returning string
    file.close();
    return content;
}

/**
 * @brief Loads the vertex and fragment shader using given filepaths
 * 
 * @param vertexPath   // Vertex shader filepath
 * @param fragmentPath // Fragment shader filepath
 * @return void
 */
void Shader::LoadShader(string vertexPath, string fragmentPath) {
      // Creating shaders
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

      // Reading shaders
    string vertShaderStr = ReadFile(vertexPath);
    string fragShaderStr = ReadFile(fragmentPath);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

      // Compiling shaders
    glShaderSource(vertShader, 1, &vertShaderSrc, nullptr);
    glCompileShader(vertShader);

    glShaderSource(fragShader, 1, &fragShaderSrc, nullptr);
    glCompileShader(fragShader);

      // Attaching shaders to engine
    shader->program = glCreateProgram();
    glAttachShader(shader->program, vertShader);
    glAttachShader(shader->program, fragShader);

      // Cleanup
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

      // Setting up program
    glLinkProgram(shader->program);
    glUseProgram(shader->program);
}

GLuint Shader::GetProgram() { return shader->program; }