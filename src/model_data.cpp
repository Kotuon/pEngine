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
#include <GL/gl.h>

// Engine includes //
#include "model_data.hpp"
#include "trace.hpp"

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
    for (const Face& otherFace : other.faces) {
        faces.emplace_back(otherFace);
    }
}

/**
 * @brief Loads data of a model from given file
 * 
 * @param filename_ Name of the file containing the model data
 * @return true 
 * @return false 
 */
bool Model_Data::Load(string filename_) {
      // Setting the name of the file (used in model_data_manager)
    filename = filename_;

      // Creating variables for reading
    vector<unsigned> vertex_indices, uv_indices, normal_indices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_uvs;
    vector<vec3> temp_normals;

      // Opening the file
    string fileToOpen = "data/models/" + string(filename) + ".obj";
    FILE* file = fopen(fileToOpen.c_str(), "r");
    if (!file) {
        Trace::Message("File '" + filename + "' was not successfully opened.\n");
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
            vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.emplace_back(vertex);
            continue;
        }

        if (strcmp(line_header, "vt") == 0) {
            vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.emplace_back(uv);
            continue;
        }

        if (strcmp(line_header, "vn") == 0) {
            vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.emplace_back(normal);
            continue;
        }

        if (strcmp(line_header, "f") == 0) {
            Face face;

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
            face.vertices.emplace_back(temp_vertices[vertex_index[0] - 1]);
            face.vertices.emplace_back(temp_vertices[vertex_index[1] - 1]);
            face.vertices.emplace_back(temp_vertices[vertex_index[2] - 1]);

              // Setting uvs for current face
            face.uvs.emplace_back(temp_uvs[uv_index[0] - 1]);
            face.uvs.emplace_back(temp_uvs[uv_index[1] - 1]);
            face.uvs.emplace_back(temp_uvs[uv_index[2] - 1]);

              // Setting normals for current face
            face.normals.emplace_back(temp_normals[normal_index[0] - 1]);
            face.normals.emplace_back(temp_normals[normal_index[1] - 1]);
            face.normals.emplace_back(temp_normals[normal_index[2] - 1]);

              // Setting colors of the faces
            if (faces.size() % 6 == 0) {
                face.color[0] = 0.f;
                face.color[1] = 1.f;
                face.color[2] = 0.f;
            }
            else if (faces.size() % 6 == 1) {
                face.color[0] = 1.f;
                face.color[1] = .5f;
                face.color[2] = 0.f;
            }
            else if (faces.size() % 6 == 2) {
                face.color[0] = 1.f;
                face.color[1] = 0.f;
                face.color[2] = 0.f;
            }
            else if (faces.size() % 6 == 3) {
                face.color[0] = 1.f;
                face.color[1] = 1.f;
                face.color[2] = 0.f;
            }
            else if (faces.size() % 6 == 4) {
                face.color[0] = 0.f;
                face.color[1] = 0.f;
                face.color[2] = 1.f;
            }
            else if (faces.size() % 6 == 5) {
                face.color[0] = 1.f;
                face.color[1] = 0.f;
                face.color[2] = 1.f;
            }

            faces.emplace_back(face);
        }
    }

    return true;
}

/**
 * @brief Draws the faces
 * 
 */
void Model_Data::Draw() const {
    for (const Face& face : faces) {
          // Setting color of face
        glColor3f(face.color[0], face.color[1], face.color[2]);
          // Drawing vertices of face
        for (vec3 vert : face.vertices) {
            glVertex3f(vert.x, vert.y, vert.z);
        }
          // Setting uvs for face
        for (vec2 uv : face.uvs) {
            glTexCoord2f(uv.x, 1 - uv.y);
        }
    }
}

/**
 * @brief Returns the filename that the models data was gotten from
 * 
 * @return string Name of the file that contains model data
 */
string Model_Data::GetFilename() const {
    return filename;
}