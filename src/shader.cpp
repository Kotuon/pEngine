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

// Library includes //
#include <glew.h>

// Engine includes //
#include "shader.hpp"
#include "trace.hpp"

static Shader* shader = nullptr; //!< Shader object

/**
 * @brief Initializes the shader object
 * 
 * @param settings File_Reader object that contains name of shaders to use
 * @return true 
 * @return false 
 */
bool Shader::Initialize(File_Reader& settings) {
    shader = new Shader;
    if (!shader) {
        Trace::Message("Shader failed to initialize.\n");
        return false;
    }

    //LoadShader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    LoadShader("src/shaders/" + settings.Read_String("vertexShader") + ".glsl", 
        "src/shaders/" + settings.Read_String("fragShader") + ".glsl");
    return true;
}

/**
 * @brief Tells program to use shader
 * 
 * @return void
 */
void Shader::Update() {
    glUseProgram(shader->program);
}

/**
 * @brief Shutdown shader
 * 
 * @return void
 */
void Shader::Shutdown() {
    if (!shader) return;

    glDeleteProgram(shader->program);

    delete shader;
    shader = nullptr;
}

/**
 * @brief Reads shader file into std::string
 * 
 * @param filepath Shader file
 * @return std::string 
 */
std::string Shader::ReadFile(std::string filepath) {
    std::string content;

      // Opening the shader file
    std::ifstream file(filepath.c_str(), std::ios::in);
    if (!file.is_open()) {
        Trace::Message("Failed to read file: " + filepath + "\n");
        return "";
    }

      // Saving shader file into std::string
    std::string line = "";
    while (!file.eof()) {
        getline(file, line);
        content.append(line + "\n");
    }

      // Closing file and returning std::string
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
void Shader::LoadShader(std::string vertexPath, std::string fragmentPath) {
      // Creating shaders
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

      // Reading shaders
    std::string vertShaderStr = ReadFile(vertexPath);
    std::string fragShaderStr = ReadFile(fragmentPath);
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

    shader->matrixId = glGetUniformLocation(shader->program, "MVP");
    shader->viewMatrixId = glGetUniformLocation(shader->program, "V");
    shader->modelMatrixId = glGetUniformLocation(shader->program, "M");
    shader->lightId = glGetUniformLocation(shader->program, "LightPosition_worldspace");
    shader->lightPowerId = glGetUniformLocation(shader->program, "LightPower");
}

/**
 * @brief Returns the program id
 * 
 * @return GLuint 
 */
GLuint Shader::GetProgram() { return shader->program; }

/**
 * @brief Returns the mvp buffer id
 * 
 * @return GLuint 
 */
GLuint Shader::GetMatrixId() { return shader->matrixId; }

/**
 * @brief Returns the view matrix buffer id
 * 
 * @return GLuint 
 */
GLuint Shader::GetViewMatrixId() { return shader->viewMatrixId; }

/**
 * @brief Returns the model matrix buffer id
 * 
 * @return GLuint 
 */
GLuint Shader::GetModelMatrixId() { return shader->modelMatrixId; }

/**
 * @brief Returns the light pos buffer id
 * 
 * @return GLuint 
 */
GLuint Shader::GetLightId() { return shader->lightId; }

/**
 * @brief Returns the light power buffer id
 * 
 * @return GLuint 
 */
GLuint Shader::GetLightPowerId() { return shader->lightPowerId; }
