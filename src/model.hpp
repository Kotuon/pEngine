/**
 * @file model.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MODEL_HPP
#define MODEL_HPP

// std includes //
#include <vector>
#include <array>
#include <string>

// Library includes //
#include <GL/gl.h>
#include <vec3.hpp>
#include <vec2.hpp>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"
#include "model_data.hpp"

using namespace std;
using namespace glm;

/*! Model class */
class Model : public Component {
    public:
        Model(GLenum mode_ = GL_TRIANGLES);
        Model(const Model& other);
        Model(File_Reader& reader, GLenum mode_ = GL_TRIANGLES);
        Model* Clone() const;

        void Load(File_Reader& reader);
        void Draw(mat4 projection, mat4 view);

        void Read(File_Reader& reader);
        void SwitchModel(string modelName);

        string GetModelName() const;

        static CType GetCType();
    private:
        GLenum mode;      //!< Draw mode (Default is GL_TRIANGLES)
        Model_Data* data; //!< Data about the faces of the model
};

#endif