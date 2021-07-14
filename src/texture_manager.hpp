
#pragma once
#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

// std includes //
#include <string>

// Engine includes //
#include "file_reader.hpp"
#include "texture.hpp"

using namespace std;

class Texture_Manager {
    public:
        static bool Initialize();
        static Texture* Get(File_Reader& reader);
        static Texture* Get(string textureName);
        static void Shutdown();
    private:
        vector<Texture*> textures;
};

#endif