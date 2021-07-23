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

#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP

// std includes //
#include <vector>
#include <array>
#include <string>

// Library includes //
#include <GL/gl.h>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"
#include "file_writer.hpp"
#include "model_data.hpp"
#include "texture.hpp"

/*! Model class */
class Model : public Component {
    public:
        Model(GLenum mode_ = GL_TRIANGLES);
        Model(const Model& other);
        Model(File_Reader& reader, GLenum mode_ = GL_TRIANGLES);
        Model* Clone() const;

        void Load(File_Reader& reader);
        void Draw(glm::mat4 projection, glm::mat4 view);

        void Read(File_Reader& reader);
        void Write(File_Writer& writer);
        
        void SwitchModel(std::string modelName);
        void SwitchTexture(std::string textureName);

        std::string GetModelName() const;
        std::string GetTextureName() const;

        Texture* GetTexture() const;

        static CType GetCType();
    private:
        GLenum mode;      //!< Draw mode (Default is GL_TRIANGLES)
        Model_Data* data; //!< Data about the faces of the model
        Texture* texture; //!< Texture object of model
};

#endif