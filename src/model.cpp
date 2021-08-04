/**
 * @file model.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <cstdio>

// Engine includes //
  // Object //
#include "object.hpp"
  // Component //
#include "model.hpp"
#include "model_data_manager.hpp"
#include "transform.hpp"
  // Misc //
#include "texture.hpp"
#include "texture_manager.hpp"
#include "trace.hpp"

/**
 * @brief Creates a Model object with default values
 * 
 * @param mode_ Draw mode for opengl
 */
Model::Model(GLenum mode_) : Component(CType::CModel), mode(mode_), data(nullptr), texture(nullptr) {}

/**
 * @brief Copy constructor
 * 
 * @param other 
 */
Model::Model(const Model& other) : Component(CType::CModel) { *this = other; }

/**
 * @brief Creates a Model object using the data from a file
 * 
 * @param reader File with Model data
 * @param mode_  Draw mode for opengl
 */
Model::Model(File_Reader& reader, GLenum mode_) : Component(CType::CModel), mode(mode_), data(nullptr), texture(nullptr) {
    Read(reader);
}

/**
 * @brief Clones this Model object
 * 
 * @return Model* Cloned Model
 */
Model* Model::Clone() const { return new Model(*this); }

/**
 * @brief Load in the model data from a file (use model manager to not have
 *        multiple versions of the same model)
 * 
 * @param reader File_reader object that contains Model info 
 */
void Model::Load(File_Reader& reader) {
    data = Model_Data_Manager::Get(reader);
    texture = Texture_Manager::Get(reader);
}

/**
 * @brief Draw the model
 * 
 * @param projection Projection matrix of the scene
 * @param view View matrix of the scene
 */
void Model::Draw(glm::mat4 projection, glm::mat4 view) {
    Transform* transform = GetParent()->GetComponent<Transform>();
    if (!data) return;

    data->Draw(this, transform, projection, view);
}

/**
 * @brief Reads name of model file and passes it to the Load function
 * 
 * @param reader File that contains the name of the model's file
 */
void Model::Read(File_Reader& reader) { Load(reader); }

/**
 * @brief Gives name of model and texture to writer
 * 
 * @param writer 
 */
void Model::Write(File_Writer& writer) {
    std::string modelName = data->GetModelName();
    std::string textureName = texture->GetTextureName();

    writer.Write_String("modelToLoad", modelName.c_str());
    writer.Write_String("textureToLoad", textureName.c_str());
}

/**
 * @brief Switches the current model to that of the filename provided
 * 
 * @param modelName 
 */
void Model::SwitchModel(std::string modelName) {
    Model_Data* proxy = Model_Data_Manager::Get(modelName);
    if (!proxy) return;

    data = proxy;
}

/**
 * @brief Switches the current texture to that of the filename provided
 * 
 * @param textureName 
 */
void Model::SwitchTexture(std::string textureName) {
    Texture* proxy = Texture_Manager::Get(textureName);
    if (!proxy) return;

    texture = proxy;
}

/**
 * @brief Returns the filename of the current model
 * 
 * @return std::string 
 */
std::string Model::GetModelName() const {
    if (!data) return "no model";
    return data->GetModelName();
}

/**
 * @brief Returns the filename of the current texture
 * 
 * @return std::string 
 */
std::string Model::GetTextureName() const {
    if (!texture) return "no texture";
    return texture->GetTextureName();
}

/**
 * @brief Returns pointer to texture object
 * 
 * @return Texture* 
 */
Texture* Model::GetTexture() const { return texture; }

/**
 * @brief Gets the CType of Model (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Model::GetCType() {
    return CType::CModel;
}