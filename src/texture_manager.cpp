
#include "texture_manager.hpp"
#include "trace.hpp"

static Texture_Manager* texture_manager = nullptr;

bool Texture_Manager::Initialize() {
    texture_manager = new Texture_Manager;
    if (!texture_manager) {
        Trace::Message("Texture Manager was not initialized.\n");
        return false;
    }

    texture_manager->textures.reserve(10);
    return true;
}

Texture* Texture_Manager::Get(File_Reader& reader) {
    string filename = reader.Read_String("textureToLoad");
    for (Texture* texture : texture_manager->textures) {
        if (texture->GetTextureName().compare(filename) == 0) {
            return texture;
        }
    }

    Texture* texture = new Texture;
    texture->Load(filename);
    texture_manager->textures.emplace_back(texture);

    return texture;
}

Texture* Texture_Manager::Get(string textureName) {
    for (Texture* texture : texture_manager->textures) {
        if (texture->GetTextureName().compare(textureName) == 0) {
            return texture;
        }
    }

    Texture* texture = new Texture;
    texture->Load(textureName);
    texture_manager->textures.emplace_back(texture);

    return texture;
}

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