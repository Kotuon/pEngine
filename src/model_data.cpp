/**
 * @file model_data.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <cstdio>
#include <cstring>

// Library includes //
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>

// Engine includes //
#include "engine.hpp"
#include "model.hpp"
#include "model_data.hpp"
#include "trace.hpp"
#include "shader.hpp"

/**
 * @brief Default constructor
 * 
 */
Model_Data::Model_Data() {}

/**
 * @brief Copy constructor
 * 
 * @param other 
 */
Model_Data::Model_Data(const Model_Data& other) {
    for (float vert : other.vertices) {
        vertices.emplace_back(vert);
    }
    for (float norm : other.normals) {
        normals.emplace_back(norm);
    }
    for (float uv : other.uvs) {
        uvs.emplace_back(uv);
    }

    vertexbuffer = other.vertexbuffer;
    normalbuffer = other.normalbuffer;
    uvbuffer = other.uvbuffer;
}

/**
 * @brief Deletes all buffers of the model
 * 
 */
Model_Data::~Model_Data() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
}

/**
 * @brief Loads data of a model from given file
 * 
 * @param reader File_Reader object containing the model data
 * @return true 
 * @return false 
 */
bool Model_Data::Load(File_Reader& reader) {
    std::string modelName_ = reader.Read_String("modelToLoad");

    return Read(modelName_);
}

/**
 * @brief Loads in model using given filename
 * 
 * @param modelName_ Model's filename
 * @return true 
 * @return false 
 */
bool Model_Data::Load(std::string modelName_) { return Read(modelName_); }

/**
 * @brief Reads model data from file
 * 
 * @param modelName_ Model's filename
 * @return true 
 * @return false 
 */
bool Model_Data::Read(std::string modelName_) {
      // Setting the name of the file (used in model_data_manager)
    modelName = modelName_;

      // Creating variables for reading
    std::vector<unsigned> vertex_indices, uv_indices, normal_indices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

      // Opening the file
    std::string fileToOpen = "data/models/" + modelName;
    FILE* file = fopen(fileToOpen.c_str(), "r");
    if (!file) {
        Trace::Message("File '" + modelName + "' was not successfully opened.\n");
        return false;
    }

      // Until the whole file is read
    while (true) {
        char line_header[256];

          // Getting next line of the file
        int res = fscanf(file, "%s", line_header);
        if (res == EOF) break;

          // Checking for which data needs to be read in
        if (strcmp(line_header,"v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.emplace_back(vertex);
            continue;
        }

        if (strcmp(line_header, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.emplace_back(uv);
            continue;
        }

        if (strcmp(line_header, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.emplace_back(normal);
            continue;
        }

        if (strcmp(line_header, "f") == 0) {
              // Connecting face to previous read vertices, uvs, and normals
            unsigned vertex_index[3], uv_index[3], normal_index[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0],
                &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);//,
            
              // Expects models split into triangles
            if (matches != 9) {
                Trace::Message("File is incompatible with this parser. Export using different settings.");
                return false;
            }

              // Setting vertices for current face
            vertices.emplace_back((temp_vertices[vertex_index[0] - 1]).x);
            vertices.emplace_back((temp_vertices[vertex_index[0] - 1]).y);
            vertices.emplace_back((temp_vertices[vertex_index[0] - 1]).z);

            vertices.emplace_back((temp_vertices[vertex_index[1] - 1]).x);
            vertices.emplace_back((temp_vertices[vertex_index[1] - 1]).y);
            vertices.emplace_back((temp_vertices[vertex_index[1] - 1]).z);

            vertices.emplace_back((temp_vertices[vertex_index[2] - 1]).x);
            vertices.emplace_back((temp_vertices[vertex_index[2] - 1]).y);
            vertices.emplace_back((temp_vertices[vertex_index[2] - 1]).z);

              // Setting uvs for current face
            uvs.emplace_back((temp_uvs[uv_index[0] - 1]).x);
            uvs.emplace_back((temp_uvs[uv_index[0] - 1]).y);

            uvs.emplace_back((temp_uvs[uv_index[1] - 1]).x);
            uvs.emplace_back((temp_uvs[uv_index[1] - 1]).y);
            
            uvs.emplace_back((temp_uvs[uv_index[2] - 1]).x);
            uvs.emplace_back((temp_uvs[uv_index[2] - 1]).y);

              // Setting normals for current face
            normals.emplace_back((temp_normals[normal_index[0] - 1]).x);
            normals.emplace_back((temp_normals[normal_index[0] - 1]).y);
            normals.emplace_back((temp_normals[normal_index[0] - 1]).z);

            normals.emplace_back((temp_normals[normal_index[1] - 1]).x);
            normals.emplace_back((temp_normals[normal_index[1] - 1]).y);
            normals.emplace_back((temp_normals[normal_index[1] - 1]).z);

            normals.emplace_back((temp_normals[normal_index[2] - 1]).x);
            normals.emplace_back((temp_normals[normal_index[2] - 1]).y);
            normals.emplace_back((temp_normals[normal_index[2] - 1]).z);
        }
    }

      // Bind vertex data to buffers
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    
      // Bind uv data to buffers
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs[0], GL_STATIC_DRAW);

      // Bind normals data to buffers
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);

    return true;
}

/**
 * @brief Draws the models
 * 
 * @param parent Model component
 * @param transform Transform component
 * @param projection Projection matrix of the scene
 * @param view View matrix of the scene
 */
void Model_Data::Draw(Model* parent, Transform* transform, glm::mat4 projection, glm::mat4 view) {
      // Creating the MVP (Model * View * Projection) matrix
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, transform->GetPosition());
    model = glm::scale(model, transform->GetScale());

      // Sending data to the shaders
    glm::mat4 MVP = projection * view * model;
    glUniformMatrix4fv(Shader::GetMatrixId(), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(Shader::GetModelMatrixId(), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(Shader::GetViewMatrixId(), 1, GL_FALSE, &view[0][0]);

      // Sending light data to the shaders
    glm::vec3 lightPos = Engine::GetLightPos();
    glUniform3f(Shader::GetLightId(), lightPos.x, lightPos.y, lightPos.z);
    glUniform1f(Shader::GetLightPowerId(), Engine::GetLightPower());

      // Setup texture for drawing if it exists
    if (parent->GetTexture())
        parent->GetTexture()->Display();

      // Setup the model vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

      // Setup the model uv
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

      // Setup the model normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

      // Draw the object
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

      // Disable data sent to shaders
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}

/**
 * @brief Returns the filename that the models data was gotten from
 * 
 * @return string Name of the file that contains model data
 */
std::string Model_Data::GetModelName() const { return modelName; }
