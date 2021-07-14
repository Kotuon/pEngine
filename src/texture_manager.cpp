/**
 * @file texture_manager.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "texture_manager.hpp"
#include "trace.hpp"

static Texture_Manager* texture_manager = nullptr; //!< Texture_Manager object

/**
 * @brief Initializes the texture_manager
 * 
 * @return true 
 * @return false 
 */
bool Texture_Manager::Initialize() {
      // Initializing texture_manager
    texture_manager = new Texture_Manager;
    if (!texture_manager) {
        Trace::Message("Texture Manager was not initialized.\n");
        return false;
    }

      // Reserving space in the texture_manager
    texture_manager->textures.reserve(10);
    return true;
}

/**
 * @brief Looks for texture in list of loaded textures. If found it returns a
 *        pointer. If not found it creates texture, adds it to the list of textures
 *        and returns a pointer to it.
 * 
 * @param reader File_Reader object that contains name of texture
 * @return Texture* 
 */
Texture* Texture_Manager::Get(File_Reader& reader) {
      // Getting texture's filename
    string filename = reader.Read_String("textureToLoad");
      // Looking for texture in list of loaded textures
    for (Texture* texture : texture_manager->textures) {
        if (texture->GetTextureName().compare(filename) == 0) {
            return texture;
        }
    }

      // Creating new texture
    Texture* texture = new Texture;
    texture->Load(filename);
    texture_manager->textures.emplace_back(texture);

    return texture;
}

/**
 * @brief Looks for texture in list of loaded textures. If found it returns a
 *        pointer. If not found it creates texture, adds it to the list of textures
 *        and returns a pointer to it.
 * 
 * @param textureName Name of texture
 * @return Texture* 
 */
Texture* Texture_Manager::Get(string textureName) {
      // Looking for texture in list of loaded textures
    for (Texture* texture : texture_manager->textures) {
        if (texture->GetTextureName().compare(textureName) == 0) {
            return texture;
        }
    }

      // Creating new texture
    Texture* texture = new Texture;
    texture->Load(textureName);
    texture_manager->textures.emplace_back(texture);

    return texture;
}

/**
 * @brief Deletes all texture object and then the manager
 * 
 * @return void
 */
void Texture_Manager::Shutdown() {
    if (!texture_manager) return;

    for (Texture* texture : texture_manager->textures) {
        if (!texture) continue;

        delete texture;
        texture = nullptr;
    }

    delete texture_manager;
    texture_manager = nullptr;
}