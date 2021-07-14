/**
 * @file model_data.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef MODEL_DATA_HPP
#define MODEL_DATA_HPP

// std includes //
#include <vector>
#include <array>
#include <string>

// Library includes //
#include <vec3.hpp>
#include <vec2.hpp>
#include <mat4x4.hpp>
#include <GL/gl.h>

// Engine includes //
#include "transform.hpp"

using namespace std;
using namespace glm;

class Model;

/*! Model_Data class */
class Model_Data {
    public:
        Model_Data();
        Model_Data(const Model_Data& other);

        ~Model_Data();

        bool Load(File_Reader& reader);
        bool Load(string modelName_);

        bool Read(string modelName_);

        void Draw(Model* parent, Transform* transform, mat4 projection, mat4 view);

        string GetModelName() const;
    private:
        vector<float> vertices; //!< Contains vertices of model
        vector<float> normals;  //!< Contains normals of model
        vector<float> uvs;      //!< Contains uv data of model
        string modelName;       //!< Name of the file for the model
        GLuint vertexbuffer;    //!< Vertex buffer of model
        GLuint normalbuffer;    //!< Normal buffer of model
        GLuint uvbuffer;        //!< UV buffer of model
};

#endif