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

Model_Data::~Model_Data() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteTextures(1, &texture);
}

/**
 * @brief Loads data of a model from given file
 * 
 * @param filename_ Name of the file containing the model data
 * @return true 
 * @return false 
 */
bool Model_Data::Load(File_Reader& reader) {
    string modelName_ = reader.Read_String("modelToLoad");
    string textureName_ = reader.Read_String("textureToLoad");

    return Read(modelName_, textureName_);
}

bool Model_Data::Load(string modelName_, string textureName_) {
    return Read(modelName_, textureName_);
}

bool Model_Data::Read(string modelName_, string textureName_) {
      // Setting the name of the file (used in model_data_manager)
    modelName = modelName_;

      // Creating variables for reading
    vector<unsigned> vertex_indices, uv_indices, normal_indices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_uvs;
    vector<vec3> temp_normals;

      // Opening the file
    string fileToOpen = "data/models/" + modelName;
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

    textureName = textureName_;
    texture = Model_Data::LoadDDS("data/textures/" + textureName);
    textureId = glGetUniformLocation(Shader::GetProgram(), "myTextureSampler");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);

    return true;
}

/**
 * @brief Draws the faces
 * 
 */
void Model_Data::Draw(Transform* transform, mat4 projection, mat4 view) {
    mat4 model = mat4(1.f);
    model = translate(model, transform->GetPosition());
    model = scale(model, transform->GetScale());

    mat4 MVP = projection * view * model;
    glUniformMatrix4fv(Shader::GetMatrixId(), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(Shader::GetModelMatrixId(), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(Shader::GetViewMatrixId(), 1, GL_FALSE, &view[0][0]);

    vec3 lightPos = vec3(4, 4, 0);
    glUniform3f(Shader::GetLightId(), lightPos.x, lightPos.y, lightPos.z);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureId, 0);

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

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}

/**
 * @brief Returns the filename that the models data was gotten from
 * 
 * @return string Name of the file that contains model data
 */
string Model_Data::GetModelName() const {
    return modelName;
}

string Model_Data::GetTextureName() const {
    return textureName;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
GLuint Model_Data::LoadDDS(string imagepath) {
    unsigned char header[124];

    FILE *fp;

      // Opening the file
    fp = fopen(imagepath.c_str(), "rb");
    if (fp == nullptr)
        return 0;

      // Making sure it is a dds
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

      // Getting the surface description
    fread(&header, 124, 1, fp); 

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);

    unsigned char * buffer;
    unsigned int bufsize;

    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);

      // Close the file
    fclose(fp);

    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
    unsigned int format;
    switch(fourCC) { 
        case FOURCC_DXT1: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
            break; 
        case FOURCC_DXT3: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
            break; 
        case FOURCC_DXT5: 
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
            break; 
        default: 
            free(buffer); 
            return 0; 
    }

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
    
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
    unsigned int offset = 0;

    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) { 
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
            0, size, buffer + offset); 
     
        offset += size; 
        width  /= 2; 
        height /= 2; 

        if(width < 1) width = 1;
        if(height < 1) height = 1;

    } 

    free(buffer); 

    return textureID;
}