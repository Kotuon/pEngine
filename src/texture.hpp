/**
 * @file texture.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// std includes //
#include <string>

// Library includes //
#include <GL/gl.h>

using namespace std;

/*! Texture class */
class Texture {
    public:
        ~Texture();
        void Load(string textureName_);
        void Display();
        string GetTextureName() const;
        GLuint GetTextureNum() const;
    private:
        static GLuint LoadDDS(string filename);
    private:
        string textureName; //!< Name of texture
        GLuint textureNum;  //!< Loaded texture data id
        GLuint textureId;   //!< Textures buffer id
        bool hasBeenSet;    //!< Whether there is a texture or not
};

#endif