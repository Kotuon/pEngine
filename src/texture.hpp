
#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// std includes //
#include <string>

// Library includes //
#include <GL/gl.h>

using namespace std;

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
        string textureName;
        GLuint textureNum;
        GLuint textureId;
};

#endif