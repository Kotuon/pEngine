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
#include "trace.hpp"

/**
 * @brief Creates a Model object with default values
 * 
 * @param mode_ Draw mode for opengl
 */
Model::Model(GLenum mode_) : Component(CType::CModel), mode(mode_), data(nullptr) {}

/**
 * @brief Copy constructor
 * 
 * @param other 
 */
Model::Model(const Model& other) : Component(CType::CModel) {
    *this = other;
}

/**
 * @brief Creates a Model object using the data from a file
 * 
 * @param reader File with Model data
 * @param mode_  Draw mode for opengl
 */
Model::Model(File_Reader& reader, GLenum mode_) : Component(CType::CModel), mode(mode_), data(nullptr) {
    Read(reader);
}

/**
 * @brief Clones this Model object
 * 
 * @return Model* Cloned Model
 */
Model* Model::Clone() const {
    return new Model(*this);
}

/**
 * @brief Load in the model data from a file (use model manager to not have
 *        multiple versions of the same model)
 * 
 * @param filename 
 */
void Model::Load(string filename) {
    data = Model_Data_Manager::Get(filename);
}

/**
 * @brief Draw the model
 * 
 */
void Model::Draw() {
    Transform* transform = GetParent()->GetComponent<Transform>();

      // Setting position and scale of model using transform of the object
    vec3 pos = transform->GetPosition();
    vec3 scale = transform->GetScale();
    glTranslatef((GLfloat)pos.x, (GLfloat)pos.y, (GLfloat)pos.z);
    glScalef(scale.x, scale.y, scale.z);
    glRotatef(transform->GetRotation(), 1.f, 1.f, 1.f);

      // Drawing the model
    glBegin(mode);
    data->Draw(transform);
    glEnd();
}

/**
 * @brief Reads name of model file and passes it to the Load function
 * 
 * @param reader File that contains the name of the model's file
 */
void Model::Read(File_Reader reader) {
    Load(reader.Read_String("modelToLoad"));
}

/**
 * @brief Gets the CType of Model (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Model::GetCType() {
    return CType::CModel;
}