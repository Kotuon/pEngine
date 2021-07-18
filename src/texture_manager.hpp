/**
 * @file texture_manager.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

// std includes //
#include <string>
#include <vector>

// Engine includes //
#include "file_reader.hpp"
#include "texture.hpp"

/*! Texture_Manager class */
class Texture_Manager {
    public:
        static bool Initialize();
        static Texture* Get(File_Reader& reader);
        static Texture* Get(std::string textureName);
        static void Shutdown();
    private:
        std::vector<Texture*> textures; //!< List of loaded textures
};

#endif