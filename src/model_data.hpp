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

#ifndef MODEL_DATA_HPP
#define MODEL_DATA_HPP

// std includes //
#include <vector>
#include <array>
#include <string>

// Library includes //
#include <vec3.hpp>
#include <vec2.hpp>

using namespace std;
using namespace glm;

/*! Model_Data class */
class Model_Data {
    public:
        Model_Data();
        Model_Data(const Model_Data& other);

        bool Load(string filename_);
        void Draw() const;

        string GetFilename() const;
    private:
        /*! Face struct */
        struct Face {
            vector<vec3> vertices; //!< Vertices of the model
            vector<vec2> uvs;      //!< UVS of the model
            vector<vec3> normals;  //!< Normals of the model
            array<float, 3> color; //!< Colors of the model
        }; 
        vector<Face> faces; //!< Faces of the model
        string filename;    //!< Name of the file for the model
};

#endif