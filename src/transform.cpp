/**
 * @file transform.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "transform.hpp"

/**
 * @brief Creates Transform object with default values
 * 
 */
Transform::Transform() : Component(CType::CTransform), 
    position(vec3(0.f, 0.f, 0.f)), scale(vec3(1.f, 1.f, 1.f)), rotation(0.f) {}

/**
 * @brief Copy constructor
 * 
 * @param other 
 */
Transform::Transform(const Transform& other) : Component(CType::CTransform) { 
    *this = other;
}

/**
 * @brief Creates Transform object using file
 * 
 * @param reader File to use for making Transform object
 */
Transform::Transform(File_Reader& reader) : Component(CType::CTransform), 
    position(vec3(0.f, 0.f, 0.f)), scale(vec3(1.f, 1.f, 1.f)), rotation(0.f) {
    Read(reader);
}

/**
 * @brief Clones current Transform object
 * 
 * @return Transform* Cloned Transform
 */
Transform* Transform::Clone() const {
    return new Transform(*this);
}

/**
 * @brief Sets position of object
 * 
 * @param pos 
 */
void Transform::SetPosition(vec3 pos) { position = pos; }

/**
 * @brief Returns position of object
 * 
 * @return vec3 
 */
vec3 Transform::GetPosition() const { return position; }

vec3& Transform::GetPosition() { return position; }

/**
 * @brief Sets old position of object
 * 
 * @param oldPos 
 */
void Transform::SetOldPosition(vec3 oldPos) { oldPosition = oldPos; }

/**
 * @brief Returns old position of object
 * 
 * @return vec3 
 */
vec3 Transform::GetOldPosition() const { return oldPosition; }

/**
 * @brief Sets scale of object
 * 
 * @param sca 
 */
void Transform::SetScale(vec3 sca) { scale = sca; }

/**
 * @brief Returns scale of object
 * 
 * @return vec3 
 */
vec3 Transform::GetScale() const { return scale; }

vec3& Transform::GetScale() { return scale; }

/**
 * @brief Sets rotation of object
 * 
 * @param rot 
 */
void Transform::SetRotation(vec3 rot) { rotation = rot; }

/**
 * @brief Returns rotation of object
 * 
 * @return float 
 */
vec3 Transform::GetRotation() const { return rotation; }

vec3& Transform::GetRotation() { return rotation; }

/**
 * @brief Reads data for Transform object from file
 * 
 * @param reader File to read from
 */
void Transform::Read(File_Reader& reader) {
    SetScale(reader.Read_Vec3("scale"));
    //SetRotation(reader.Read_Float("rotation"));
}

/**
 * @brief Gets the CType of Transform (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Transform::GetCType() {
    return CType::CTransform;
}